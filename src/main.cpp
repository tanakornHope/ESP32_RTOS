#include <Arduino.h>
#include <esp_task_wdt.h>

TaskHandle_t Task1 = NULL;
TaskHandle_t Task2 = NULL;
TaskHandle_t Task3 = NULL;
TaskHandle_t Task4 = NULL;

void f4_Task(void *pvParam);
void f3_Task(void *pvParam);
void f2_Task(void *pvParam);
void f1_Task(void *pvParam);

void setup()
{
  Serial.begin(115200);
  esp_task_wdt_init(4, true);
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i <= 10; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }

  //delay(2000);
  xTaskCreatePinnedToCore(f1_Task, "func1_Task", 1000, NULL, 2, &Task1, 1);
  xTaskCreatePinnedToCore(f2_Task, "func2_Task", 1000, NULL, 4, &Task2, 0);
  xTaskCreatePinnedToCore(f3_Task, "func3_Task", 1000, NULL, 3, &Task3, 0);
  xTaskCreatePinnedToCore(f4_Task, "func4_Task", 1000, NULL, 1, &Task4, 0);
}

void loop()
{
  Serial.println("main loop.");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
}

void f4_Task(void *pvParam)
{
  vTaskDelay(500);
  /* Serial.println(String("Hello from TASK4 , Priority is : ") + uxTaskPriorityGet(Task4));
  int newPriority = 0;
  Serial.println(String("NOW WE CHANGE PRIORITY OF TASK4 TO BE : ") + newPriority );      
  vTaskPrioritySet(Task4,newPriority);
  
  Serial.println(String("Hello again from TASK4 , then delete TASK4 !"));
  vTaskDelete(NULL); */
  Serial.println("Hello From Task#4");
  vTaskDelete(Task4);
}

void f3_Task(void *pvParam)
{
  vTaskDelay(500);
  /* Serial.println(String("Hello from TASK3 , then Suspend TASK2 & TASK3 !"));
  vTaskSuspend(Task2); 
  vTaskSuspend(NULL);       

  Serial.println(String("Hello again from TASK3 , then delete TASK3 !"));
  vTaskDelete(NULL); */
  Serial.println("Hello From Task#3");
  vTaskDelete(Task3);
}

void f2_Task(void *pvParam)
{
  vTaskDelay(500);
  /* Serial.println(String("Hello from TASK2 , then Resume TASK3 !"));
  vTaskResume(Task3);       

  Serial.println(String("Hello again from TASK2 , then delete TASK2 !"));
  vTaskDelete(Task2); */
  Serial.println("Hello From Task#2");
  vTaskDelete(Task2);
}

void f1_Task(void *pvParam)
{
  vTaskDelay(500);
  /* Serial.println(String("Hello from TASK1 , then Resume TASK2 !"));
  vTaskResume(Task2);       

  Serial.println(String("Hello again from TASK1 , then delete TASK1 !"));
  vTaskDelete(NULL); */
  Serial.println("Hello From Task#1");

  while (true)
  {
    Serial.println("f1 task");
    vTaskDelay(1);
  }

  vTaskDelete(Task1);
}