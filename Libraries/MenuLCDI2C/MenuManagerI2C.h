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


#include "MenuEntryI2C.h"
#include "MenuLCDI2C.h"
#include "MenuIntHelperI2C.h"
#include "MenuFloatHelper.h"
#include "MenuDoubleHelper.h"

enum MENU_ACTIONI2C { MENU_ACTIONI2C_UP, MENU_ACTIONI2C_DOWN, MENU_ACTIONI2C_SELECT, MENU_ACTIONI2C_BACK };

class MenuManagerI2C
{
  public:
  MenuManagerI2C(MenuLCDI2C* pMenuLCD);
  bool addMenuRoot( MenuEntryI2C * p_MenuEntryI2C);
  MenuEntryI2C * getMenuRoot();
  void DrawMenu();
  void DoMenuAction( MENU_ACTIONI2C action );
  void MenuUp();
  void MenuDown();
  void MenuSelect();
  void MenuBack();
  void addChild( MenuEntryI2C * p_MenuEntryI2C );    
  void addSibling( MenuEntryI2C * p_MenuEntryI2C );  
  void SelectRoot();
  void DoIntInput( int iMin, int iMax, int iStart, int iSteps, char **label, int iLabelLines, int *pInt );
  void DoFloatInput( float iMin, float iMax, float iStart, float iSteps, char **label, int iLabelLines, float *pFloat );
  void DoDoubleInput(double iMin, double iMax, double iStart, double iSteps, char **label, int iLabelLines, double *pDouble);
  void DrawInputRow( char *pString );

  void WipeMenu( MenuLCDI2C::Direction dir);


  
  private:
  MenuEntryI2C* m_pRootMenuEntryI2C;
  MenuEntryI2C* m_pCurrentMenuEntry;
  MenuLCDI2C* m_pMenuLCD;
  unsigned int m_fDoingIntInput;
  unsigned int m_fDoingFloatInput;
  unsigned int m_fDoingDoubleInput;
  MenuIntHelperI2C *m_pMenuIntHelper;
  MenuFloatHelper *m_pMenuFloatHelper;
  MenuDoubleHelper *m_pMenuDoubleHelper;
  int m_iIntLine;
  int *m_pInt;
  float *m_pFloat;
  double *m_pDouble;
};



