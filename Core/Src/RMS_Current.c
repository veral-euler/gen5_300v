/* rms_current.c */
#include "RMS_Current.h"
#include <math.h>
#include <string.h>

RMSCalculator_t motorRMS;

/* Fast inverse square root approximation (optional optimization) */
static inline float FastInvSqrt(float x) {
    // Quake III algorithm - fast approximation
    float halfx = 0.5f * x;
    int32_t i = *(int32_t*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - halfx * x * x);  // One Newton iteration
    return x;
}

/* Fast square root using inverse sqrt */
static inline float FastSqrt(float x) {
    if (x <= 0.0f) return 0.0f;
    return x * FastInvSqrt(x);
}

/* Initialize RMS calculator */
void RMS_Init(RMSCalculator_t *rms, RMSMethod_t method) {
    memset(rms, 0, sizeof(RMSCalculator_t));
    rms->method = method;
}

/* Add current samples - CALL THIS IN YOUR ADC ISR OR REGULARLY */
void RMS_AddSample(RMSCalculator_t *rms, float ia, float ib) {
    // Calculate third phase current (balanced system)
    float ic = -ia - ib;

    switch (rms->method) {
        case RMS_METHOD_RUNNING_AVG: {
            // Circular buffer method - most accurate
            uint16_t idx = rms->bufferIndex;

            // Remove old values from sum
            rms->sumIa_sq -= rms->bufferIa[idx];
            rms->sumIb_sq -= rms->bufferIb[idx];
            rms->sumIc_sq -= rms->bufferIc[idx];

            // Store new squared values
            rms->bufferIa[idx] = ia * ia;
            rms->bufferIb[idx] = ib * ib;
            rms->bufferIc[idx] = ic * ic;

            // Add new values to sum
            rms->sumIa_sq += rms->bufferIa[idx];
            rms->sumIb_sq += rms->bufferIb[idx];
            rms->sumIc_sq += rms->bufferIc[idx];

            // Increment index with wraparound
            rms->bufferIndex = (idx + 1) & (RMS_WINDOW_SIZE - 1);  // Fast modulo for power of 2

            rms->sampleCount++;
            if (rms->sampleCount >= RMS_WINDOW_SIZE) {
                rms->rmsReady = true;
            }
            break;
        }

        case RMS_METHOD_EXPONENTIAL: {
            // Exponential moving average - fastest
            float ia_sq = ia * ia;
            float ib_sq = ib * ib;
            float ic_sq = ic * ic;

            rms->sumIa_sq = RMS_ALPHA * rms->sumIa_sq + (1.0f - RMS_ALPHA) * ia_sq;
            rms->sumIb_sq = RMS_ALPHA * rms->sumIb_sq + (1.0f - RMS_ALPHA) * ib_sq;
            rms->sumIc_sq = RMS_ALPHA * rms->sumIc_sq + (1.0f - RMS_ALPHA) * ic_sq;

            rms->sampleCount++;
            if (rms->sampleCount >= 10) {  // Just needs a few samples to settle
                rms->rmsReady = true;
            }
            break;
        }

        case RMS_METHOD_SIMPLE: {
            // Simple accumulation
            rms->sumIa_sq += ia * ia;
            rms->sumIb_sq += ib * ib;
            rms->sumIc_sq += ic * ic;

            rms->sampleCount++;
            if (rms->sampleCount >= RMS_WINDOW_SIZE) {
                rms->rmsReady = true;
            }
            break;
        }
    }
}

/* Calculate RMS values - CALL THIS PERIODICALLY (e.g., every 100ms) */
void RMS_Calculate(RMSCalculator_t *rms) {
    if (!rms->rmsReady) {
        return;
    }

    switch (rms->method) {
        case RMS_METHOD_RUNNING_AVG: {
            // Average over buffer and take square root
            // Using bit shift instead of division (RMS_WINDOW_SIZE must be power of 2)
            rms->rmsIa = FastSqrt(rms->sumIa_sq / RMS_WINDOW_SIZE);
            rms->rmsIb = FastSqrt(rms->sumIb_sq / RMS_WINDOW_SIZE);
            rms->rmsIc = FastSqrt(rms->sumIc_sq / RMS_WINDOW_SIZE);
            break;
        }

        case RMS_METHOD_EXPONENTIAL: {
            // Exponential filter already has the average
            rms->rmsIa = FastSqrt(rms->sumIa_sq);
            rms->rmsIb = FastSqrt(rms->sumIb_sq);
            rms->rmsIc = FastSqrt(rms->sumIc_sq);
            break;
        }

        case RMS_METHOD_SIMPLE: {
            // Average and reset
            if (rms->sampleCount > 0) {
                rms->rmsIa = FastSqrt(rms->sumIa_sq / rms->sampleCount);
                rms->rmsIb = FastSqrt(rms->sumIb_sq / rms->sampleCount);
                rms->rmsIc = FastSqrt(rms->sumIc_sq / rms->sampleCount);

                // Reset for next window
                rms->sumIa_sq = 0;
                rms->sumIb_sq = 0;
                rms->sumIc_sq = 0;
                rms->sampleCount = 0;
                rms->rmsReady = false;
            }
            break;
        }
    }

    // Calculate total RMS (vector sum for 3-phase)
    // For balanced system: Total RMS = sqrt((Ia^2 + Ib^2 + Ic^2) / 3)
    float sumSquares = rms->rmsIa * rms->rmsIa +
                       rms->rmsIb * rms->rmsIb +
                       rms->rmsIc * rms->rmsIc;
    rms->rmsTotal = FastSqrt(sumSquares / 3.0f);
}

void UpdateMotorRMS(void) {
    static uint32_t lastCalcTime = 0;
    uint32_t currentTime = HAL_GetTick();

    // Calculate RMS every 100ms
    if (currentTime - lastCalcTime >= 100) {
        RMS_Calculate(&motorRMS);
        lastCalcTime = currentTime;

        if (RMS_IsReady(&motorRMS)) {
            d.rms_a = RMS_GetPhaseA(&motorRMS);
            d.rms_b = RMS_GetPhaseB(&motorRMS);
            d.rms_c = RMS_GetPhaseC(&motorRMS);
            d.rms_total = RMS_GetTotal(&motorRMS);
        }
    }
}

/* Getter functions */
float RMS_GetPhaseA(RMSCalculator_t *rms) { return rms->rmsIa; }
float RMS_GetPhaseB(RMSCalculator_t *rms) { return rms->rmsIb; }
float RMS_GetPhaseC(RMSCalculator_t *rms) { return rms->rmsIc; }
float RMS_GetTotal(RMSCalculator_t *rms) { return rms->rmsTotal; }
bool RMS_IsReady(RMSCalculator_t *rms) { return rms->rmsReady; }
