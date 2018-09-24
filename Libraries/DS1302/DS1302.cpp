/*
  DS1302.cpp - Arduino library support for the DS1302 Trickle Charge Timekeeping Chip
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library has been made to easily interface and use the DS1302 RTC with
  the Arduino.

  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "DS1302.h"

#define REG_SEC		0
#define REG_MIN		1
#define REG_HOUR	2
#define REG_DATE	3
#define REG_MON		4
#define REG_DOW		5
#define REG_YEAR	6
#define REG_WP		7
#define REG_TCR		8

/* Public */

DS1302_RAM::DS1302_RAM()
{
	for (int i=0; i<31; i++)
		cell[i]=0;
}

bool DS1302::set(time_t t)
{
  tmElements_t tm;
  breakTime(t, tm);
  tm.Second |= 0x80;  // stop the clock 
  write(tm); 
  tm.Second &= 0x7f;  // start the clock
  write(tm); 
}

char *DS1302::getTimeStr(uint8_t format)
{
	char *output= "xxxxxxxx";
	tmElements_t t;
	read(t);
	if (t.Hour<10)
		output[0]=48;
	else
		output[0]=char((t.Hour / 10)+48);
	output[1]=char((t.Hour % 10)+48);
	output[2]=58;
	if (t.Minute<10)
		output[3]=48;
	else
		output[3]=char((t.Minute / 10)+48);
	output[4]=char((t.Minute % 10)+48);
	output[5]=58;
	if (format==FORMAT_SHORT)
		output[5]=0;
	else
	{
	if (t.Second<10)
		output[6]=48;
	else
		output[6]=char((t.Second / 10)+48);
	output[7]=char((t.Second % 10)+48);
	output[8]=0;
	}
	return output;
}

char *DS1302::getDOWStr(uint8_t format)
{
	char *output= "xxxxxxxxx";
	tmElements_t t;
	read(t);
	switch (t.Wday)
	{
		case MONDAY:
			output="Monday";
			break;
		case TUESDAY:
			output="Tuesday";
			break;
		case WEDNESDAY:
			output="Wednesday";
			break;
		case THURSDAY:
			output="Thursday";
			break;
		case FRIDAY:
			output="Friday";
			break;
		case SATURDAY:
			output="Saturday";
			break;
		case SUNDAY:
			output="Sunday";
			break;
	}     
	if (format==FORMAT_SHORT)
		output[3]=0;
	return output;
}

char *DS1302::getDateStr(uint8_t slformat, uint8_t eformat, char divider)
{
	char *output= "xxxxxxxxxx";
	int yr, offset;
	tmElements_t t;
	read(t);
	switch (eformat)
	{
		case FORMAT_LITTLEENDIAN:
			if (t.Day<10)
				output[0]=48;
			else
				output[0]=char((t.Day / 10)+48);
			output[1]=char((t.Day % 10)+48);
			output[2]=divider;
			if (t.Month<10)
				output[3]=48;
			else
				output[3]=char((t.Month / 10)+48);
			output[4]=char((t.Month % 10)+48);
			output[5]=divider;
			if (slformat==FORMAT_SHORT)
			{
				yr=t.Year-2000;
				if (yr<10)
					output[6]=48;
				else
					output[6]=char((yr / 10)+48);
				output[7]=char((yr % 10)+48);
				output[8]=0;
			}
			else
			{
				yr=t.Year;
				output[6]=char((yr / 1000)+48);
				output[7]=char(((yr % 1000) / 100)+48);
				output[8]=char(((yr % 100) / 10)+48);
				output[9]=char((yr % 10)+48);
				output[10]=0;
			}
			break;
		case FORMAT_BIGENDIAN:
			if (slformat==FORMAT_SHORT)
				offset=0;
			else
				offset=2;
			if (slformat==FORMAT_SHORT)
			{
				yr=t.Year-2000;
				if (yr<10)
					output[0]=48;
				else
					output[0]=char((yr / 10)+48);
				output[1]=char((yr % 10)+48);
				output[2]=divider;
			}
			else
			{
				yr=t.Year;
				output[0]=char((yr / 1000)+48);
				output[1]=char(((yr % 1000) / 100)+48);
				output[2]=char(((yr % 100) / 10)+48);
				output[3]=char((yr % 10)+48);
				output[4]=divider;
			}
			if (t.Month<10)
				output[3+offset]=48;
			else
				output[3+offset]=char((t.Month / 10)+48);
			output[4+offset]=char((t.Month % 10)+48);
			output[5+offset]=divider;
			if (t.Day<10)
				output[6+offset]=48;
			else
				output[6+offset]=char((t.Day / 10)+48);
			output[7+offset]=char((t.Day% 10)+48);
			output[8+offset]=0;
			break;
		case FORMAT_MIDDLEENDIAN:
			if (t.Month<10)
				output[0]=48;
			else
				output[0]=char((t.Month / 10)+48);
			output[1]=char((t.Month % 10)+48);
			output[2]=divider;
			if (t.Day<10)
				output[3]=48;
			else
				output[3]=char((t.Day / 10)+48);
			output[4]=char((t.Day % 10)+48);
			output[5]=divider;
			if (slformat==FORMAT_SHORT)
			{
				yr=t.Year-2000;
				if (yr<10)
					output[6]=48;
				else
					output[6]=char((yr / 10)+48);
				output[7]=char((yr % 10)+48);
				output[8]=0;
			}
			else
			{
				yr=t.Year;
				output[6]=char((yr / 1000)+48);
				output[7]=char(((yr % 1000) / 100)+48);
				output[8]=char(((yr % 100) / 10)+48);
				output[9]=char((yr % 10)+48);
				output[10]=0;
			}
			break;
	}
	return output;
}

boolean DS1302::chipPresent ()
{
	return true;
}

void DS1302::setup(uint8_t ce_pin, uint8_t data_pin, uint8_t sclk_pin)
{
	_ce_pin = ce_pin;
	_data_pin = data_pin;
	_sclk_pin = sclk_pin;

	pinMode(_ce_pin, OUTPUT);
	pinMode(_sclk_pin, OUTPUT);
}

time_t DS1302::get()   // Aquire data from buffer and convert to time_t
{
  tmElements_t tm;
  if (read(tm) == false) return 0;
  return(makeTime(tm));
}

bool DS1302::read(tmElements_t &t)
{
	 
	_burstRead();
	t.Second	= bcd2dec(_burstArray[0]);
	t.Minute	= bcd2dec(_burstArray[1]);
	t.Hour	= bcd2dec(_burstArray[2]);
	t.Day	= bcd2dec(_burstArray[3]);
	t.Month	= bcd2dec(_burstArray[4]);
	//danidip ver esto : t.dow	= _burstArray[5];
	t.Year	= CalendarYrToTm(bcd2dec(_burstArray[6])+2000);
//	Serial.print("leyendo");
	//	Serial.println(bcd2dec(_burstArray[6])+2000);
}

bool DS1302::write(tmElements_t &t)
{

	//if (((t.Hour>=0) && (t.Hour<24)) && ((t.Minute>=0) && (t.Minute<60)) && ((t.Second>=0) && (t.Second<60)) && ((t.Day>0) && (t.Day<=31)) && ((t.Month>0) && (t.Month<=12)) && ((t.Year>=2000) && (t.Year<3000)))
	//{
		_writeRegister(REG_HOUR, dec2bcd(t.Hour));
		_writeRegister(REG_MIN, dec2bcd(t.Minute));
		_writeRegister(REG_SEC, dec2bcd(t.Second));
		_writeRegister(REG_YEAR, dec2bcd(tmYearToCalendar(t.Year)-2000));
		
		_writeRegister(REG_MON, dec2bcd(t.Month));
		_writeRegister(REG_DATE, dec2bcd(t.Day));
		return true;
	//}
	//return false;
}

 uint8_t DS1302::dec2bcd(uint8_t num)
{
  return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal
uint8_t DS1302::bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}
  
 void DS1302::halt(bool enable)
{
  uint8_t _reg = _readRegister(REG_SEC);
  _reg &= ~(1 << 7);
  _reg |= (enable << 7);
  _writeRegister(REG_SEC, _reg);
}

 void DS1302::writeProtect(bool enable)
{
  uint8_t _reg = (enable << 7);
  _writeRegister(REG_WP, _reg);
}

	 void DS1302::setTCR(uint8_t value)
{
	_writeRegister(REG_TCR, value);
}

/* Private */


	uint8_t DS1302::_ce_pin;
	uint8_t DS1302::_data_pin;
	uint8_t DS1302::_sclk_pin;
	uint8_t DS1302::_burstArray[8];
	
uint8_t DS1302::_readByte()
{
	pinMode(_data_pin, INPUT);

	uint8_t value = 0;
	uint8_t currentBit = 0;

	for (int i = 0; i < 8; ++i)
	{
		currentBit = digitalRead(_data_pin);
		value |= (currentBit << i);
		digitalWrite(_sclk_pin, HIGH);
		delayMicroseconds(1);
		digitalWrite(_sclk_pin, LOW);
	}
	return value;
}

void DS1302::_writeByte(uint8_t value)
{
	pinMode(_data_pin, OUTPUT);
	shiftOut(_data_pin, _sclk_pin, LSBFIRST, value);
}

uint8_t DS1302::_readRegister(uint8_t reg)
{
	uint8_t cmdByte = 129;
	cmdByte |= (reg << 1);

	uint8_t readValue;

	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(cmdByte);
	readValue = _readByte();
	
	digitalWrite(_ce_pin, LOW);

	return readValue;
}

void DS1302::_writeRegister(uint8_t reg, uint8_t value)
{
	uint8_t cmdByte = (128 | (reg << 1));

	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(cmdByte);
	_writeByte(value);

	digitalWrite(_ce_pin, LOW);
}

void DS1302::_burstRead()
{
	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(191);
	for (int i=0; i<8; i++)
	{
		_burstArray[i] = _readByte();
	}
	digitalWrite(_ce_pin, LOW);
}

 
 
void DS1302::writeBuffer(DS1302_RAM r)
{
	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(254);
	for (int i=0; i<31; i++)
	{
		_writeByte(r.cell[i]);
	}
	digitalWrite(_ce_pin, LOW);
}

DS1302_RAM DS1302::readBuffer()
{
	DS1302_RAM r;

	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(255);
	for (int i=0; i<31; i++)
	{
		r.cell[i] = _readByte();
	}
	digitalWrite(_ce_pin, LOW);

	return r;
}

void DS1302::poke(uint8_t addr, uint8_t value)
{
	if ((addr >=0) && (addr<=30))
	{
		addr = (addr * 2) + 192;

		digitalWrite(_sclk_pin, LOW);
		digitalWrite(_ce_pin, HIGH);

		_writeByte(addr);
		_writeByte(value);

		digitalWrite(_ce_pin, LOW);
	}
}

uint8_t DS1302::peek(uint8_t addr)
{
	if ((addr >=0) && (addr<=30))
	{
		addr = (addr * 2) + 193;

		uint8_t readValue;

		digitalWrite(_sclk_pin, LOW);
		digitalWrite(_ce_pin, HIGH);

		_writeByte(addr);
		readValue = _readByte();
		
		digitalWrite(_ce_pin, LOW);

		return readValue;
	}
	else
		return 0;
}

