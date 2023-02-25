#ifndef __RGB_LIGHT_H
#define __RGB_LIGHT_H	 
#include "sys.h" 

#define DATA_PINA GPIO_Pin_6
#define PINOUT PAout(6)
#define N_Max	59
	
/**/
void DATA_Pin_Init(void);
void RGB_Send_1Code(void);
void RGB_Send_0Code(void);
void RGB_Reset(void);
void RGB_Send_1Bits(uint8_t Data);
void RGB_Send_24Bits(uint32_t Data);

/*Ӧ�ú������������ݺ��������ε���*/
void Send_RGBDATA(uint32_t Data);
void Send_RGB(uint8_t R,uint8_t G,uint8_t B);
/*Ӧ�ú��������������ݣ��ٵ���*/
void Set_RGBDATA(uint16_t Num,uint32_t Data);								//��16����������
void Set_RGB(uint16_t Num,uint8_t R,uint8_t G,uint8_t B);		//��RGBֵ����
uint32_t Get_RGB(uint16_t Num);															//��RGBֵ����
void Refresh();																							//�������
void Refresh_All();																					//���������ƴ�

uint8_t Set_RGBDATA1(uint32_t Data);
uint8_t Set_RGB1(uint8_t R,uint8_t G,uint8_t B);
void  RGB_SETBE(uint8_t BeginNum,uint8_t EndNum);

#endif