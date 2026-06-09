/**
 * @file pin_export.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-20
 * 
 * 
 */

 /* ==================== [Includes] ========================================== */
#include "../Driver/driver_pin.h"
#include "elab_export.h"

 /* ==================== [Defines] ========================================== */


 /* ==================== [Macros] ============================================ */
 
 /* ==================== [Typedefs] ========================================== */
 
 /* ==================== [Static Prototypes] ========================================== */
 
/* ==================== [Static Variables] ========================================== */
static elab_pin_driver_t led_run_pin;
static const elab_pin_dt_config_t led_run_pin_dt_config =
{
    .name = "led_pin",
    .port = "GPIOC",
    .pin = 13,
    .mode = PIN_MODE_OUTPUT_PP,
    .init_level = false,
    .has_init_level = true,
    .active_low = false,
};

/* ==================== [Static Functions] ================================== */
static void driver_pin_mcu_export(void)
{
    elab_driver_pin_init_cfg(&led_run_pin, &led_run_pin_dt_config);
}

 /* ==================== [Public Functions] ================================== */
ELAB_INIT_EXPORT(driver_pin_mcu_export,EXPORT_DRVIVER);


