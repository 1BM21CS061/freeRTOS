#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

static SemaphoreHandle_t mutex;

// Blink LED based on rate passed by parameter
void blinkLED(void *parameters) {
  // Copy the parameter into a local variable
  int num = *(int *)parameters;

  // Print the parameter
  Serial.print("Received: ");
  Serial.println(num);

  xSemaphoreGive(mutex);

  Serial.println("check2");

  // Configure the LED pin
  pinMode(2, OUTPUT);

  // Blink forever and ever
  while (1) {
    digitalWrite(2, HIGH);
    vTaskDelay(num / portTICK_PERIOD_MS);
    digitalWrite(2, LOW);
    vTaskDelay(num / portTICK_PERIOD_MS);
  }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {

  long int delay_arg;

  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  
  Serial.println();
  Serial.println("---FreeRTOS Mutex Challenge---");
  Serial.println("Enter a number for delay (milliseconds)");

  // Wait for input from Serial
  while (Serial.available() <= 0);

  // Read integer value
  delay_arg = Serial.parseInt();
  Serial.print("Sending: ");
  Serial.println(delay_arg);

  mutex = xSemaphoreCreateMutex();

  if(xSemaphoreTake(mutex,portMAX_DELAY)==pdTRUE){
    Serial.println("Mutex obtained");
  }
  else
  {
    Serial.println("Mutex not obtained");
  }
  
  // Start task 1
  xTaskCreatePinnedToCore(blinkLED,
                          "Blink LED",
                          1024,
                          (void *)&delay_arg,
                          1,
                          NULL,
                          app_cpu);

  xSemaphoreTake(mutex,portMAX_DELAY);

  // Show that we accomplished our task of passing the stack-based argument
  Serial.println("Done!");
}

void loop() {
  
  // Do nothing but allow yielding to lower-priority tasks
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
