/*
  ST7735 SPI TFT display CCS PIC C driver
  Updates:
      Mars 2018:   -added pushColor function
                   -draw BMP images from MMC/SD card now uses the pushColor function (faster than drawpixel)
      August 2017: -Added draw BMP images from MMC/SD card

  This driver works also with Adafruit 1.8" TFT display
  Reference: Adafruit 1.8" SPI display driver
  Adafruit invests time and resources providing this open source code, please
  support Adafruit & open-source hardware by purchasing products from Adafruit!
  https://simple-circuit.com/
  contact@simple-circuit.com
*/

#include "./display.h"
#include "./io.h"
#include "../delay.h"
#include <builtins.h>

#define _swap(a, b) { int16_t t; t = a; a = b; b = t; }
#define _dist(a, b) ((a > b) ? (a - b) : (b - a))

static bool wrap = true;
static uint8_t colstart = 0, rowstart = 0, _tft_type;

static const uint8_t font[] = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5F, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x07, 0x00,
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    0x23, 0x13, 0x08, 0x64, 0x62,
    0x36, 0x49, 0x56, 0x20, 0x50,
    0x00, 0x08, 0x07, 0x03, 0x00,
    0x00, 0x1C, 0x22, 0x41, 0x00,
    0x00, 0x41, 0x22, 0x1C, 0x00,
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
    0x08, 0x08, 0x3E, 0x08, 0x08,
    0x00, 0x80, 0x70, 0x30, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x60, 0x60, 0x00,
    0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E,
    0x00, 0x42, 0x7F, 0x40, 0x00,
    0x72, 0x49, 0x49, 0x49, 0x46,
    0x21, 0x41, 0x49, 0x4D, 0x33,
    0x18, 0x14, 0x12, 0x7F, 0x10,
    0x27, 0x45, 0x45, 0x45, 0x39,
    0x3C, 0x4A, 0x49, 0x49, 0x31,
    0x41, 0x21, 0x11, 0x09, 0x07,
    0x36, 0x49, 0x49, 0x49, 0x36,
    0x46, 0x49, 0x49, 0x29, 0x1E,
    0x00, 0x00, 0x14, 0x00, 0x00,
    0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x41, 0x22, 0x14, 0x08,
    0x02, 0x01, 0x59, 0x09, 0x06,
    0x3E, 0x41, 0x5D, 0x59, 0x4E,
    0x7C, 0x12, 0x11, 0x12, 0x7C,
    0x7F, 0x49, 0x49, 0x49, 0x36,
    0x3E, 0x41, 0x41, 0x41, 0x22,
    0x7F, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x49, 0x49, 0x49, 0x41,
    0x7F, 0x09, 0x09, 0x09, 0x01,
    0x3E, 0x41, 0x41, 0x51, 0x73,
    0x7F, 0x08, 0x08, 0x08, 0x7F,
    0x00, 0x41, 0x7F, 0x41, 0x00,
    0x20, 0x40, 0x41, 0x3F, 0x01,
    0x7F, 0x08, 0x14, 0x22, 0x41,
    0x7F, 0x40, 0x40, 0x40, 0x40,
    0x7F, 0x02, 0x1C, 0x02, 0x7F,
    0x7F, 0x04, 0x08, 0x10, 0x7F,
    0x3E, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x09, 0x09, 0x09, 0x06,
    0x3E, 0x41, 0x51, 0x21, 0x5E,
    0x7F, 0x09, 0x19, 0x29, 0x46,
    0x26, 0x49, 0x49, 0x49, 0x32,
    0x03, 0x01, 0x7F, 0x01, 0x03,
    0x3F, 0x40, 0x40, 0x40, 0x3F,
    0x1F, 0x20, 0x40, 0x20, 0x1F,
    0x3F, 0x40, 0x38, 0x40, 0x3F,
    0x63, 0x14, 0x08, 0x14, 0x63,
    0x03, 0x04, 0x78, 0x04, 0x03,
    0x61, 0x59, 0x49, 0x4D, 0x43,
    0x00, 0x7F, 0x41, 0x41, 0x41,
    0x02, 0x04, 0x08, 0x10, 0x20,
    0x00, 0x41, 0x41, 0x41, 0x7F,
    0x04, 0x02, 0x01, 0x02, 0x04,
    0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00,
    0x20, 0x54, 0x54, 0x78, 0x40,
    0x7F, 0x28, 0x44, 0x44, 0x38,
    0x38, 0x44, 0x44, 0x44, 0x28,
    0x38, 0x44, 0x44, 0x28, 0x7F,
    0x38, 0x54, 0x54, 0x54, 0x18,
    0x00, 0x08, 0x7E, 0x09, 0x02,
    0x18, 0xA4, 0xA4, 0x9C, 0x78,
    0x7F, 0x08, 0x04, 0x04, 0x78,
    0x00, 0x44, 0x7D, 0x40, 0x00,
    0x20, 0x40, 0x40, 0x3D, 0x00,
    0x7F, 0x10, 0x28, 0x44, 0x00,
    0x00, 0x41, 0x7F, 0x40, 0x00,
    0x7C, 0x04, 0x78, 0x04, 0x78,
    0x7C, 0x08, 0x04, 0x04, 0x78,
    0x38, 0x44, 0x44, 0x44, 0x38,
    0xFC, 0x18, 0x24, 0x24, 0x18,
    0x18, 0x24, 0x24, 0x18, 0xFC,
    0x7C, 0x08, 0x04, 0x04, 0x08,
    0x48, 0x54, 0x54, 0x54, 0x24,
    0x04, 0x04, 0x3F, 0x44, 0x24,
    0x3C, 0x40, 0x40, 0x20, 0x7C,
    0x1C, 0x20, 0x40, 0x20, 0x1C,
    0x3C, 0x40, 0x30, 0x40, 0x3C,
    0x44, 0x28, 0x10, 0x28, 0x44,
    0x4C, 0x90, 0x90, 0x90, 0x7C,
    0x44, 0x64, 0x54, 0x4C, 0x44,
    0x00, 0x08, 0x36, 0x41, 0x00,
    0x00, 0x00, 0x77, 0x00, 0x00,
    0x00, 0x41, 0x36, 0x08, 0x00,
    0x02, 0x01, 0x02, 0x04, 0x02
};

static void sendCommand(uint8_t cmd) {
    DisplayIO_BeginSend(false);
    DisplayIO_PushByte(cmd);
    DisplayIO_CommitSend();
}

static void sendData(uint8_t data) {
    DisplayIO_BeginSend(true);
    DisplayIO_PushByte(data);
    DisplayIO_CommitSend();
}

static void Bcmd() {
    sendCommand(ST7735_SWRESET);
    delay_ms(50);

    sendCommand(ST7735_SLPOUT);
    delay_ms(500);

    sendCommand(ST7735_COLMOD);
    sendData(0x05);
    delay_ms(10);

    sendCommand(ST7735_FRMCTR1);
    sendData(0x00);
    sendData(0x06);
    sendData(0x03);
    delay_ms(10);

    sendCommand(ST7735_MADCTL);
    sendData(0x08);

    sendCommand(ST7735_DISSET5);
    sendData(0x15);
    sendData(0x02);

    sendCommand(ST7735_INVCTR);
    sendData(0x00);

    sendCommand(ST7735_PWCTR1);
    sendData(0x02);
    sendData(0x70);
    delay_ms(10);

    sendCommand(ST7735_PWCTR2);
    sendData(0x05);

    sendCommand(ST7735_PWCTR3);
    sendData(0x01);
    sendData(0x02);

    sendCommand(ST7735_VMCTR1);
    sendData(0x3C);
    sendData(0x38);
    delay_ms(10);

    sendCommand(ST7735_PWCTR6);
    sendData(0x11);
    sendData(0x15);

    sendCommand(ST7735_GMCTRP1);
    sendData(0x09); sendData(0x16); sendData(0x09); sendData(0x20);
    sendData(0x21); sendData(0x1B); sendData(0x13); sendData(0x19);
    sendData(0x17); sendData(0x15); sendData(0x1E); sendData(0x2B);
    sendData(0x04); sendData(0x05); sendData(0x02); sendData(0x0E);

    sendCommand(ST7735_GMCTRN1);
    sendData(0x0B); sendData(0x14); sendData(0x08); sendData(0x1E);
    sendData(0x22); sendData(0x1D); sendData(0x18); sendData(0x1E);
    sendData(0x1B); sendData(0x1A); sendData(0x24); sendData(0x2B);
    sendData(0x06); sendData(0x06); sendData(0x02); sendData(0x0F);
    delay_ms(10);

    sendCommand(ST7735_CASET);
    sendData(0x00); sendData(0x02); sendData(0x08); sendData(0x81);

    sendCommand(ST7735_RASET);
    sendData(0x00); sendData(0x01); sendData(0x08); sendData(0xA0);

    sendCommand(ST7735_NORON);
    delay_ms(10);

    sendCommand(ST7735_DISPON);
    delay_ms(500);
}

static void Rcmd1() {
    sendCommand(ST7735_SWRESET);
    delay_ms(150);

    sendCommand(ST7735_SLPOUT);
    delay_ms(500);

    sendCommand(ST7735_FRMCTR1);
    sendData(0x01);
    sendData(0x2C);
    sendData(0x2D);

    sendCommand(ST7735_FRMCTR2);
    sendData(0x01);
    sendData(0x2C);
    sendData(0x2D);

    sendCommand(ST7735_FRMCTR3);
    sendData(0x01); sendData(0x2C); sendData(0x2D);
    sendData(0x01); sendData(0x2C); sendData(0x2D);

    sendCommand(ST7735_INVCTR);
    sendData(0x07);

    sendCommand(ST7735_PWCTR1);
    sendData(0xA2);
    sendData(0x02);
    sendData(0x84);

    sendCommand(ST7735_PWCTR2);
    sendData(0xC5);

    sendCommand(ST7735_PWCTR3);
    sendData(0x0A);
    sendData(0x00);

    sendCommand(ST7735_PWCTR4);
    sendData(0x8A);
    sendData(0x2A);

    sendCommand(ST7735_PWCTR5);
    sendData(0x8A);
    sendData(0xEE);

    sendCommand(ST7735_VMCTR1);
    sendData(0x0E);

    sendCommand(ST7735_INVOFF);

    sendCommand(ST7735_MADCTL);
    sendData(0xC8);

    sendCommand(ST7735_COLMOD);
    sendData(0x05); 
}

static void Rcmd2green() {
    sendCommand(ST7735_CASET);
    sendData(0x00); sendData(0x02);
    sendData(0x00); sendData(0x7F + 0x02);

    sendCommand(ST7735_RASET);
    sendData(0x00); sendData(0x01);
    sendData(0x00); sendData(0x9F + 0x01);
}

static void Rcmd2red() {
    sendCommand(ST7735_CASET);
    sendData(0x00); sendData(0x00);
    sendData(0x00); sendData(0x7F);

    sendCommand(ST7735_RASET);
    sendData(0x00); sendData(0x00);
    sendData(0x00); sendData(0x9F);
}

static void Rcmd3() {
    sendCommand(ST7735_GMCTRP1);
    sendData(0x02); sendData(0x1C); sendData(0x07); sendData(0x12);
    sendData(0x37); sendData(0x32); sendData(0x29); sendData(0x2D);
    sendData(0x29); sendData(0x25); sendData(0x2B); sendData(0x39);
    sendData(0x00); sendData(0x01); sendData(0x03); sendData(0x10);

    sendCommand(ST7735_GMCTRN1);
    sendData(0x03); sendData(0x1D); sendData(0x07); sendData(0x06);
    sendData(0x2E); sendData(0x2C); sendData(0x29); sendData(0x2D);
    sendData(0x2E); sendData(0x2E); sendData(0x37); sendData(0x3F);
    sendData(0x00); sendData(0x00); sendData(0x02); sendData(0x10);

    sendCommand(ST7735_NORON);
    delay_ms(10);

    sendCommand(ST7735_DISPON);
    delay_ms(100);
}

void Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    sendCommand(ST7735_CASET);
    sendData((uint8_t)((x0 + colstart) >> 8));
    sendData((uint8_t)(x0 + colstart));
    sendData((uint8_t)((x1 + colstart) >> 8));
    sendData((uint8_t)(x1 + colstart));

    sendCommand(ST7735_RASET);
    sendData((uint8_t)((y0 + rowstart) >> 8));
    sendData((uint8_t)(y0 + rowstart));
    sendData((uint8_t)((y1 + rowstart) >> 8));
    sendData((uint8_t)(y1 + rowstart));

    sendCommand(ST7735_RAMWR); // Write to RAM
}

void Display_DrawPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x < 0) || (y < 0) || (x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT)) 
        return;

    Display_SetAddrWindow(x, y, x + 1, y + 1);
    sendData((uint8_t)(color >> 8));
    sendData((uint8_t)color);
}

void Display_FillScreen(uint16_t color) {
    Display_FillRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, color);
}

void Display_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    uint8_t hi, lo;

    if ((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT) || (h <= 0))
        return;

    if ((y + h - 1) >= DISPLAY_HEIGHT)
        h = DISPLAY_HEIGHT - y;

    hi = (uint8_t)(color >> 8);
    lo = (uint8_t)color;

    Display_SetAddrWindow(x, y, x, y + h - 1);

    DisplayIO_BeginSend(true);

    while (h--)
        DisplayIO_PushPair(hi, lo);

    DisplayIO_CommitSend();
}

void Display_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    uint8_t hi, lo;

    if ((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT) || (w <= 0))
        return;

    if ((x + w - 1) >= DISPLAY_WIDTH)
        w = DISPLAY_WIDTH - x;

    hi = (uint8_t)(color >> 8);
    lo = (uint8_t)color;

    Display_SetAddrWindow(x, y, x + w - 1, y);

    DisplayIO_BeginSend(true);

    while (w--)
        DisplayIO_PushPair(hi, lo);

    DisplayIO_CommitSend();
}

void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t err, ystep;
    int16_t steep = _dist(y0, y1) > _dist(x0, x1);

    if (steep) {
        _swap(x0, y0);
        _swap(x1, y1);
    }

    if (x0 > x1) {
        _swap(x0, x1);
        _swap(y0, y1);
    }

    int16_t dx = x1 - x0;
    int16_t dy = _dist(y0, y1);

    err = dx / 2;
    ystep = (y0 < y1) ? 1 : -1;

    for (; x0 <= x1; x0++) {
        if (steep)
            Display_DrawPixel(y0, x0, color);
        else
            Display_DrawPixel(x0, y0, color);

        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void Display_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    if (r <= 0)
        return;

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    Display_DrawPixel(x0 + 0, y0 + r, color);
    Display_DrawPixel(x0 + 0, y0 - r, color);
    Display_DrawPixel(x0 + r, y0 + 0, color);
    Display_DrawPixel(x0 - r, y0 + 0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        Display_DrawPixel(x0 - y, y0 + x, color);
        Display_DrawPixel(x0 - x, y0 + y, color);

        Display_DrawPixel(x0 + x, y0 + y, color);
        Display_DrawPixel(x0 + y, y0 + x, color);

        Display_DrawPixel(x0 + x, y0 - y, color);
        Display_DrawPixel(x0 + y, y0 - x, color);

        Display_DrawPixel(x0 - y, y0 - x, color);
        Display_DrawPixel(x0 - x, y0 - y, color);
    }
}

void Display_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
    if (r <= 0)
        return;

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x8) {
            Display_DrawPixel(x0 - y, y0 + x, color);
            Display_DrawPixel(x0 - x, y0 + y, color);
        }

        if (cornername & 0x4) {
            Display_DrawPixel(x0 + x, y0 + y, color);
            Display_DrawPixel(x0 + y, y0 + x, color);
        }

        if (cornername & 0x2) {
            Display_DrawPixel(x0 + x, y0 - y, color);
            Display_DrawPixel(x0 + y, y0 - x, color);
        }

        if (cornername & 0x1) {
            Display_DrawPixel(x0 - y, y0 - x, color);
            Display_DrawPixel(x0 - x, y0 - y, color);
        }
    }
}

void Display_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    if (r <= 0)
        return;

    Display_DrawFastVLine(x0, y0 - r, 2 * r + 1, color);
    Display_FillCircleHelper(x0, y0, r, 3, 0, color);
}

void Display_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
    if (r <= 0)
        return;

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1) {
            Display_DrawFastVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
            Display_DrawFastVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
        }

        if (cornername & 0x2) {
            Display_DrawFastVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
            Display_DrawFastVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
        }
    }
}

void Display_FillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    uint8_t hi, lo;
    
    if ((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
        return;

    if (x < 0) {
        w += x;
        x = 0;
    }

    if (y < 0) {
        h += y;
        y = 0;
    }

    if ((x + w - 1) >= DISPLAY_WIDTH)
        w = DISPLAY_WIDTH  - x;

    if ((y + h - 1) >= DISPLAY_HEIGHT) 
        h = DISPLAY_HEIGHT - y;

    Display_SetAddrWindow(x, y, x + w - 1, y + h - 1);
    hi = (uint8_t)(color >> 8);
    lo = (uint8_t)color;

    DisplayIO_BeginSend(true);

    for (y = h; y > 0; y--)
        for (x = w; x > 0; x--)
            DisplayIO_PushPair(hi, lo);

    DisplayIO_CommitSend();
}

void Display_DrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    Display_DrawFastHLine(x, y, w, color);
    Display_DrawFastHLine(x, y + h - 1, w, color);
    Display_DrawFastVLine(x, y, h, color);
    Display_DrawFastVLine(x + w - 1, y, h, color);
}

void Display_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint16_t color) {
    Display_DrawFastHLine(x + r, y, w - 2 * r, color);
    Display_DrawFastHLine(x + r, y + h - 1, w - 2 * r, color);
    Display_DrawFastVLine(x, y + r, h - 2 * r, color);
    Display_DrawFastVLine(x + w - 1, y + r, h - 2 * r, color);
    Display_DrawCircleHelper(x + r, y + r, r, 1, color);
    Display_DrawCircleHelper(x + w - r - 1, y + r, r, 2, color);
    Display_DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
    Display_DrawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

void Display_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint16_t color) {
    Display_FillRectangle(x + r, y, w - 2 * r, h, color);
    Display_FillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
    Display_FillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

void Display_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    Display_DrawLine(x0, y0, x1, y1, color);
    Display_DrawLine(x1, y1, x2, y2, color);
    Display_DrawLine(x2, y2, x0, y0, color);
}

void Display_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    int16_t y;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        _swap(y0, y1);
        _swap(x0, x1);
    }

    if (y1 > y2) {
        _swap(y2, y1);
        _swap(x2, x1);
    }

    if (y0 > y1) {
        _swap(y0, y1);
        _swap(x0, x1);
    }

    // Handle awkward all-on-same-line case as its own thing
    if(y0 == y2) {
        int16_t a = x0;
        int16_t b = x0;

        if (x1 < a)      a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a)      a = x2;
        else if (x2 > b) b = x2;

        Display_DrawFastHLine(a, y0, b - a + 1, color);

        return;
    }

    int16_t dx01 = x1 - x0;
    int16_t dy01 = y1 - y0;
    int16_t dx02 = x2 - x0;
    int16_t dy02 = y2 - y0;
    int16_t dx12 = x2 - x1;
    int16_t dy12 = y2 - y1;

    int16_t sa = 0;
    int16_t sb = 0;

    // Include y1 scanline or skip it
    int16_t last = (y1 == y2) ? y1 : y1 - 1;

    for (y = y0; y <= last; y++) {
        int16_t a = x0 + sa / dy01;
        int16_t b = x0 + sb / dy02;

        sa += dx01;
        sb += dx02;

        /* longhand:
            a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
            b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */

        if(a > b)
            _swap(a, b);

        Display_DrawFastHLine(a, y, b - a + 1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);

    for(; y<=y2; y++) {
        int16_t a = x1 + sa / dy12;
        int16_t b = x0 + sb / dy02;

        sa += dx12;
        sb += dx02;

        /* longhand:
            a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
            b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */

        if(a > b)
            _swap(a, b);

        Display_DrawFastHLine(a, y, b - a + 1, color);
    }
}

void Display_DrawChar(int16_t x, int16_t y, char c, uint16_t color, uint16_t bg, size_t size) {
    int16_t _size = (int16_t)size;

    if ((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
        return;
    
    switch (c) {
        case '\n':
        case '\t':
        case '\b':
            return;
    }

    if (size < 1)
        size = 1;

    if ((c < ' ') || (c > '~'))
        c = '?';
    
    for (int16_t i = 0; i < 5; i++) {
        uint8_t line = font[(c - 32) * 5 + (size_t)i];

        for (int16_t j = 0; j < 7; j++, line >>= 1) {
            if (line & 0x01) {
                if(size == 1)
                    Display_DrawPixel(x + i, y + j, color);
                else
                    Display_FillRectangle(x + (i * _size), y + (j * _size), _size, _size, color);
            } else if(bg != color) {
                if (size == 1)
                    Display_DrawPixel(x + i, y + j, bg);
                else
                    Display_FillRectangle(x + (i * _size), y + (j * _size), _size, _size, bg);
            }
        }
    }
}

void Display_SetTextWrap(bool w) {
    wrap = w;
}

void Display_DrawText(int16_t x, int16_t y, const char *text, uint16_t color, uint16_t bg, size_t size) {
    int16_t _size = (int16_t)size;
    int16_t cursor_x = x, cursor_y = y;
    int16_t textsize = (int16_t)strlen(text);

    for (int16_t i = 0; i < textsize; i++) {
        bool line_feed = wrap && ((cursor_x + _size * 5) > DISPLAY_WIDTH);

        if (line_feed) {
            cursor_x = 0;
            cursor_y += _size * 7 + 3;

            if (cursor_y > DISPLAY_HEIGHT)
                cursor_y = DISPLAY_HEIGHT;
            
            if (text[i] == 0x20)
                continue;
        }

        switch (text[i]) {
            case '\n':
                if (!line_feed) {
                    cursor_x = 0;
                    cursor_y += _size * 7 + 3;

                    if (cursor_y > DISPLAY_HEIGHT)
                        cursor_y = DISPLAY_HEIGHT;
                }
                break;

            default:
                Display_DrawChar(cursor_x, cursor_y, text[i], color, bg, _size);
                cursor_x += _size * 6;

                if (cursor_x > DISPLAY_WIDTH)
                    cursor_x = DISPLAY_WIDTH;
        }
    }
}

void Display_InvertDisplay(bool on) {
    if (on)
        sendCommand(ST7735_INVON);
    else
        sendCommand(ST7735_INVOFF);
}

void Display_SetScrollDefinition(int16_t top_fix_height, int16_t bottom_fix_height, bool scroll_direction) {
    int16_t scroll_height = DISPLAY_HEIGHT - top_fix_height - bottom_fix_height;

    sendCommand(ST7735_VSCRDEF);
    sendData((uint8_t)(top_fix_height >> 8));
    sendData((uint8_t)top_fix_height);
    sendData((uint8_t)(scroll_height >> 8));
    sendData((uint8_t)scroll_height);
    sendData((uint8_t)(bottom_fix_height >> 8));
    sendData((uint8_t)bottom_fix_height);
    delay_us(1);

    sendCommand(ST7735_MADCTL);

    if (scroll_direction) {
        switch (_tft_type) {
            case 0:
                sendData(0xD8);
                break;

            case 1:
                sendData(0xD0);
                break;

            case 2:
                sendData(0x18);
                break;
        }
    } else {
        switch (_tft_type) {
            case 0:
                sendData(0xC8);
                break;

            case 1:
                sendData(0xC0);
                break;

            case 2:
                sendData(0x08);
                break;
        }
    }
}

void Display_SendColor(uint16_t color) {
    uint8_t hi = (uint8_t)(color >> 8);
    uint8_t lo = (uint8_t)color;

    DisplayIO_BeginSend(true);

    DisplayIO_PushPair(hi, lo);
    delay_us(1);

    DisplayIO_CommitSend();
}

void Display_VerticalScroll(bool vsp) {
    sendCommand(ST7735_VSCRSADD);
    sendData(0x00);
    sendData((vsp) ? 1 : 0);
}

void Display_NormalDisplay(void) {
    sendCommand(ST7735_NORON);
}

void Display_GreenTab_Initialize(void) {
    DisplayIO_Reset();

    Rcmd1();
    Rcmd2green();
    Rcmd3();

    colstart = 2;
    rowstart = 1;
    _tft_type = 0;
}

void Display_RedTab_Initialize(void) {
    DisplayIO_Reset();

    Rcmd1();
    Rcmd2red();
    Rcmd3();

    _tft_type = 0;
}

void Display_BlackTab_Initialize(void) {
    DisplayIO_Reset();

    Rcmd1();
    Rcmd2red();
    Rcmd3();

    sendCommand(ST7735_MADCTL);
    sendData(0xC0);

    _tft_type = 1;
}

void Display_ST7735B_Initialize(void) {
    DisplayIO_Reset();

    Bcmd();

    _tft_type = 2;
}
