#include<lpc21xx.h>
#include"delay.h"
#define LCD_D 0xF<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

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
	 IODIR1 = LCD_D | RS | E | RW  ;
	 IOCLR1 = RW;
	 LCD_C(0x01);
	 LCD_C(0x02);
	 LCD_C(0x0c);
	 LCD_C(0x28);
}
void LCD_C(unsigned char cmd )
{
	//IOPIN1 = cmd<<16;
	IOCLR1 = LCD_D;
	IOSET1 = (cmd & (0xf0))<< 16;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;

	IOCLR1 = LCD_D;
	IOSET1 = (cmd & (0x0f))<< 20;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;

}
void LCD_DA(unsigned char d )
{
	//IOPIN1 = d<<16;
	IOCLR1 = LCD_D;
	IOSET1 = (d & (0xf0))<<16;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;

	IOCLR1 = LCD_D;
	IOSET1 = (d & (0x0f))<<20;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;


}
