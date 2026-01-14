/* speed_estimator.c */
#include "Speed_estimator.h"

SpeedEstimator_t motorSpeed;

/* Normalize angle to [-PI, PI] range - FAST */
static inline float NormalizeAngle(float angle) {
    // Fast modulo using fmodf
    angle = fmodf(angle, TWO_PI);
    if (angle > M_PI) {
        angle -= TWO_PI;
    } else if (angle < -M_PI) {
        angle += TWO_PI;
    }
    return angle;
}

/* Initialize speed estimator */
void Speed_Init(SpeedEstimator_t *speed) {
    memset(speed, 0, sizeof(SpeedEstimator_t));
    speed->lastMovementTime = 0;
    speed->motorMoving = false;
}

/* Fast simple differentiation for high speed */
static inline float CalculateSpeed_HighSpeed(SpeedEstimator_t *speed, float deltaAngle, uint32_t deltaTime) {
    // ω = Δθ / Δt
    // deltaTime is in microseconds, convert to seconds
    float deltaTimeSec = (float)deltaTime * US_TO_SEC;

    if (deltaTimeSec < 0.000001f) {  // Prevent division by very small number
        return speed->angularVelocity;  // Return previous value
    }

    return deltaAngle / deltaTimeSec;
}

/* Moving average for low speed (reduces noise) */
static float CalculateSpeed_LowSpeed(SpeedEstimator_t *speed, float instantSpeed) {
    // Add to circular buffer
    speed->speedBuffer[speed->bufferIndex] = instantSpeed;
    speed->bufferIndex = (speed->bufferIndex + 1) % SPEED_WINDOW_LOW;

    if (speed->bufferFilled < SPEED_WINDOW_LOW) {
        speed->bufferFilled++;
    }

    // Calculate average
    float sum = 0.0f;
    for (uint8_t i = 0; i < speed->bufferFilled; i++) {
        sum += speed->speedBuffer[i];
    }

    return sum / (float)speed->bufferFilled;
}

/* Update speed calculation - CALL THIS REGULARLY */
void Speed_Update(SpeedEstimator_t *speed, float angleRad, uint32_t timeUs) {
    // Store previous values
    speed->previousAngle = speed->currentAngle;
    speed->previousTime = speed->currentTime;

    // Update current values
    speed->currentAngle = angleRad;
    speed->currentTime = timeUs;

    // First call initialization
    if (speed->previousTime == 0) {
        speed->previousTime = timeUs;
        speed->previousAngle = angleRad;
        return;
    }

    // Calculate time difference
    uint32_t deltaTime = timeUs - speed->previousTime;

    // Skip if time difference is too small (prevents division issues)
    if (deltaTime < 10) {  // Less than 10 microseconds
        return;
    }

    // Calculate angle difference
    float deltaAngle = angleRad - speed->previousAngle;

    // Handle angle wraparound (crossing 0/2π boundary)
    deltaAngle = NormalizeAngle(deltaAngle);

    // Calculate instantaneous speed
    float instantSpeed = CalculateSpeed_HighSpeed(speed, deltaAngle, deltaTime);
    float absSpeed = fabsf(instantSpeed);

    // Convert to RPM for threshold comparison
    float instantRPM = absSpeed * RAD_TO_RPM;

    // Adaptive filtering based on speed
    if (instantRPM < LOW_SPEED_THRESHOLD_RPM) {
        // Low speed - use moving average to reduce noise
        speed->angularVelocity = CalculateSpeed_LowSpeed(speed, instantSpeed);
        speed->useLowSpeedMethod = true;
    } else {
        // High speed - use instantaneous value (faster response)
        // Optional: very light filtering
        speed->angularVelocity = 0.8f * instantSpeed + 0.2f * speed->angularVelocity;
        speed->useLowSpeedMethod = false;
    }

    // Update derived speeds
    speed->speedRPM = speed->angularVelocity * RAD_TO_RPM;
    speed->speedHz = fabsf(speed->speedRPM) * POLEPAIRS / 60.0f;  // Electrical frequency

    // Movement detection
    if (fabsf(speed->speedRPM) > 1.0f) {  // Moving if > 1 RPM
        speed->motorMoving = true;
        speed->lastMovementTime = timeUs;
    } else {
        // Check timeout (no movement for 500ms)
        if ((timeUs - speed->lastMovementTime) > 500000) {
            speed->motorMoving = false;
            speed->angularVelocity = 0.0f;
            speed->speedRPM = 0.0f;
            speed->speedHz = 0.0f;
        }
    }
}

void PositionControlLoop(void) {
    uint32_t timestamp = GetMicroseconds();            // Your timer

    // Update speed - THIS IS VERY FAST
    Speed_Update(&motorSpeed, d.mech_angle, timestamp);

    // Get results
    d.rad_s	= Speed_GetRadPerSec(&motorSpeed);
    d.RPM = Speed_GetRPM(&motorSpeed);
    d.elecfreq = Speed_GetElectricalFreq(&motorSpeed);
}

/* Getter functions */
float Speed_GetRadPerSec(SpeedEstimator_t *speed) {
    return speed->angularVelocity;
}

float Speed_GetRPM(SpeedEstimator_t *speed) {
    return speed->speedRPM;
}

float Speed_GetElectricalFreq(SpeedEstimator_t *speed) {
    return speed->speedHz;
}

bool Speed_IsMotorMoving(SpeedEstimator_t *speed) {
    return speed->motorMoving;
}
