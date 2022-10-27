//Demo for 4-Digit Display and 4-Digit Display (D4056A) by Catalex
//Hardware: A 4-Digit Display or a 4-Digit Display (D4056A) 
//Board: Catduino or Arduino UNO R3,Arduino Mega2560...
//IDE:   Arduino-1.0
//Function: Sixteen characters that is 0 to 9 and A b C d E F will flow 
//		    from right to left.
//Store: http://www.aliexpress.com/store/1199788
/*********************************************************************/
#include "TM1637.h"  // https://github.com/tehniq3/TM1637-display
#define CLK 9//pins definitions for TM1637 and can be changed to other ports       
#define DIO 8
TM1637 tm1637(CLK,DIO);
void setup()
{
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop()
{
  int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
  int8_t ListDisp[4];
  unsigned char i = 0;
  unsigned char count = 0;
  delay(150);
  while(1)
  {
    i = count;
    count ++;
    if(count == sizeof(NumTab)) count = 0;
    for(unsigned char BitSelect = 0;BitSelect < 4;BitSelect ++)
    {
      ListDisp[BitSelect] = NumTab[i];
      i ++;
      if(i == sizeof(NumTab)) i = 0;
    }
    tm1637.display(0,ListDisp[0]);
    tm1637.display(1,ListDisp[1]); 
    tm1637.display(2,ListDisp[2]);
    tm1637.display(3,ListDisp[3]);
    delay(300);
  }
}
