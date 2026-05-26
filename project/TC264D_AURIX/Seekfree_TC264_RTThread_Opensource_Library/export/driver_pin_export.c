#include "driver_pin.h"
#include "elab_export.h"

/* ==================== [Includes] ========================================== */

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */
static elab_pin_driver_t pin_led;
/* ==================== [Static Functions] ================================== */
void driver_pin_export(void)
{
elab_driver_pin_init(&pin_led, "led_pin", P20_8);
elab_pin_set_mode(&pin_led.device.super, PIN_MODE_OUTPUT_PP);


}

ELAB_INIT_EXPORT(driver_pin_export, EXPORT_DRVIVER);
/* ==================== [Public Functions] ================================== */
