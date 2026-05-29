/**
 * @file oled096.c
 * @author ZC (387646983@qq.com)
 * @brief SSD1306 0.96 inch OLED device.
 * @version 0.1
 * @date 2026-05-29
 */

/* ==================== [Includes] ========================================== */
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "oled096.h"
#include "elab_assert.h"
#include "elab_export.h"
#include "elab_i2c.h"
#include "elab_log.h"

/* ==================== [Defines] =========================================== */
ELAB_TAG("OLED096");

#define OLED_I2C_DEVICE_NAME        "oled"
#define OLED_I2C_TIMEOUT_MS         100
#define OLED_CMD_CONTROL_BYTE       0x00
#define OLED_DATA_CONTROL_BYTE      0x40
#define OLED_WIDTH                  128
#define OLED_HEIGHT                 64
#define OLED_PAGE_COUNT             8
#define OLED_PRINTF_BUF_SIZE        30
#define OLED_PI                     3.1415926f
#define OLED_DISPLAY_DEVICE_NAME    "display0"

/* ==================== [Static Prototypes] ================================= */
static elab_err_t OLED_WriteCommand(uint8_t command);
static elab_err_t OLED_WriteData(const uint8_t *data, uint16_t size);
static void OLED_SetCursor(uint8_t page, uint8_t column);
static uint32_t OLED_Pow(uint32_t x, uint32_t y);
static uint8_t OLED_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty,
                            int16_t testx, int16_t testy);
static uint8_t OLED_IsInAngle(int16_t x, int16_t y,
                                int16_t start_angle, int16_t end_angle);


/* ==================== [Static Variables] ================================== */
static uint8_t OLED_DisplayBuf[OLED_PAGE_COUNT][OLED_WIDTH];
static elab_device_t *oled_device = NULL;


/* ==================== [Static Functions] ================================== */
static elab_err_t OLED_WriteCommand(uint8_t command)
{
    return elab_i2c_write_memory(oled_device,
                                    OLED_CMD_CONTROL_BYTE,
                                    &command,
                                    1,
                                    OLED_I2C_TIMEOUT_MS);
}

static elab_err_t OLED_WriteData(const uint8_t *data, uint16_t size)
{
    return elab_i2c_write_memory(oled_device,
                                    OLED_DATA_CONTROL_BYTE,
                                    (uint8_t *)data,
                                    size,
                                    OLED_I2C_TIMEOUT_MS);
}

static void OLED_SetCursor(uint8_t page, uint8_t column)
{
    OLED_WriteCommand((uint8_t)(0xB0 | page));
    OLED_WriteCommand((uint8_t)(0x10 | ((column & 0xF0) >> 4)));
    OLED_WriteCommand((uint8_t)(0x00 | (column & 0x0F)));
}

static uint32_t OLED_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;

    while (y--)
    {
        result *= x;
    }

    return result;
}

static uint8_t OLED_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty,
                            int16_t testx, int16_t testy)
{
    int16_t i;
    int16_t j;
    uint8_t c = 0;

    for (i = 0, j = nvert - 1; i < nvert; j = i++)
    {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) /
            (verty[j] - verty[i]) + vertx[i]))
        {
            c = !c;
        }
    }

    return c;
}

static uint8_t OLED_IsInAngle(int16_t x, int16_t y,
                                int16_t start_angle, int16_t end_angle)
{
    int16_t point_angle = (int16_t)(atan2((double)y, (double)x) / OLED_PI * 180.0);

    if (start_angle < end_angle)
    {
        if (point_angle >= start_angle && point_angle <= end_angle)
        {
            return 1;
        }
    }
    else
    {
        if (point_angle >= start_angle || point_angle <= end_angle)
        {
            return 1;
        }
    }

    return 0;
}


/* ==================== [Public Functions] ================================== */
void OLED_Update(void)
{
    uint8_t page;

    for (page = 0; page < OLED_PAGE_COUNT; page++)
    {
        OLED_SetCursor(page, 0);
        OLED_WriteData(OLED_DisplayBuf[page], OLED_WIDTH);
    }
}

void OLED_UpdateArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    uint8_t page;

    if (x > 127 || y > 63 || width == 0 || height == 0)
    {
        return;
    }
    if (x + width > OLED_WIDTH)
    {
        width = OLED_WIDTH - x;
    }
    if (y + height > OLED_HEIGHT)
    {
        height = OLED_HEIGHT - y;
    }

    for (page = y / 8; page < (y + height - 1) / 8 + 1; page++)
    {
        OLED_SetCursor(page, x);
        OLED_WriteData(&OLED_DisplayBuf[page][x], width);
    }
}

void OLED_Clear(void)
{
    memset(OLED_DisplayBuf, 0x00, sizeof(OLED_DisplayBuf));
}

void OLED_ClearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    uint8_t i;
    uint8_t j;

    if (x > 127 || y > 63 || width == 0 || height == 0)
    {
        return;
    }
    if (x + width > OLED_WIDTH)
    {
        width = OLED_WIDTH - x;
    }
    if (y + height > OLED_HEIGHT)
    {
        height = OLED_HEIGHT - y;
    }

    for (j = y; j < y + height; j++)
    {
        for (i = x; i < x + width; i++)
        {
            OLED_DisplayBuf[j / 8][i] &= (uint8_t)~(0x01 << (j % 8));
        }
    }
}

void OLED_Reverse(void)
{
    uint8_t i;
    uint8_t page;

    for (page = 0; page < OLED_PAGE_COUNT; page++)
    {
        for (i = 0; i < OLED_WIDTH; i++)
        {
            OLED_DisplayBuf[page][i] ^= 0xFF;
        }
    }
}

void OLED_ReverseArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    uint8_t i;
    uint8_t j;

    if (x > 127 || y > 63 || width == 0 || height == 0)
    {
        return;
    }
    if (x + width > OLED_WIDTH)
    {
        width = OLED_WIDTH - x;
    }
    if (y + height > OLED_HEIGHT)
    {
        height = OLED_HEIGHT - y;
    }

    for (j = y; j < y + height; j++)
    {
        for (i = x; i < x + width; i++)
        {
            OLED_DisplayBuf[j / 8][i] ^= (uint8_t)(0x01 << (j % 8));
        }
    }
}

void OLED_ShowChar(uint8_t x, uint8_t y, char ch, uint8_t font_size)
{
    if (ch < ' ' || ch > '~')
    {
        ch = '?';
    }

    if (font_size == OLED_8X16)
    {
        OLED_ShowImage(x, y, 8, 16, OLED_F8x16[ch - ' ']);
    }
    else if (font_size == OLED_6X8)
    {
        OLED_ShowImage(x, y, 6, 8, OLED_F6x8[ch - ' ']);
    }
}

void OLED_ShowString(uint8_t x, uint8_t y, const char *string, uint8_t font_size)
{
    uint8_t i;

    for (i = 0; string[i] != '\0'; i++)
    {
        OLED_ShowChar((uint8_t)(x + i * font_size), y, string[i], font_size);
    }
}

void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size)
{
    uint8_t i;

    for (i = 0; i < length; i++)
    {
        OLED_ShowChar((uint8_t)(x + i * font_size),
                        y,
                        (char)(number / OLED_Pow(10, length - i - 1) % 10 + '0'),
                        font_size);
    }
}

void OLED_ShowSignedNum(uint8_t x, uint8_t y, int32_t number,
                        uint8_t length, uint8_t font_size)
{
    uint8_t i;
    uint32_t number_abs;

    if (number >= 0)
    {
        OLED_ShowChar(x, y, '+', font_size);
        number_abs = (uint32_t)number;
    }
    else
    {
        OLED_ShowChar(x, y, '-', font_size);
        number_abs = (uint32_t)(-number);
    }

    for (i = 0; i < length; i++)
    {
        OLED_ShowChar((uint8_t)(x + (i + 1) * font_size),
                        y,
                        (char)(number_abs / OLED_Pow(10, length - i - 1) % 10 + '0'),
                        font_size);
    }
}

void OLED_ShowHexNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size)
{
    uint8_t i;
    uint8_t single_number;

    for (i = 0; i < length; i++)
    {
        single_number = (uint8_t)(number / OLED_Pow(16, length - i - 1) % 16);
        if (single_number < 10)
        {
            OLED_ShowChar((uint8_t)(x + i * font_size),
                            y,
                            (char)(single_number + '0'),
                            font_size);
        }
        else
        {
            OLED_ShowChar((uint8_t)(x + i * font_size),
                            y,
                            (char)(single_number - 10 + 'A'),
                            font_size);
        }
    }
}

void OLED_ShowBinNum(uint8_t x, uint8_t y, uint32_t number,
                    uint8_t length, uint8_t font_size)
{
    uint8_t i;

    for (i = 0; i < length; i++)
    {
        OLED_ShowChar((uint8_t)(x + i * font_size),
                        y,
                        (char)(number / OLED_Pow(2, length - i - 1) % 2 + '0'),
                        font_size);
    }
}

void OLED_ShowFloatNum(uint8_t x, uint8_t y, double number,
                        uint8_t int_length, uint8_t fra_length,
                        uint8_t font_size)
{
    uint32_t pow_num;
    uint32_t int_num;
    uint32_t fra_num;

    if (number >= 0)
    {
        OLED_ShowChar(x, y, '+', font_size);
    }
    else
    {
        OLED_ShowChar(x, y, '-', font_size);
        number = -number;
    }

    int_num = (uint32_t)number;
    number -= int_num;
    pow_num = OLED_Pow(10, fra_length);
    fra_num = (uint32_t)(number * pow_num + 0.5);
    int_num += fra_num / pow_num;
    fra_num %= pow_num;

    OLED_ShowNum((uint8_t)(x + font_size), y, int_num, int_length, font_size);
    OLED_ShowChar((uint8_t)(x + (int_length + 1) * font_size), y, '.', font_size);
    OLED_ShowNum((uint8_t)(x + (int_length + 2) * font_size),
                    y, fra_num, fra_length, font_size);
}

void OLED_ShowChinese(uint8_t x, uint8_t y, const char *chinese)
{
    uint8_t p_chinese = 0;
    uint8_t p_index;
    uint8_t i;
    char single_chinese[OLED_CHN_CHAR_WIDTH + 1] = {0};

    for (i = 0; chinese[i] != '\0'; i++)
    {
        single_chinese[p_chinese] = chinese[i];
        p_chinese++;

        if (p_chinese >= OLED_CHN_CHAR_WIDTH)
        {
            single_chinese[p_chinese] = '\0';
            p_chinese = 0;

            for (p_index = 0; strcmp(OLED_CF16x16[p_index].Index, "") != 0; p_index++)
            {
                if (strcmp(OLED_CF16x16[p_index].Index, single_chinese) == 0)
                {
                    break;
                }
            }

            OLED_ShowImage((uint8_t)(x + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * 16),
                            y, 16, 16, OLED_CF16x16[p_index].Data);
        }
    }
}

void OLED_ShowImage(uint8_t x, uint8_t y, uint8_t width,
                    uint8_t height, const uint8_t *image)
{
    uint8_t i;
    uint8_t j;

    if (x > 127 || y > 63 || width == 0 || height == 0)
    {
        return;
    }

    OLED_ClearArea(x, y, width, height);

    for (j = 0; j < (height - 1) / 8 + 1; j++)
    {
        for (i = 0; i < width; i++)
        {
            if (x + i > 127)
            {
                break;
            }
            if (y / 8 + j > 7)
            {
                return;
            }

            OLED_DisplayBuf[y / 8 + j][x + i] |= (uint8_t)(image[j * width + i] << (y % 8));

            if (y / 8 + j + 1 > 7 || (y % 8) == 0)
            {
                continue;
            }

            OLED_DisplayBuf[y / 8 + j + 1][x + i] |=
                (uint8_t)(image[j * width + i] >> (8 - y % 8));
        }
    }
}

void OLED_Printf(uint8_t x, uint8_t y, uint8_t font_size, const char *format, ...)
{
    char string[OLED_PRINTF_BUF_SIZE];
    va_list arg;

    va_start(arg, format);
    vsnprintf(string, sizeof(string), format, arg);
    va_end(arg);
    OLED_ShowString(x, y, string, font_size);
}

void OLED_DrawPoint(uint8_t x, uint8_t y)
{
    if (x > 127 || y > 63)
    {
        return;
    }

    OLED_DisplayBuf[y / 8][x] |= (uint8_t)(0x01 << (y % 8));
}

uint8_t OLED_GetPoint(uint8_t x, uint8_t y)
{
    if (x > 127 || y > 63)
    {
        return 0;
    }

    return (OLED_DisplayBuf[y / 8][x] & (0x01 << (y % 8))) ? 1 : 0;
}

void OLED_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    int16_t x;
    int16_t y;
    int16_t dx;
    int16_t dy;
    int16_t d;
    int16_t incr_e;
    int16_t incr_ne;
    int16_t temp;
    int16_t sx0 = x0;
    int16_t sy0 = y0;
    int16_t sx1 = x1;
    int16_t sy1 = y1;
    uint8_t yflag = 0;
    uint8_t xyflag = 0;

    if (sy0 == sy1)
    {
        if (sx0 > sx1)
        {
            temp = sx0;
            sx0 = sx1;
            sx1 = temp;
        }
        for (x = sx0; x <= sx1; x++)
        {
            OLED_DrawPoint((uint8_t)x, (uint8_t)sy0);
        }
    }
    else if (sx0 == sx1)
    {
        if (sy0 > sy1)
        {
            temp = sy0;
            sy0 = sy1;
            sy1 = temp;
        }
        for (y = sy0; y <= sy1; y++)
        {
            OLED_DrawPoint((uint8_t)sx0, (uint8_t)y);
        }
    }
    else
    {
        if (sx0 > sx1)
        {
            temp = sx0; sx0 = sx1; sx1 = temp;
            temp = sy0; sy0 = sy1; sy1 = temp;
        }
        if (sy0 > sy1)
        {
            sy0 = -sy0;
            sy1 = -sy1;
            yflag = 1;
        }
        if (sy1 - sy0 > sx1 - sx0)
        {
            temp = sx0; sx0 = sy0; sy0 = temp;
            temp = sx1; sx1 = sy1; sy1 = temp;
            xyflag = 1;
        }

        dx = sx1 - sx0;
        dy = sy1 - sy0;
        incr_e = 2 * dy;
        incr_ne = 2 * (dy - dx);
        d = 2 * dy - dx;
        x = sx0;
        y = sy0;

        while (x <= sx1)
        {
            if (yflag && xyflag) { OLED_DrawPoint((uint8_t)y, (uint8_t)(-x)); }
            else if (yflag) { OLED_DrawPoint((uint8_t)x, (uint8_t)(-y)); }
            else if (xyflag) { OLED_DrawPoint((uint8_t)y, (uint8_t)x); }
            else { OLED_DrawPoint((uint8_t)x, (uint8_t)y); }

            x++;
            if (d < 0)
            {
                d += incr_e;
            }
            else
            {
                y++;
                d += incr_ne;
            }
        }
    }
}

void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t width,
                        uint8_t height, uint8_t is_filled)
{
    uint8_t i;
    uint8_t j;

    if (!is_filled)
    {
        for (i = x; i < x + width; i++)
        {
            OLED_DrawPoint(i, y);
            OLED_DrawPoint(i, (uint8_t)(y + height - 1));
        }
        for (i = y; i < y + height; i++)
        {
            OLED_DrawPoint(x, i);
            OLED_DrawPoint((uint8_t)(x + width - 1), i);
        }
    }
    else
    {
        for (i = x; i < x + width; i++)
        {
            for (j = y; j < y + height; j++)
            {
                OLED_DrawPoint(i, j);
            }
        }
    }
}

void OLED_DrawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
                        uint8_t x2, uint8_t y2, uint8_t is_filled)
{
    uint8_t minx = x0;
    uint8_t miny = y0;
    uint8_t maxx = x0;
    uint8_t maxy = y0;
    uint8_t i;
    uint8_t j;
    int16_t vx[] = {x0, x1, x2};
    int16_t vy[] = {y0, y1, y2};

    if (!is_filled)
    {
        OLED_DrawLine(x0, y0, x1, y1);
        OLED_DrawLine(x0, y0, x2, y2);
        OLED_DrawLine(x1, y1, x2, y2);
    }
    else
    {
        if (x1 < minx) { minx = x1; }
        if (x2 < minx) { minx = x2; }
        if (y1 < miny) { miny = y1; }
        if (y2 < miny) { miny = y2; }
        if (x1 > maxx) { maxx = x1; }
        if (x2 > maxx) { maxx = x2; }
        if (y1 > maxy) { maxy = y1; }
        if (y2 > maxy) { maxy = y2; }

        for (i = minx; i <= maxx; i++)
        {
            for (j = miny; j <= maxy; j++)
            {
                if (OLED_pnpoly(3, vx, vy, i, j))
                {
                    OLED_DrawPoint(i, j);
                }
            }
        }
    }
}

void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t radius, uint8_t is_filled)
{
    int16_t px = 0;
    int16_t py = radius;
    int16_t d = 1 - radius;
    int16_t j;

    while (px <= py)
    {
        OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + py));
        OLED_DrawPoint((uint8_t)(x + py), (uint8_t)(y + px));
        OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y - py));
        OLED_DrawPoint((uint8_t)(x - py), (uint8_t)(y - px));
        OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y - py));
        OLED_DrawPoint((uint8_t)(x + py), (uint8_t)(y - px));
        OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + py));
        OLED_DrawPoint((uint8_t)(x - py), (uint8_t)(y + px));

        if (is_filled)
        {
            for (j = -py; j < py; j++)
            {
                OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + j));
                OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + j));
            }
            for (j = -px; j < px; j++)
            {
                OLED_DrawPoint((uint8_t)(x - py), (uint8_t)(y + j));
                OLED_DrawPoint((uint8_t)(x + py), (uint8_t)(y + j));
            }
        }

        px++;
        if (d < 0)
        {
            d += 2 * px + 1;
        }
        else
        {
            py--;
            d += 2 * (px - py) + 1;
        }
    }
}

void OLED_DrawEllipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, uint8_t is_filled)
{
    int16_t px = 0;
    int16_t py = b;
    int16_t j;
    float d1 = b * b + a * a * (-b + 0.5f);
    float d2;

    while (b * b * (px + 1) < a * a * (py - 0.5f))
    {
        if (is_filled)
        {
            for (j = -py; j < py; j++)
            {
                OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + j));
                OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + j));
            }
        }
        OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + py));
        OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y - py));
        OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + py));
        OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y - py));

        if (d1 <= 0)
        {
            d1 += b * b * (2 * px + 3);
        }
        else
        {
            d1 += b * b * (2 * px + 3) + a * a * (-2 * py + 2);
            py--;
        }
        px++;
    }

    d2 = b * b * (px + 0.5f) * (px + 0.5f) +
            a * a * (py - 1) * (py - 1) - a * a * b * b;

    while (py > 0)
    {
        if (is_filled)
        {
            for (j = -py; j < py; j++)
            {
                OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + j));
                OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + j));
            }
        }
        OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + py));
        OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y - py));
        OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + py));
        OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y - py));

        if (d2 <= 0)
        {
            d2 += b * b * (2 * px + 2) + a * a * (-2 * py + 3);
            px++;
        }
        else
        {
            d2 += a * a * (-2 * py + 3);
        }
        py--;
    }
}

void OLED_DrawArc(uint8_t x, uint8_t y, uint8_t radius,
                    int16_t start_angle, int16_t end_angle, uint8_t is_filled)
{
    int16_t px = 0;
    int16_t py = radius;
    int16_t d = 1 - radius;
    int16_t j;

    while (px <= py)
    {
        if (OLED_IsInAngle(px, py, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + py)); }
        if (OLED_IsInAngle(py, px, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x + py), (uint8_t)(y + px)); }
        if (OLED_IsInAngle(-px, -py, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y - py)); }
        if (OLED_IsInAngle(-py, -px, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x - py), (uint8_t)(y - px)); }
        if (OLED_IsInAngle(px, -py, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y - py)); }
        if (OLED_IsInAngle(py, -px, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x + py), (uint8_t)(y - px)); }
        if (OLED_IsInAngle(-px, py, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + py)); }
        if (OLED_IsInAngle(-py, px, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x - py), (uint8_t)(y + px)); }

        if (is_filled)
        {
            for (j = -py; j < py; j++)
            {
                if (OLED_IsInAngle(px, j, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x + px), (uint8_t)(y + j)); }
                if (OLED_IsInAngle(-px, j, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x - px), (uint8_t)(y + j)); }
            }
            for (j = -px; j < px; j++)
            {
                if (OLED_IsInAngle(-py, j, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x - py), (uint8_t)(y + j)); }
                if (OLED_IsInAngle(py, j, start_angle, end_angle)) { OLED_DrawPoint((uint8_t)(x + py), (uint8_t)(y + j)); }
            }
        }

        px++;
        if (d < 0)
        {
            d += 2 * px + 1;
        }
        else
        {
            py--;
            d += 2 * (px - py) + 1;
        }
    }
}

uint8_t OLED_TestConnection(void)
{
    elab_err_t ret;

    if (oled_device == NULL)
    {
        oled_device = elab_device_find(OLED_I2C_DEVICE_NAME);
    }

    if (oled_device == NULL)
    {
        return 0;
    }

    ret = OLED_WriteCommand(0xAE);
    return (ret > 0) ? 1U : 0U;
}

void OLED_TestAllOn(void)
{
    OLED_WriteCommand(0xA5);
}

void OLED_TestResumeRAM(void)
{
    OLED_WriteCommand(0xA4);
    OLED_Update();
}

void device_oled096_init(void)
{
    static const uint8_t init_cmds[] =
    {
        0xAE,
        0xD5, 0x80,
        0xA8, 0x3F,
        0xD3, 0x00,
        0x40,
        0xA1,
        0xC8,
        0xDA, 0x12,
        0x81, 0x7F,
        0xA4,
        0xA6,
        0xD9, 0xF1,
        0xDB, 0x40,
        0x20, 0x02,
        0x8D, 0x14,
        0xAF,
    };
    uint8_t i;

    oled_device = elab_device_find(OLED_I2C_DEVICE_NAME);
    elab_assert(oled_device != NULL);

    for (i = 0; i < sizeof(init_cmds); i++)
    {
        OLED_WriteCommand(init_cmds[i]);
    }

    OLED_Clear();
    OLED_Update();
	
	/*在(0, 0)位置显示字符'A'，字体大小为8*16点阵*/
	//OLED_ShowChar(0, 0, 'A', OLED_8X16);
	
	/*在(16, 0)位置显示字符串"Hello World!"，字体大小为8*16点阵*/
	OLED_ShowString(0, 0, "bilibili space/6451333", OLED_8X16);
	
	/*在(0, 18)位置显示字符'A'，字体大小为6*8点阵*/
	OLED_ShowChar(0, 18, 'A', OLED_6X8);
	
	/*在(16, 18)位置显示字符串"Hello World!"，字体大小为6*8点阵*/
	OLED_ShowString(16, 18, "Hello World!", OLED_6X8);
	
	/*在(0, 28)位置显示数字12345，长度为5，字体大小为6*8点阵*/
	OLED_ShowNum(0, 28, 12345, 5, OLED_6X8);
	
	/*在(40, 28)位置显示有符号数字-66，长度为2，字体大小为6*8点阵*/
	OLED_ShowSignedNum(40, 28, -66, 2, OLED_6X8);
	
	/*在(70, 28)位置显示十六进制数字0xA5A5，长度为4，字体大小为6*8点阵*/
	OLED_ShowHexNum(70, 28, 0xA5A5, 4, OLED_6X8);
	
	/*在(0, 38)位置显示二进制数字0xA5，长度为8，字体大小为6*8点阵*/
	OLED_ShowBinNum(0, 38, 0xA5, 8, OLED_6X8);
	
	/*在(60, 38)位置显示浮点数字123.45，整数部分长度为3，小数部分长度为2，字体大小为6*8点阵*/
	OLED_ShowFloatNum(60, 38, 123.45, 3, 2, OLED_6X8);
	
	OLED_ShowString(0, 48, "OLED Ready", OLED_6X8);
	
	/*在(96, 48)位置显示图像，宽16像素，高16像素，图像数据为Diode数组*/
	OLED_ShowImage(96, 48, 16, 16, Diode);
	
	/*在(96, 18)位置打印格式化字符串，字体大小为6*8点阵，格式化字符串为"[%02d]"*/
	OLED_Printf(96, 18, OLED_6X8, "[%02d]", 6);
    OLED_Update();

}

ELAB_INIT_EXPORT(device_oled096_init, EXPORT_APP);
