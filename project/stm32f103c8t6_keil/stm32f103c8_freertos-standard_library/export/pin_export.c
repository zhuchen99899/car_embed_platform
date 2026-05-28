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
 /* ==================== [Static Functions] ================================== */
static void driver_pin_mcu_export(void){
elab_driver_pin_init(&led_run_pin, "PIN_PC13", "C.13");
elab_pin_set_mode(&led_run_pin.device.super, PIN_MODE_OUTPUT_PP);
}
 /* ==================== [Public Functions] ================================== */
ELAB_INIT_EXPORT(driver_pin_mcu_export,EXPORT_DRVIVER);


