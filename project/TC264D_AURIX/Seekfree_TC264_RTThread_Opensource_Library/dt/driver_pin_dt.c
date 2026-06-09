/**
 * @file driver_pin_dt.c
 * @brief TC264D pin devicetree conversion layer.
 */

#include <string.h>
#include "driver_pin_dt.h"

static bool _port_number_from_dt_name(const char *port, uint8_t *port_num)
{
    if (port == NULL || port_num == NULL)
    {
        return false;
    }

    if (strcmp(port, "P00") == 0)
    {
        *port_num = 0U;
    }
    else if (strcmp(port, "P02") == 0)
    {
        *port_num = 2U;
    }
    else if (strcmp(port, "P10") == 0)
    {
        *port_num = 10U;
    }
    else if (strcmp(port, "P11") == 0)
    {
        *port_num = 11U;
    }
    else if (strcmp(port, "P13") == 0)
    {
        *port_num = 13U;
    }
    else if (strcmp(port, "P14") == 0)
    {
        *port_num = 14U;
    }
    else if (strcmp(port, "P15") == 0)
    {
        *port_num = 15U;
    }
    else if (strcmp(port, "P20") == 0)
    {
        *port_num = 20U;
    }
    else if (strcmp(port, "P21") == 0)
    {
        *port_num = 21U;
    }
    else if (strcmp(port, "P22") == 0)
    {
        *port_num = 22U;
    }
    else if (strcmp(port, "P23") == 0)
    {
        *port_num = 23U;
    }
    else if (strcmp(port, "P32") == 0)
    {
        *port_num = 32U;
    }
    else if (strcmp(port, "P33") == 0)
    {
        *port_num = 33U;
    }
    else
    {
        return false;
    }

    return true;
}

bool elab_driver_pin_resolve_dt(const elab_pin_dt_config_t *dt,
                                PIN_enum *pin_num)
{
    const char *port;
    uint8_t port_num;

    if (dt == NULL || pin_num == NULL || dt->name == NULL)
    {
        return false;
    }

    port = dt->port;

    if (!_port_number_from_dt_name(port, &port_num) || dt->pin > 15U)
    {
        return false;
    }

    *pin_num = (PIN_enum)((uint16_t)port_num * 32U + dt->pin);

    return true;
}
