#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu = 1;
#endif 

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
char *ptr;
int i = 0;

void TaskA(void *paramter)
{
  while(1)
  {
    vTaskDelay(2000/portTICK_PERIOD_MS);
    if(Serial.available()>0)
    {
      i = Serial.available();
      
      ptr = (char*)pvPortMalloc(i*sizeof(char));

      for(int j=0;j<i;j++)
      {
        *(ptr+j) = Serial.read();
      }

      vTaskResume(task_2);
    }
  }
}

void TaskB(void *paramter)
{
  while(1)
  {
    for(int j=0;j<i;j++)
    {
      Serial.print(*(ptr+j));
    }

    Serial.println();

    vPortFree(ptr);
    ptr = NULL;

    Serial.println("Enter a string");

    vTaskSuspend(task_2);
  }
}

void setup() {
  Serial.begin(115200);

  vTaskDelay(1000/portTICK_PERIOD_MS);

  Serial.print("freeRTOS Heap Demo");
  Serial.println("--------------------");

  Serial.println("Enter a string");
  
  xTaskCreatePinnedToCore(TaskA,"TaskA",2000,NULL,2,&task_1,app_cpu);
  xTaskCreatePinnedToCore(TaskB,"TaskB",2000,NULL,1,&task_2,app_cpu);


  vTaskSuspend(task_2);
  
  //Delete setup and loop
  vTaskDelete(NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}