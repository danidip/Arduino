/*
  This example will blink a LED attached to pin 13 each 0.5s
*/

#include <Timer.h>

//Instantiate the timer at 500 milliseconds
Timer timer = Timer(500);

uint8_t led = 13;
uint8_t ledState = LOW;

void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  if(timer.check()){
    digitalWrite(led, ledState);
    ledState = !ledState;
  }
}
