#include<lpc21xx.h>
#include"delay.h"
/*void delay_ms(unsigned int ms)
{
T0PR =15000-1;
T0TCR =0x01;
while(T0TC<ms);
T0TCR=0x03;
T0TCR=0x00;
}*/
int main()
{
	int i,j;
	IODIR0 = 0xFF;
	for(i=0;i<10;i++)
	{
	for(j=7;j>=0;j--)
	{
		IOSET0=1<<j;
		delay_ms(500);
		IOCLR0=1<<j;
	}
  }
}
