/* speed_estimator.h */
#ifndef SPEED_ESTIMATOR_H
#define SPEED_ESTIMATOR_H

#include "main.h"

#define MIN_RPM 0
#define MAX_RPM 6500

/* Speed calculation configuration */
#define LOW_SPEED_THRESHOLD_RPM 100      // Below this, use different method
#define VERY_LOW_SPEED_THRESHOLD_RPM 10  // Below this, use encoder pulses
#define SPEED_WINDOW_LOW 8               // Averaging window for low speed
#define SPEED_WINDOW_HIGH 4              // Averaging window for high speed

/* Constants for fast calculation */
#define RAD_TO_RPM 9.54929658551f        // 60 / (2*PI)
#define RPM_TO_RAD 0.10471975512f        // (2*PI) / 60
#define US_TO_SEC 0.000001f              // 1 / 1000000

/* Speed estimator structure */
typedef struct {
    // Angle tracking
    float currentAngle;      // Current mechanical angle (radians)
    float previousAngle;     // Previous mechanical angle (radians)

    // Time tracking
    uint32_t currentTime;    // Current timestamp (microseconds)
    uint32_t previousTime;   // Previous timestamp (microseconds)

    // Speed calculation
    float angularVelocity;   // Mechanical speed (rad/s)
    float speedRPM;          // Speed in RPM
    float speedHz;           // Electrical frequency (Hz)

    // Filtering for low speeds
    float speedBuffer[SPEED_WINDOW_LOW];
    uint8_t bufferIndex;
    uint8_t bufferFilled;

    // Last valid speed (for timeout detection)
    uint32_t lastMovementTime;
    bool motorMoving;

    // Method tracking
    bool useLowSpeedMethod;
} SpeedEstimator_t;

/* Function prototypes */
void Speed_Init(SpeedEstimator_t *speed);
void Speed_Update(SpeedEstimator_t *speed, float angleRad, uint32_t timeUs);
float Speed_GetRadPerSec(SpeedEstimator_t *speed);
float Speed_GetRPM(SpeedEstimator_t *speed);
float Speed_GetElectricalFreq(SpeedEstimator_t *speed);
bool Speed_IsMotorMoving(SpeedEstimator_t *speed);
void PositionControlLoop(void);

extern SpeedEstimator_t motorSpeed;

#endif
