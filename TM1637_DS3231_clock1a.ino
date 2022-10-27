// base sketch from https://brainy-bits.com/tutorials/4-bits-7-segment-led-display-with-arduino/
// changed TM1637 library by niq_ro for degree, r & h letter
// DS3231 clock on TM1637 LED display by niq_ro from http://www.tehnic.go.ro
// & http://arduinotehniq.com/


#include <Encoder.h> // from http://www.pjrc.com/teensy/td_libs_Encoder.html
Encoder knob(3, 2); //encoder connected to pins 2 and 3 (and ground)
#define buton 6

#include "TM1637.h"  // https://github.com/tehniq3/TM1637-display
 
//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//0~9,A,b,C,d,E,F,"-"," ",degree,r,h

#define CLK 9//Pins for TM1637       
#define DIO 8
TM1637 tm1637(CLK,DIO);

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
//RTC_DS3231 rtc;
RTC_DS1307 rtc;

int hh, mm; 

// These variables are for the push button routine
int buttonstate = 0; //flag to see if the button has been pressed, used internal on the subroutine only
int pushlengthset = 2500; // value for a long push in mS
int pushlength = pushlengthset; // set default pushlength
int pushstart = 0;// sets default push value for the button going low
int pushstop = 0;// sets the default value for when the button goes back high

int knobval; // value for the rotation of the knob
boolean buttonflag = false; // default value for the button flag
int sethourstemp;
int setminstemp;

#define goarna 7 // buzzer

void setup()
{
  tm1637.init();
  tm1637.set(5); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  rtc.begin();
// manual adjust
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
// automatic adjust
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

   pinMode(buton,INPUT);//push button on encoder connected 
  digitalWrite(buton,HIGH); //Pull at 1 high

   pinMode(goarna, OUTPUT);   
   digitalWrite(goarna, LOW); //set in 0 logical level
   tone(goarna, 4000,50); 
}//end "setup()"
 
void loop(){
DateTime now = rtc.now();
hh = now.hour(), DEC;
mm = now.minute(), DEC;

tm1637.point(POINT_ON);
if ((hh/10) == 0) tm1637.display(0,17);
else
    tm1637.display(0,hh/10);     // hour
    tm1637.display(1,hh%10);
    tm1637.display(2,mm/10);    // minutes
    tm1637.display(3,mm%10);    // 
delay(500);

 pushlength = pushlengthset;
    pushlength = getpushlength ();
    delay (10);
    
    if (pushlength > pushlengthset)
    {
    tone(goarna, 2000,50);
    //   ShortPush ();   
    }
      
       //This runs the setclock routine if the knob is pushed for a long time
       if (pushlength < pushlengthset) {
        tone(goarna, 1000,50);
       //  delay(500);
         DateTime now = rtc.now();
         sethourstemp=now.hour(),DEC;
         setminstemp=now.minute(),DEC;       
         setclock();
         pushlength = pushlengthset;
       };

    tm1637.point(POINT_OFF);
if ((hh/10) == 0) tm1637.display(0,17);
else
    tm1637.display(0,hh/10);     // hour
    tm1637.display(1,hh%10);
    tm1637.display(2,mm/10);    // minutes
    tm1637.display(3,mm%10);    // 
delay(500);
}// end loop() 

// subroutine to return the length of the button push.
int getpushlength () {
  buttonstate = digitalRead(buton);  
       if(buttonstate == LOW && buttonflag==false) {     
              pushstart = millis();
              buttonflag = true;
          };
          
       if (buttonstate == HIGH && buttonflag==true) {
         pushstop = millis ();
         pushlength = pushstop - pushstart;
         buttonflag = false;
       };
       return pushlength;
}

int sethours () {
  if ((sethourstemp/10) == 0) tm1637.display(0,17);
else
    tm1637.display(0,sethourstemp/10);     // hour
    tm1637.display(1,sethourstemp%10);
    tm1637.display(2,16);    // minutes
    tm1637.display(3,16);    // 
    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return sethourstemp;
    }
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) {
      knobval = -1;
    }
    if (knobval > 1) {
      knobval = 1;
    }
    sethourstemp=sethourstemp + knobval;
    if (sethourstemp < 0) {
      sethourstemp = 23;
    }
    if (sethourstemp > 23) {
      sethourstemp = 0;
    }
    sethours();
}

int setmins () {
    tm1637.display(0,16);     // hour
    tm1637.display(1,16);
    tm1637.display(2,setminstemp/10);    // minutes
    tm1637.display(3,setminstemp%10);    // 
    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return setminstemp;
    }
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) {
      knobval = -1;
    }
    if (knobval > 1) {
      knobval = 1;
    }
    setminstemp=setminstemp + knobval;
    if (setminstemp < 0) {
      setminstemp = 59;
    }
    if (setminstemp > 59) {
      setminstemp = 0;
    }
    setmins();
}

//sets the clock
void setclock (){
   sethours ();
   delay(500);
   setmins ();
   delay(500);
   rtc.adjust(DateTime(2017,4,1,sethourstemp,setminstemp,0));
   delay (500); 
   hh = sethourstemp;
   mm = setminstemp;
}

