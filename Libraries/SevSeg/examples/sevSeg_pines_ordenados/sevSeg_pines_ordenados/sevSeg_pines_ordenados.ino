 

#include "SevSeg.h"

 
SevSeg sevseg;
 
unsigned long timer;
int CentSec=0;

void setup() {
#define digit1 9
#define digit2 6
#define digit3 5
#define digit4 A1
#define segA  8
#define segB  4
#define segC 13
#define segD 11
#define segE 10
#define segF 7
#define segG A0
#define segDP 12
#define displayType  COMMON_ANODE
#define numberOfDigits  4
  sevseg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  //sevseg.Begin(1,4,9,6,5,A0,A3,A3,8,4,A2,A1,7,A5);
  //aca estaria para la plaqueta que diseñe
  //Set the desired brightness (0 to 100);
  
  timer=millis();
}

void loop() {
  //Produce an output on the display
  

  //Check if 10ms has elapsed
  unsigned long mils=millis();
  if (mils-timer>=10) {
    timer=mils;
    CentSec++;
    if (CentSec=10000) { // Reset to 0 after counting for 100 seconds.
      CentSec=0;
    }
    //Update the number to be displayed, with a decimal
    //place in the correct position.
	char  tempString[5];
	sprintf(tempString, "%s", CentSec );
	tempString[5] = '\0';

    sevseg.DisplayString (tempString,0 );
  }
}








