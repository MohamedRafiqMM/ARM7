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
	int i,j,k;
	IODIR0=0xFF;
  for(k=0;k<10;k++)
{
	for(i=0,j=7;i<j;i++,j--)
	{
	IOSET0 = 1<<i | 1<<j ;
	delay_sec(5);
	IOCLR0 = 1<<i | 1<<j ;	
	}
	for(;!((i<=0)&&(j>=7));i--,j++)
	{
	IOSET0 = 1<<i | 1<<j ;
	delay_sec(5);
	IOCLR0 = 1<<i | 1<<j ;	
	}
}
}
