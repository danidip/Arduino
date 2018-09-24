#include <EEPROM.h>
#include <EEPROMWriteAnything.h>


struct configuration_t
{
	int Ver; //firmware Version
	int SIyAxis;  //Y part of formula of soldering Iron
	int SISlope;  //slope part of soldering Iron
	double HGKp;  
	double HGKi;
	double HGKd;
	int HGPidTime;
	int MAX_SOLDIR_TEMP;
	int MAX_HOTAIR_TEMP;
} configuration;

void clearEEprom()
{
	for (int i = 0; i < EEPROM.length(); i++) {
		EEPROM.write(i, 0);
	}
}

void getConfig()
{
#ifdef USE_EEPR
	EEPROM_readAnything(0, configuration);
	//if version doesn't match then initializes EEPROM to hardcoded values, it works for first time as well
	if (configuration.Ver != version)
	{
		printLine(1, "clearing");
		printLine(2, "eeprom");
		
		clearEEprom();
		printLine(1, "eeprom");
		printLine(2, "cleared!");
		delay(2000);
		initializeToHardCodedValues();
		EEPROM_writeAnything(0, configuration);
		getConfig();
	}
#else
	initializeToHardCodedValues();
#endif 
	//iSIyAxis = configuration.SIyAxis;
	//iSISlope = configuration.SISlope;
	Kp = configuration.HGKp;
	Ki = configuration.HGKi;
	Kd = configuration.HGKd;
	HGPidTime = configuration.HGPidTime ;
	//iMAX_SOLDIR_TEMP = 0;// configuration.MAX_SOLDIR_TEMP;
	iMAX_HOTAIR_TEMP = configuration.MAX_HOTAIR_TEMP;
}

void setConfig()
{
	configuration.Ver = version;
	configuration.SIyAxis = 0;// iSIyAxis;
	configuration.SISlope = 0;// iSISlope;
	configuration.HGKp = Kp;
	configuration.HGKi = Ki;
	configuration.HGKd = Kd;
	configuration.HGPidTime = HGPidTime;
	configuration.MAX_SOLDIR_TEMP = 0;//iMAX_SOLDIR_TEMP;
	configuration.MAX_HOTAIR_TEMP = iMAX_HOTAIR_TEMP;
	EEPROM_writeAnything(0, configuration);
}

 
void initializeToHardCodedValues()
{
	configuration.Ver = version;
	configuration.SIyAxis = 8955;
	configuration.SISlope = 7918;
	configuration.HGKp =0.25;
	configuration.HGKi = 0.25;
	configuration.HGKd = 0.20;
	configuration.HGPidTime = 200;
	configuration.MAX_SOLDIR_TEMP = 350;
	configuration.MAX_HOTAIR_TEMP = 450;
}