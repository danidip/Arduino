 


#ifndef MenuFloatHelper_H

#define MenuFloatHelper_H 1
class MenuFloatHelper
{
  public:
  MenuFloatHelper( float iMin, float iMax, float iStart, float iStep );
  float numIncrease();
  float numDecrease();
  float getFloat();
  private:
  float m_curNum;
  float m_min;
  float m_max;
  float m_step;
};
#endif


