#include<lpc21xx.h>
#include<string.h>
#include"LCD.h"
#include"UART0.h"


#define SW1 14 // vote for person 1
#define SW2 15 // reset
#define SW3 16 // view total vote 


unsigned char j;
unsigned char k=0;

			

char t[3][13];			 

unsigned int p1=0;
unsigned int p2=0;



int main()
{

   			 

   LCD_INIT();
   UART0_CONFIG();
   UART0_INTRE();
   
    while(1)
	{
  
	LCD_C(0x80);
	LCD_STR("TAP THE CARD");
	VICIntEnable = 1<<6;
/******************************check card limit ***********************************/
	 if(!(k<3))
	 {
	 LCD_C(0x01);
	 LCD_C(0x80);
	 LCD_STR("!EXCEEDS THE LIMITS OF TAG");
	 delay_sec(2);
	 while(1)
	   {
	
		LCD_C(0x80);
		LCD_STR("TOTAL COUNT");
		LCD_C(0xc0);
		LCD_STR("p1 : ");
		LCD_INT(p1);
		LCD_STR("  p2 : ");
		LCD_INT(p2);
		delay_sec(5);
		LCD_C(0x01);
		LCD_STR("Press reset SW4");
		while(((IOPIN0>>SW2&1)!= 0));
		goto lable1;
	   }
	 }
/******************************* Reset ************************************************/

		if(((IOPIN0>>SW2)&1)==0)
		{
		lable1:
		delay_ms(150);
		p1 = 0;
		p2 = 0;

		for(k=0;k<3;k++)
		strcpy(t[k],"junk");

		k=0;
		LCD_C(0x01);
		LCD_C(0x80);
		LCD_STR("RESET DONE");
		delay_sec(3);
		}

/************************ to view total count *********************************/

		if(((IOPIN0>>SW3)&1) == 0)
		{
		
		delay_ms(150);
		LCD_C(0x01);
		LCD_C(0x80);
		LCD_STR("TOTAL COUNT");
		LCD_C(0xc0);
		LCD_STR("p1 : ");
		LCD_INT(p1);
		LCD_STR("  p2 : ");
		LCD_INT(p2);
		delay_sec(2);
		LCD_C(0x01);
		}

/*****************************check card tap *****************************************/

	if(tag[1]!= 0)
       {
	   
    	 delay_ms(500);
/****************** check is already voted *************************************/
		for(j=0;j<3;j++) 
		{
       	 if(strcmp(tag,t[j])==0)
         {
		 LCD_C(0x01);
		 LCD_C(0x80);
         LCD_STR("!Already voted");
		 delay_sec(2);
		 LCD_C(0x01);
         goto lable;
         }
		 }

/********************************************************************************/
	
	  strcpy(t[k++],tag);		// register the tag

/************************to vote count *****************************************/
	 
	  while(1)
	  {
	  LCD_C(0x01);
	  LCD_C(0x80);
	  LCD_STR("press the switch to vote ");
	  delay_ms(500);


	  	if(((IOPIN0>>SW1)&1)==0)
	  	{
	    ++p1;
		LCD_C(0x01);
		LCD_C(0x80);
		LCD_STR(" THANK YOU FOR VOTING ");
		delay_sec(2);
		LCD_C(0x01);
	    break;
        }
  	  	else if(((IOPIN0>>SW2)&1)==0)
	  	{
	    ++p2;
		LCD_C(0x01);
		LCD_C(0x80);
		LCD_STR(" THANK YOU FOR VOTING ");
		delay_sec(2);
		LCD_C(0x01);
	    break;
 	    } 
/*************************************************************************/
		 
	    }
		lable :
       tag[1] = 0; 
	} 
	  
  }      
}



















