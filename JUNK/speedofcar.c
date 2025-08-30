#include<lpc21xx.h>
#include"delay.h"
#include"LCD.h"
unsigned int v = 5 ;
void IR1_ISR(void) __irq
{
	EXTINT = 0x01;
	T0TCR = 0X01;
	VICVectAddr = 0;
}
void IR2_ISR(void) __irq
{
	EXTINT =0x02;
	T0TCR = 0x00;
	v = T0TC;
	T0TCR = 0x03;
	T0TCR = 0x00;
	VICVectAddr = 0;
	
	
}

 int main()
 {
	 
		PINSEL0 = 0xCC;
		EXTMODE = 0x03;
	 EXTPOLAR = 0x03;
	 VICIntEnable = 1<<14 |1<<15;
	 T0PR = 15000-1;
	 while(1)
	 {
		if(v<5)
		{
			LCD_C(0x80);
			LCD_STR("OVER SPEED");
		}
   }
	
 }
 void Interrupt_config(void)
 {
	 VICIntSelect = 0;
	 VICVectCntl0 = 0x20 | 14;
	 VICVectAddr0 = (int)IR1_ISR;
	 
	 VICVectCntl1 = 0x20 | 15;
	 VICVectAddr1 = (int)IR2_ISR;
 }
 
 