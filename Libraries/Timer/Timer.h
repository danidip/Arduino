/*
	
*/
#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class Timer{
	public:
		Timer(unsigned long interval = 0, bool autoreset = true, void (*callback)() = NULL);
		
		bool check();
		void disable();
		void enable();
		bool isEnabled();
		void reset();
		
		void setInterval(unsigned long interval);
		unsigned long getInterval();
		
		void setAutoreset(bool autoreset);
		bool getAutoreset();
		
	private:
		bool enabled;
		bool autoreset;
		unsigned long interval;
		unsigned long startMillis;
		void (*callback)();
};

#endif