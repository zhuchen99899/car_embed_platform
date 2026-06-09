#include "driver_pin.h"
#include "elab_export.h"

/* ==================== [Includes] ========================================== */

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */
static elab_pin_driver_t pin_led;
static const elab_pin_dt_config_t pin_led_dt_config =
{
    .name = "led_pin",
    .port = "P20",
    .pin = 8,
    .mode = PIN_MODE_OUTPUT_PP,
    .init_level = false,
    .has_init_level = true,
    .active_low = false,
};
/* ==================== [Static Functions] ================================== */
void driver_pin_export(void)
{
    elab_driver_pin_init_cfg(&pin_led, &pin_led_dt_config);
}

ELAB_INIT_EXPORT(driver_pin_export, EXPORT_DRVIVER);
/* ==================== [Public Functions] ================================== */
