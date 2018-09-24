unsigned long timerHora = 0;
char line[16];
const int displayRedrawCount = 300;
void setupLCD()
{
	// set up the LCD's number of columns and rows:
	lcd.init(); // initialize the lcd 
	lcd.backlight();
	lcd.home();
	lcd.clear();
}
 
void processLCD()
{
	char hGSeparator = ' ';
	//char hGOnSeparator = ' ';
	char fanSeparator = ' ';
	char str[17];
	switch (state)
	{
	case waiting:
		
		//refresh display and serial output 
		if (millis() - timerHora >= displayRedrawCount)
		{  // skips some cycles, otherwise output processing will block input processing
			timerHora = millis();
			switch (buttonMenuPos)
			{
#ifdef EnableIron
			case 0:
				sISeparator = '*';
				break;
#endif
			case 1:
				hGSeparator = '*';
				break;
			case 2:
				fanSeparator = '*';
				break;
			}

			//hGOnSeparator = bHGHeaterOn ? '+' : ' ';
			
#ifdef EnableIron
			sprintf(str, "S=%3d%c%3d       ", sIThermo, sISeparator, sIEncoderPosCount);
#else
			sprintf(str, "Act=%3d Des=%3d%c", reportHGTemp(), hGEncoderPosCount, hGSeparator);
#endif 
			lcd.setCursor(0, 0);
			lcd.print(str);

#ifdef EnableIron
			sprintf(str, "H=%3d%c%3d F%c%3d%%", reportHGTemp(), hGSeparator, hGEncoderPosCount, fanSeparator, fan_pwm_value * 100 / 255);
#else

			sprintf(str, "Vent=%3d%%   %c  %c", (int)(fan_pwm_value * 100 / 255), bHGHeaterOn ? '!' : ' ', fanSeparator);
#endif 
			lcd.setCursor(0, 1);
			lcd.print(str);
		}
		break;
	case configuring:
		break;
	case shutdown:

		int HGtemp = reportHGTemp();

		if (HGtemp > 40)
		{
			sprintf(str, "Shutting        ");
			lcd.setCursor(0, 0);
			lcd.print(str);
			sprintf(str, "Down %3d        ", HGtemp);
			lcd.setCursor(0, 1);
			lcd.print(str);
		}
		else
		{
			lcd.setCursor(0, 0);
			lcd.print("You can Switch  ");
			lcd.setCursor(0, 1);
			lcd.print("Off safely !    ");
		}
		break;
	}
}

void clearScreen()
{
	lcd.home();
	lcd.print("                ");
	lcd.setCursor(0, 1);
	lcd.print("               ");
	lcd.home();
}




void printLine(int linea, char*  que)
{
	

	if (linea == 1)
	{
		if ((strncmp((const char*)line, (const char*)que, 16) != 0)  )
		{
			lcd.setCursor(0, 0);
			lcd.print("                ");
			lcd.setCursor(0, 0);
			lcd.print(que);
			memcpy(line, que, 16);
		}
			}
	if (linea == 2)
	{
		if (strcmp((const char*)line, (const char*)que) != 0 )
		{
		 
			lcd.setCursor(0, 1);
			lcd.print("                ");
			lcd.setCursor(0, 1);
			lcd.print(que);
			memcpy(line, que, 16);
		}
	}
}