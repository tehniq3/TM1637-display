		//	Author:Fred.Chu
	//	Date:9 April,2013
	//
	//	Applicable Module:
	//		  4-Digit Display by catalex
	//		  4-Digit Display (D4056A) by catalex
	//   Store: http://www.aliexpress.com/store/1199788
	//
	//	This library is free software; you can redistribute it and/or
	//	modify it under the terms of the GNU Lesser General Public
	//	License as published by the Free Software Foundation; either
	//	version 2.1 of the License, or (at your option) any later version.
	//
	//	This library is distributed in the hope that it will be useful,
	//	but WITHOUT ANY WARRANTY; without even the implied warranty of
	//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	//	Lesser General Public License for more details.
	//
	//	You should have received a copy of the GNU Lesser General Public
	//	License along with this library; if not, write to the Free Software
	//	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
	//
	//	Modified record:
	//      Author: Nicu FLORICA (niq_ro) - http://www.tehnic.go.ro & http://www.arduinotehniq.com
      //      Date: 25 november, 2015
      //      Note: added sign for degree, letter 'r' & 'h'
      //      Date: 10 march, 2016
      //      Note: added sign for degree, letter 'r', 'h' & 'n'
      //      Date: 21 september, 2016
      //      Note: added letter 't', "u up and _ bottom" & "u bottom and - up" 
      // 	Date: 27 October 2022
      //  	Note: added 'o' and 'P'
	/*******************************************************************************/
	
#ifndef TM1637_h
#define TM1637_h
#include <inttypes.h>
#include <Arduino.h>
	//************definitions for TM1637*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
	
#define STARTADDR  0xc0 
	/**** definitions for the clock point of the 4-Digit Display *******/
#define POINT_ON   1
#define POINT_OFF  0
	/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7
//--------------------------------------------------------//
//Special characters index of tube table
#define INDEX_NEGATIVE_SIGN	16
#define INDEX_BLANK			17
/************definitions for type of the 4-Digit Display*********************/
#define D4036B 0
#define D4056A 1

	class TM1637
	{
	  public:
		uint8_t Cmd_SetData;
		uint8_t Cmd_SetAddr;
		uint8_t Cmd_DispCtrl;
		boolean _PointFlag; 	//_PointFlag=1:the clock point on
		uint8_t _DispType;
		TM1637(uint8_t, uint8_t);
		void init(uint8_t = D4036B);
		void writeByte(int8_t wr_data);//write 8bit data to tm1637
		void start(void);//send start bits
		void stop(void); //send stop bits
		void display(int8_t DispData[]);
		void display(uint8_t BitAddr,int8_t DispData);
		void display(double Decimal);
		void display(int16_t Decimal);
		void clearDisplay(void);
		void set(uint8_t = BRIGHT_TYPICAL,uint8_t = 0x40,uint8_t = 0xc0);//To take effect the next time it displays.
		void point(boolean PointFlag);//whether to light the clock point ":".To take effect the next time it displays.
		void coding(int8_t DispData[]); 
		int8_t coding(int8_t DispData); 
	  private:
		uint8_t Clkpin;
		uint8_t Datapin;
		uint8_t DecPoint;
		boolean BlankingFlag;
	};
#endif
