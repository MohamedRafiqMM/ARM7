#include<lpc21xx.h>
#include<stdio.h>
#include"UART0.h"
#include"LCD.h"

#define SW1	1<<6   //for reset
#define LED1    1<<7
#define LED2    1<<8





int main()
{
	IODIR0 |= LED1 |LED2;
   UART0_CONFIG();
   LCD_INIT();
   EXTINT_INTRE();
   
 
   while(1)
   {
                if(((IOPIN0>>SW)&1)==0)
                 {
                  count = 0; 
                 } 
 
   		if(flag1 == 1)
   		{
      		sprintf((char *)digit ,"PERSON ENTRED : %d",count);
	  		UART0_STR(digit);
			LCD_C(0x01);
			LCD_C(0x80);
			LCD_STR("PERSON ENTRED");
			LCD_C(0xc0);
			LCD_STR("TOTAL COUNT : ");
			LCD_INT(count);
			
	  		flag1 = 0;
	 	}
	 	else if(flag2 == 1)
	 	{
	 		sprintf((char *)digit ,"PERSON ENTRED : %d",count);
	  		UART0_STR(digit);
			LCD_C(0x01);
			LCD_C(0x80);
			LCD_STR("PERSON EXITED");
			LCD_C(0xc0);
			LCD_STR("TOTAL COUNT : ");
			LCD_INT(count);
			
			flag2 =0;
		}	

   		if((count > 0) && (count<5)) 
                {
    		IOCLR0 = LED1;
                IOSET0 = LED2;
                }
  		else if(count>=5)
			IOCLR0 = LED1 | LED2 ;
   		else 
   			IOSET0  = LED1 |LED2 ;

   }





}

		  