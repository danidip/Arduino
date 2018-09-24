/*
  This example will blink a LED attached to pin 13 each 0.5s
  At this example, the autoreset is set to false,
  so, after it's complete, the timer is disabled, and you have to reset it at every check
*/

#include <Timer.h>

//Instantiate the timer at 500 milliseconds
Timer timer = Timer(500, false);

uint8_t led = 13;
uint8_t ledState = LOW;

void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  if(timer.check()){
    digitalWrite(led, ledState);
    ledState = !ledState;
    timer.reset();
  }
}
