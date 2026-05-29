#include "bsp_usart.h"
#include "bsp_key.h"
#include "bsp_dwt.h"
#include "elab_log.h"
#include "elab_export.h"
#include "cmsis_os.h"
ELAB_TAG("Main");
/*Function definition*/


static void Callback_LEDTOGGLE(void* pvParameters)
{
	while(1)
	{
	//LED1_TOGGLE;
  //elog_debug("toggle");
	osDelay(500);
	}

}


/*Hardware initialization*/
static void BSP_Init(void)
{
  /*Use this priority grouping uniformly, never group again
  * 4 bits for pre-emption priority
  */
  

  
  /*Serial port initialization*/
  USART_Config();
  DWT_Delay_Init();

}


void export_zero(void)
{

elog_debug("export_zero");
}
ELAB_INIT_EXPORT(export_zero,0);

void test_export(void)
{

  /*Key initialization*/
  Key_GPIO_Config();
}
ELAB_INIT_EXPORT(test_export,EXPORT_DRVIVER);

static const osThreadAttr_t thread_test = 
{
    .name = "ThreadTest1",
    .attr_bits = osThreadDetached,
    .priority = osPriorityNormal,
    .stack_size = 2048,
};


int main(void)
{  

  BSP_Init();
  osThreadNew(Callback_LEDTOGGLE, NULL, &thread_test);
	elab_run();
  while(1);
}








/*********************************************END OF FILE**********************/


