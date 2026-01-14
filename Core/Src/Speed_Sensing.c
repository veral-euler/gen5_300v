#include "Speed_Sensing.h"
#include "main.h"

void Speed_Filter(float Speed)
{
	static float prev_speed = 0.0f;
	static float prev_filtered_speed = 0.0f;

    d.rad_s = ((SPEED_FILTER_CONSTANT_1 * prev_filtered_speed) + (SPEED_FILTER_CONSTANT_2 *(Speed+prev_speed)));
    d.RPM = d.rad_s / 0.1047f;

    prev_speed = Speed;
    prev_filtered_speed = d.rad_s;
}

void Speed_Sense(float MechAngle)
{
    static float sine_rotor ,sine_rotor_prev;
    static float derivative_sine_rotor;
    static float cosine_rotor,cosine_rotor_prev;
    static float derivative_cosine_rotor;

    sine_rotor = sinf(MechAngle);
    derivative_sine_rotor = DERIVATIVE_CONSTANT*(sine_rotor-sine_rotor_prev);

    cosine_rotor = cosf(MechAngle);
    derivative_cosine_rotor = DERIVATIVE_CONSTANT*(cosine_rotor-cosine_rotor_prev);

    sine_rotor_prev = sine_rotor;
    cosine_rotor_prev = cosine_rotor;

    d.raw_rad_s = ((cosine_rotor*derivative_sine_rotor)-(sine_rotor*derivative_cosine_rotor));

    if (d.raw_rad_s >= 628.318f) {
        d.raw_rad_s = 628.318f;
    } else if (d.raw_rad_s <= -628.318f) {
        d.raw_rad_s = -628.318f;
    }

    Speed_Filter(d.raw_rad_s);
}
