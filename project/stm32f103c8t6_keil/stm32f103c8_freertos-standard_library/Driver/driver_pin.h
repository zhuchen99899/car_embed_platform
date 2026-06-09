/**
 * @file driver_pin.h
 * @author ZC (387646983@qq.com)
 * @brief
 * @version 0.1
 * @date 2026-05-19
 */
#ifndef DRIVER_PIN_H
#define DRIVER_PIN_H

/* ==================== [Includes] ========================================== */

#include "elab_pin.h"
#include "stm32f10x_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Typedefs] ========================================== */

typedef struct elab_pin_dt_config
{
    const char *name;
    const char *port;
    uint8_t pin;
    uint8_t mode;
    bool init_level;
    bool has_init_level;
    bool active_low;
} elab_pin_dt_config_t;

typedef struct elab_pin_driver
{
    elab_pin_t device;
    elab_pin_dt_config_t config;
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
} elab_pin_driver_t;

/* ==================== [Global Prototypes] ================================== */

void elab_driver_pin_init_cfg(elab_pin_driver_t *me,
                                const elab_pin_dt_config_t *config);
void elab_driver_pin_init(elab_pin_driver_t *me,
                            const char *name,
                            const char *port,
                            uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_PIN_H */
