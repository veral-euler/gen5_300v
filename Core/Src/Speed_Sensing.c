#include "Speed_Sensing.h"
#include "main.h"

void Speed_Filter(float Speed)
{
	static float prev_speed = 0.0f;
	static float prev_filtered_speed = 0.0f;

    d.rad_s = ((SPEED_FILTER_CONSTANT_1 * prev_filtered_speed) + (SPEED_FILTER_CONSTANT_2 *(Speed+prev_speed)));
    //d.RPM = d.rad_s / 0.1047f;

    prev_speed = Speed;
    prev_filtered_speed = d.rad_s;
}

void Speed_Sense(float MechAngle)
{
    static float prev_angle = 0.0f;
    float angle_delta;
    
    // Direct angle derivative (no sin/cos approximation)
    angle_delta = MechAngle - prev_angle;
    
    // Handle angle wrap-around for 0-2π or -π to π ranges
    if (angle_delta > 3.14159f) {
        angle_delta -= 6.28318f;
    } else if (angle_delta < -3.14159f) {
        angle_delta += 6.28318f;
    }
    
    // Raw speed = angle_delta / time_sample
    d.raw_rad_s = angle_delta * DERIVATIVE_CONSTANT;  // 1000 Hz sampling
    
    if (d.raw_rad_s >= 942.477f) {
        d.raw_rad_s = 942.477f;
    } else if (d.raw_rad_s <= -942.477f) {
        d.raw_rad_s = -942.477f;
    }
    
    Speed_Filter(d.raw_rad_s);
    
    prev_angle = MechAngle;
}
