#include "bsp_dwt.h"

static uint32_t us_factor = 0;

void DWT_Delay_Init(void)
{
    /* 使能 DWT */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* 清零计数器 */
    DWT->CYCCNT = 0;

    /* 开启计数器 */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    /* SystemCoreClock = 72MHz */
    us_factor = SystemCoreClock / 1000000;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * us_factor;

    while ((DWT->CYCCNT - start) < ticks);
}


