#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "hardware/i2c.h"
#include "../pico-ssd1306/ssd1306.h"
#include "../pico-ssd1306/textRenderer/TextRenderer.h"

namespace Display
{
    void drawCross(pico_ssd1306::SSD1306 *display);
}

#endif /* _DISPLAY_H */
