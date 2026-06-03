/**
 * @file driver_bus_iic.c
 * @author ZC (387646983@qq.com)
 * @brief TC264D hardware I2C bus driver.
 * @version 0.2
 * @date 2026-06-01
 */

/* ==================== [Includes] ========================================== */
#include "elab_log.h"
#include "elab_assert.h"
#include "elab_export.h"
#include "driver_bus.h"

#include "IfxI2c_I2c.h"

/* ==================== [Defines] =========================================== */
ELAB_TAG("DriverIIC");

#ifndef DRIVER_I2C_DEFAULT_CLOCK_HZ
#define DRIVER_I2C_DEFAULT_CLOCK_HZ         100000U
#endif

/*
 * TC264D I2C0 hardware pin options:
 *   SCL/SDA: P02.5/P02.4, P13.1/P13.2, P15.4/P15.5
 * Override these macros if the board uses a different hardware I2C pin pair.
 */
#ifndef DRIVER_I2C_SCL_PIN
#define DRIVER_I2C_SCL_PIN                  (&IfxI2c0_SCL_P02_5_INOUT)
#endif

#ifndef DRIVER_I2C_SDA_PIN
#define DRIVER_I2C_SDA_PIN                  (&IfxI2c0_SDA_P02_4_INOUT)
#endif

#ifndef DRIVER_I2C_PAD_DRIVER
#define DRIVER_I2C_PAD_DRIVER               IfxPort_PadDriver_cmosAutomotiveSpeed1
#endif

/* ==================== [Static Prototypes] ================================= */
static int32_t _xfer(elab_i2c_bus_t *me, uint16_t addr, elab_i2c_msg_t msg);
static elab_err_t _config(elab_i2c_bus_t *me, elab_i2c_bus_config_t *config);
static void driver_i2c_init_module(uint32_t clock);
static IfxI2c_I2c_Status driver_i2c_xfer_once(uint16_t addr,
                                                elab_i2c_msg_t msg);

/* ==================== [Static Variables] ================================== */
static const elab_i2c_bus_ops_t i2c_bus_ops =
{
    .xfer = _xfer,
    .config = _config,
};

static IfxI2c_Pins i2c0_pins =
{
    DRIVER_I2C_SCL_PIN,
    DRIVER_I2C_SDA_PIN,
    DRIVER_I2C_PAD_DRIVER,
};


static IfxI2c_I2c i2c0_handle;
static bool i2c0_initialized = false;

/* ==================== [Public Functions] ================================== */
static void driver_i2c_bus_init(elab_i2c_bus_t *i2c_bus, const char *i2c_bus_name)
{
    elab_assert(i2c_bus_name != NULL);

    if (elab_device_valid(i2c_bus_name))
    {
        return;
    }

    elab_i2c_bus_register(i2c_bus, i2c_bus_name, &i2c_bus_ops, &i2c0_pins);
}

void driver_i2c_bus_register(elab_i2c_bus_t *i2c_bus, const char *i2c_bus_name)
{
    driver_i2c_bus_init(i2c_bus, i2c_bus_name);
}



static void driver_i2c_init_module(uint32_t clock)
{
    IfxI2c_I2c_Config config;

    if (clock == 0U)
    {
        clock = DRIVER_I2C_DEFAULT_CLOCK_HZ;
    }

    IfxI2c_I2c_initConfig(&config, &MODULE_I2C0);
    config.pins = &i2c0_pins;
    config.baudrate = (float32)clock;
    IfxI2c_I2c_initModule(&i2c0_handle, &config);

    i2c0_initialized = true;
}

static elab_err_t _config(elab_i2c_bus_t *me, elab_i2c_bus_config_t *config)
{
    (void)me;

    elab_assert(config != NULL);

    if (config->addr_10bit)
    {
        return ELAB_ERR_INVALID;
    }

    driver_i2c_init_module(config->clock);

    return ELAB_OK;
}

static IfxI2c_I2c_Status driver_i2c_xfer_once(uint16_t addr,
                                                elab_i2c_msg_t msg)
{
    uint8_t dummy = 0U;
    IfxI2c_I2c_Device device;
    IfxI2c_I2c_deviceConfig device_config;

    IfxI2c_I2c_initDeviceConfig(&device_config, &i2c0_handle);
    device_config.deviceAddress = (uint8_t)(addr << 1);
    IfxI2c_I2c_initDevice(&device, &device_config);

    if (msg.buffer == NULL)
    {
        msg.buffer = &dummy;
    }

    if (msg.write)
    {
        return IfxI2c_I2c_write(&device, msg.buffer, (Ifx_SizeT)msg.len);
    }

    return IfxI2c_I2c_read(&device, msg.buffer, (Ifx_SizeT)msg.len);
}

static int32_t _xfer(elab_i2c_bus_t *me, uint16_t addr, elab_i2c_msg_t msg)
{
    IfxI2c_I2c_Status status;

    elab_assert(me != NULL);
    elab_assert(msg.buffer != NULL || msg.len == 0U);

    if (addr > 0x7FU)
    {
        return ELAB_ERR_INVALID;
    }

    if (!i2c0_initialized)
    {
        driver_i2c_init_module(DRIVER_I2C_DEFAULT_CLOCK_HZ);
    }

    status = driver_i2c_xfer_once(addr, msg);
    if (status != IfxI2c_I2c_Status_ok)
    {
        return ELAB_ERROR;
    }

    elab_i2c_xfer_end(me);

    return (int32_t)msg.len;
}

/* ----------------------------- end of file -------------------------------- */
