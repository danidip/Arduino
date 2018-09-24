#ifndef DS1302_h
#define DS1302_h

 
#include "Arduino.h"
 

#include <Time.h>

#define FORMAT_SHORT	1
#define FORMAT_LONG	2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3

#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define TCR_D1R2K	165
#define TCR_D1R4K	166
#define TCR_D1R8K	167
#define TCR_D2R2K	169
#define TCR_D2R4K	170
#define TCR_D2R8K	171
#define TCR_OFF		92


class DS1302_RAM
{
public:
	byte	cell[31];

		DS1302_RAM();
};

class DS1302
{
public:
		static void setup(uint8_t ce_pin, uint8_t data_pin, uint8_t sclk_pin);
		static time_t get();
    static bool set(time_t t);
    static bool read(tmElements_t &t);
    static bool write(tmElements_t &tm);
    bool   chipPresent ();
		char	*getDateStr(uint8_t slformat=FORMAT_LONG, uint8_t eformat=FORMAT_LITTLEENDIAN, char divider='.');
		char	*getTimeStr(uint8_t format=FORMAT_LONG);
		char	*getDOWStr(uint8_t format=FORMAT_LONG);


	static void	halt(bool value);
	static void	writeProtect(bool enable);
	static void	setTCR(uint8_t value);

	static void		writeBuffer(DS1302_RAM r);
	DS1302_RAM	readBuffer();
	static void		poke(uint8_t addr, uint8_t value);
	static uint8_t		peek(uint8_t addr);

private:
	static uint8_t _ce_pin;
	static uint8_t _data_pin;
	static uint8_t _sclk_pin;
	static uint8_t _burstArray[8];

	static uint8_t	_readByte();
	static void	     _writeByte(uint8_t value);
	static uint8_t	_readRegister(uint8_t reg);
	static void     _writeRegister(uint8_t reg, uint8_t value);
	static void		  _burstRead();
	static uint8_t 	dec2bcd(uint8_t num);
  static uint8_t 	bcd2dec(uint8_t num);
};
#endif
