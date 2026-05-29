/**
 * @file device_export.c
 * @author ZC (387646983@qq.com)
 * @brief Board-level device registration.
 * @version 0.1
 * @date 2026-05-20
 */

/* ==================== [Includes] ========================================== */
#include "adapter.h"
#include "elab_export.h"
#include "elab_i2c.h"

/* ==================== [Static Variables] ================================== */
static elab_led_t led_run;
static elab_i2c_t dev_i2c_oled;

static const elab_i2c_config_t config_oled =
{
    .clock = 100000,
    .addr_10bit = false,
    /* Use the 7-bit SSD1306 address. The bus driver adds the R/W bit. */
    .addr = 0x3C,
};

/* ==================== [Static Functions] ================================== */
static void device_adapter_export(void)
{
    elab_led_register(&led_run, "led_run", "PIN_PC13", false);
    elab_led_set_value(&led_run.super, 4);

    elab_i2c_register(&dev_i2c_oled, "oled", "i2c0", config_oled);
}

ELAB_INIT_EXPORT(device_adapter_export, EXPORT_DEVICE);

/* ----------------------------- end of file -------------------------------- */
