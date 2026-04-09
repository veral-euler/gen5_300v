#include "NTC_Temp_Reading.h"

int16_t NTC_Read(uint16_t analog_val, float R0)
{
    float resistance = (analog_val * 10000.0f)/(65536.0f - analog_val);
    float temp_K = resistance/R0;

    temp_K = logf(temp_K);
    temp_K /= 4000.0f;
    temp_K += 1.0/(25.0f + 273.15f);
    temp_K = 1.0/temp_K;
    temp_K -= 273.15;

    return (int16_t)temp_K;
}

int16_t PTC_Read(uint16_t analog_val, float R0)
{
    float v_sense = analog_val * (3.297f / 65536.0f);
    float resistance = 10000.0f * (v_sense / (3.297f - v_sense));

    float c = resistance / R0;
    float discriminant = (CVD_A * CVD_A) - (4.0f * CVD_B * c);
    float temp = (-CVD_A + sqrtf(discriminant)) / (2.0f * CVD_B);

    return (int16_t)temp;
}
