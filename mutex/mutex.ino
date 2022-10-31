#include <Arduino_FreeRTOS.h>
#include "semphr.h"

//Handle for the mutex. It will be used to reference mutex
SemaphoreHandle_t  xMutex;

void setup()
{
  Serial.begin(9600);

// create mutex and assign it a already create handler
  xMutex = xSemaphoreCreateMutex();

/* create two instances of task "OutputTask" which are used to display string on arduino serial monitor.
* We passed name of task as a parameter to these tasks such as ""Task 1" and "Task 2".
* Priority of both the task is same.
* Resource used is emulated as delay.
*/
  xTaskCreate(OutputTask,"Printer Task 1", 100,"Task 1",1,NULL);
  xTaskCreate(OutputTask,"Printer Task 2", 100,"Task 2",1,NULL);
  vTaskStartScheduler();
}

// this is a definition of tasks
void OutputTask(void *pvParameters)
{
  char *pcStringToPrint;
  pcStringToPrint = (char *)pvParameters;
  while(1)
  {
    printer(pcStringToPrint);

  }
}
// this printer task send data to arduino serial monitor
//aslo it is shared resource between both instances of the tasks
void printer(const char* pcString)
{
  // take mutex
  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.print(pcString); // send string to serial monitor
  Serial.println(" waiting ....");
  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.print(pcString);
  Serial.println(" complete");
  xSemaphoreGive(xMutex); // release mutex
  vTaskDelay(pdMS_TO_TICKS(10));// allow other task to use resource; without this current task gets priority always
}
void loop(){}
