
/*
To keep a physical interface as simple as possible, this sketch demonstrates generating four output events from a single push-button.
1) Click:  rapid press and release
2) Double-Click:  two clicks in quick succession
3) Press and Hold:  holding the button down
4) Long Press and Hold:  holding the button for a long time
*/

// Button timing variables
int debounce = 50;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 500;            // max ms between clicks for a double click event
int holdTime = 2000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 5000;    // ms long hold period: how long to wait for press+hold event

							// Button variables
//int buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already


int processEncoder()
{
	int aVal;
	boolean bCW;
	aVal = digitalRead(EncoderDirA);
	switch (state)
	{
	case waiting:
		if (aVal != pinALast) { // Means the knob is rotating
								// if the knob is rotating, we need to determine direction
								// We do that by reading pin B.
			if (digitalRead(EncoderDirB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
				switch (buttonMenuPos)
				{
#ifdef EnableIron
				case 0:
					sIEncoderPosCount += 10;
					break;
#endif
				case 1:
					if (hGEncoderPosCount < iMAX_HOTAIR_TEMP)
						hGEncoderPosCount += 10;
					break;
				case 2:
					fanEncoderPosCount += 10;
					break;
				}
				bCW = true;
			}
			else {// Otherwise B changed first and we're moving CCW
				bCW = false;
				switch (buttonMenuPos)
				{
#ifdef EnableIron
				case 0:
					if (sIEncoderPosCount >= 10)
						sIEncoderPosCount -= 10;
					break;
#endif
				case 1:
					if (hGEncoderPosCount >= 10)
						hGEncoderPosCount -= 10;
					break;
				case 2:
					fanEncoderPosCount -= 10;
					break;
				}
			}
		}
		
		break;
	case configuring:
		if (aVal != pinALast) { // Means the knob is rotating
								// if the knob is rotating, we need to determine direction
								// We do that by reading pin B.
			if (digitalRead(EncoderDirB) != aVal)
			{
				bCW = true;
				return btnDOWN;
			}
			else // Otherwise B changed first and we're moving CCW
			{
				bCW = false;
				return btnUP;
			}
			return btnNONE;
			
		}
		break;
	}
	pinALast = aVal;
}
void processEncoderButton() {
	// Get button event and act accordingly
	int b = checkButton();
	switch (b)
	{
	case  1:
		//int buttonStatus = digitalRead(EncoderButton);
		//if (buttonStatus == LOW && buttonStatus != buttonLast)
		//{
			//Serial.println("Pushbutton");
		#ifdef EnableIron
					buttonMenuPos = buttonMenuPos == 2 ? 0 : buttonMenuPos + 1;
		#else
					buttonMenuPos = buttonMenuPos == 2 ? 1 : buttonMenuPos + 1;
		#endif
		//} buttonLast = buttonStatus;
		break;
	case  2: // double click
		switch (state)
		{
			case waiting:
				bHGHeaterOn = !bHGHeaterOn;
			break;
			case shutdown:
				state = configuring;
				redrawMenu();
			break;
		}
		break;
	case  3: //press and hold
		switch (state)
		{
		case waiting:
			state = shutdown;
			break;
		case shutdown:
			state = waiting;
			//turn off the heather while restart up
			hGEncoderPosCount = 0;
			digitalWrite(hGHeatingElementPin, LOW);
			break;
		}
		break;
	case  4: //long press and hold
		 
		switch (state)
		{
		 
			 
		case configuring:
			state = waiting;
			break;
		}

		break;
	}
}

int checkButton() {
	int event = 0;
	int buttonVal = digitalRead(EncoderButton);
	// Button pressed down
	if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
	{
		downTime = millis();
		ignoreUp = false;
		waitForUp = false;
		singleOK = true;
		holdEventPast = false;
		longHoldEventPast = false;
		if ((millis() - upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
		else  DConUp = false;
		DCwaiting = false;
	}
	// Button released
	else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
	{
		if (!ignoreUp)
		{
			upTime = millis();
			if (DConUp == false) DCwaiting = true;
			else
			{
				event = 2;
				DConUp = false;
				DCwaiting = false;
				singleOK = false;
			}
		}
	}
	// Test for normal click event: DCgap expired
	if (buttonVal == HIGH && (millis() - upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
	{
		event = 1;
		DCwaiting = false;
	}
	// Test for hold
	if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
		// Trigger "normal" hold
		if (!holdEventPast)
		{
			event = 3;
			waitForUp = true;
			ignoreUp = true;
			DConUp = false;
			DCwaiting = false;
			//downTime = millis();
			holdEventPast = true;
		}
		// Trigger "long" hold
		if ((millis() - downTime) >= longHoldTime)
		{
			if (! longHoldEventPast)
			{
				event = 4;
				longHoldEventPast = true;
			}
		}
	}
	buttonLast = buttonVal;
	return event;
}
