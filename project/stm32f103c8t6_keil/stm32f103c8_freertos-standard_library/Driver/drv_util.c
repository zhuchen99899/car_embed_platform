/*
 * eLesson Project
 * Copyright (c) 2023, EventOS Team, <event-os@outlook.com>
 */

/* includes ----------------------------------------------------------------- */
#include <stdlib.h>
#include <string.h>
#include "drv_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/* public functions --------------------------------------------------------- */
/**
  * @brief  Check whether a GPIO pin name is valid.
  * @param  name GPIO pin name string, format: "A.00" ~ "F.15".
  * @retval true  The pin name format and pin number are valid.
  * @retval false The pin name format or pin number is invalid.
  *
  * @note   The caller should make sure name is not NULL.
  */
bool check_pin_name_valid(const char *name)
{
    bool valid = true;

    if ((strlen(name) != 4) || name[1] != '.')
    {
        valid = false;
    }
    else if (!(name[0] >= 'A' && name[0] <= 'F'))
    {
        valid = false;
    }
    else if (!(name[2] >= '0' && name[2] <= '9'))
    {
        valid = false;
    }
    else if (!(name[3] >= '0' && name[3] <= '9'))
    {
        valid = false;
    }

    char *str_num = (char *)&name[2];
    int32_t pin_num = atoi(str_num);
    if (pin_num < 0 || pin_num >= 16)
    {
        valid = false;
    }

    return valid;
}

/**
  * @brief  Get GPIO port instance from a pin name.
  * @param  name GPIO pin name string, format: "A.xx" ~ "F.xx".
  * @retval GPIO port pointer, such as GPIOA/GPIOB/GPIOC.
  *
  * @note   Call check_pin_name_valid() before this function to avoid invalid
  *         table indexing.
  */
GPIO_TypeDef *get_port_from_name(const char *name)
{
    static const GPIO_TypeDef *port_table[] =
    {
        GPIOA, GPIOB, GPIOC, GPIOD, NULL, GPIOF,
    };

    return (GPIO_TypeDef *)port_table[name[0] - 'A'];
}

/**
  * @brief  Get GPIO pin mask from a pin name.
  * @param  name GPIO pin name string, format: "A.00" ~ "F.15".
  * @retval GPIO pin mask, such as GPIO_Pin_0/GPIO_Pin_15.
  *
  * @note   Call check_pin_name_valid() before this function. After the format
  *         is checked, atoi() can safely parse the pin number field.
  */
uint16_t get_pin_from_name(const char *name)
{
    char *str_num = (char *)&name[2];
    int32_t pin_num = atoi(str_num);

    return (uint16_t)(1 << pin_num);
}

/**
  * @brief  Enable GPIO peripheral clock according to a pin name.
  * @param  name GPIO pin name string, format: "A.xx" ~ "C.xx".
  * @retval None.
  *
  * @note   This helper currently enables clocks for GPIOA/GPIOB/GPIOC only.
  */
void gpio_clock_enable(const char *name)
{

    /* Enable the clock. */
    if (get_port_from_name(name) == GPIOA)
    {
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (get_port_from_name(name) == GPIOB)
    {
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if (get_port_from_name(name) == GPIOC)
    {
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
    }


}

#ifdef __cplusplus
}
#endif

/* ----------------------------- end of file -------------------------------- */
