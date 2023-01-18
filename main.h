#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "../pico-ssd1306/ssd1306.h"
#include "../pico-ssd1306/textRenderer/TextRenderer.h"

#include "lib/display.h"
#include "lib/measurement.h"

#define I2C_CLOCK 1000 * 1000 /* 1MHz rate */
#define DISPLAY_ADDR 0x3C

#define ADC0 26
#define ADC1 27

#define LED_BUILTIN PICO_DEFAULT_LED_PIN
#define BTN_START 14
#define BTN_DISP 15
#define MOS_GATE 21

extern float vRef;
extern float vLoad;
extern float intRes;
extern float emForce;

extern char stringBuffer[];

extern bool measureDone;

extern bool displayInfo;

#endif /* _MAIN_H */