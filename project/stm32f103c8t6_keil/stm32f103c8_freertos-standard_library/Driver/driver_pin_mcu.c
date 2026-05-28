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
#include "drv_util.h"
#include "stm32f10x.h"
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
                            const char *name, const char *pin_name)
{
    elab_assert(me != NULL);
    elab_assert(name != NULL);
    assert_name(check_pin_name_valid(pin_name), pin_name);

    /* Enable the clock. */
    gpio_clock_enable(pin_name);

    me->pin_name = pin_name;
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
    GPIO_TypeDef *port = get_port_from_name(driver->pin_name);
    uint16_t pin = get_pin_from_name(driver->pin_name);

    /* Configure GPIO pin. */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStruct);
    GPIO_SetBits(port, pin); /* 默认高电平 */
    
    return ELAB_OK;
}

static elab_err_t _set_mode(elab_pin_t * const me, uint8_t mode)
{
    elab_assert(me != NULL);
    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;
    GPIO_TypeDef *port = get_port_from_name(driver->pin_name);
    uint16_t pin = get_pin_from_name(driver->pin_name);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (mode == PIN_MODE_OUTPUT_PP)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if (mode == PIN_MODE_INPUT_ANOLOG)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    }
    else
    {
        return ELAB_ERR_INVALID;
    }
    GPIO_InitStruct.GPIO_Pin = pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStruct);
    return ELAB_OK;
    
}

static elab_err_t _get_status(elab_pin_t * const me, bool *status)
{
    elab_assert(me != NULL);
    elab_assert(status != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;
    GPIO_TypeDef *port = get_port_from_name(driver->pin_name);
    uint16_t pin = get_pin_from_name(driver->pin_name);

    *status = (GPIO_ReadInputDataBit(port, pin) == Bit_SET) ? true : false;

    return ELAB_OK;
}


static elab_err_t _set_status(elab_pin_t * const me, bool status)
{
    elab_assert(me != NULL);

    elab_pin_driver_t *driver = (elab_pin_driver_t *)me->super.user_data;
    GPIO_TypeDef *port = get_port_from_name(driver->pin_name);
    uint16_t pin = get_pin_from_name(driver->pin_name);

    if (status)
    {
        GPIO_SetBits(port, pin);
    }
    else
    {
        GPIO_ResetBits(port, pin);
    }

    return ELAB_OK;
}


