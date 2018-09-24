#include <dht.h>
#define dht_dpin A0

dht DHT;
int contactor = 8; 
void setup (){
Serial.begin(9600);
pinMode(contactor, OUTPUT);
delay(300);
Serial.println("Humedad y temperatura");
delay(700);
}

void loop (){
DHT.read11(dht_dpin);
Serial.print("Humedad=");
Serial.print(DHT.humidity);
Serial.println("%");
Serial.print("temperatura=");
Serial.print(DHT.temperature);
Serial.println("C ");
if (DHT.temperature > 34)
{
  digitalWrite(contactor, LOW); 
}
else
{
  digitalWrite(contactor, HIGH); 
}

delay(800);


}