//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              CLK   ��PA5��SCL��
//              MOSI   ��PA7��SDA��
//              RES  ��PB0
//              DC   ��PB1 
//							BLK  ��A4 ��������
//							MISO ���Բ���
//              ----------------------------------------------------------------
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	   
#include "stdint.h"	  
#define LCD_W 240
#define LCD_H 240

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	240
#define Max_Row		240
#define	Brightness	0xFF 
#define X_WIDTH 	240
#define Y_WIDTH 	240	    						  
//-----------------OLED�˿ڶ���----------------  					   
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_1)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_1)
 		     
#define OLED_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS
#define OLED_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

extern  u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

void Lcd_Init(void); 
void LCD_Clear(uint16_t Color);
void Address_set(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2);
void LCD_WR_DATA8(char da); //��������-8λ����
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);

void LCD_SetColor(uint16_t BACK,uint16_t WRITE);

void LCD_DrawPoint(uint16_t x,uint16_t y);//����
void LCD_DrawPoint_big(uint16_t x,uint16_t y);//��һ�����
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); //����
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);//��ʾһ���ַ�
void LCD_ShowNum(uint16_t x,u16 y,u32 num,uint8_t len);//��ʾ����
void LCD_Show2Num(uint16_t x,u16 y,u16 num,uint8_t len);//��ʾ2������
void LCD_ShowString(uint16_t x,u16 y,const char *p);		 //��ʾһ���ַ���,16����

 
void LCD_Showimage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const unsigned char* image); 
void LCD_Showhanzi(uint16_t x,uint16_t y,uint16_t index,uint8_t Size);

/*ע��x��ʾ�У�y��ʾ��*/

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  						//0000 0000 0001 1111
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800						//1111 1000 0000 0000
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0						//0000 0111 1110 0000
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



