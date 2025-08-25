#include<lpc21xx.h>
typedef unsigned char USC;
void UART0_CONFIG(void);
void UART0_TX(USC);
USC UART0_RX(void);
void UART0_STR(USC *);
void UART0_INT(int);
void UART0_FLOAT(float f);

/******************************************/
void UART0_CONFIG(void)
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0x00;
	U0LCR = 0x03;
} 
/******************************************/
void UART0_TX(USC ch)
{
	while(((U0LSR>>5)&1)==0);
	
	U0THR = ch;
}
/******************************************/
USC UART0_RX(void)
{
	while((U0LSR&1) == 0);
	
	return U0RBR; 
}

void UART0_STR(USC *s)
{
	while(*s)
	{
		UART0_TX(*s++);
	}
}
/******************************************/
void UART0_INT(int n)
{
	USC a[20];
  signed char i=0;
	if(n==0)
	UART0_TX('0');
	else
	{
		if(n<0)
		{
			UART0_TX('-');
			n=-n;
		}
		while(n>0)
		{
			a[i++]=((n%10)+48);
			n=n/10;
		}
		for(--i;i>=0;i--)
		UART0_TX(a[i]);
	}
}
/******************************************/
void UART0_FLOAT(float f)
{
	int temp;
	temp=f;
	UART0_INT(temp);
	UART0_TX('.');
	temp=((f-temp)*10);
	UART0_INT(temp);
}
/******************************************/
