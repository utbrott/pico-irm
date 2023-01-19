#include <math.h>
#include "measurement.h"

#define R1 66700
#define R2 21800
#define PICO_ADC_REF 3.27f /* @ ADC_REF pin */

#define R_REF 1018   /* 1k ohm reference resistor, actual 1018 ohm */
#define R_LOAD 16.85 /* 15 ohm Power Resistor, actual 16.85 ohm */
#define R_MOS 0.15   /* IRL540N MOSFET Rds @ 3.3V */

const float conversionFactor = PICO_ADC_REF / (1 << 12);

float measure::getVoltage(int adcId)
{
    /* Get measurement from ADC */
    adc_select_input(adcId);
    uint16_t adcRaw = adc_read();

    float voltage = (adcRaw * conversionFactor * (R1 + R2)) / R2;

    voltage = roundf(voltage * 1000) / 1000;

    return voltage;
}

/**
 * DC Internal Resistance using voltage drop
 * Ri = (V1 - V2) / (I1 - I2)
 *
 */
float measure::calculateIRes(float vRef, float vLoad)
{
    /* Calculate currents */
    float iRef = vRef / R_REF;
    float iLoad = vLoad / (R_LOAD + R_MOS);

    float voltage = vRef - vLoad;
    float current = iRef - iLoad;

    float internalResistance = abs(voltage / current);

    internalResistance = roundf(internalResistance * 1000) / 1000;

    return internalResistance;
}

/**
 * Electromotive force
 * E = V + I * Ri
 *
 */
float measure::calculateEmForce(float vRef, float vLoad, float intRes)
{
    /* Calculate currents */
    float iRef = vRef / R_REF;
    float iLoad = vLoad / (R_LOAD + R_MOS);

    float emForceRef = vRef + (iRef * intRes);
    float emForceLoad = vLoad + (iLoad + intRes);

    float emForce = (emForceRef + emForceLoad) / 2;

    emForce = roundf(emForce * 1000) / 1000;

    return emForce;
}