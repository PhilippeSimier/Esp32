#include "freertos/event_groups.h"

// define event bits
#define TASK_1_BIT ( 1 << 0 ) //1
#define TASK_2_BIT ( 1 << 1 ) //10
#define TASK_3_BIT ( 1 << 2 ) //100
#define ALL_SYNC_BITS (TASK_1_BIT | TASK_2_BIT | TASK_3_BIT) //111

hw_timer_t * timer = NULL;  // create a hardware timer
EventGroupHandle_t eg;      // create event group
int count = 0;

// timer ISR callback
void IRAM_ATTR onTimer()
{
  BaseType_t xHigherPriorityTaskWoken; 
  count++;
  switch (count)
  {
    case 2:           // set event bit of task1
      xEventGroupSetBitsFromISR(eg, TASK_1_BIT, &xHigherPriorityTaskWoken);
      break;

    case 3:         // set event bit of task 2 and 3
      xEventGroupSetBitsFromISR(eg, TASK_2_BIT | TASK_3_BIT, &xHigherPriorityTaskWoken);
      break ;

    case 4:         // reset counter to start again
      count = 0;
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(9600);
  eg = xEventGroupCreate();

  timer = timerBegin(0, 80, true);               // 1 tick takes 1/(80MHZ/80) → 1 microsecond
  timerAttachInterrupt(timer, &onTimer, true);   // attach onTimer function to our timer
  timerAlarmWrite(timer, 1000000, true);         // call onTimer function every second 1000000 ticks  true – repeat the alarm
  timerAlarmEnable(timer);                       // start timer alarm
  Serial.println("start timer");

  xTaskCreate(
    task1,      /* Task function. */
    "task1",    /* name of task. */
    10000,      /* Stack size of task */
    NULL,       /* parameter of the task */
    1,          /* priority of the task */
    NULL);      /* Task handle to keep track of created task */

  xTaskCreate(
    task2,      /* Task function. */
    "task2",    /* name of task. */
    10000,      /* Stack size of task */
    NULL,       /* parameter of the task */
    1,          /* priority of the task */
    NULL);      /* Task handle to keep track of created task */

  xTaskCreate(
    task3,      /* Task function. */
    "task3",    /* name of task. */
    10000,      /* Stack size of task */
    NULL,       /* parameter of the task */
    1,          /* priority of the task */
    NULL);      /* Task handle to keep track of created task */
}

void loop() {}

void task1( void * parameter )
{
  for (;;) { 
    EventBits_t xbit = xEventGroupWaitBits(eg, TASK_1_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
    Serial.print("task1 has event bit: "); 
    Serial.println(xbit);
  }
  vTaskDelete( NULL );
}

void task2( void * parameter )
{
  for (;;) { 
    EventBits_t xbit = xEventGroupWaitBits(eg, TASK_2_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
    Serial.print("task2 has event bit: "); 
    Serial.println(xbit);
  }
  vTaskDelete( NULL );
}

void task3( void * parameter )
{
  for (;;) { 
    EventBits_t xbit = xEventGroupWaitBits(eg, TASK_3_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
    Serial.print("task3 has even bit: "); 
    Serial.println(xbit);
  }
  vTaskDelete( NULL );
}
