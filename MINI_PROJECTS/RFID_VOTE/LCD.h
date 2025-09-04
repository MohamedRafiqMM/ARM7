#include<lpc21xx.h>
#include"delay.h"
#define LCD_D 0xFF<<16
#define RS 1<<24
#define E 1<<25

void LCD_CGRAM(unsigned char);
void LCD_F(float ,int  );
void LCD_C(unsigned char cmd );
void LCD_DA(unsigned char d );
void LCD_INIT(void);
void LCD_STR(unsigned char*);
void LCD_INT(int );
unsigned char  s[10];
void LCD_CGRAM(unsigned char n)
{
	unsigned i;
	LCD_C(0x40);
	for(i=0;i<n;i++)
	LCD_DA(s[i]);
}
void LCD_F(float f,int n)
{
  int temp;
	temp = f;
	LCD_INT(temp);
	LCD_DA('.');
	temp = ((f-temp)*n);
	LCD_INT(temp);
}
void LCD_INT(int n)
{
	unsigned char arr[5];
	signed char i=0;
	if(n==0)
		LCD_DA('0');
	else
	{
		if(n<0)
		{
			LCD_DA('-');
			n=-n;
		}
		while(n>0)
		{
			arr[i++]=((n%10)+48);
			n=n/10;
		}
		for(--i;i>=0;i--)
		LCD_DA(arr[i]);
	}
}
void LCD_STR(unsigned char*s)
{
	unsigned count=0;
	while(*s)
	{
		count++;
		LCD_DA(*s++);
		if(count==16)
			LCD_C(0xc0);
	}
}
void LCD_INIT(void)
{
	 IODIR1 = LCD_D | RS | E ;
	 LCD_C(0x01);
	 LCD_C(0x02);
	 LCD_C(0x0c);
	 LCD_C(0x38);
}
void LCD_C(unsigned char cmd )
{
	IOPIN1 = cmd<<16;
	//IOCLR1 = 0X01;
	//IOSET1 = (cmd<<16)&LCD_D;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void LCD_DA(unsigned char d )
{
	IOPIN1 = d<<16;
	//IOCLR1 = 0X01;
	//IOSET1 = (d<<16)&LCD_D;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
