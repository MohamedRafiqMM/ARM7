#include"delay.h"
#include"UART0.h"
#include"LCD.h"
int main()
{
	unsigned int i;
	USC rxbyte[21];
	LCD_INIT();
	UART0_CONFIG();
	
	while(1)
	{
		
	lable:
	LCD_C(0x01);
	LCD_STR("Enter your name");
	i=0;
		
	do
	{
	 if(i>=21)
	 {
	 LCD_C(0x80);
	 LCD_STR("!EXCEEDED THE LIMITS");
	 delay_sec(5);
	 LCD_C(0x01);
	 LCD_C(0x80);
	 LCD_STR("ONLY 20 CHAR MAX");
	 delay_sec(5);
	 LCD_C(0x01);
	 goto lable;
	 }
	 
	 rxbyte[i] = UART0_RX();	
	 
	}while(rxbyte[i++] != '\r');//'\r' to detect "ENTER"
	
	
	rxbyte[i-1]='\0';

	/* to display received string*/	
	LCD_C(0x01);	
	LCD_STR("RX : ");
	LCD_STR(rxbyte);
	
	/* to transmit the string*/		
	for(i=0;rxbyte[i];i++)
	UART0_TX(rxbyte[i]);
	
	/* to display transmitted string*/		
	LCD_C(0xc0);
	LCD_STR("TX : ");
	LCD_STR(rxbyte);
	delay_sec(5);
	
	}
}
