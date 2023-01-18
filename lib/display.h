#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "hardware/i2c.h"
#include "../pico-ssd1306/ssd1306.h"
#include "../pico-ssd1306/textRenderer/TextRenderer.h"

namespace display
{
    void clear(pico_ssd1306::SSD1306 *display);
    void drawText(pico_ssd1306::SSD1306 *display, const char *text, uint8_t col, uint8_t row);
}

#endif /* _DISPLAY_H */
