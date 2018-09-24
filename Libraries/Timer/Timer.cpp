#include "Timer.h"

Timer::Timer(unsigned long interval, bool autoreset, void (*callbackFunction)()){
	this->autoreset = autoreset;
	this->callback = callbackFunction;
	this->interval = interval;
	
	if(this->interval > 0){
		this->enabled = true;
		this->startMillis = millis();
	}else{
		this->enabled = false;
	}
}

bool Timer::check(){
	if(this->enabled){
		if((millis() - this->startMillis) >= this->interval){
			if(this->autoreset){
				this->startMillis = millis();
			}else{
				this->enabled = false;
			}
			if(this->callback){
				callback();
			}
			return true;
		}
	}
	return false;
}

void Timer::disable(){
	this->enabled = false;
}

void Timer::enable(){
	this->enabled = true;
}

bool Timer::isEnabled(){
	return this->enabled;
}

void Timer::reset(){
	this->enabled = true;
	this->startMillis = millis();
}

void Timer::setInterval(unsigned long interval){
	this->interval = interval;
}

unsigned long Timer::getInterval(){
	return this->interval;
}

void Timer::setAutoreset(bool autoreset){
	this->autoreset = autoreset;
}

bool Timer::getAutoreset(){
	return this->autoreset;
}