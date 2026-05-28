
/**
 * @file adapter_export.c
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
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */
static elab_led_t led_run;

static void device_adapter_export(void)
{
elab_led_register(&led_run, "led_run", "PIN_PC13", false);
// elab_led_toggle(&led_run.super, 500);
elab_led_set_value(&led_run.super, 4);
}
/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */

ELAB_INIT_EXPORT(device_adapter_export, EXPORT_DEVICE);
 /* ----------------------------- end of file -------------------------------- */

