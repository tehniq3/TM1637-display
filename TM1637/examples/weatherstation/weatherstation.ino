// base sketch from https://brainy-bits.com/tutorials/4-bits-7-segment-led-display-with-arduino/
// changed TM1637 library by niq_ro for degree, r & h letter
// thermometer & hygromether with DHT sensor on TM1637 LED display by niq_ro from http://www.tehnic.go.ro
// & http://arduinotehniq.com/

#include "TM1637.h"  // https://github.com/tehniq3/TM1637-display
 
//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//0~9,A,b,C,d,E,F,"-"," ",degree,r,h,n
// 10 -> A, 11 -> b, 12 ->C, 13 -> d, 14 -> E, 15 -> F
// 16 -> -, 17 -> space, 18 -> degree sign, 19 -> r, 20 -> h, 21 -> n


#include <DHT.h> 
#define DHTPIN A2     // what pin we're connected the DHT output
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22 
DHT dht(DHTPIN, DHTTYPE); 
 
#define CLK 9//Pins for TM1637       
#define DIO 8
 
TM1637 tm1637(CLK,DIO);
 
void setup(){
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
 
  delay(1500);//Delay to let system boot
  dht.begin();   
 
}//end "setup()"
 
 
 
void loop(){
 
  //Start of Program 
 
//  DHT.read11(dht_pin);
 
   int humidity = dht.readHumidity();
   int temp = dht.readTemperature();  
//   int temp = 23;
//   int humidity = 48;
 
 int digitoneT = temp / 10;
 int digittwoT = temp % 10;
 
 int digitoneH = humidity / 10;
 int digittwoH = humidity % 10;
  
 
    tm1637.display(0,digitoneT); 
    tm1637.display(1,digittwoT);
    tm1637.display(2,18); // put degree
    tm1637.display(3,12);  // put a C at the end
    
    delay (3000);
    
    tm1637.display(0,17);  // empty
    tm1637.display(1,17);  // empty
    tm1637.display(2,17);  // empty
    tm1637.display(3,17);  // empty


    tm1637.display(0,digitoneH); 
    tm1637.display(1,digittwoH);
    tm1637.display(2,19);  // r
    tm1637.display(3,20);  // h
 
  
  //Fastest should be once every two seconds.
    delay(3000);
 
}// end loop() 
