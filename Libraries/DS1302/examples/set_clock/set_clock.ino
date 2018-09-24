/*
Example sketch for interfacing with the DS1302 timekeeping chip.

Copyright (c) 2009, Matt Sparks
All rights reserved.

http://quadpoint.org/projects/arduino-ds1302
*/
#include <stdio.h>
#include <string.h>
#include <Time.h>
#include <DS1302.h>



/* Set the appropriate digital I/O pin connections */
uint8_t RST_PIN   = A2;
uint8_t DAT_PIN   = A4;
uint8_t CLK_PIN = A5;


const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/* Create buffers */
char buf[50];
char charday[10];

/* Create a DS1302 object */
DS1302 rtc;


void print_time()

{
  /* Get the current time and date from the chip */
  tmElements_t t ;
  rtc.read(t);

  /* Name the day of the week */
  memset(charday, 0, sizeof(charday));  /* clear day buffer */
  switch (t.Day) {
    case 1:
      strcpy(charday, "Sunday");
      break;
    case 2:
      strcpy(charday, "Monday");
      break;
    case 3:
      strcpy(charday, "Tuesday");
      break;
    case 4:
      strcpy(charday, "Wednesday");
      break;
    case 5:
      strcpy(charday, "Thursday");
      break;
    case 6:
      strcpy(charday, "Friday");
      break;
    case 7:
      strcpy(charday, "Saturday");
      break;
  }

  /* Format the time and date and insert into the temporary buffer */
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           charday,
           tmYearToCalendar(t.Year), t.Month, t.Day,
           t.Hour, t.Minute, t.Second);

  /* Print the formatted string to serial so we can see the time */
  Serial.println(buf);
}


void setup()
{
  Serial.begin(9600);
  rtc.setup(RST_PIN, DAT_PIN, CLK_PIN);
  /* Initialize a new chip by turning off write protection and clearing the
     clock halt flag. These methods needn't always be called. See the DS1302
     datasheet for details. */
  rtc.writeProtect(false);
  rtc.halt(false);


 


  /* Make a new time object to set the date and time */
  /*   Tuesday, May 19, 2009 at 21:16:37.            */
  tmElements_t t;
  t.Year =2009;
  t.Month =  5;
  t.Day = 19;
  t.Hour = 21;
  t.Minute = 16;
  t.Second = 37;
  if (getDate(__DATE__, t) && getTime(__TIME__, t)) {
  
   
   if (rtc.write(t))
    Serial.println("Grabo");
    else
     Serial.println("no Grabo1");
    
  }
  else
  {
    Serial.println("no Grabo");
  }
}

uint8_t bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}

/* Loop and print the time every second */
void loop()
{
  print_time();
  delay(1000);
}


bool getTime(const char *str, tmElements_t &tm)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str, tmElements_t &tm)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;
  //Serial.print("String:");
  //Serial.println(str);
  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  
  return true;
}