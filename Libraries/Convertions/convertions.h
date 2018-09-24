#ifndef convertions_h
#define convertions_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

 


class convertions
{
public:
	
  String charToString(char *valor);
  char* stringToChar(String valor);
  char* substr(int i,int j,char *ch);
  char* concat(char *char1,char *char2);
  char* intToChar (int i);
private:
	
};

#endif
