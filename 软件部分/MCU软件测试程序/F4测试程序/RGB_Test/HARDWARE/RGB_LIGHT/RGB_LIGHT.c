#include "RGB_LIGHT.h"
#include "RGB_ColorNUMs.h" 

#define DATA_PINA GPIO_Pin_3
#define PINOUT PAout(3)

void DATA_Pin_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

  GPIO_InitStructure.GPIO_Pin = DATA_PINA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	//GPIO_SetBits(GPIOA,DATA_PINA );
	PINOUT=0;
}

void RGB_Send_1Code(void)
{
	uint16_t i=0;
	PINOUT=1;
	for(i=0;i<50;i++);
	PINOUT=0;
	for(i=0;i<50;i++);
}

void RGB_Send_0Code(void)
{
	uint16_t i=0;
	PINOUT=1;
	for(i=0;i<10;i++);
	PINOUT=0;
	for(i=0;i<50;i++);
}

void RGB_Reset(void)
{
	delay_us(300);
}

void RGB_Send_1Bits(uint8_t Data)
{
	if(Data)	RGB_Send_1Code();
	else			RGB_Send_0Code();
}

/**************
Ĭ��ΪBRGֵ����
**************/
void RGB_Send_24Bits(uint32_t Data)				//0xFF(FFFFFF)	
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		RGB_Send_1Bits((uint8_t)(Data&0x00000001));
		Data>>=1;
	}
}

/****************
����RGB����ֵ����
****************/
void Send_RGBDATA(uint32_t Data)			//FF1122		��Ϊ22FF11
{
	uint8_t i;				
	uint32_t data=0x00000000;
	data|=Data<<16;					//220000
	data|=Data>>8;				//22FF11
	for(i=0;i<24;i++)
	{
		RGB_Send_1Bits((uint8_t)(data&0x00000001));
		data>>=1;
	}
}
/****************
����RGB����ֵ����
****************/
void Send_RGB(uint8_t R,uint8_t G,uint8_t B)
{
	uint32_t Data=0x00000000;
	Data|=((uint32_t)B<<16);
	Data|=((uint32_t)R<<8);
	Data|=((uint32_t)G);
	RGB_Send_24Bits(Data);
}
