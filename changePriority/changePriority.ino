#include<Arduino_FreeRTOS.h>

void task1(void*);
void task2(void*);

TaskHandle_t taskHandle1;
TaskHandle_t taskHandle2;

void setup() {
  Serial.begin(9600);
  xTaskCreate(task1, "task1", 100, NULL,1, &taskHandle1);
  xTaskCreate(task2, "task2", 100, NULL,2, &taskHandle2);
  vTaskStartScheduler();
}

void loop() {
  // Nothing in loop
}

void task1(void* param){
  UBaseType_t priority = uxTaskPriorityGet( NULL ); // Get current task priority
  Serial.print("Initial task1 priority ");
  Serial.println(priority);
  vTaskPrioritySet( taskHandle1, 2 );
  vTaskDelay(1000/portTICK_PERIOD_MS);
  priority = uxTaskPriorityGet( NULL );
  Serial.print("Final task1 priority ");
  Serial.println(priority);
  vTaskDelete(taskHandle1);
}

void task2(void* param){
  UBaseType_t priority = uxTaskPriorityGet( NULL ); // Get current task priority
  Serial.print("Initial task2 priority ");
  Serial.println(priority);
  vTaskPrioritySet( taskHandle2, 1);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  priority = uxTaskPriorityGet( NULL );
  Serial.print("Final task2 priority ");
  Serial.println(priority);
  vTaskDelete(taskHandle2);
}
