#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu = 1;
#endif 

void TestTask(void *paramter)
{
  while(1)
  {
    int a = 1;
    int b[100];

    for(int i=0;i<100;i++)
    {
      b[i] = a+i;
    }

    Serial.println(b[0]);

    //Print out remaining stack memory 
    Serial.print("High water mark(words):");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));


    //Print out number of free heap memory bytes before malloc
    Serial.print("Heap before malloc(bytes):");
    Serial.println(xPortGetFreeHeapSize());

    int *ptr = (int*)pvPortMalloc(1024*sizeof(int));

    if(ptr==NULL)
    {
      Serial.println("Not enough heap.");
    }
    else
    {
      for(int i=0;i<1024;i++)
      {
        *(ptr+i) = 3;
      }
    }

    //Print out number of free heap memory bytes after malloc
    Serial.print("Heap after malloc(bytes):");
    Serial.println(xPortGetFreeHeapSize());

    //Free up allocated memory
    vPortFree(ptr);

    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  vTaskDelay(1000/portTICK_PERIOD_MS);

  Serial.println("--------------------");
  
  xTaskCreatePinnedToCore(TestTask,"Test Task",1500,NULL,1,NULL,app_cpu);


  //Delete setup and loop
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
