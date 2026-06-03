#ifndef __SSD1306_H__
#define __SSD1306_H__

/* ==================== [Includes] ========================================== */
#include <stdint.h>
#include "elab_i2c.h"
#include "OLED_Data.h"

/* ==================== [Defines] =========================================== */
#define SSD1306_8X16          8
#define SSD1306_6X8           6

#define SSD1306_UNFILLED      0
#define SSD1306_FILLED        1

/* ==================== [Typedefs] ========================================== */
typedef struct
{
    elab_i2c_t i2c;
} ssd1306_t;

/* ==================== [Public Functions] ================================== */
void device_ssd1306_init(void);

void SSD1306_Update(void);
void SSD1306_UpdateArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void SSD1306_Clear(void);
void SSD1306_ClearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void SSD1306_Reverse(void);
void SSD1306_ReverseArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

void SSD1306_ShowChar(uint8_t x, uint8_t y, char ch, uint8_t font_size);
void SSD1306_ShowString(uint8_t x, uint8_t y, const char *string, uint8_t font_size);
void SSD1306_ShowNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size);
void SSD1306_ShowSignedNum(uint8_t x, uint8_t y, int32_t number,
                        uint8_t length, uint8_t font_size);
void SSD1306_ShowHexNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size);
void SSD1306_ShowBinNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size);
void SSD1306_ShowFloatNum(uint8_t x, uint8_t y, double number,
                        uint8_t int_length, uint8_t fra_length,
                        uint8_t font_size);
void SSD1306_ShowChinese(uint8_t x, uint8_t y, const char *chinese);
void SSD1306_ShowImage(uint8_t x, uint8_t y, uint8_t width,
                    uint8_t height, const uint8_t *image);
void SSD1306_Printf(uint8_t x, uint8_t y, uint8_t font_size, const char *format, ...);

void SSD1306_DrawPoint(uint8_t x, uint8_t y);
uint8_t SSD1306_GetPoint(uint8_t x, uint8_t y);
void SSD1306_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void SSD1306_DrawRectangle(uint8_t x, uint8_t y, uint8_t width,
                        uint8_t height, uint8_t is_filled);
void SSD1306_DrawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
                        uint8_t x2, uint8_t y2, uint8_t is_filled);
void SSD1306_DrawCircle(uint8_t x, uint8_t y, uint8_t radius, uint8_t is_filled);
void SSD1306_DrawEllipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, uint8_t is_filled);
void SSD1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius,
                    int16_t start_angle, int16_t end_angle, uint8_t is_filled);

uint8_t SSD1306_TestConnection(void);
void SSD1306_TestAllOn(void);
void SSD1306_TestResumeRAM(void);

#endif
