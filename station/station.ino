#include "Average.h"
#include <MAX6675_Thermocouple.h>
const int version = 2;
//#define EnableIron

//uses EEPROM
#define USE_EEPR
/*
 Name:		station.ino
 Created:	8/9/2018 5:22:20 PM
 Author:	chanu
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>
double Setpoint, Input, Output;
double Kp = 2, Ki = 5, Kd = 1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
int HGPidTime = 1000;
unsigned long windowStartTime;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


//Encoder's pins
#define EncoderDirA   A3  // Connected to D3 (Rotation)
#define EncoderDirB   A2  // Connected to D4 (Rotation)
#define EncoderButton 10  // Connected to D5 (Pressing)
//#define hGThermoPin   A1  // the analog input pin for reading an amplified voltage of the heat gun's thermocouple


#define SCK_PIN 3
#define CS_PIN  4
#define SO_PIN  5

MAX6675_Thermocouple* thermocouple = NULL;

#define hGFanPWMPin   9  // the output pin for controlling the heat gun's fan
#define hGHeatingElementPin  7  // the output pin for controlling the heat gun's heating element 

//MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

#ifdef EnableIron
#define sIThermoPin          A0  // the analog input pin for reading an amplified voltage of the soldering iron's thermocouple 
#define sIHeatingElementPin  8 // the output pin for controlling the soldering iron's heating element
char sISeparator = ' ';
int sIEncoderPosCount = 0;
int sIThermo = 0;
int buttonMenuPos = 0;
#else
int buttonMenuPos = 1;
#endif
 
//Movs for lcd Menu
#define btnRIGHT 1
#define btnUP 2
#define btnDOWN 3
#define btnSELECT 5
#define btnNONE 7

int hGEncoderPosCount = 0;
int fanEncoderPosCount = 255;
int fan_pwm_value = 255;
int outputValue = 0;
int iMAX_HOTAIR_TEMP = 500;
 
boolean bHGHeaterOn = false;

int cyclesCount = 0;
int pinALast;
enum eStatus { waiting, configuring,shutdown };
eStatus state;
void setup() {
	thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
	pinMode(EncoderDirA, INPUT_PULLUP);
	pinMode(EncoderDirB, INPUT_PULLUP);
	pinMode(EncoderButton, INPUT_PULLUP);
	pinMode(hGHeatingElementPin, OUTPUT);
#ifdef EnableIron
	pinMode(sIHeatingElementPin, OUTPUT);
#endif
	setupLCD();
	getConfig();
	
	pinALast = digitalRead(EncoderDirA);
	setupMenus();
	printLine(1,"Menu");	 
	delay(500);
	state = waiting;
	
	Input = reportHGTemp();
	Setpoint = 0;
	
	windowStartTime = millis();
	myPID.SetOutputLimits(0, HGPidTime);
	myPID.SetMode(AUTOMATIC);

	delay(1500);
	clearScreen();
}

void loop() 
{
	
	switch (state)
	{
	case waiting:
	processSI();
	processHG();
	 //setting fan speed
	processEncoder(); // processing encoder signals
	processEncoderButton();
	break;
	case configuring:
		//first we need to disable the heating element while configuring
		hGEncoderPosCount = 0;
		digitalWrite(hGHeatingElementPin, LOW);
		processMenu();
	break;
	case shutdown:
		processEncoderButton();
	break;
	}
	processFan();
	processLCD();
}

void processSI()
{
#ifdef EnableIron
	sIThermo = analogRead(sIThermoPin); // Reads the value from the specified analog pin, ADC will map input voltages between 0V and 5V  into integer values between 0 and 1023
	//sIThermo = (int)((iSIyAxis/10000) * sIThermo - (iSISlope/1000)); // use [3]
	//strange behaviour dividing floats an ints results in 0 that's why all the casts
	float res = (float)(((float)iSIyAxis / (float)10000) * (float)sIThermo + ((float)iSISlope / (float)1000));
	sIThermo = (int)(res);
	int i;

	//thermostats are implemented by using an on-off controller
 
	//thermostat 1
	i = sIEncoderPosCount - sIThermo;
	i = i > 0 ? i : 0;

	int sI_out;

	if (i)
		sI_out = HIGH;
	else
		sI_out = LOW;

	digitalWrite(sIHeatingElementPin, sI_out);
 
#endif 
}
void processHG()
{
	Input = reportHGTemp();
	Setpoint = hGEncoderPosCount;
	myPID.Compute();
	if (millis() - windowStartTime > HGPidTime)
	{ //time to shift the Relay Window
		windowStartTime += HGPidTime;
	}
	if (Output > millis() - windowStartTime && bHGHeaterOn)
		digitalWrite(hGHeatingElementPin, HIGH);
	else 
		digitalWrite(hGHeatingElementPin, LOW);
		/*
	int i;
	i = hGEncoderPosCount - reportHGTemp();
	i = i > 0 ? i : 0;
	int hG_out;
	if (i && bHGHeaterOn)
		hG_out = HIGH;
	else
		hG_out = LOW;

	digitalWrite(hGHeatingElementPin, hG_out);
	*/
}

//Average<int> aveHG(10); // stores in array last 10 values then returns the average
unsigned long timerHG = 0;
const int displayHG = 1000;
int ultimaLectura = 0; 
int reportHGTemp()
{
	if (millis() - timerHG >= displayHG)
	{   
		timerHG = millis();
		ultimaLectura = (int) thermocouple->readCelsius();	
	}
	return ultimaLectura;
}


void processFan()
{
	int i = fanEncoderPosCount;
	i = i > 0 ? i : 0;
	i = i < 255 ? i : 255;

	fan_pwm_value = i;
	analogWrite(hGFanPWMPin, fan_pwm_value);
}
