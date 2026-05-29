#ifndef __OLED096_H__
#define __OLED096_H__

/* ==================== [Includes] ========================================== */
#include <stdint.h>
#include "elab_i2c.h"
#include "OLED_Data.h"

/* ==================== [Defines] =========================================== */
#define OLED_8X16          8
#define OLED_6X8           6

#define OLED_UNFILLED      0
#define OLED_FILLED        1

/* ==================== [Typedefs] ========================================== */
typedef struct
{
    elab_i2c_t i2c;
} oled096_t;

/* ==================== [Public Functions] ================================== */
void device_oled096_init(void);

void OLED_Update(void);
void OLED_UpdateArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void OLED_Clear(void);
void OLED_ClearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void OLED_Reverse(void);
void OLED_ReverseArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

void OLED_ShowChar(uint8_t x, uint8_t y, char ch, uint8_t font_size);
void OLED_ShowString(uint8_t x, uint8_t y, const char *string, uint8_t font_size);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size);
void OLED_ShowSignedNum(uint8_t x, uint8_t y, int32_t number,
                        uint8_t length, uint8_t font_size);
void OLED_ShowHexNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size);
void OLED_ShowBinNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size);
void OLED_ShowFloatNum(uint8_t x, uint8_t y, double number,
                        uint8_t int_length, uint8_t fra_length,
                        uint8_t font_size);
void OLED_ShowChinese(uint8_t x, uint8_t y, const char *chinese);
void OLED_ShowImage(uint8_t x, uint8_t y, uint8_t width,
                    uint8_t height, const uint8_t *image);
void OLED_Printf(uint8_t x, uint8_t y, uint8_t font_size, const char *format, ...);

void OLED_DrawPoint(uint8_t x, uint8_t y);
uint8_t OLED_GetPoint(uint8_t x, uint8_t y);
void OLED_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t width,
                        uint8_t height, uint8_t is_filled);
void OLED_DrawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
                        uint8_t x2, uint8_t y2, uint8_t is_filled);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t radius, uint8_t is_filled);
void OLED_DrawEllipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, uint8_t is_filled);
void OLED_DrawArc(uint8_t x, uint8_t y, uint8_t radius,
                    int16_t start_angle, int16_t end_angle, uint8_t is_filled);

uint8_t OLED_TestConnection(void);
void OLED_TestAllOn(void);
void OLED_TestResumeRAM(void);

#endif
