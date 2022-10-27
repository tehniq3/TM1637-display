//Demo for 4-Digit Display only by Catalex
//Hardware: A 4-Digit Display 
//Board: Catduino or Arduino UNO R3,Arduino Mega2560...
//IDE:   Arduino-1.0
//Function: Display the time on the digital tube.
//Store: http://www.aliexpress.com/store/1199788
/*********************************************************************/
#include <TimerOne.h>
#include "TM1637.h"  // https://github.com/tehniq3/TM1637-display
#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 4;
unsigned char hour = 15;


#define CLK 9//pins definitions for TM1637 and can be changed to other ports    
#define DIO 8
TM1637 tm1637(CLK,DIO);

void setup()
{
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR  
}
void loop()
{
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }
  
}
void TimingISR()
{
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;  
  }
 // Serial.println(second);
  ClockPoint = (~ClockPoint) & 0x01;
}
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF); 
  TimeDisp[0] = hour / 10;
  TimeDisp[1] = hour % 10;
  TimeDisp[2] = minute / 10;
  TimeDisp[3] = minute % 10;
  Update = OFF;
}
