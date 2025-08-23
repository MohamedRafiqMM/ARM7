#include<lpc21xx.h>

#define LCD_D 0xFF<<0
#define RS 1<<8
#define E 1<<9
void LCD_INIT(void);
void delay_ms(unsigned int ms);
void LCD_DA(unsigned char d );
void LCD_C(unsigned char cmd );

int main()
{
	LCD_INIT();
	while(1)
	{
	LCD_C(0x80);
	LCD_DA('A');
	
	}
}
void LCD_INIT(void)
{
	IODIR0=0x3FF;
	 LCD_C(0x01);
	 LCD_C(0x02);
	 LCD_C(0x0c);
	 LCD_C(0x38);
}
void LCD_C(unsigned char cmd )
{
	IOPIN0=(((IOPIN0)&(0xFFFFFF00))|cmd);
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_DA(unsigned char d )
{
	IOPIN0=(((IOPIN0)&(0xFFFFFF00))|d);
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void delay_ms(unsigned int ms)
{
	T0PR  = 15000-1;
	T0TCR = 0x01;
  while(T0TC<ms);
  T0TCR = 0x03;
  T0TCR = 0x00;	
}

