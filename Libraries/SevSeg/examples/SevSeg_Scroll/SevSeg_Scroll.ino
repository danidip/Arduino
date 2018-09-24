/*
 the display you have to call myDisplay.DisplayNumber(#, decimalPlace) multiple times a second. Put this
 in the main loop.
 
 Looking at the display like this: 8.8.8.8. pin 1 is on the lower row, starting from the left. 
 Pin 12 is the top row, upper left pin.
 
 
 ToDo:
 Allow for user selectable digits
 Pass in a brightness value
 Possibly allow user to specify leading zeros or no
 Covert big byte array to binary: http://arduino.cc/forum/index.php/topic,39760.0.html
 Measure current going through limiting resistors to make sure we're getting 20mA per segment per digit (should be 80mA for four digits)
 
 */

#include "SevSeg.h"

SevSeg myDisplay;

//Create global variables
unsigned long timer;
int deciSecond = 0;

void setup() {

  int displayType = COMMON_ANODE; 

# ifdef MEGA
   //Declare what pins are connected to the digits
   int digit1 = 1; //Pin 12 on my 4 digit display
   int digit2 = 2; //Pin 9 on my 4 digit display
   int digit3 = 3; //Pin 8 on my 4 digit display
   int digit4 = 4; //Pin 6 on my 4 digit display
   
   //Declare what pins are connected to the segments
   int segA = 22; //Pin 11 on my 4 digit display
   int segB = 23; //Pin 7 on my 4 digit display
   int segC = 24; //Pin 4 on my 4 digit display
   int segD = 25; //Pin 2 on my 4 digit display
   int segE = 26; //Pin 1 on my 4 digit display
   int segF = 27; //Pin 10 on my 4 digit display
   int segG = 28; //Pin 5 on my 4 digit display
   int segDP= 29; //Pin 3 on my 4 digit display
#else
//Declare what pins are connected to the digits
   int digit1 = 9; //Pin 12 on my 4 digit display
   int digit2 = 6; //Pin 9 on my 4 digit display
   int digit3 = 5; //Pin 8 on my 4 digit display
   int digit4 = A1; //Pin 6 on my 4 digit display
   
   //Declare what pins are connected to the segments
   int segA = 8; //Pin 11 on my 4 digit display
   int segB = 4; //Pin 7 on my 4 digit display
   int segC = 13; //Pin 4 on my 4 digit display
   int segD = 11; //Pin 2 on my 4 digit display
   int segE = 10; //Pin 1 on my 4 digit display
   int segF = 7; //Pin 10 on my 4 digit display
   int segG = A0; //Pin 5 on my 4 digit display
   int segDP= 12; //Pin 3 on my 4 digit display
#endif


  int numberOfDigits = 4; //Do you have a 2 or 4 digit display?
  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  myDisplay.SetBrightness(100);
  myDisplay.DisplayScroll("PENELOPE TE QUIERO A LA UNA A LAS DOS Y A LAS TRES"); 
}

void loop() {

  //Produce an output on the display
  //Example ways of displaying a decimal number
  //sprintf(tempString, "%d", deciSecond); //Convert deciSecond into a string that is left adjusted
  //sprintf(tempString, "%04d", deciSecond); //Convert deciSecond into a string with leading zeros
  //sprintf(tempString, "%4d", negativeDeciSecond); //Shows a negative sign infront of right adjusted number
  //sprintf(tempString, "%4X", deciSecond); //Count in HEX, right adjusted
 // myDisplay.DisplayString(tempString, 3); //(numberToDisplay, decimal point location)
  
  //Other examples
  //myDisplay.DisplayString(tempString, 0); //Display string, no decimal point
  //myDisplay.DisplayString("-23b", 3); //Display string, decimal point in third position
  
  myDisplay.keepScrolling(100);
  if (!myDisplay.isScrolling)
    {
      myDisplay.DisplayScroll("HAY UN DESTINO QUE NO TIENE PRUEBAS, por ESO ESTA HISTORIA"); 
    }
 
}

 