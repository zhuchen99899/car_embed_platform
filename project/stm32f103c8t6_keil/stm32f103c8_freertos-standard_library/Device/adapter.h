/**
 * @file adapter.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-20
 * 
 * 
 */

 
 #ifndef ADAPTER_H 
 #define ADAPTER_H 
 
 /* ==================== [Includes] ========================================== */
 
#include "elab_led.h"
 
#ifdef __cplusplus
extern "C"{
#endif

 /* ==================== [Defines] ========================================== */

 /* ==================== [Typedefs] ========================================== */
 
 /* ==================== [Global Prototypes] ================================== */
void elab_led_register(elab_led_t *const me, const char *name,
                      const char *pin_name, bool status_led_on);
 /* ==================== [Macros] ============================================ */
 
#ifdef __cplusplus
}
#endif

#endif	/* ADAPTER_H */
 


