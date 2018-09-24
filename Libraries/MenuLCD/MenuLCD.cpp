#include <arduino.h>
#include <LiquidCrystal.h>
#include "MenuLCD.h"

MenuLCD::MenuLCD(int characters, int lines):
	m_characters( characters ),
  m_lines( lines )
	{
	}
	
MenuLCD::MenuLCD(int LCDRS, int LCDE, int LCDD4, int LCDD5, int LCDD6, int LCDD7, int characters, int lines)
: m_LCDRS( LCDRS ),
  m_LCDE( LCDE ),
  m_LCDD4( LCDD4 ),
  m_LCDD5( LCDD5 ),
  m_LCDD6( LCDD6 ),
  m_LCDD7( LCDD7 ),
  m_characters( characters ),
  m_lines( lines )
{
}

bool MenuLCD::MenuLCDSetup()
{
  m_pLCD = new LiquidCrystal(m_LCDRS, m_LCDE, m_LCDD4, m_LCDD5, m_LCDD6, m_LCDD7);
  m_pLCD->begin(m_characters, m_lines);
}

bool MenuLCD::PrintMenu( char* pString[], int nLines, int nSelectedLine = 0 )
{
  m_pLCD->clear();
  for( int i =0; i < nLines; i++ )

  {
    if( i == nSelectedLine )
    {//this line should be surrounded by []
       m_pLCD->setCursor(0, i);
       m_pLCD->write( '[');
       m_pLCD->setCursor(1,i);
       m_pLCD->print( pString[i] );
       m_pLCD->setCursor(m_characters - 1, i);
       m_pLCD->write( ']');
    }
    else
    {
      m_pLCD->setCursor(0,i);
      m_pLCD->write( ' ');
      m_pLCD->print( pString[i] );
      m_pLCD->setCursor(m_characters - 1, i);
       m_pLCD->write( ' ');
    }

  }
}

void MenuLCD::WipeMenu( char* pString[], int nLines, MenuLCD::Direction dir )
{
  char lineBuff[ 256 ];  
  m_pLCD->clear();
  for( int i = 0; i < m_characters; ++i )
  {
    for( int j =0; j < nLines; ++j )
    {
      m_pLCD->setCursor( 0, j );
      m_pLCD->setCursor(0,j);
      if (strlen( pString[j] ) > i )
      {
        if( dir == LEFT )
        {
          strcpy(lineBuff, (pString[j] + i ) );
          strcat(lineBuff, "  " );
        }
        else
        {
          lineBuff[0] = '\0';
          for( int k = 0; k < i; ++k )
          {
            strcat(lineBuff, " " );
          }
          strcat(lineBuff, pString[j]);
        }
      }
      else
      {
        strcpy(lineBuff, " " );
      }
      m_pLCD->print( lineBuff );
      
    }
  //delay(50);
  }
}


bool MenuLCD::PrintLineRight( char* pString, int iRow )
{
  //clear the line
  char buff[ m_characters ];
  for( int i = 0; i < m_characters; ++i )
  {
    buff[i] = ' ';
  }
  m_pLCD->setCursor( 0, iRow );
  m_pLCD->print( buff );
  //now print the new number
  m_pLCD->setCursor(m_characters - strlen(pString),iRow);
  m_pLCD->print( pString );  
}

bool MenuLCD::PrintLine( char* pString, int iRow )
{
  //clear the line
  m_pLCD->setCursor( 0, iRow );
  m_pLCD->print( pString );
}

int MenuLCD::getLines()
{
  return m_lines;
}
int MenuLCD::getCharacters()
{
  return m_characters;
}

void MenuLCD::setLines(int lines) 
{
   m_lines = lines;
}
void MenuLCD::setCharacters(int chars)
{
  m_characters = chars;
}
void MenuLCD::ClearLCD()
{
  m_pLCD->clear();
}

LiquidCrystal * MenuLCD::getLCD()
{
  return m_pLCD;
}
 

void MenuLCD::setLCD (LiquidCrystal* LCD)
{
	m_pLCD = LCD;
}
