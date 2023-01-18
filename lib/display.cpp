#include "display.h"

void display::clear(pico_ssd1306::SSD1306 *display)
{
  display->clear();
  display->sendBuffer();
}

void display::drawText(pico_ssd1306::SSD1306 *display, const char *text, uint8_t col, uint8_t row)
{
  col = col * 8;
  row = row * 8;

  drawText(display, font_8x8, text, col, row, pico_ssd1306::WriteMode::ADD);

  display->sendBuffer();
}