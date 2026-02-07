#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H

#include "main.h"

typedef struct {
    float rate_up;          // RPM per second
    float rate_down;        // RPM per second
    float last_output;      // Last output value in RPM
    float last_time;        // Last timestamp in seconds
    bool initialized;       // Flag to check if first call
} RateLimiter;

void RateLimiter_Init(RateLimiter *limiter, 
                      float rate_up_rpm_per_sec, 
                      float rate_down_rpm_per_sec,
                      float initial_output);

float RateLimiter_Update(RateLimiter *limiter, 
                         float speed_reference, 
                         float current_time);

extern RateLimiter limiter;

#endif