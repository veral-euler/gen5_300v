#include "Rate_Limiter.h"

RateLimiter limiter;
RateLimiter torqueRate;

/**
 * Initialize the rate limiter
 * 
 * @param limiter: Pointer to RateLimiter struct
 * @param rate_up_rpm_per_sec: Maximum allowed increase in RPM per second
 * @param rate_down_rpm_per_sec: Maximum allowed decrease in RPM per second (positive value)
 * @param initial_output: Initial output value in RPM
 */
void RateLimiter_Init(RateLimiter *limiter, 
                      float rate_up_rpm_per_sec, 
                      float rate_down_rpm_per_sec,
                      float initial_output) {
    limiter->rate_up = rate_up_rpm_per_sec;
    limiter->rate_down = rate_down_rpm_per_sec;
    limiter->last_output = initial_output;
    limiter->last_time = 0.0f;
    limiter->initialized = false;
}

/**
 * Update the rate limiter with new speed reference
 * 
 * @param limiter: Pointer to RateLimiter struct
 * @param speed_reference: Desired speed in RPM (always positive)
 * @param current_time: Current timestamp in seconds
 * @return: Rate-limited output in RPM
 */
float RateLimiter_Update(RateLimiter *limiter, 
                         float speed_reference, 
                         float current_time) {
    float dt, delta, max_change, limited_output;
    
    // First call - initialize with reference
    if (!limiter->initialized) {
        limiter->last_time = current_time;
        limiter->last_output = speed_reference;
        limiter->initialized = true;
        return limiter->last_output;
    }
    
    // Calculate time step
    dt = current_time - limiter->last_time;
    
    // Invalid time step
    if (dt <= 0.0f) {
        return limiter->last_output;
    }
    
    // Calculate the change in reference
    delta = speed_reference - limiter->last_output;
    
    // Calculate maximum allowed change based on direction
    if (delta > 0.0f) {
        max_change = limiter->rate_up * dt;
    } else {
        max_change = -limiter->rate_down * dt;
    }
    
    // Apply rate limiting
    if (delta > 0.0f && delta > max_change) {
        limited_output = limiter->last_output + max_change;
    } else if (delta < 0.0f && delta < max_change) {
        limited_output = limiter->last_output + max_change;
    } else {
        limited_output = speed_reference;
    }
    
    // Update state
    limiter->last_output = limited_output;
    limiter->last_time = current_time;
    
    return limited_output;
}