/**
 * @file device_export.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-20
 * 
 * 
 */

/* ==================== [Includes] ========================================== */
#include "adapter.h"
#include "elab_export.h"
#include "elab_i2c.h"
#include "elab_led.h"

elab_led_t led;
static elab_i2c_t dev_i2c_oled;

static const elab_i2c_config_t config_oled =
{
    .clock = 100000,
    .addr_10bit = false,
    .addr = 0x3C,
};
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Static Functions] ================================== */
void device_led_export(void)
{
    elab_led_register(&led, "led_device", "led_pin", false);
    elab_led_set_value(&led.super, 4);


     elab_i2c_register(&dev_i2c_oled, "oled", "i2c0", config_oled);

}
ELAB_INIT_EXPORT(device_led_export, EXPORT_DEVICE);

/* ==================== [Public Functions] ================================== */
