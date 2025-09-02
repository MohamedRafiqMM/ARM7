#include<lpc21xx.h>
#include"delay.h"
#include"types.h"

u8 dat;
/***defines for pin function selection***/

#define SCL_EN  0x00000010
#define SDA_EN  0x00000040

/***defines for I2C_SPEED Configuration ***/

#define CCLK      60000000  //Hz
#define PCLK      CCLK/4    //Hz
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2)

/***bit defines for I2CONSET sfr***/

#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define   EN_BIT 6


void I2C_INIT(void);
void I2C_START(void);
void I2C_STOP(void);
void I2C_RESTART(void);
void I2C_WRITE(unsigned char dat);
u8 I2C_NACK(void);


void I2C_SLAVE_WRITE(u8 SLAVE_ADDR ,u8 WORD_ADDR ,u8 dat);
u8 I2C_SLAVE_READ(u8 SLAVE_ADDR,u8 WORD_ADDR);
void I2C_SLAVE_PAGE_WRITE(u8 SLAVE_ADDR ,u8 WORD_ADDR ,u8 *p, u8 nbytes);
u8 I2C_SLAVE_SEQU_READ(u8 SLAVE_ADDR ,u8 WORD_ADDR ,u8 *p, u8 nbytes);


/**********************************************************  I2C  ********************************************************************/



void I2C_INIT(void)
{
	PINSEL0 |= 0X50;
	I2SCLL = LOADVAL;
	I2SCLH = LOADVAL;
	I2CONSET = 1<<EN_BIT;
}


void I2C_START(void)
{
	I2CONSET = 1<<STA_BIT;

	while(((I2CONSET>>SI_BIT)&1) == 0);
	I2CONCLR = 1<<STA_BIT;
}


void I2C_STOP(void)
{
	I2CONSET = 1<<STO_BIT;
	I2CONCLR = 1<<SI_BIT;
}


void I2C_RESTART(void)
{
	I2CONSET = 1<<STA_BIT;
  I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1) == 0);
	I2CONCLR = 1<<STA_BIT;
}


void I2C_WRITE(unsigned char dat)
{
	I2DAT = dat;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1) == 0);
}


u8 I2C_NACK(void)
{
	I2CONSET = 0X00;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1) == 0);
	return I2DAT;
	
}


u8 I2C_MASTER_ACK(void)
{
	I2CONSET = 0X04;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1) == 0);
	I2CONCLR = 0X04;
	return I2DAT;
	
}
/**********************************************************  SLAVE ***********************************************************************/

void I2C_SLAVE_WRITE(u8 SLAVE_ADDR ,u8 WORD_ADDR ,u8 dat)
{
	I2C_START();
	I2C_WRITE(SLAVE_ADDR<<1);
	I2C_WRITE(WORD_ADDR);
	I2C_WRITE(dat);
	I2C_STOP();
	delay_ms(10);
}


u8 I2C_SLAVE_READ(u8 SLAVE_ADDR,u8 WORD_ADDR)
{
	I2C_START();
	I2C_WRITE(SLAVE_ADDR<<1);
	I2C_WRITE(WORD_ADDR);
	I2C_RESTART();
	I2C_WRITE(SLAVE_ADDR<<1|1);
	dat = I2C_NACK();
	I2C_STOP();
	return dat;
	
}


void I2C_SLAVE_PAGE_WRITE(u8 SLAVE_ADDR ,u8 WORD_ADDR ,u8 *p, u8 nbytes)
{
	u8 i;
	I2C_START();
	I2C_WRITE(SLAVE_ADDR<<1);
	I2C_WRITE(WORD_ADDR);
	
	for(i =0;1<nbytes;i++)
	I2C_WRITE(p[i]);
	
	I2C_STOP();
	delay_ms(10);
}


u8 I2C_SLAVE_SEQU_READ(u8 SLAVE_ADDR ,u8 WORD_ADDR ,u8 *p, u8 nbytes)
{
	u8 i;
	I2C_START();
	I2C_WRITE(SLAVE_ADDR<<1);
	I2C_WRITE(WORD_ADDR);
	I2C_RESTART();
	I2C_WRITE(SLAVE_ADDR<<1|1);
	
	for(i=0;i<nbytes-1;i++)
	p[i] = I2C_MASTER_ACK();
	
	p[i] = I2C_NACK();
	I2C_STOP();
	return dat;
	
}

/*******************************************************************************************************************************************/


