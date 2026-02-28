#include "NTC_Temp_Reading.h"

int16_t NTC_Read(uint16_t analog_val, float R0)
{
    float resistance = (analog_val * 10000.0f)/(65536.0f - analog_val);
    float temp_K = resistance/R0;

    temp_K = log(temp_K);
    temp_K /= 4000.0f;
    temp_K += 1.0/(25.0f + 273.15f);
    temp_K = 1.0/temp_K;
    temp_K -= 273.15;

    return (int16_t)temp_K;
}
