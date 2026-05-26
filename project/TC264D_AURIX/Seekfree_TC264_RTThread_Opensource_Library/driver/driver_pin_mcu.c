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
void elab_driver_pin_init(elab_pin_driver_t *me,
                            const char *name, PIN_enum pin_num)
{
    elab_assert(me != NULL);
    elab_assert(name != NULL);

    me->pin_num = pin_num;
    elab_pin_register(&me->device, name, &pin_driver_ops, me);
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

    /* Configure GPIO pin. */

    gpio_init(driver->pin_num, GPO, 0, PUSHPULL);
    return ELAB_OK;
}

static elab_err_t _set_mode(elab_pin_t * const me, uint8_t mode)
{
    elab_assert(me != NULL);
    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;

    if (mode == PIN_MODE_OUTPUT_PP)
    {
    gpio_dir(driver->pin_num, GPO,PUSHPULL);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        gpio_dir(driver->pin_num, GPO,OPENDRAIN);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        gpio_dir(driver->pin_num, GPI,PULLUP);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        gpio_dir(driver->pin_num, GPI,PULLDOWN);
    }
    else if (mode == PIN_MODE_INPUT_ANOLOG)
    {
        gpio_dir(driver->pin_num, GPI,PULLUP);
    }
    else
    {
        return ELAB_ERR_INVALID;
    }
    
    return ELAB_OK;
}

static elab_err_t _get_status(elab_pin_t * const me, bool *status)
{
    elab_assert(me != NULL);
    elab_assert(status != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;


    *status = (gpio_get(driver->pin_num) == 1) ? true : false;

    return ELAB_OK;
}


static elab_err_t _set_status(elab_pin_t * const me, bool status)
{
    elab_assert(me != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;

    if (status)
    {
        gpio_set(driver->pin_num, 1);
    }
    else
    {
        gpio_set(driver->pin_num, 0);
    }

    return ELAB_OK;
}


