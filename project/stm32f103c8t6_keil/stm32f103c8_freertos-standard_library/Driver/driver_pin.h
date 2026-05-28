/**
 * @file driver_pin.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-19
 * 
 * 
 */
#ifndef DRIVER_PIN_H 
#define DRIVER_PIN_H 

/* ==================== [Includes] ========================================== */

#include "elab_pin.h"

#ifdef __cplusplus
extern "C"{
#endif

/* ==================== [Defines] ========================================== */

/* ==================== [Typedefs] ========================================== */
typedef struct elab_pin_driver
{
    elab_pin_t device;
    const char *pin_name;
} elab_pin_driver_t;
/* ==================== [Global Prototypes] ================================== */
void elab_driver_pin_init(elab_pin_driver_t *me,
                            const char *name, const char *pin_name);
/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
}
#endif

#endif	/* DRIVER_PIN_H */

