#include "display.h"

void Display::drawCross(pico_ssd1306::SSD1306 *display)
{
  for (int y = 0; y < 32; y++)
  {
    display->setPixel(32, y);
  }

  for (int x = 0; x < 128; x++)
  {
    display->setPixel(x, 8);
  }
}