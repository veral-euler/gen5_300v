
/* rms_current.h */
#ifndef RMS_CURRENT_H
#define RMS_CURRENT_H

#include "main.h"

/* Configuration */
#define RMS_WINDOW_SIZE 1024      // Power of 2 for fast division (use bit shift)
#define RMS_ALPHA 0.95f         // Exponential filter coefficient (0-1)

/* RMS calculation methods */
typedef enum {
    RMS_METHOD_RUNNING_AVG,     // Circular buffer - most accurate
    RMS_METHOD_EXPONENTIAL,     // Exponential filter - fastest, less accurate
    RMS_METHOD_SIMPLE           // Simple averaging - good balance
} RMSMethod_t;

/* RMS Calculator Structure */
typedef struct {
    // Squared current accumulations
    float sumIa_sq;
    float sumIb_sq;
    float sumIc_sq;

    // Circular buffer (for running average method)
    float bufferIa[RMS_WINDOW_SIZE];
    float bufferIb[RMS_WINDOW_SIZE];
    float bufferIc[RMS_WINDOW_SIZE];
    uint16_t bufferIndex;

    // Sample count
    uint32_t sampleCount;

    // Calculated RMS values
    float rmsIa;
    float rmsIb;
    float rmsIc;
    float rmsTotal;

    // Method selection
    RMSMethod_t method;

    // Update flag
    bool rmsReady;
} RMSCalculator_t;

/* Function prototypes */
void RMS_Init(RMSCalculator_t *rms, RMSMethod_t method);
void RMS_AddSample(RMSCalculator_t *rms, float ia, float ib);
void RMS_Calculate(RMSCalculator_t *rms);
float RMS_GetPhaseA(RMSCalculator_t *rms);
float RMS_GetPhaseB(RMSCalculator_t *rms);
float RMS_GetPhaseC(RMSCalculator_t *rms);
float RMS_GetTotal(RMSCalculator_t *rms);
bool RMS_IsReady(RMSCalculator_t *rms);
void UpdateMotorRMS(void);

extern RMSCalculator_t motorRMS;

#endif
