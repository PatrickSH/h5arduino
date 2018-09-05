#include <Arduino_FreeRTOS.h>


/*void TaskBlink( void *pvParameters );
void TaskBlinkSecond( void *pvParameters );

void setup() {

  //Create tasks
  xTaskCreate(
    TaskBlink
    ,  "Test"
    ,  128  // Stack size
    ,  NULL
    ,  1  // priority
    ,  NULL );

  xTaskCreate(
     TaskBlinkSecond
    ,  "Test1"
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );
}

void loop()
{

}

//Tasks

void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  // initialize analog pin 13 as an output.
  pinMode(A0, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(A0, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(A0, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 4000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void TaskBlinkSecond(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(A1, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(A1, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(A1, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}*/

void TaskBlink( void *pvParameters );
void TaskBlinkSecond( void *pvParameters );
void TaskReportToConsole( void *pvParameters );
static TaskHandle_t xTask1 = NULL, xTask2 = NULL, xTask3 = NULL;
String input, output;
String inp;
String content;
void setup() {
  Serial.begin(9600);
 Serial.println("Hej");

      xTaskCreate(
        TaskBlink
        ,  "Test"
        ,  128  // Stack size
        ,  NULL
        ,  1  // priority
        ,  &xTask1 );
    
      xTaskCreate(
         TaskBlinkSecond
        ,  "Test1"
        ,  128  // Stack size
        ,  NULL
        ,  tskIDLE_PRIORITY  // priority
        , &xTask2);

        xTaskCreate(
          TaskReportToConsole
          ,"Test3"
          ,128
          ,NULL
          ,tskIDLE_PRIORITY
          , &xTask3);
    
        vTaskStartScheduler();
 
}



void loop()
{
  char character;

  if(Serial.available()){
    String cmd = Serial.readStringUntil('\n');
    Serial.println(cmd);
  }
  


  /*//while(Serial.available() > 0){
    strcat(example,Serial.read());
    Serial.println(example);
    if(inp == "Blink"){
      Serial.println("Hje");
    }
  //}
  
  String text = Serial.readString();
  Serial.println(text);
    //if(input=='Blink'){
      //Create tasks

    //}
    //else{

    //}*/

}

//Tasks

void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  // initialize analog pin 13 as an output.
  pinMode(A0, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
     /* Send a notification to prvTask2(), bringing it out of the Blocked
        state. */
    
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    xTaskNotifyGive( xTask2 );
    /* Block to wait for prvTask2() to notify this task. */
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    digitalWrite(A0, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(A0, LOW);    // turn the LED off by making the voltage LOW
    
  }
}

void TaskBlinkSecond(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(A1, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
       /* Send a notification to prvTask2(), bringing it out of the Blocked
        state. */

    vTaskDelay( 3000 / portTICK_PERIOD_MS ); // wait for one second
    //xTaskNotifyGive( xTask1 );
    xTaskNotifyGive( xTask3 );
    /* Block to wait for prvTask2() to notify this task. */
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    digitalWrite(A1, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(A1, LOW);    // turn the LED off by making the voltage LOW
   
  }
}

void TaskReportToConsole(void *pvParameters)
{
  (void) pvParameters;
    for (;;) // A Task shall never return or exit.
    {
      vTaskDelay( 3000 / portTICK_PERIOD_MS ); // wait for one second
      xTaskNotifyGive( xTask1 );
      /* Block to wait for prvTask2() to notify this task. */
      ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
      Serial.println("Done");     
    }
}
