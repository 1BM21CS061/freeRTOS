#if CONFIG_FREERTOS_UNICORE 
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif 

static int shared_var = 0;
static SemaphoreHandle_t mutex;  

void inc_task(void* parameters)
{
  int local_var;

  while(1)
  {
    if(xSemaphoreTake(mutex,0)==pdTRUE)
    {
      local_var = shared_var;
      local_var++;
      vTaskDelay(random(100,500)/portTICK_PERIOD_MS);
      shared_var = local_var;


      xSemaphoreGive(mutex);
      Serial.println(shared_var);
    }
    else 
    {
      // Serial.println("Waiting");
    }

  }
}

void setup() {
  randomSeed(analogRead(0));

  Serial.begin(300);

  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("Race Condition Demo");

  mutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(inc_task,"Increase Task A",1024,NULL,1,NULL,app_cpu);

  xTaskCreatePinnedToCore(inc_task,"Increase Task B",1024,NULL,1,NULL,app_cpu);

  vTaskDelete(NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}
