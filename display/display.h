/* 
 * File:   screen.h
 * Author: frederic
 *
 * Created on January 3, 2023, 10:54 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef bool bit_t;

#define DISPLAY_WIDTH   128
#define DISPLAY_HEIGHT  160

// Command definitions
#define ST7735_NOP      ((uint8_t)0x00)
#define ST7735_SWRESET  ((uint8_t)0x01)
#define ST7735_RDDID    ((uint8_t)0x04)
#define ST7735_RDDST    ((uint8_t)0x09)
#define ST7735_SLPIN    ((uint8_t)0x10)
#define ST7735_SLPOUT   ((uint8_t)0x11)
#define ST7735_PTLON    ((uint8_t)0x12)
#define ST7735_NORON    ((uint8_t)0x13)
#define ST7735_INVOFF   ((uint8_t)0x20)
#define ST7735_INVON    ((uint8_t)0x21)
#define ST7735_DISPOFF  ((uint8_t)0x28)
#define ST7735_DISPON   ((uint8_t)0x29)
#define ST7735_CASET    ((uint8_t)0x2A)
#define ST7735_RASET    ((uint8_t)0x2B)
#define ST7735_RAMWR    ((uint8_t)0x2C)
#define ST7735_RAMRD    ((uint8_t)0x2E)
#define ST7735_PTLAR    ((uint8_t)0x30)
#define ST7735_VSCRDEF  ((uint8_t)0x33)
#define ST7735_COLMOD   ((uint8_t)0x3A)
#define ST7735_MADCTL   ((uint8_t)0x36)
#define ST7735_VSCRSADD ((uint8_t)0x37)
#define ST7735_FRMCTR1  ((uint8_t)0xB1)
#define ST7735_FRMCTR2  ((uint8_t)0xB2)
#define ST7735_FRMCTR3  ((uint8_t)0xB3)
#define ST7735_INVCTR   ((uint8_t)0xB4)
#define ST7735_DISSET5  ((uint8_t)0xB6)
#define ST7735_PWCTR1   ((uint8_t)0xC0)
#define ST7735_PWCTR2   ((uint8_t)0xC1)
#define ST7735_PWCTR3   ((uint8_t)0xC2)
#define ST7735_PWCTR4   ((uint8_t)0xC3)
#define ST7735_PWCTR5   ((uint8_t)0xC4)
#define ST7735_VMCTR1   ((uint8_t)0xC5)
#define ST7735_RDID1    ((uint8_t)0xDA)
#define ST7735_RDID2    ((uint8_t)0xDB)
#define ST7735_RDID3    ((uint8_t)0xDC)
#define ST7735_RDID4    ((uint8_t)0xDD)
#define ST7735_GMCTRP1  ((uint8_t)0xE0)
#define ST7735_GMCTRN1  ((uint8_t)0xE1)
#define ST7735_PWCTR6   ((uint8_t)0xFC)
     
// Color definitions
#define ST7735_BLACK    ((uint16_t)0x0000)
#define ST7735_BLUE     ((uint16_t)0x001F)
#define ST7735_RED      ((uint16_t)0xF800)
#define ST7735_GREEN    ((uint16_t)0x07E0)
#define ST7735_CYAN     ((uint16_t)0x07FF)
#define ST7735_MAGENTA  ((uint16_t)0xF81F)
#define ST77XX_ORANGE   ((uint16_t)0xFC00)
#define ST7735_YELLOW   ((uint16_t)0xFFE0)
#define ST7735_WHITE    ((uint16_t)0xFFFF)
#define ST7735_GREY     ((uint16_t)0xCCCC)

// Convert 24-bit color to 16-bit color
#define Color565(r, g, b) ((((uint16_t)(r & 0xF8)) << 8) | (((uint16_t)(g & 0xFC)) << 3) | (((uint16_t)b) >> 3))

#ifdef	__cplusplus
extern "C" {
#endif

void Display_GreenTab_Initialize(void);
void Display_RedTab_Initialize(void);
void Display_BlackTab_Initialize(void);
void Display_ST7735B_Initialize(void);

void Display_FillScreen(uint16_t color);
void Display_FillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void Display_DrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void Display_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint16_t color);
void Display_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint16_t color);

void Display_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void Display_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

void Display_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void Display_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
void Display_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void Display_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

void Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

void Display_DrawPixel(int16_t x, int16_t y, uint16_t colour);
void Display_DrawChar(int16_t x, int16_t y, char c, uint16_t colour, uint16_t bg, size_t size);
void Display_DrawText(int16_t x, int16_t y, const char *text, uint16_t color, uint16_t bg, size_t size);

void Display_SetTextWrap(bool w);

void Display_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void Display_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void Display_InvertDisplay(bool on);

void Display_SetScrollDefinition(int16_t top_fix_height, int16_t bottom_fix_height, bool scroll_direction);
void Display_VerticalScroll(bool vsp);

void Display_NormalDisplay(void);
void Display_SendColor(uint16_t color);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */
