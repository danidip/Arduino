 
#include "MenuDoubleHelper.h"

MenuDoubleHelper::MenuDoubleHelper( double iMin, double iMax, double iStart, double iStep ):
m_min( iMin), m_max( iMax ), m_curNum( iStart ), m_step( iStep)
{
}
double MenuDoubleHelper::numIncrease()
{
  
  if( m_curNum + m_step <= m_max )
  {
    m_curNum += m_step;
  }
  return m_curNum;
}
double MenuDoubleHelper::numDecrease()
{
  if( m_curNum - m_step >= m_min )
  {
    m_curNum -= m_step;
  }  
  return m_curNum;
}
double MenuDoubleHelper::getDouble()
{
  return m_curNum;  
}

