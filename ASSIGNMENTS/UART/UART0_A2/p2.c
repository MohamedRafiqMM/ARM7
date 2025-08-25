#include"delay.h"
#include"UART0.h"
#include"LCD.h"
int main()
{
	USC rxbyte;
	LCD_INIT();
	UART0_CONFIG();
	while(1)
	{
	rxbyte=UART0_RX();
	LCD_C(0x01);	
	LCD_STR("RX : ");
	LCD_DA(rxbyte);
	rxbyte=rxbyte^32;
	UART0_TX(rxbyte);
	LCD_C(0x88);
	LCD_STR("TX : ");
	LCD_DA(rxbyte);
	}
}
