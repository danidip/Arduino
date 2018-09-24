 
#include "MenuFloatHelper.h"

MenuFloatHelper::MenuFloatHelper( float iMin, float iMax, float iStart, float iStep ):
m_min( iMin), m_max( iMax ), m_curNum( iStart ), m_step( iStep)
{
}
float MenuFloatHelper::numIncrease()
{
  
  if( m_curNum + m_step <= m_max )
  {
    m_curNum += m_step;
  }
  return m_curNum;
}
float MenuFloatHelper::numDecrease()
{
  if( m_curNum - m_step >= m_min )
  {
    m_curNum -= m_step;
  }  
  return m_curNum;
}
float MenuFloatHelper::getFloat()
{
  return m_curNum;  
}

