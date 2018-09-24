 


#ifndef MenuDoubleHelper_H

#define MenuDoubleHelper_H 1
class MenuDoubleHelper
{
  public:
  MenuDoubleHelper( double iMin, double iMax, double iStart, double iStep );
  double numIncrease();
  double numDecrease();
  double getDouble();
  private:
  double m_curNum;
  double m_min;
  double m_max;
  double m_step;
};
#endif


