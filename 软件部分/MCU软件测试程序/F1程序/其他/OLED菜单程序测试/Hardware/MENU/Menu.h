#ifndef __MUNE_H
#define __MUNE_H
#include "stdint.h"

struct Page
{
	uint16_t BackGronudColor;								//ҳ�汳����ɫ
	uint16_t RectColor;											//ҳ��߿���ɫ
	uint8_t ChoiceNum;											//ѡ����Ŀ
	uint16_t CNColor;												//������ɫ
	uint16_t CNRectColor;										//���ֿ���ɫ
	const uint8_t ChoiceCN32x32[10][16*8];	//��������,��һά�������Ϊ10
};

extern struct Page MenuPage[3];

void Page_Init();
void ShowPage(uint8_t PageNum);

#endif
