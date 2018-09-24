#include <arduino.h>

#include <LiquidCrystal_I2C.h>
#include "MenuLCDI2C.h"
 
MenuLCDI2C::MenuLCDI2C(int characters, int lines):
	m_characters( characters ),
    m_lines( lines )
	{
	}
	 
MenuLCDI2C::MenuLCDI2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
: m_lcd_Addr (lcd_Addr),
  m_characters (lcd_cols),
  m_lines (lcd_rows)
{
}

bool MenuLCDI2C::MenuLCDSetup()
{
  m_pLCD = new LiquidCrystal_I2C(m_lcd_Addr, m_characters, m_lines);
  m_pLCD->begin(m_characters, m_lines);
}

bool MenuLCDI2C::PrintMenu( char* pString[], int nLines, int nSelectedLine = 0 )
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

void MenuLCDI2C::WipeMenu( char* pString[], int nLines, MenuLCDI2C::Direction dir )
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


bool MenuLCDI2C::PrintLineRight( char* pString, int iRow )
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

bool MenuLCDI2C::PrintLine( char* pString, int iRow )
{
  //clear the line
  m_pLCD->setCursor( 0, iRow );
  m_pLCD->print( pString );
}

int MenuLCDI2C::getLines()
{
  return m_lines;
}
int MenuLCDI2C::getCharacters()
{
  return m_characters;
}

void MenuLCDI2C::setLines(int lines) 
{
   m_lines = lines;
}
void MenuLCDI2C::setCharacters(int chars)
{
  m_characters = chars;
}
void MenuLCDI2C::ClearLCD()
{
  m_pLCD->clear();
}

LiquidCrystal_I2C * MenuLCDI2C::getLCD()
{
  return m_pLCD;
}
 

void MenuLCDI2C::setLCD (LiquidCrystal_I2C* LCD)
{
	m_pLCD = LCD;
}
