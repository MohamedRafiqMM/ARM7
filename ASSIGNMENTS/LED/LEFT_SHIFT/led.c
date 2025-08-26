#include<lpc21xx.h>
void delay_ms(unsigned int ms)
{
T0PR =15000-1;
T0TCR =0x01;
while(T0TC<ms);
T0TCR=0x03;
T0TCR=0x00;
}
int main()
{
	int i,j;
	for(i=0;i<8;i++)
	{
	IODIR0|=1<<i;
	}
  for(i=0;i<10;i++)
{
	for(j=0;j<8;j++)
	{
		IOSET0=1<<j;
		delay_ms(10);
		IOCLR0=1<<j;
	}
}
}

