#include "main.h"

float vRef = 0.000;
float vLoad = 0.000;
float intRes = 0.000;
float emForce = 0.000;

char stringBuffer[25];

bool measureDone = false;
bool displayInfo = false;

int main()
{
    stdio_init_all();

    /* I2C, Display Init */
    i2c_init(i2c0, I2C_CLOCK);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    pico_ssd1306::SSD1306 oled = pico_ssd1306::SSD1306(i2c0, DISPLAY_ADDR, pico_ssd1306::Size::W128xH32);

    /* ADC Init */
    adc_init();
    // adc_gpio_init(ADC0); /* ADC0 doest work? */
    adc_gpio_init(ADC1);

    /* GPIO Init */
    gpio_init(LED_BUILTIN);
    gpio_init(MOS_GATE);
    gpio_init(BTN_START);
    gpio_init(BTN_DISP);

    gpio_set_dir(LED_BUILTIN, GPIO_OUT);
    gpio_set_dir(MOS_GATE, GPIO_OUT);
    gpio_set_dir(BTN_START, GPIO_IN);
    gpio_set_dir(BTN_DISP, GPIO_IN);

    /* Prepare */
    display::clear(&oled);
    display::drawText(&oled, "Ready", 0, 0);
    gpio_put(LED_BUILTIN, 1);
    gpio_put(MOS_GATE, 0);

    while (true)
    {
        if (!gpio_get(BTN_START))
        {
            display::clear(&oled);
            measureDone = false;

            vRef = measure::getVoltage(1);

            gpio_put(MOS_GATE, 1);
            sleep_ms(100);
            vLoad = measure::getVoltage(1);
            gpio_put(MOS_GATE, 0);

            intRes = measure::calculateIRes(vRef, vLoad);
            emForce = measure::calculateEmForce(vRef, vLoad, intRes);

            measureDone = true;
        }

        if (!gpio_get(BTN_DISP))
        {
            displayInfo = !displayInfo;
            display::clear(&oled);
            sleep_ms(100); /* Debounce */
        }

        if (measureDone)
        {
            sprintf(stringBuffer, "V1: %.3f V", vRef);
            display::drawText(&oled, stringBuffer, 0, 0);

            sprintf(stringBuffer, "V2: %.3f V", vLoad);
            display::drawText(&oled, stringBuffer, 0, 1);

            switch (displayInfo)
            {
            case true:
                sprintf(stringBuffer, "E:  %.3f V", emForce);
                display::drawText(&oled, stringBuffer, 0, 3);
                break;

            case false:
                sprintf(stringBuffer, "Ri: %.3f Ohm", intRes);
                display::drawText(&oled, stringBuffer, 0, 3);
                break;
            }
        }
    }
}
