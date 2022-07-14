#include "inc/FreeRTOS.h"
#include "inc/task.h"
#include "inc/semphr.h"
#include "inc/STD_TYPES.h"
#include "inc/SS_interface.h"
#include "inc/timer_interface.h"


#define LIST_SIZE    10

uint8_t ListOfReading[LIST_SIZE] = {ZERO,ONE,TWO,THREE,FOUR,FIFE,SIX,SEVEN,EIGHT,NINE};

uint8_t reading = ZERO;
SemaphoreHandle_t s;


void TASK1(void* param) // display reading value
{
    while(1) {
        xSemaphoreTake(s, portMAX_DELAY);
        int local_reading = reading;
        xSemaphoreGive(s);

        SS_voidDisplayNum(0,local_reading,COMMON_CATHODE);
        vTaskDelay(2000);
    }
}

void TASK2(void* param) // set reading value
{
    static uint8_t i = 0;
    while(1) {
        reading = ListOfReading[i];
        i = (i+1)%LIST_SIZE;
        vTaskDelay(2000);
    }

}

void SetReading(void) // set reading value
{
    static uint8_t i = 0;

    BaseType_t HP_Task = pdFALSE;

    if(xSemaphoreTakeFromISR(s,&HP_Task) == pdPASS) {
        reading = ListOfReading[i];
        xSemaphoreGiveFromISR(s,&HP_Task);
    }


    i = (i+1)%LIST_SIZE; 
}

int main()
{
    SS_Init(0);

    global_int_enable();
	timer_enableInterrupt(OVERFLOW_FLAG);
	
	// timer configurations
	timer_init(); // timer mode is nomal
	timer_setInterval(256); // 266.24 ms
	timer_setCallback(SetReading);

    TaskHandle_t task1_handle;
    // TaskHandle_t task2_handle;

    xTaskCreate(TASK1, "Task1",configMINIMAL_STACK_SIZE,NULL,1,&task1_handle);
    // xTaskCreate(TASK2, "Task2",configMINIMAL_STACK_SIZE,NULL,0,&task2_handle);

    vSemaphoreCreateBinary(s);

	timer_start(TIMER0); // timer clk = tclk/1024 (timer tick time = 1.04 ms)
    
    vTaskStartScheduler();
    while (1)
    {
        
    }
    
    return 0;
}