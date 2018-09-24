//http://www.instructables.com/id/Make-an-accurate-Arduino-clock-using-only-one-wire/ 

#ifndef NoRTC_h
#define NoRTC_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Time
{
public:
  int sec;
  int min;
  int hr;
  int date;
  int mon;
  int day;
  int yr;

  Time();
  Time(int yr, int mon, int date,
       int hr, int min, int sec,
       int day);
};


class NoRTC
{
public:
	
  NoRTC();
  Time now;
	void setPin(int pin, int analogPWMpin);
  void setTime(Time t);
  Time time ();
  void write_protect(bool nada); 
  void halt(bool nada); 
  void clockCounter() ;

private:
	int clockInt;
	int masterClock;
};

#endif
