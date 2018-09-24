#include <dht.h>
#define dht_dpin A0

dht DHT;

void setup (){
Serial.begin(9600);
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
delay(800);


}