//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  �� �� ��   : main.c
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

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
//u8 ref=0;//ˢ����ʾ
//u16 vx=15542,vy=11165;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
//u16 chx=140,chy=146;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
void xianshi()//��ʾ��Ϣ
{   
	u16 lx,ly;
	BACK_COLOR=BLUE;
	POINT_COLOR=RED;	
	LCD_Showhanzi(10,0,0,1);  //��
	LCD_Showhanzi(45,0,2,2);  //��

  LCD_ShowString(10,35,"1.3 IPS-SPI 240*320");
	LCD_ShowString(10,55,"LCD_W:");	LCD_ShowNum(70,55,LCD_W,3);
	LCD_ShowString(110,55,"LCD_H:");LCD_ShowNum(160,55,LCD_H,3);	
	lx=10;ly=75;			
}



void showimage() //��ʾ40*40ͼƬ
{
	LCD_Showimage(60,120,40,40,image);
//	ref=0;				
}
 int main(void)
 {
		u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��

		Lcd_Init();			//��ʼ��TFT
	
		LCD_Clear(WHITE); //����
		LCD_SetColor(WHITE,BLACK);

		xianshi(); //��ʾ��Ϣ
    showimage(); //��ʾ40*40ͼƬ


		while(1)
		{    
		}
}
