/*
  This example will blink a LED attached to pin 13 each 0.5s
  At this example, the blink will be done by a callback function.
  When you have to define a callback function, you need to define the autoreset too, as the callback function is the 3rd parameter of the constructor
*/

#include <Timer.h>

//Instantiate the timer at 500 milliseconds
Timer timer = Timer(500, true, blinkLed);

uint8_t led = 13;
uint8_t ledState = LOW;

void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  timer.check();
}

void blinkLed(){
  digitalWrite(led, ledState);
  ledState = !ledState;
}
