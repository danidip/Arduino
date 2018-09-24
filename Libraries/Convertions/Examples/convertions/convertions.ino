#include <convertions.h>
char valorchar[] = "Prueba";
convertions con;



void setup()
{
    Serial.begin(9600);
}
void wrap ()
{
}

void loop()
{
  
  /* String pepe = con.charToString(valorchar);
   Serial.println(pepe);
  */  
  
  /* 
   char *sarasa;
   sarasa = con.stringToChar (pepe) ;
   Serial.println(sarasa);
   free (sarasa);
  */   
  /*
  char s[]="substringreloco";
  char *tutu = con.substring(3,5,s);
  Serial.println (tutu);
  free (tutu);
  */
  char s[]="abarajame ";
  char s1[]="en la banera";
  char *pupa = con.concat(s,s1);
  Serial.println (pupa);
  free (pupa);  
                
}