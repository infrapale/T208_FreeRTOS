//****************************************************************************
// FreeRTOS for AVR MCU's Uno, Mega
//****************************************************************************
// Based on a library example in Arduino IDE
// You need to install the Arduino_FreeRTOS using the library manager first
//****************************************************************************
//  Tom Hoglund 2019-06-13: I added 2 task to see how much Uno can take. Working OK
//****************************************************************************
//  Github: https://github.com/infrapale/T208_FreeRTOS.git
//  Github: git@github.com:infrapale/T208_FreeRTOS.git
//****************************************************************************
#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void TaskCount( void *pvParameters );
void TaskPrintCount( void *pvParameters );
unsigned int counter;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  counter = 0;

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );

  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1  // priority
    ,  NULL );

 xTaskCreate(
    TaskCount
    ,  (const portCHAR *) "increase counter"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  10  // priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
xTaskCreate(
    TaskPrintCount
    ,  (const portCHAR *) "Print counter"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  10  // priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}


void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
    vTaskDelay(5000/portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskCount(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);

  for (;;)
  {
    counter++;
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}
void TaskPrintCount(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  for (;;)
  {
    Serial.println(counter);
    vTaskDelay( 10000 / portTICK_PERIOD_MS );
  }
}
