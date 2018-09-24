/*
 Arduino_LCD_Menu Library
Copyright Dustin Andrews, David Andrews 2012 
Licensed under the follwing license:

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
in the documentation and/or other materials provided with the distribution. 
The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#include "MenuManager.h"
#include "MenuEntry.h"

MenuManager::MenuManager(MenuLCD* pMenuLCD)
: m_pMenuLCD( pMenuLCD),
  m_fDoingIntInput( false )
{
}

bool MenuManager::addMenuRoot( MenuEntry * p_menuItem)
{
  m_pRootMenuEntry = p_menuItem;
  m_pCurrentMenuEntry = p_menuItem;
}

void MenuManager::addSibling( MenuEntry * p_menuItem)
{
  m_pCurrentMenuEntry->addSibling( p_menuItem );  
}

void MenuManager::addChild( MenuEntry * p_menuItem)
{
  m_pCurrentMenuEntry->addChild( p_menuItem );
}


MenuEntry * MenuManager::getMenuRoot()
{
  return m_pRootMenuEntry;
}


void MenuManager::WipeMenu( MenuLCD::Direction dir )
{
  if( dir == MenuLCD::LEFT )
  {
    for( int i = 0; i < m_pMenuLCD->getCharacters(); ++i )
    { 
      m_pMenuLCD->getLCD()->scrollDisplayLeft();
      delay(75);
    }
  }
  else
  {
    for( int i = 0; i < m_pMenuLCD->getCharacters(); ++i )
    {
      m_pMenuLCD->getLCD()->scrollDisplayRight();
      delay(75);
    }
  }
}


void MenuManager::DrawMenu()
{
  if( m_pCurrentMenuEntry->getNextSibling() == NULL )
  {
    if( m_pCurrentMenuEntry->getPrevSibling() != NULL )
    {
      char *pMenuTexts[2] = {m_pCurrentMenuEntry->getPrevSibling()->getMenuText(), m_pCurrentMenuEntry->getMenuText()};
      m_pMenuLCD->PrintMenu( pMenuTexts, 2, 1 );
    }
    else
    {
      char * pText = m_pCurrentMenuEntry->getMenuText();
      m_pMenuLCD->PrintMenu( &pText, 1, 0 );      
    }
  }
  else
  {
    char *pMenuTexts[2] = {m_pCurrentMenuEntry->getMenuText(), m_pCurrentMenuEntry->getNextSibling()->getMenuText()};
    m_pMenuLCD->PrintMenu( pMenuTexts, 2, 0 );
  }
}

void MenuManager::DoMenuAction( MENU_ACTION action )
{
  if( m_fDoingIntInput == true )
  {
    int iNewNum = m_pMenuIntHelper->getInt();
    char buff[64];
    switch (action )
    {
      case MENU_ACTION_UP:
        iNewNum = m_pMenuIntHelper->numDecrease();
        itoa( iNewNum, buff, 10 );
        DrawInputRow( buff );
        *m_pInt = iNewNum;
        break;
      case MENU_ACTION_DOWN:
        iNewNum = m_pMenuIntHelper->numIncrease();
        itoa( iNewNum, buff, 10 );
        DrawInputRow( buff );
        *m_pInt = iNewNum;
        break;
      case MENU_ACTION_SELECT:
        m_fDoingIntInput = false;
        DrawMenu();
        break;
      case MENU_ACTION_BACK:
        m_fDoingIntInput = false;
        DrawMenu();
        break;
    }    
  }
  else
  {
    m_pMenuLCD->ClearLCD();
    delay(10);
    DrawMenu();
    switch (action )
    {
      case MENU_ACTION_UP:
        this->MenuUp();
        break;
      case MENU_ACTION_DOWN:
        this->MenuDown();
        break;
      case MENU_ACTION_SELECT:
        this->MenuSelect();
        break;
      case MENU_ACTION_BACK:
        this->MenuBack();
        break;
    }
  }
}

void MenuManager::MenuUp()
{
  MenuEntry *prev = m_pCurrentMenuEntry->getPrevSibling();
  if( prev != NULL )
  {
    m_pCurrentMenuEntry = prev;
  }
  else
  {
    //Flash?
  }
  DrawMenu();
}

void MenuManager::MenuDown()
{
  MenuEntry *next = m_pCurrentMenuEntry->getNextSibling();
  if( next != NULL )
  {
    m_pCurrentMenuEntry = next;
  }
  else
  {
    //Flash?
  }
  DrawMenu();

}

void MenuManager::MenuSelect()
{
  MenuEntry *child = m_pCurrentMenuEntry->getChild();
  if( child != NULL )
  {
    WipeMenu( MenuLCD::LEFT);
    m_pCurrentMenuEntry = child;
    DrawMenu();
  }
  else
  {
    if( !m_pCurrentMenuEntry->isBackEntry() )
    {
      WipeMenu( MenuLCD::LEFT);
    }
    m_pCurrentMenuEntry->ExecuteCallback();
    if( !m_fDoingIntInput )
    {
      DrawMenu();
    }
  }  
}

void MenuManager::MenuBack()
{
  if( m_pCurrentMenuEntry->getParent() != NULL )
  {
    WipeMenu( MenuLCD::RIGHT);
    m_pCurrentMenuEntry = m_pCurrentMenuEntry->getParent();
    DrawMenu();
  }
}

void MenuManager::SelectRoot()
{
  m_pCurrentMenuEntry = m_pRootMenuEntry;
}

void MenuManager::DrawInputRow( char *pString )
{
  m_pMenuLCD->PrintLineRight( pString, m_pMenuLCD->getLines() - 1 );
}

void MenuManager::DoIntInput( int iMin, int iMax, int iStart, int iSteps, char **label, int iLabelLines, int *pInt )
{
  char buff[64];
  m_fDoingIntInput = true;
  m_pInt = pInt;
  *pInt = iStart;
  //The MenuIntHelper class will keep track of the input, but all other logic will stay here
  if( m_pMenuIntHelper != NULL )
  {
    delete m_pMenuIntHelper;
  }
  m_pMenuIntHelper = new MenuIntHelper(  iMin, iMax, iStart, iSteps );
  //print the label
  m_pMenuLCD->PrintMenu( label, iLabelLines, -1 );
  m_iIntLine = iLabelLines;  //Off by one because index is zero based
  itoa( m_pMenuIntHelper->getInt(), buff, 10 );  
  DrawInputRow( buff );
}
void ftoa(float f, char *str, uint8_t precision) {
  uint8_t i, j, divisor = 1;
  int8_t log_f;
  int32_t int_digits = (int)f;             //store the integer digits
  float decimals;
  char s1[12];

  memset(str, 0, sizeof(str));  
  memset(s1, 0, 10);

  if (f < 0) {                             //if a negative number 
    str[0] = '-';                          //start the char array with '-'
    f = abs(f);                            //store its positive absolute value
  }
  log_f = ceil(log10(f));                  //get number of digits before the decimal
  if (log_f > 0) {                         //log value > 0 indicates a number > 1
    if (log_f == precision) {              //if number of digits = significant figures
      f += 0.5;                            //add 0.5 to round up decimals >= 0.5
      itoa(f, s1, 10);                     //itoa converts the number to a char array
      strcat(str, s1);                     //add to the number string
    }
    else if ((log_f - precision) > 0) {    //if more integer digits than significant digits
      i = log_f - precision;               //count digits to discard
      divisor = 10;
      for (j = 0; j < i; j++) divisor *= 10;    //divisor isolates our desired integer digits 
      f /= divisor;                             //divide
      f += 0.5;                            //round when converting to int
      int_digits = (int)f;
      int_digits *= divisor;               //and multiply back to the adjusted value
      itoa(int_digits, s1, 10);
      strcat(str, s1);
    }
    else {                                 //if more precision specified than integer digits,
      itoa(int_digits, s1, 10);            //convert
      strcat(str, s1);                     //and append
    }
  }

  else {                                   //decimal fractions between 0 and 1: leading 0
    s1[0] = '0';
    strcat(str, s1);
  }

  if (log_f < precision) {                 //if precision exceeds number of integer digits,
    decimals = f - (int)f;                 //get decimal value as float
    strcat(str, ".");                      //append decimal point to char array

    i = precision - log_f;                 //number of decimals to read
    for (j = 0; j < i; j++) {              //for each,
      decimals *= 10;                      //multiply decimals by 10
      if (j == (i-1)) decimals += 0.5;     //and if it's the last, add 0.5 to round it
      itoa((int)decimals, s1, 10);         //convert as integer to character array
      strcat(str, s1);                     //append to string
      decimals -= (int)decimals;           //and remove, moving to the next
    }
  }
}
void MenuManager::DoFloatInput( float iMin, float iMax, float iStart, float iSteps, char **label, int iLabelLines, float *pFloat )
{
  char buff[64];
  m_fDoingIntInput = true;
  m_pFloat = pFloat;
  *pFloat = iStart;
  //The MenuIntHelper class will keep track of the input, but all other logic will stay here
  if( m_pMenuIntHelper != NULL )
  {
    delete m_pMenuIntHelper;
  }
  m_pMenuFloatHelper = new MenuFloatHelper(  iMin, iMax, iStart, iSteps );
  //print the label
  m_pMenuLCD->PrintMenu( label, iLabelLines, -1 );
  m_iIntLine = iLabelLines;  //Off by one because index is zero based
  ftoa( m_pMenuFloatHelper->getFloat(), buff, 10 );  
  DrawInputRow( buff );
}

