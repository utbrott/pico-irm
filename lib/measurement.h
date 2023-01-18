#ifndef _MEASUREMENT_H
#define _MEASUREMENT_H

#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

extern const float conversion_factor;

namespace measure
{
    float getVoltage(int adcId);
    float getRoundedValue(float value);
    float calculateIRes(float vRef, float vLoad);
    float calculateEmForce(float v1, float v2, float intRes);
}

#endif /* _MEASUREMENT_H*/