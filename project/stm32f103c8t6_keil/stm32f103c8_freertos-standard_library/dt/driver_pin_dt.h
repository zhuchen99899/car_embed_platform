/**
 * @file driver_pin_dt.h
 * @brief STM32F103 pin devicetree conversion layer.
 */
#ifndef DRIVER_PIN_DT_H
#define DRIVER_PIN_DT_H

#include <stdbool.h>
#include "../Driver/driver_pin.h"

#ifdef __cplusplus
extern "C" {
#endif

bool elab_driver_pin_resolve_dt(const elab_pin_dt_config_t *dt,
                                GPIO_TypeDef **port,
                                uint16_t *pin);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_PIN_DT_H */
