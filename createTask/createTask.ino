#include<Arduino_FreeRTOS.h>

void task1(void *param);
void task2(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

void task1(void* param){ // Task-1
  while(1){ //Infinite loop
    Serial.println("Task1");
    vTaskDelay(1000/portTICK_PERIOD_MS); // 1000ms delay
  }
}

void task2(void* param){ // Task-2
  while(1){ //Infinite loop
    Serial.println("Task2");
    vTaskDelay(1000/portTICK_PERIOD_MS); // 1sec delay
  }
}

void setup() {
  Serial.begin(9600); // set baudrate
  Serial.print("tick period is ");Serial.println(portTICK_PERIOD_MS);//
  xTaskCreate(task1, "Task1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(task2, "Task2", 100, NULL, 2, &Task_Handle2);
}

void loop() {
  // No operations

}
