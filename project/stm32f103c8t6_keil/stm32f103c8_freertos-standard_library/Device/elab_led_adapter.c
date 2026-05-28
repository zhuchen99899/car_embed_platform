/**
 * @file elab_led_adapter.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-20
 * 
 * 
 */
/* include ------------------------------------------------------------------ */
#include "elab_pin.h"
#include "adapter.h"

/* private function --------------------------------------------------------- */
static elab_err_t _pin_set_status_adapter(void *backend, bool status)
{
    elab_pin_set_status((elab_device_t *)backend, status);
    return ELAB_OK;
}

/* private variables -------------------------------------------------------- */
static const elab_led_backend_ops_t _pin_backend_ops =
{
    .set_status = _pin_set_status_adapter,
};

/* public function ---------------------------------------------------------- */
void elab_led_register(elab_led_t *const me, const char *name,
                        const char *pin_name, bool status_led_on)
{
    if (pin_name == NULL)
    {
        return;
    }

    elab_led_register_with_backend(me, name, &_pin_backend_ops,
                                    elab_device_find(pin_name), status_led_on);
}

/* ----------------------------- end of file -------------------------------- */
