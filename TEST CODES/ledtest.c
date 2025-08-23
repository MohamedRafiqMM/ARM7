#include<lpc21xx.h>
void delay_ms(unsigned int ms)
{
	T0PR  = 15000-1;
	T0TCR = 0x01;
  while(T0TC<ms);
  T0TCR = 0x03;
  T0TCR = 0x00;	
}
int main()
{
	IODIR0=1<<0;
	while(1)
	{
		IOSET0=1<<0;
		delay_ms(500);
		IOCLR0=1<<0;
		delay_ms(500);
	}
}
