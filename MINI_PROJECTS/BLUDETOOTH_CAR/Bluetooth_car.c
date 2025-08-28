
/*
IN1	IN2	Spinning Direction
Low(0)	Low(0)	Motor OFF
High(1)	Low(0)	Forward
Low(0)	High(1)	Backward
High(1)	High(1)	Motor OFF
*/

#include<lpc21xx.h>
#include"delay.h"
#include"LCD.h"
#include"UART0.h"
#define TXRX 0x05
USC M;
int main()
{
	UART0_CONFIG();
	LCD_INIT();
	IODIR0 =  M10 | M11 | M20 | M21 ;
	LCD_C(0X84);
	LCD_STR("V24CE9M1");
	LCD_C(0Xc0);
	LCD_STR("BLUETOOTH CAR");
	delay_ms(500);
	
	
	
	
	while(1)
	{
	
	M = UART0_RX();
	
	if(M == 'F') 
	{
		UART0_STR("Moving Forward ");
		LCD_C(0X01);
		LCD_C(0X80);
		LCD_STR("MOVING FORWARD");
		IOSET0 =  M10;
		IOCLR0 =  M11;
		IOSET0 =  M20;
		IOCLR0 =  M21;
		
	}
	else if(M == 'B')
	{
		UART0_STR("Moving Backward");
		LCD_C(0X01);
		LCD_C(0X80);
		LCD_STR("MOVING BACKWARD");
		IOCLR0 =  M10;
		IOSET0 =  M11;
		IOCLR0 =  M20;
		IOSET0 =  M21;
		
	}
	else if(M == 'R')
	{
		UART0_STR("Moving Right");
		LCD_C(0X01);
		LCD_C(0X80);
		LCD_STR("MOVING RIGHT");
		IOSET0 =  M10;
		IOCLR0 =  M11;
		IOCLR0 =  M20;
		IOSET0 =  M21;
		
		
	}
	else if(M == 'L')
	{
		UART0_STR("Moving Left");
		LCD_C(0X01);
		LCD_C(0X80);
		LCD_STR("MOVING LEFT");
		IOCLR0 =  M10;
		IOSET0 =  M11;
		IOSET0 =  M20;
		IOCLR0 =  M21;
		M = 'c';
	}
	else if(M == 'S')
	{
		UART0_STR("STOPED");
		LCD_C(0X01);
		LCD_C(0X80);
		LCD_STR("STOPED");
		IOSET0 =  M10;
		IOSET0 =  M11;
		IOSET0 =  M20;
		IOSET0 =  M21;
	
	}
	UART0_TX('\n');
	
	
	}
	
}
