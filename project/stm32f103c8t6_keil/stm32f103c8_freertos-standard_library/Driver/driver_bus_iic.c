/**
 * @file driver_bus_iic.c
 * @author ZC (387646983@qq.com)
 * @brief Software I2C driver.
 * @version 0.1
 * @date 2026-05-20
 */

/* ==================== [Includes] ========================================== */
#include "elab_log.h"
#include "elab_assert.h"
#include "elab_export.h"
#include "bsp_dwt.h"
#include "driver_bus.h"
#include "stm32f10x.h"

/* ==================== [Defines] =========================================== */
ELAB_TAG("DriverIIC");

#define SORT_I2C_PORT_RCC      RCC_APB2Periph_GPIOB
#define SOFT_I2C_PORT          GPIOB
#define SOFT_I2C_SCL_PIN       GPIO_Pin_6
#define SOFT_I2C_SDA_PIN       GPIO_Pin_7
#define SOFT_I2C_TIMEOUT       1000U
#define I2C_SCL_HIGH           GPIO_SetBits(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN)
#define I2C_SCL_LOW            GPIO_ResetBits(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN)
#define I2C_SDA_HIGH           GPIO_SetBits(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN)
#define I2C_SDA_LOW            GPIO_ResetBits(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN)
#define I2C_SDA                GPIO_ReadInputDataBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN)

/* ==================== [Static Prototypes] ================================= */
static int32_t _xfer(elab_i2c_bus_t *, uint16_t addr, elab_i2c_msg_t msg);
static elab_err_t _config(elab_i2c_bus_t *, elab_i2c_bus_config_t *config);

static void SoftI2C_SdaOut(void);
static void SoftI2C_SdaIn(void);
static void SoftI2C_Start(void);
static void SoftI2C_Stop(void);
static void SoftI2C_Send(uint8_t data);
static uint8_t SoftI2C_Read(void);
static uint8_t SoftI2C_WaitAck(void);
static void SoftI2C_Ack(void);
static void SoftI2C_NoAck(void);

/* ==================== [Static Variables] ================================== */

 static const elab_i2c_bus_ops_t pin_driver_ops =
{
    .xfer = _xfer,
    .config = _config,
};
/* ==================== [Public Functions] ================================== */
static void driver_i2c_bus_init(elab_i2c_bus_t *i2c_bus, const char *i2c_bus_name)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(SORT_I2C_PORT_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = SOFT_I2C_SCL_PIN | SOFT_I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SOFT_I2C_PORT, &GPIO_InitStructure);

    I2C_SCL_HIGH;
    I2C_SDA_HIGH;

    elab_i2c_bus_register(i2c_bus, i2c_bus_name, &pin_driver_ops, NULL);
}


void driver_i2c_bus_register(elab_i2c_bus_t *i2c_bus, const char *i2c_bus_name)
{
    driver_i2c_bus_init(i2c_bus, i2c_bus_name);
}

/* ==================== [Static Functions] ================================== */
static void SoftI2C_SdaOut(void)
{
    GPIO_InitTypeDef GPIO_InitTypeStruct;

    RCC_APB2PeriphClockCmd(SORT_I2C_PORT_RCC, ENABLE);
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitTypeStruct.GPIO_Pin = SOFT_I2C_SDA_PIN;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SOFT_I2C_PORT, &GPIO_InitTypeStruct);
}

static void SoftI2C_SdaIn(void)
{
    GPIO_InitTypeDef GPIO_InitTypeStruct;

    RCC_APB2PeriphClockCmd(SORT_I2C_PORT_RCC, ENABLE);
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitTypeStruct.GPIO_Pin = SOFT_I2C_SDA_PIN;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SOFT_I2C_PORT, &GPIO_InitTypeStruct);
}

static void SoftI2C_Start(void)
{
    SoftI2C_SdaOut();
    I2C_SDA_HIGH;
    I2C_SCL_HIGH;
    delay_us(4);
    I2C_SDA_LOW;
    delay_us(4);
    I2C_SCL_LOW;
}

static void SoftI2C_Stop(void)
{
    SoftI2C_SdaOut();
    I2C_SDA_LOW;
    I2C_SCL_HIGH;
    delay_us(4);
    I2C_SDA_HIGH;
    delay_us(4);
}

static void SoftI2C_Send(uint8_t data)
{
    uint8_t mask;

    SoftI2C_SdaOut();
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
        if ((data & mask) != 0)
        {
            I2C_SDA_HIGH;
        }
        else
        {
            I2C_SDA_LOW;
        }

        delay_us(2);
        I2C_SCL_HIGH;
        delay_us(2);
        I2C_SCL_LOW;
    }
}

static uint8_t SoftI2C_Read(void)
{
    uint8_t mask;
    uint8_t data = 0;

    I2C_SDA_HIGH;
    SoftI2C_SdaIn();
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
        delay_us(1);
        I2C_SCL_HIGH;
        delay_us(1);
        if (I2C_SDA == Bit_SET)
        {
            data |= mask;
        }
        I2C_SCL_LOW;
    }

    return data;
}

static uint8_t SoftI2C_WaitAck(void)
{
    uint16_t timeout = 0;

    I2C_SDA_HIGH;
    SoftI2C_SdaIn();
    delay_us(1);
    I2C_SCL_HIGH;
    delay_us(1);

    while (I2C_SDA == Bit_SET)
    {
        timeout++;
        if (timeout > SOFT_I2C_TIMEOUT)
        {
            SoftI2C_Stop();
            return 1;
        }
        delay_us(1);
    }

    I2C_SCL_LOW;
    delay_us(1);
    return 0;
}

static void SoftI2C_Ack(void)
{
    I2C_SCL_LOW;
    SoftI2C_SdaOut();
    I2C_SDA_LOW;
    delay_us(1);
    I2C_SCL_HIGH;
    delay_us(4);
    I2C_SCL_LOW;
    delay_us(4);
    I2C_SDA_HIGH;
}

static void SoftI2C_NoAck(void)
{
    I2C_SCL_LOW;
    SoftI2C_SdaOut();
    I2C_SDA_HIGH;
    delay_us(1);
    I2C_SCL_HIGH;
    delay_us(4);
    I2C_SCL_LOW;
    delay_us(4);
}

static elab_err_t _config(elab_i2c_bus_t *me, elab_i2c_bus_config_t *config)
{
    (void)me;

    if (config->addr_10bit)
    {
        return ELAB_ERR_INVALID;
    }

    return ELAB_OK;
}

static int32_t _xfer(elab_i2c_bus_t *me, uint16_t addr, elab_i2c_msg_t msg)
{
    uint16_t i;
    uint8_t rw_addr;

    elab_assert(me != NULL);
    elab_assert(msg.buffer != NULL || msg.len == 0);

    rw_addr = (uint8_t)((addr << 1) | (msg.write ? 0U : 1U));

    SoftI2C_Start();
    SoftI2C_Send(rw_addr);
    if (SoftI2C_WaitAck() != 0)
    {
        return ELAB_ERROR;
    }

    if (msg.write)
    {
        for (i = 0; i < msg.len; i++)
        {
            SoftI2C_Send(msg.buffer[i]);
            if (SoftI2C_WaitAck() != 0)
            {
                return ELAB_ERROR;
            }
        }
    }
    else
    {
        for (i = 0; i < msg.len; i++)
        {
            msg.buffer[i] = SoftI2C_Read();
            if (i + 1U < msg.len)
            {
                SoftI2C_Ack();
            }
            else
            {
                SoftI2C_NoAck();
            }
        }
    }

    SoftI2C_Stop();
    elab_i2c_xfer_end(me);
    return (int32_t)msg.len;
}

/* ----------------------------- end of file -------------------------------- */
