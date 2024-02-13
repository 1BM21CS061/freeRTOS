#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu = 1;
#endif 

static const int led = 2;

void toggleLED(void *parameter)
{
  while(1)
  {
    digitalWrite(led,HIGH);
    vTaskDelay(5000/portTICK_PERIOD_MS);
    digitalWrite(led,LOW);
    vTaskDelay(5000/portTICK_PERIOD_MS);
    Serial.println("Task 1");
  }
}

void toggleLED1(void *parameter)
{
  while(1)
  {
    vTaskDelay(2000/portTICK_PERIOD_MS);
    digitalWrite(led,LOW);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    digitalWrite(led,HIGH);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    Serial.println("Task 2");
  }
}

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200);

  //Task to run forever and pin the task to one of the cores
  xTaskCreatePinnedToCore(toggleLED,        //Function called
                          "Toggle LED",     //Name of Task
                          1024,             //Stack Size(bytes)
                          NULL,             //Parameter to pass to function
                          1,                //Task Priority(0 to configMAX_PRIORITIES-1)
                          NULL,             //Task Handle (handle this task from another task or execution loop)        
                          app_cpu);         //Run on one core

  xTaskCreatePinnedToCore(toggleLED1,"Toggle LED 1",1024,NULL,1,NULL,app_cpu);
}

void loop() {
  // put your main code here, to run repeatedly:

}
