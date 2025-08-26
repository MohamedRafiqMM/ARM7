#include<lpc21xx.h>
#define LED1 1<<4
#define LED2 1<<5
#define LED3 1<<6
#define LED4 1<<7
#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3
int main()
{
	IODIR0 =0xF0 ;
	while(1)
	{
		if(((IOPIN0>>SW1)&1)==0)
		{
			IOCLR0 = LED1;
		}
		else
		{
			IOSET0 = LED1;
		}
	 if(((IOPIN0>>SW2)&1)==0)
		{
			IOCLR0 = LED2;
		}
		else
		{
			IOSET0 = LED2;
		}
	 if(((IOPIN0>>SW3)&1)==0)
		{
			IOCLR0 = LED3;
		}
		else
		{
			IOSET0 = LED3;
		}
	 if(((IOPIN0>>SW4)&1)==0)
		{
			IOCLR0 = LED4;
		}
		else
		{
			IOSET0 = LED4;
		}
		}
	}

