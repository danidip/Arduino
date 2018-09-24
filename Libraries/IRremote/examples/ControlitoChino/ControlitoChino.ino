
#include <IRremote.h>
#define pinremoto A0


#define botonmantenido	 4294967295
#define botonchmenos     16753245
#define botonch          16736925
#define botonchmas       16769565

#define botonprevtrack   16720605
#define boton nexttrack  16712445
#define botonplaypause   16761405

#define  botonvolup      16754775   
#define  botonvoldown    16769055  
#define  botoneq         16748655

#define boton0           16738455
#define boton100         16750695
#define boton200         16756815

#define boton1           16724175
#define boton2           16718055
#define boton3           16743045

#define boton4           16716015
#define boton5           16726215
#define boton6           16734885

#define boton7           16728765
#define boton8           16730805
#define boton9           16732845

unsigned long timer;
IRrecv irrecv(pinremoto);
decode_results results;



void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {    
    Serial.println (results.value);
 if (results.decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results.decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results.decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results.decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results.decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }  
    irrecv.resume();
  }
}


