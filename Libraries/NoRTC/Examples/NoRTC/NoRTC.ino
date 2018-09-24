// el cable va desde el pin 2 al A0

#include <NoRTC.h>
int intNoRTC= 0;
int pwmpin=2;
char buf[50];
char day[10];
NoRTC rtc;


void print_time()
{
  Time t = rtc.now;
/*
    

    switch (t.day)
    {
    case 1: strcpy(day, "Sunday"); break;
    case 2: strcpy(day, "Monday"); break;
    case 3: strcpy(day, "Tuesday"); break;
    case 4: strcpy(day, "Wednesday"); break;
    case 5: strcpy(day, "Thursday"); break;
    case 6: strcpy(day, "Friday"); break;
    case 7: strcpy(day, "Saturday"); break;
    }
    */
    snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day, t.yr, t.mon, t.date, t.hr, t.min, t.sec);
    Serial.println(buf);
}


void setup()
{
    Serial.begin(9600);
    Time t(2014, 9, 22, 19, 03, 0, 2);
    rtc.setPin(intNoRTC,pwmpin);
    attachInterrupt(intNoRTC, wrap, RISING);
    rtc.setTime(t);
}
void wrap ()
{
  rtc.clockCounter();
}

void loop()
{

  print_time();
}