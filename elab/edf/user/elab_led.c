/*
 * eLab Project
 * Copyright (c) 2023, EventOS Team, <event-os@outlook.com>
 */

/* include ------------------------------------------------------------------ */
#include "elab_led.h"
#include "../../common/elab_assert.h"

ELAB_TAG("EdfLed");

/* private config ----------------------------------------------------------- */
#define ELAB_LED_POLL_PEROID                    (50)
#define ELAB_LED_ON_LONG_MS                     (2000)
#define ELAB_LED_ON_SHORT_MS                    (500)
#define ELAB_LED_OFF_MS                         (500)

/* private defines ---------------------------------------------------------- */
enum elab_led_mode
{
    ELAB_LED_MODE_NULL = 0,
    ELAB_LED_MODE_TOGGLE,
    ELAB_LED_MODE_VALUE,
};


static void _set_status(elab_led_t *led, bool status);
static void _timer_func(void *argument);

/* Private variables ---------------------------------------------------------*/
static const elab_dev_ops_t _led_ops =
{
    .enable = NULL,
    .read = NULL,
    .write = NULL,
#if (ELAB_DEV_PALTFORM == ELAB_PALTFORM_POLL)
    .poll = NULL,
#endif
};

static const osTimerAttr_t timer_attr_led =
{
    .name = "led_timer",
    .attr_bits = 0,
    .cb_mem = NULL,
    .cb_size = 0,
};

/* public function ---------------------------------------------------------- */
/**
 * @brief LED注册接口
 * 
 * @param me 
 * @param name 
 * @param backend_ops  后端设备接口
 * @param backend  后端设备句柄
 * @param status_led_on 
 */
void elab_led_register_with_backend(elab_led_t *const me, const char *name,
                                    const elab_led_backend_ops_t *backend_ops,
                                    void *backend, bool status_led_on)
{
    elab_assert(me != NULL);
    elab_assert(name != NULL);
    elab_assert(backend_ops != NULL);
    elab_assert(backend_ops->set_status != NULL);
    elab_assert(backend != NULL);
    elab_assert(!elab_device_valid(name));

    osStatus_t ret_os = osOK;
    
    /* Newly establish the timer and start it. */
    me->timer = osTimerNew(_timer_func, osTimerPeriodic, me, &timer_attr_led);
    assert_name(me->timer != NULL, name);
    ret_os = osTimerStart(me->timer, ELAB_LED_POLL_PEROID);
    elab_assert(ret_os == osOK);

    /* Set the data of the device. */
    me->super.ops = &_led_ops;
    me->super.user_data = NULL;
    me->mode = ELAB_LED_MODE_NULL;
    me->status = false;
    me->status_led_on = status_led_on;
    me->backend_ops = backend_ops;
    me->backend = backend;

    _set_status(me, me->status);

    /* Register to device manager. */
    elab_device_attr_t attr_led =
    {
        .name = name,
        .sole = false,
        .type = ELAB_DEVICE_UNKNOWN,
    };
    elab_device_register(&me->super, &attr_led);
}
/**
 * @brief 直接设置LED状态接口，设置时LED将退出闪烁或数值模式
 * 
 * @param me 
 * @param status 
 */
void elab_led_set_status(elab_device_t *const me, bool status)
{
    elab_assert(me != NULL);

    elab_led_t *led = ELAB_LED_CAST(me);

    led->mode = ELAB_LED_MODE_NULL; //退出闪烁或数值模式
    led->status = status;
    _set_status(led, led->status);
}

/**
 * @brief 设置LED闪烁模式
 * 
 * @param me 
 * @param period_ms 
 */
void elab_led_toggle(elab_device_t *const me, uint32_t period_ms)
{
    elab_assert(me != NULL);
    elab_assert(period_ms >= ELAB_LED_POLL_PEROID);
    
    elab_led_t *led = ELAB_LED_CAST(me);

    if (led->mode != ELAB_LED_MODE_TOGGLE || led->period_ms != period_ms) //闪烁模式
    {
        led->mode = ELAB_LED_MODE_TOGGLE;
        led->time_out = osKernelGetTickCount() + period_ms;
        led->period_ms = period_ms;
    }
}

/**
  * @brief  The led device value setting function. 值模式
  * @param  me      elab led device handle.
  * @param  value   The led device value.
  * @retval None.
  */
void elab_led_set_value(elab_device_t *const me, uint8_t value)
{
    elab_assert(me != NULL);

    elab_led_t *led = ELAB_LED_CAST(me);
    if (led->mode != ELAB_LED_MODE_VALUE || led->period_ms != value)
    {
        led->mode = ELAB_LED_MODE_VALUE;
        led->value = value;
        led->value_count = 0;
        led->value_count_max = (value + 1) * 2;
        led->time_out = osKernelGetTickCount() + ELAB_LED_ON_LONG_MS;
        led->status = 0;
        _set_status(led, led->status);
    }
}

/* private function --------------------------------------------------------- */
static void _set_status(elab_led_t *led, bool status)
{
    bool backend_status = led->status_led_on ? status : !status;

    (void)led->backend_ops->set_status(led->backend, backend_status);
}

/**
  * @brief  eLab LED polling timer function.
  * @param  argument    Timer function argument.
  * @retval None
  */
static void _timer_func(void *argument)
{
    elab_led_t *led = ELAB_LED_CAST(argument);

    /* When led is working in TOGGLE mode. */
    if (led->mode == ELAB_LED_MODE_TOGGLE)
    {
        if (osKernelGetTickCount() >= led->time_out)
        {
            led->status = !led->status;
            _set_status(led, led->status);
            led->time_out += led->period_ms;
        }
    }
    /* When led is working in VALUE mode. */
    else if (led->mode == ELAB_LED_MODE_VALUE)
    {
        if (osKernelGetTickCount() >= led->time_out)
        {
            led->status = !led->status;
            _set_status(led, led->status);
            led->value_count ++;
            if (led->value_count >= led->value_count_max)
            {
                led->value_count = 0;
            }

            if (led->value_count == 0)
            {
                led->time_out += ELAB_LED_ON_LONG_MS;
            }
            else if (led->value_count % 2 == 0)
            {
                led->time_out += ELAB_LED_ON_SHORT_MS;
            }
            else
            {
                led->time_out += ELAB_LED_OFF_MS;
            }
        }
    }
}

/* ----------------------------- end of file -------------------------------- */
