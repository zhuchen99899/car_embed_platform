/**
 * @file driver_pin_mcu.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-19
 * 
 * 
 */
/* ==================== [Includes] ========================================== */

#include "elab_log.h"
#include "elab_assert.h"
#include "driver_pin.h"
#include "../dt/driver_pin_dt.h"
#include "zf_gpio.h"
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */
ELAB_TAG("DriverPin");
/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */
static elab_err_t _init(elab_pin_t * const me);
static elab_err_t _set_mode(elab_pin_t * const me, uint8_t mode);
static elab_err_t _get_status(elab_pin_t * const me, bool *status);
static elab_err_t _set_status(elab_pin_t * const me, bool status);
static elab_err_t _gpio_init_mode(elab_pin_driver_t *driver);
static elab_err_t _gpio_set_mode(PIN_enum pin_num, uint8_t mode);
static bool _to_physical_status(elab_pin_driver_t *driver, bool status);
/* ==================== [Static Variables] ========================================== */
static const elab_pin_ops_t pin_driver_ops =
{
    .init = _init,
    .set_mode = _set_mode,
    .get_status = _get_status,
    .set_status = _set_status,
};
/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */
void elab_driver_pin_init_cfg(elab_pin_driver_t *me,
                                const elab_pin_dt_config_t *config)
{
    elab_assert(me != NULL);
    elab_assert(config != NULL);
    elab_assert(config->name != NULL);

    me->config = *config;
    elab_assert(elab_driver_pin_resolve_dt(&me->config, &me->pin_num));
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

/**
  * @brief  The PIN driver initialization function.
  * @param  me  PIN device handle.
  * @retval None.
  */
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

    return _gpio_set_mode(driver->pin_num, mode);
}

static elab_err_t _get_status(elab_pin_t * const me, bool *status)
{
    elab_assert(me != NULL);
    elab_assert(status != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;
    bool value = (gpio_get(driver->pin_num) == 1) ? true : false;

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
        gpio_set(driver->pin_num, 1);
    }
    else
    {
        gpio_set(driver->pin_num, 0);
    }

    return ELAB_OK;
}

static elab_err_t _gpio_init_mode(elab_pin_driver_t *driver)
{
    uint8_t init_level = 0U;

    elab_assert(driver != NULL);

    if (driver->config.has_init_level)
    {
        init_level = _to_physical_status(driver, driver->config.init_level) ? 1U : 0U;
    }

    if (driver->config.mode == PIN_MODE_OUTPUT_PP)
    {
        gpio_init(driver->pin_num, GPO, init_level, PUSHPULL);
    }
    else if (driver->config.mode == PIN_MODE_OUTPUT_OD)
    {
        gpio_init(driver->pin_num, GPO, init_level, OPENDRAIN);
    }
    else if (driver->config.mode == PIN_MODE_INPUT)
    {
        gpio_init(driver->pin_num, GPI, 0U, NO_PULL);
    }
    else if (driver->config.mode == PIN_MODE_INPUT_PULLUP)
    {
        gpio_init(driver->pin_num, GPI, 0U, PULLUP);
    }
    else if (driver->config.mode == PIN_MODE_INPUT_PULLDOWN)
    {
        gpio_init(driver->pin_num, GPI, 0U, PULLDOWN);
    }
    else if (driver->config.mode == PIN_MODE_INPUT_ANOLOG)
    {
        gpio_init(driver->pin_num, GPI, 0U, NO_PULL);
    }
    else
    {
        gpio_init(driver->pin_num, GPO, 0U, PUSHPULL);
    }

    return ELAB_OK;
}

static elab_err_t _gpio_set_mode(PIN_enum pin_num, uint8_t mode)
{
    if (mode == PIN_MODE_OUTPUT_PP)
    {
        gpio_dir(pin_num, GPO, PUSHPULL);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        gpio_dir(pin_num, GPO, OPENDRAIN);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        gpio_dir(pin_num, GPI, NO_PULL);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        gpio_dir(pin_num, GPI, PULLUP);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        gpio_dir(pin_num, GPI, PULLDOWN);
    }
    else if (mode == PIN_MODE_INPUT_ANOLOG)
    {
        gpio_dir(pin_num, GPI, NO_PULL);
    }
    else
    {
        return ELAB_ERR_INVALID;
    }

    return ELAB_OK;
}

static bool _to_physical_status(elab_pin_driver_t *driver, bool status)
{
    elab_assert(driver != NULL);

    if (driver->config.active_low)
    {
        status = !status;
    }

    return status;
}


