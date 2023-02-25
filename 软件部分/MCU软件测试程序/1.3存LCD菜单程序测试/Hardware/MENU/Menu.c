#include "Menu.h"
#include "oled.h"
#include "oledfont.h"
uint16_t BackGronudColor=WHITE;
uint16_t RectColor=LIGHTBLUE;
uint16_t StrColor=BLACK;

struct Pagedata MenuPage[4][3];
uint8_t	MenuMode=1;				//1.���� 2.����ʱ�� 3.ͼƬ��ʾ
uint8_t	TypeNum=0;	
uint8_t	PictNum=0;	



void LCD_Menu_Init()
{
	MenuPage[0][0].ChoiceNum=4;
	MenuPage[0][0].CurrentChoice=1;
	
	MenuPage[1][0].ChoiceNum=4;
	MenuPage[1][3].ChoiceNum=2;
	MenuPage[1][4].ChoiceNum=3;
	MenuPage[2][0].ChoiceNum=3;
}

/*��������ʱ�Ӻ����ý�����ʾ*/
void LCD_ShowOutline()
{
	if(MenuMode==3) return;
	uint8_t i;
	/*����ɫ*/
	LCD_Clear(BackGronudColor);
	/*���߿�*/
	LCD_SetColor(BackGronudColor,RectColor);
	for(i=0;i<5;i++)
	{
		LCD_DrawRectangle(i,i,239-i,239-i);
		LCD_DrawLine(0,39-i,239,39-i);
		LCD_DrawLine(0,199+i,239,199+i);
	}
	/*��ʾ�ַ�*/
	LCD_ShowString(160,12,"Mode");
	LCD_ShowNum(160+8*4,12,MenuMode,1);
	switch(MenuMode)
	{
		case 1:
			LCD_Showhanzi(12+16*0,12,0,1);			//��
			LCD_Showhanzi(12+16*1,12,1,1);			//��
			LCD_Showhanzi(12+16*2,12,2,1);			//��
			LCD_Showhanzi(12+16*3,12,3,1);			//ʽ
			LCD_ShowChar(12+16*4,12,':',0);
			LCD_ShowNum(12+16*5,12,TypeNum,1);
			LCD_Showhanzi(132+16*0,12,0,1);			//��
			LCD_Showhanzi(132+16*1,12,1,1);			//��
			LCD_Showhanzi(132+16*2,12,4,1);			//ͼ
			LCD_Showhanzi(132+16*3,12,5,1);			//Ƭ
			LCD_ShowChar(132+16*4,12,':',0);
			LCD_ShowNum(12+16*5,12,PictNum,1);
			break;
		case 2:
			break;
	}
		
}
/*48*/
void LCD_UpdareMenu()
{
}

/*�˵��л�����*/
uint8_t Sure_Flag=0;
uint8_t Back_Flag=0;
uint8_t Uuup_Flag=0;
uint8_t Down_Flag=0;
uint8_t MenuUpdateFlag[4]={0};	//ˢ�±�ʾλ	ѡ��ˢ�±�ʾλ	ҳˢ�±�ʾλ	�˵�ˢ�±�ʾλ
uint8_t CurrentPage[2]={0,0};		//�˵�����

//							(1,1)
//				(1,0)	(1,2)
//							(1,3)
//	(0,0)	(2,0)	...
//				(3,0)	...
//				
void LCD_Switch()
{
	if(Sure_Flag)
	{
		if(!CurrentPage[0]) CurrentPage[0]=MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice;
		else if(!CurrentPage[1]) CurrentPage[1]=MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice;
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[2]=1;
		Sure_Flag=0;
	}
	
	if(Back_Flag)
	{
		if(CurrentPage[1]) 
		{
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=1;
			CurrentPage[1]=0;
		}
		else if(CurrentPage[0])
		{
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=1;
			CurrentPage[0]=0;
		}
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[2]=1;
		Sure_Flag=0;
	}
	
	if(Uuup_Flag)
	{
		if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice>1)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice-=1;
		else if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice<=1)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=MenuPage[CurrentPage[0]][CurrentPage[1]].ChoiceNum;
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
		Sure_Flag=0;
	}
	
	if(Down_Flag)
	{
		if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice<MenuPage[CurrentPage[0]][CurrentPage[1]].ChoiceNum)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice+=1;
		else if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice>=1)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=1;
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
		Sure_Flag=0;
	}
	if(CurrentPage[1])
	{
		FunctionIn(CurrentPage[0],CurrentPage[1]);
	}
}

uint8_t  ShortTimeBuff=0;
void FunctionIn(uint8_t i,uint8_t j)
{
	
}
