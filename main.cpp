#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../pico-ssd1306/ssd1306.h"
#include "../pico-ssd1306/textRenderer/TextRenderer.h"

#include "lib/display.h"

#define I2C_CLOCK 1000 * 1000 /* 1MHz rate */
#define DISPLAY_ADDR 0x3C

int main()
{
    const uint LED_BUILTIN = PICO_DEFAULT_LED_PIN;

    i2c_init(i2c0, I2C_CLOCK);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    gpio_init(LED_BUILTIN);
    gpio_set_dir(LED_BUILTIN, GPIO_OUT);

    pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(i2c0, DISPLAY_ADDR, pico_ssd1306::Size::W128xH32);

    Display::drawCross(&display);

    display.sendBuffer();

    while (true)
    {
        gpio_put(LED_BUILTIN, 1);
        sleep_ms(250);
        gpio_put(LED_BUILTIN, 0);
        sleep_ms(750);
    }
}
