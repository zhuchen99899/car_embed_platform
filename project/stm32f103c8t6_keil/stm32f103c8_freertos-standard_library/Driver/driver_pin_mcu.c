/**
 * @file driver_pin_mcu.c
 * @author ZC (387646983@qq.com)
 * @brief
 * @version 0.1
 * @date 2026-05-19
 */

/* ==================== [Includes] ========================================== */

#include "elab_log.h"
#include "elab_assert.h"
#include "driver_pin.h"
#include "../dt/driver_pin_dt.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/* ==================== [Macros] ============================================ */

ELAB_TAG("DriverPin");

/* ==================== [Static Prototypes] ================================= */

static elab_err_t _init(elab_pin_t * const me);
static elab_err_t _set_mode(elab_pin_t * const me, uint8_t mode);
static elab_err_t _get_status(elab_pin_t * const me, bool *status);
static elab_err_t _set_status(elab_pin_t * const me, bool status);
static elab_err_t _gpio_init_mode(elab_pin_driver_t *driver);
static elab_err_t _gpio_set_mode(elab_pin_driver_t *driver, uint8_t mode);
static void _gpio_clock_enable(GPIO_TypeDef *port);
static bool _to_physical_status(const elab_pin_driver_t *driver, bool status);

/* ==================== [Static Variables] ================================== */

static const elab_pin_ops_t pin_driver_ops =
{
    .init = _init,
    .set_mode = _set_mode,
    .get_status = _get_status,
    .set_status = _set_status,
};

/* ==================== [Public Functions] ================================== */

void elab_driver_pin_init_cfg(elab_pin_driver_t *me,
                                const elab_pin_dt_config_t *config)
{
    elab_assert(me != NULL);
    elab_assert(config != NULL);
    elab_assert(config->name != NULL);

    me->config = *config;
    elab_assert(elab_driver_pin_resolve_dt(&me->config,
                                            &me->gpio_port,
                                            &me->gpio_pin));
    _gpio_clock_enable(me->gpio_port);
    elab_pin_register(&me->device, me->config.name, &pin_driver_ops, me);

    if (me->config.mode < PIN_MODE_MAX)
    {
        elab_pin_set_mode(&me->device.super, me->config.mode);
    }

    if (me->config.has_init_level &&
        (me->config.mode == PIN_MODE_OUTPUT_PP ||
            me->config.mode == PIN_MODE_OUTPUT_OD))
    {
        elab_pin_set_status(&me->device.super, me->config.init_level);
    }
}

void elab_driver_pin_init(elab_pin_driver_t *me,
                            const char *name,
                            const char *port,
                            uint8_t pin)
{
    const elab_pin_dt_config_t config =
    {
        .name = name,
        .port = port,
        .pin = pin,
        .mode = PIN_MODE_OUTPUT_PP,
        .init_level = false,
        .has_init_level = true,
        .active_low = false,
    };

    elab_driver_pin_init_cfg(me, &config);
}

/* ==================== [Static Functions] ================================== */

static elab_err_t _init(elab_pin_t * const me)
{
    elab_assert(me != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;

    return _gpio_init_mode(driver);
}

static elab_err_t _set_mode(elab_pin_t * const me, uint8_t mode)
{
    elab_assert(me != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;

    return _gpio_set_mode(driver, mode);
}

static elab_err_t _get_status(elab_pin_t * const me, bool *status)
{
    elab_assert(me != NULL);
    elab_assert(status != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;
    bool value = (GPIO_ReadInputDataBit(driver->gpio_port,
                                        driver->gpio_pin) == Bit_SET);

    if (driver->config.active_low)
    {
        value = !value;
    }
    *status = value;

    return ELAB_OK;
}

static elab_err_t _set_status(elab_pin_t * const me, bool status)
{
    elab_assert(me != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;
    bool physical_status = _to_physical_status(driver, status);

    if (physical_status)
    {
        GPIO_SetBits(driver->gpio_port, driver->gpio_pin);
    }
    else
    {
        GPIO_ResetBits(driver->gpio_port, driver->gpio_pin);
    }

    return ELAB_OK;
}

static elab_err_t _gpio_init_mode(elab_pin_driver_t *driver)
{
    elab_assert(driver != NULL);

    if (driver->config.has_init_level)
    {
        bool physical_status = _to_physical_status(driver,
                                                    driver->config.init_level);
        if (physical_status)
        {
            GPIO_SetBits(driver->gpio_port, driver->gpio_pin);
        }
        else
        {
            GPIO_ResetBits(driver->gpio_port, driver->gpio_pin);
        }
    }

    return _gpio_set_mode(driver, driver->config.mode);
}

static elab_err_t _gpio_set_mode(elab_pin_driver_t *driver, uint8_t mode)
{
    GPIO_InitTypeDef gpio_init = {0};

    elab_assert(driver != NULL);

    if (mode == PIN_MODE_OUTPUT_PP)
    {
        gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        gpio_init.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        gpio_init.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if (mode == PIN_MODE_INPUT_ANOLOG)
    {
        gpio_init.GPIO_Mode = GPIO_Mode_AIN;
    }
    else
    {
        return ELAB_ERR_INVALID;
    }

    gpio_init.GPIO_Pin = driver->gpio_pin;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(driver->gpio_port, &gpio_init);

    return ELAB_OK;
}

static void _gpio_clock_enable(GPIO_TypeDef *port)
{
    if (port == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (port == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if (port == GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    else if (port == GPIOD)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }
    else if (port == GPIOE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }
    else if (port == GPIOF)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    }
    else if (port == GPIOG)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    }
}

static bool _to_physical_status(const elab_pin_driver_t *driver, bool status)
{
    elab_assert(driver != NULL);

    if (driver->config.active_low)
    {
        status = !status;
    }

    return status;
}
