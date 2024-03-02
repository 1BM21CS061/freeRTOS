#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu = 1;
#endif 

//Scheduling Demo
//const char msg[] = "Coffee Compiler Club welcomes you to today's podcast.";

//Handles to control the two tasks from a third task
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

int number = 0;
int temp = 0;

void startTask1(void *parameter)
{
  while(1)
  {
    number = 0;
    vTaskDelay(1000/portTICK_PERIOD_MS);
    int i = Serial.available();
    
    while(i>0)
    {
      temp = Serial.read() - '0';
      number += temp*pow(10,i-1);
      i--;
    }

    Serial.print("Updated LED delay to: ");
    Serial.println(number);
    vTaskSuspend(task_1);
  }
}

void startTask2(void *parameter)
{
  while(1)
  {
    digitalWrite(2,HIGH);
    vTaskDelay(number/portTICK_PERIOD_MS);
    digitalWrite(2,LOW);
    vTaskDelay(number/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(300);

  pinMode(2,OUTPUT);
  
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("--------------------");

  Serial.println("Setup and Loop task running on core");
  Serial.print(xPortGetCoreID());
  Serial.print(" With Priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  Serial.println("Multi LED Task Demo");
  Serial.println("Enter a number in milliseconds to change the LED delay.");

  Serial.println(app_cpu);

  xTaskCreatePinnedToCore(startTask1,"Task 1",1024,NULL,2,&task_1,app_cpu);
  xTaskCreatePinnedToCore(startTask2,"Task 2",1024,NULL,1,&task_2,app_cpu);
}

void loop() {
  if(Serial.available()>0)
  {
    vTaskResume(task_1);
  }
}
