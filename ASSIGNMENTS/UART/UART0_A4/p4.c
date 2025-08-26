#include<LPC21XX.H>
#include"LCD.h"
#include"UART0.h"
#define LED 1<<17
#define SW 14

void UART0_int_config(void);
void UART0_ISR(void) __irq
{
	int temp;
	temp = U0IIR;
	if(temp == 0x04)
	{
		U0THR = U0RBR;
	}
	VICVectAddr = 0;
	
}
	
int main()
{

	IODIR0 = LED;
	UART0_CONFIG();
	UART0_int_config();
	VICIntEnable = 1<<6;
	
	while(1)
	{
		if(((IOPIN0>>SW)&1)==0)
		{
			IOCLR0 = LED;
		}
		else 
		{
			IOSET0 = LED;
		}
	}
}

void UART0_int_config(void)
{
	VICIntSelect = 0;
	VICVectCntl0 = 0x20|6;
	VICVectAddr0 =(int)UART0_ISR;
	U0IER = 0x03;
}
