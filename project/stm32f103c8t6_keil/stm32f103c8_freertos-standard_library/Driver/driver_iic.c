/**
 * @file driver_iic.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-20
 * @note 不在中断里跑 IIC
 *        不在软件定时器里跑 IIC
 *        不长时间关中断
 *        所有等待加 timeout
         访问总线加 mutex
 * 
 */

/* ==================== [Includes] ========================================== */
#include "elab_log.h"
#include "elab_assert.h"
#include "elab_i2c.h"
#include "stm32f10x.h"
/* ==================== [Defines] ========================================== */
ELAB_TAG("DriverIIC");

#define SORT_I2C_PORT_RCC   RCC_APB2Periph_GPIOB
#define SOFT_I2C_PORT        GPIOB
#define SOFT_I2C_SCL_PIN     GPIO_Pin_6
#define SOFT_I2C_SDA_PIN     GPIO_Pin_7
#define SOFT_I2C_TIMEOUT     1000

#define I2C_SCL_HIGH      GPIO_SetBits(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN)
#define I2C_SCL_LOW       GPIO_ResetBits(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN)
#define I2C_SDA_HIGH      GPIO_SetBits(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN)
#define I2C_SDA_LOW       GPIO_ResetBits(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN)

#define I2C_SDA           
#define I2C_SCL


/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */
static int32_t _xfer(elab_i2c_bus_t *, uint16_t addr, elab_i2c_msg_t msg);
static elab_err_t _config(elab_i2c_bus_t *, elab_i2c_bus_config_t *config);
/* ==================== [Static Variables] ========================================== */
static const elab_i2c_bus_ops_t pin_driver_ops =
{
    .xfer = _xfer,
    .config = _config,
};
/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */

static void driver_i2c_bus_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(SORT_I2C_PORT_RCC, ENABLE);   //使能PB端口时钟
    GPIO_InitStructure.GPIO_Pin = SOFT_I2C_SCL_PIN | SOFT_I2C_SDA_PIN;	//端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //50M
    GPIO_Init(SOFT_I2C_PORT, &GPIO_InitStructure);					//根据设定参数初始化GPIOB

}

INIT_EXPORT(driver_i2c_bus_init, EXPORT_LEVEL_BSP);


void SDA_OUT(void)
{ 
  GPIO_InitTypeDef GPIO_InitTypeStruct;  
  RCC_APB2PeriphClockCmd(SORT_I2C_PORT_RCC,ENABLE);  
  GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;  
  GPIO_InitTypeStruct.GPIO_Pin=SOFT_I2C_SDA_PIN;  
  GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;  
  GPIO_Init(SOFT_I2C_PORT,&GPIO_InitTypeStruct); 
}

void SDA_IN(void)  
{
  GPIO_InitTypeDef GPIO_InitTypeStruct;  
  RCC_APB2PeriphClockCmd(SORT_I2C_PORT_RCC,ENABLE);       
  GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
  GPIO_InitTypeStruct.GPIO_Pin=SOFT_I2C_SDA_PIN;  
  GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;  
  GPIO_Init(SOFT_I2C_PORT,&GPIO_InitTypeStruct);  
} 

static void SoftI2C_Start(void)
{
    SDA_OUT();
    I2C_SDA_HIGH;
    I2C_SCL_HIGH;
    delay_us(4);
    I2C_SDA_LOW;
    delay_us(4);
    I2C_SCL_LOW;
}

static void SoftI2C_Stop(void)
{
    SDA_OUT();
    I2C_SDA_LOW;
    I2C_SCL_HIGH;
    delay_us(4);
    I2C_SDA_HIGH;
    delay_us(4);
    I2C_SCL_LOW;
}

void i2c_send(uint8_t data)
{
    uint8_t mask;

    SDA_OUT();

    for (mask = 0x80; mask != 0; mask >>= 1)
    {
        if (data & mask)
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

uint8_t i2c_read(void)
{
   unsigned char mask;
   unsigned char dat;
   I2C_SDA_HIGH;                     //释放总线准备接收
     SDA_IN();
   for(mask=0x80;mask!=0;mask>>=1)
   {
      delay_us(1);
      I2C_SCL_HIGH;
      if(I2C_SDA==1)
      {
         dat|=mask;
      }
      else
      {
         dat&=~mask;
      }
      I2C_SCL_LOW;
   }
   return dat;
}

static elab_err_t _config(elab_i2c_bus_t *me, elab_i2c_bus_config_t *config)
{
    (void)me;
    (void)config;

    /* TODO */

    return ELAB_OK;
}




static int32_t _xfer(elab_i2c_bus_t *me, uint16_t addr, elab_i2c_msg_t msg)
{

    static 

    I2C_HandleTypeDef *i2c = (I2C_HandleTypeDef *)me->super.user_data;
    HAL_StatusTypeDef status = HAL_OK;

    if (msg.write)
    {
        status = HAL_I2C_Master_Transmit_IT(i2c, addr, msg.buffer, msg.len);
    }
    else
    {
        status = HAL_I2C_Master_Receive_IT(i2c, addr, msg.buffer, msg.len);
    }
    (void)status;

    return (int32_t)msg.len;
}