#ifndef __MUNE_H
#define __MUNE_H
#include "stdint.h"

struct Pagedata
{
	uint8_t ChoiceNum;											//ѡ����Ŀ
	uint8_t CurrentChoice;									//ѡ����Ŀ
//	const uint8_t ChoiceCN32x32[10][16*8];	//����ʾ��������,��һά�������Ϊ10
	char Str[4][10];									//����ʾ�ַ���
};

extern uint8_t MenuUpdateFlag[3];
extern uint8_t CurrentPage[2];		//�˵�����
extern uint8_t	MenuMode;
extern uint8_t NumGet;
void LCD_Page_Reinit(uint16_t BackGronudColor,uint16_t RectColor,uint16_t StrColor);

void LCD_Menu_Init();

void LCD_ShowOutline();

/*�˵����º���*/
void LCD_UpdateChoice();
void LCD_UpdatePage(uint8_t CurrentPage0,uint8_t CurrentPage1);
void LCD_UpdateMenu();
/*�˵��л�����*/
void LCD_Switch();

void LCD_Function();

/*�˵����ܺ���*/
void Function1();
void Function2();
void Function3();
void Function4();

#endif
