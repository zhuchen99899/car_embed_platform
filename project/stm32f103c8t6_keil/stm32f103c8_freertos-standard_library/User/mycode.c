#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "stdint.h"
#include "queue.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "semphr.h"

#include "elab_log.h"
ELAB_TAG("code");
SemaphoreHandle_t sem;
TaskHandle_t task3Hanle;

void task1(void *arg)
{
    char *p = "key1";
	while(1)
	{
		xTaskNotify(task3Hanle,123,eSetBits);
        // xTaskNotifyGive(task3Hanle);
        elog_debug("xTaskNotify");
        vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void task3(void *arg)
{
    uint32_t notifyVal = 0;
        
    while(1)
    {
        xTaskNotifyWait(0x0,
                        0xFFFFFFFFUL ,
                        &notifyVal,
                        portMAX_DELAY );
        // ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        elog_debug("receive:%d",notifyVal);
        LED1_TOGGLE;
    }
}

void myCodeStart(void)
{
    xTaskCreate(task1,"task1",100,"task1",3,NULL);
	xTaskCreate(task3,"task2",100,"task2",3,&task3Hanle);
}

