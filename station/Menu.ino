#include <MenuManagerI2C.h>
 
int botonpresionadoanterior = -1;
unsigned long tiemporeboteboton;

MenuLCDI2C g_menuLCD(16, 2);
MenuManagerI2C g_MenuManager(&g_menuLCD);



void setupMenus()
{
	g_menuLCD.setLCD(&lcd);
    g_MenuManager.addMenuRoot(new MenuEntryI2C("H.G MaxTemp", NULL, HGMaxTempCallback));
	g_MenuManager.addSibling (new MenuEntryI2C("H.G Kp", NULL, HGKp)); //this is only to watch the value collected by thermocouple changing it won't matter
	g_MenuManager.addSibling (new MenuEntryI2C("H.G Ki", NULL, HGKi));
	g_MenuManager.addSibling (new MenuEntryI2C("H.G Kd", NULL, HGyKd));
	g_MenuManager.addSibling(new MenuEntryI2C("H.G Time", NULL, HGTime));
	
#ifdef EnableIron
	g_MenuManager.addSibling (new MenuEntryI2C("SoldIron MaxTemp", NULL, SIMaxTempCallback));
	g_MenuManager.addSibling (new MenuEntryI2C("SoldIron Report", NULL, SIKp)); //this is only to watch the value collected by thermocouple changing it won't matter
	g_MenuManager.addSibling (new MenuEntryI2C("Sold Iron Y Axis", NULL, SIKi));
	g_MenuManager.addSibling (new MenuEntryI2C("Sold Iron Slope", NULL, SIKd));
#endif
	g_MenuManager.addSibling (new MenuEntryI2C("Save", NULL, SaveCallback));
	g_MenuManager.addSibling (new MenuEntryI2C("Back", NULL, BackMenuCallback));
	
	g_MenuManager.DrawMenu();
}

 

void processMenu()
{
	int btn = processEncoder();

	switch (btn)
	{
	case btnUP:
			g_MenuManager.DoMenuAction(MENU_ACTIONI2C_UP);
		break;
	case btnDOWN:
			g_MenuManager.DoMenuAction(MENU_ACTIONI2C_DOWN);
		break;
	case btnNONE:
		break;
	default:
		break;
	}
	
	if (checkButton() ==1) 
		g_MenuManager.DoMenuAction(MENU_ACTIONI2C_SELECT);
	
}
void redrawMenu()
{
	g_MenuManager.DrawMenu();
}
void BackMenuCallback(char* pMenuText, void *pUserData)
{
	state = waiting;
	g_MenuManager.SelectRoot();
}

void SaveCallback(char* pMenuText, void *pUserData)
{
	myPID.SetTunings(Kp, Ki, Kd);
	setConfig();
	printLine(1, "Settings");
	printLine(2, "saved!");
	delay(1000);
	state = waiting;
	g_MenuManager.SelectRoot();

}



void HGKp(char* pMenuText, void *pUserData)
{
	char *pLabel = "HeatGun Kp";
	int iNumLabelLines = 1;
	double iMin = 0;
	double iMax = 1023; //max adc 8bit
	double iStart = Kp;
	double iStep = 0.1;
	g_MenuManager.DoDoubleInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &Kp);
}


void HGyKd(char* pMenuText, void *pUserData)
{
	char *pLabel = "HeatGun Kd";
	int iNumLabelLines = 1;
	double iMin = 0;
	double iMax = 1023;
	double iStart = Kd;
	double iStep = 0.1;
	g_MenuManager.DoDoubleInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &Kd);
}
void HGKi(char* pMenuText, void *pUserData)
{
	char *pLabel = "Heat Gun Ki";
	int iNumLabelLines = 1;
	double iMin = -20000;
	double iMax = 20000;
	double iStart = Ki;
	double iStep = 0.1;
	g_MenuManager.DoDoubleInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &Ki);
}
void HGTime(char* pMenuText, void *pUserData)
{
	char *pLabel = "HeatGun Time";
	int iNumLabelLines = 1;
	double iMin = 0;
	double iMax = 31023;
	double iStart = HGPidTime;
	double iStep = 10;
	g_MenuManager.DoIntInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &HGPidTime);
}
void HGMaxTempCallback(char* pMenuText, void *pUserData)
{
	char *pLabel = "H.G Max Temp";
	int iNumLabelLines = 1;
	int iMin = 0;
	int iMax = 550;
	int iStart = iMAX_HOTAIR_TEMP;
	int iStep = 1;
	g_MenuManager.DoIntInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &iMAX_HOTAIR_TEMP );
}

#ifdef EnableIron
void SIReportCallback(char* pMenuText, void *pUserData)
{
	char *pLabel = "Sold Iron Report";
	int iNumLabelLines = 1;
	int iMin = 0;
	int iMax = 1023; //max adc 8bit
	int iStart = analogRead(SIThermoPin);
	int iStep = 1;
	g_MenuManager.DoIntInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, NULL);
}
void SIyAxisCallback(char* pMenuText, void *pUserData)
{
	char *pLabel = "Sold Iron Y Axis";
	int iNumLabelLines = 1;
	float iMin = -20000;
	float iMax = 20000;
	float iStart = iSIyAxis;
	float iStep = 1;
	g_MenuManager.DoFloatInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &iSIyAxis);
}
void SIMaxTempCallback(char* pMenuText, void *pUserData)
{
	char *pLabel = "Sold Iron Y Axis";
	int iNumLabelLines = 1;
	int iMin = 0;
	int iMax = 450;
	int iStart = iMAX_SOLDIR_TEMP;
	int iStep = 1;
	g_MenuManager.DoIntInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &iMAX_SOLDIR_TEMP);
}
void SISlopeCallback(char* pMenuText, void *pUserData)
{
	char *pLabel = "Heat Gun Slope";
	float iNumLabelLines = 1;
	float iMin = -20000;
	float iMax = 20000;
	float iStart = iSISlope;
	float iStep = 1;
	g_MenuManager.DoFloatInput(iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &iSISlope);
}
#endif