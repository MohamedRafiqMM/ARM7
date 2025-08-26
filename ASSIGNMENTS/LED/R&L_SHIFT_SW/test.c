#include<lpc21xx.h>
#include"delay.h"
#define SW 8
#define SW1 9
int main()
{
 int i,j;
	IODIR0=0xFF;
	IOSET0=0xFF;
 while(1)
 {
	if(((IOPIN0>>SW)&1)==0)
	{
	for(i=0;(((IOPIN0>>SW)&1)==0);i++)
	{
	for(j=7;j>=0;j--)
	{
		IOCLR0=1<<j;
		delay_ms(100);
		IOSET0=1<<j;
	}
  }
 }
 if(((IOPIN0>>SW1)&1)==0)
	{
	for(i=0;(((IOPIN0>>SW1)&1)==0);i++)
  {
	for(j=0;j<8;j++)
	{
		IOCLR0=1<<j;
		delay_ms(100);
		IOSET0=1<<j;
	}
  }
 }
 
 
 }
}
