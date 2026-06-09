/**
 * @file driver_pin_dt.c
 * @brief STM32F103 pin devicetree conversion layer.
 */

#include <string.h>
#include "driver_pin_dt.h"

static GPIO_TypeDef *_port_from_dt_name(const char *port)
{
    if (port == NULL)
    {
        return NULL;
    }

    if (strcmp(port, "GPIOA") == 0)
    {
        return GPIOA;
    }
    if (strcmp(port, "GPIOB") == 0)
    {
        return GPIOB;
    }
    if (strcmp(port, "GPIOC") == 0)
    {
        return GPIOC;
    }
    if (strcmp(port, "GPIOD") == 0)
    {
        return GPIOD;
    }
    if (strcmp(port, "GPIOE") == 0)
    {
        return GPIOE;
    }
    if (strcmp(port, "GPIOF") == 0)
    {
        return GPIOF;
    }
    if (strcmp(port, "GPIOG") == 0)
    {
        return GPIOG;
    }

    return NULL;
}

bool elab_driver_pin_resolve_dt(const elab_pin_dt_config_t *dt,
                                GPIO_TypeDef **port,
                                uint16_t *pin)
{
    GPIO_TypeDef *gpio_port;

    if (dt == NULL || port == NULL || pin == NULL || dt->name == NULL)
    {
        return false;
    }

    gpio_port = _port_from_dt_name(dt->port);
    if (gpio_port == NULL || dt->pin > 15U)
    {
        return false;
    }

    *port = gpio_port;
    *pin = (uint16_t)(1UL << dt->pin);

    return true;
}
