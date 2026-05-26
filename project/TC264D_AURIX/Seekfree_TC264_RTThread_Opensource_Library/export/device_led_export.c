/**
 * @file device_led_export.c
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
 #include "elab_led.h"

elab_led_t led;
 /* ==================== [Defines] ========================================== */
 
 /* ==================== [Macros] ============================================ */
 
 /* ==================== [Typedefs] ========================================== */
 
 /* ==================== [Static Prototypes] ========================================== */
 
 /* ==================== [Static Variables] ========================================== */
 
 /* ==================== [Static Functions] ================================== */
void device_led_export(void)
{    
elab_led_register(&led, "led_device", "led_pin", false);

elab_led_set_value(&led.super, 4);
}
ELAB_INIT_EXPORT(device_led_export, EXPORT_DEVICE);
 /* ==================== [Public Functions] ================================== */
 
