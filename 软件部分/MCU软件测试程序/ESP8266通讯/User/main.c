#include "sys.h"
int main()
{
	delay_init();
	/*USART*/
	uart1_init(115200);		//����-����
	uart2_init(115200);		//����-WIFIģ��
	/*TIM*/
	TIM3_Int_Init(7200-1,500-1);		//��������Ӧ�Ķ�ʱ��
	TIM4_Int_Init(7200-1,1000-1);		//�ƹ���Ƶ��	10Hz
	KEY_Init();
	Encoder_TIM2_Init();		//�������ӿڳ�ʼ��
	
	DATA_Pin_Init();		//WS2512�����߳�ʼ��
	
	Lcd_Init();		//��ʾ����ʼ��
	/*SPI*/
	SPI2_Init();		//W25Q64 Flash��ʼ��
	W25QXX_Init();
	
	NVIC_Config();		//�ж����ȼ�����
	
	LCD_Clear(WHITE);
	LCD_SetColor(WHITE,BLACK);
	
	Storage_Init();			//�洢��ʼ��
	LCD_Menu_Init();
	

	

	while(1)
	{
		if(MenuMode!=3)
		{
			LCD_Function();
			LCD_Switch();
			LCD_UpdateMenu();
			delay_ms(50);
		}
		if(MenuMode==3)
		{
			PicShow_Stroge();
		}
	}
}
