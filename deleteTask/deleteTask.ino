// Delete a Task
#include<Arduino_FreeRTOS.h>

// Forward declaring tasks
void task_Print1(void*);
void task_Print2(void*);

// Define task handle
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void setup() {
  // Set Buadrate of serial communication
  Serial.begin(9600);

  xTaskCreate(task_Print1, "Task1", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(task_Print2, "Task2", 100, NULL, 1, &TaskHandle_2);
  
}

void loop() {
  // empty function

}

void task_Print1(void* param){
  static int counter = 0;
  while(1){
    counter++;
    Serial.print(counter);Serial.println(". Task1");  
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void task_Print2(void* param){
  static int counter = 0;
  while(1){
    counter++;
    Serial.print(counter);Serial.println(". Task2");
    if(counter == 5){
      vTaskDelete(TaskHandle_2);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
