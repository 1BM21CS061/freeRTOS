#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const uint8_t msg_queue_len = 5;

static QueueHandle_t msg_queue1;
static QueueHandle_t msg_queue2;

void TaskA(void *parameters) {
  char item[10];

  while (1) {
    if (xQueueReceive(msg_queue2, (void *)&item, 0) == pdTRUE) {
      Serial.println(item);
    } 
    
    if (Serial.available() > 0) {
      String input = Serial.readString();

      char *token = strtok((char *)input.c_str(), " ");  // Tokenize based on space

      if (strcmp(token, "delay") == 0) {
        token = strtok(NULL, " ");
        int value = atoi(token);

        if (xQueueSend(msg_queue1, (void *)&value, 10) != pdTRUE) {
          Serial.println("Queue 1 full");
        }
      } else {
        Serial.println(input);
      }
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }

}

void TaskB(void *parameters) {
  int item;
  int delay = 0;
  int count = 0;
  String message = "Blinked";

  while (1) {
    if (xQueueReceive(msg_queue1, (void *)&item, 0) == pdTRUE) {
      delay = item;
    } 

    digitalWrite(2, HIGH);
    vTaskDelay(delay/portTICK_PERIOD_MS);
    digitalWrite(2,LOW);
    vTaskDelay(delay/portTICK_PERIOD_MS);

    count++;

    if(count==10)
    {
      if(xQueueSend(msg_queue2,(void*)&message,10)!=pdTRUE)
      {
        Serial.println("Could'nt send message to queue2");
      }
      count = 0;
    }

    vTaskDelay(3000/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(300);
  pinMode(2,OUTPUT);
  vTaskDelay(2000 / portTICK_PERIOD_MS);

  Serial.println();
  Serial.println("Queue Demo");

  msg_queue1 = xQueueCreate(msg_queue_len, 2*sizeof(int));
  msg_queue2 = xQueueCreate(msg_queue_len, 2*sizeof(int));

  xTaskCreatePinnedToCore(TaskA, "Task A", 1024, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(TaskB, "Task B", 1024, NULL, 1, NULL, app_cpu);

  vTaskDelete(NULL);
}

void loop() {
  
}