#include<lpc21xx.h>
#include"UART0.h"
#include"delay.h"
void UART0_SW(int SW)
{
	if(((IOPIN0>>SW)&1)==0)
		{
			if(SW==2)
			{
			UART0_STR("SW1 is pressed ");
			while(((IOPIN0>>SW)&1)==0);
			}
			else if(SW==3)
			{
			UART0_STR("SW2 is pressed ");
			while(((IOPIN0>>SW)&1)==0);
			}
			else if(SW==4)
			{
			UART0_STR("SW3 is pressed ");
			while(((IOPIN0>>SW)&1)==0);
			}
			else if(SW==5)
			{
			UART0_STR("SW4 is pressed ");
			while(((IOPIN0>>SW)&1)==0);
			}
		}
}

int main()
{
	UART0_CONFIG();
	while(1)
	{
		UART0_SW(2);
		UART0_SW(3);
		UART0_SW(4);
		UART0_SW(5);
	}
}

