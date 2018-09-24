//http://www.instructables.com/id/Make-an-accurate-Arduino-clock-using-only-one-wire/

#include "NoRTC.h"

Time::Time(int yr, int  mon, int date,
           int hr, int min, int sec,
           int day)
{
  this->yr   = yr;
  this->mon  = mon;
  this->date = date;
  this->hr   = hr;
  this->min  = min;
  this->sec  = sec;
  this->day  = day;
}


Time::Time()
{
  Time(2000, 1, 1, 1, 0, 0, 1);
}


Time arreglarHora (Time now)
{
	if(now.sec == 60)                                                   
	  {                                                                   
	    now.min ++;                                                       
	    now.sec = 0;                                                      
	  }
	  if(now.min == 60)                                                   
	  {                                                                   
	    now.hr ++;                                                       
	    now.min = 0;                                                      
	  }
	  if(now.hr == 24)                                                   
	  {                                                                   
	    now.hr = 0;                                                       
	    now.date ++; 
	    now.day ++;                                                     
	  }
	  if ((now.mon ==1 && now.date==32) || (now.mon ==2 && now.date==29) || (now.mon ==3 && now.date==32) || (now.mon ==4 && now.date==31) || (now.mon ==5 && now.date==32) || (now.mon ==6 && now.date==31) || (now.mon ==7 && now.date==32) || (now.mon ==8 && now.date==32) || (now.mon ==9 && now.date==31) || (now.mon ==10 && now.date==32) || (now.mon ==11 && now.date==31) || (now.mon ==12 && now.date==32))
	  {
	  	now.mon ++;
	  	now.date=1;
	  }
	  if (now.mon ==13)
	  	{
	  		now.mon = 1;
	  		now.yr ++;
	  	}
	  if (now.day == 8)
	  	now.day =1;	
	  
	  
	  return now;
}



void NoRTC::setTime(Time t)
{
	 //esto es para cuando se mambea sumando uno
	 //this->now = t;
   this->now = arreglarHora (t);
}


NoRTC::NoRTC()
{
	int masterClock =0;
}

void NoRTC::clockCounter()      // called by interrupt
{
  masterClock ++;        // with each clock rise add 1 to masterclock count
  if(masterClock == 489) // 490Hz reached     
  {                         
    now.sec ++;          // after one 490Hz cycle add 1 second ;)
    
	  
    setTime (Time(now.yr, now.mon, now.date, now.hr, now.min, now.sec, now.day) ) ;
    masterClock = 0;     // Reset after 1 second is reached
    
   }
  return;
}

void NoRTC::setPin(int pin, int analogPWMpin)
{
  clockInt = pin;
  analogReference(DEFAULT);
  analogWrite(analogPWMpin, 127);   // this starts our PWM 'clock' with a 50% duty cycle
} 


Time NoRTC::time()
{
  return this->now;
}
 void NoRTC::write_protect(bool nada)
 {
 	
 	return;
 }
 void NoRTC::halt(bool nada)
 {
 	
 	return;
 }
  