#ifndef __MUNE_H
#define __MUNE_H
#include "stdint.h"

struct Pagedata
{
	uint8_t ChoiceNum;											//ѡ����Ŀ
	uint8_t CurrentChoice;													//ѡ����Ŀ
	uint8_t Str[4][10];											//����ʾ�ַ���
	const uint8_t ChoiceCN32x32[10][16*8];	//����ʾ��������,��һά�������Ϊ10
};

extern uint8_t MenuUpdateFlag[4];

void LCD_Page_Reinit(uint16_t BackGronudColor,uint16_t RectColor,uint16_t StrColor);
void LCD_Menu_Init();

void LCD_ShowOutline();


void LCD_UpdareMenu();
/*�˵��л�����*/
void LCD_Switch();

void FunctionIn(uint8_t i,uint8_t j);

/*�˵����ܺ���*/
void Function1();
void Function2();
void Function3();
void Function4();

#endif
