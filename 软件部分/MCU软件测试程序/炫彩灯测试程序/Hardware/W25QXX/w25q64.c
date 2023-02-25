#include "w25qxx.h" 
#include "spi.h"
#include "delay.h"
/***********************
˵����
W25Q64ʵ�ʶ�д���ú���
����ʹ�ã�
Ƭѡ����CS 
GPIOPINB	GPIO_Pin_12
***********************/

/*********************************************
//ҳ			Page												256B
//����		Sector	16ҳ								4KB	4096B
//��			Block		16����							64KB
//W25Q64					128��,2048����			8MB
**********************************************/

void W25QXX_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PB12 ���� 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
 
  W25QXX_CS=1;				//SPI FLASH��ѡ��
	SPI2_Init();		   	//��ʼ��SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ
}


//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR								Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0		FLASH����д��������
//WEL								дʹ������
//BUSY							æ���λ(1,æ;0,����)
//Ĭ��:0x00

/*��ȡW25QXX��״̬�Ĵ���*/
u8 W25QXX_ReadSR(void)   
{  
	u8 byte=0;   
	W25QXX_CS=0;                            //ʹ������   
	SPI2_ReadWriteByte(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI2_ReadWriteByte(0Xff);          //��ȡһ���ֽ�  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     
	return byte;   
} 

/*дW25QXX״̬�Ĵ���*/
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void W25QXX_Write_SR(u8 sr)   
{   
	W25QXX_CS=0;                            //ʹ������   
	SPI2_ReadWriteByte(W25X_WriteStatusReg);//����дȡ״̬�Ĵ�������    
	SPI2_ReadWriteByte(sr);               	//д��һ���ֽ�  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
}   

//W25QXXдʹ��	
//��WEL��λ   
void W25QXX_Write_Enable(void)   
{
	W25QXX_CS=0;                          	//ʹ������   
    SPI2_ReadWriteByte(W25X_WriteEnable); 	//����дʹ��  
	W25QXX_CS=1;                           	//ȡ��Ƭѡ     	      
} 
//W25QXXд��ֹ	
//��WEL����  

void W25QXX_Write_Disable(void)   
{  
	W25QXX_CS=0;                            //ʹ������   
    SPI2_ReadWriteByte(W25X_WriteDisable);  //����д��ָֹ��    
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 		

//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:				���ݴ洢��
//ReadAddr:				��ʼ��ȡ�ĵ�ַ(24bit	0x000000~0x7FFFFF)
//NumByteToRead:	Ҫ��ȡ���ֽ���(���65535,Flash��8388608�ֽ�)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
		u16 i;   										    
		W25QXX_CS=0;                            	//ʹ������   
    SPI2_ReadWriteByte(W25X_ReadData);         	//���Ͷ�ȡ����   
    SPI2_ReadWriteByte((u8)((ReadAddr)>>16));  	//����24bit��ַ    
    SPI2_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPI2_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
		{ 
        pBuffer[i]=SPI2_ReadWriteByte(0XFF);   	//ѭ������  
    }
		W25QXX_CS=1;  				    	      
}  

//��һҳ(0~32767)��ʼ��������256���ֽڵ�����
//pBuffer:				���ݴ洢������1~256
//PageNum:				ҳ��1~32768
//NumByteToWrite:	1~256
void W25QXX_Read_Page(u8* pBuffer,u16 PageNum,u16 NumByteToRead)
{
	u32 WRAddr=(PageNum-1)*256;
	W25QXX_Read(pBuffer,WRAddr,NumByteToRead);	
}

void W25QXX_Read_Sector(u8* pBuffer,u16 SectorNum,u16 NumByteToRead)
{ 
	u32 WRAddr=(SectorNum-1)*4096;
	W25QXX_Read(pBuffer,WRAddr,NumByteToRead);
}


//��һ��ҳ(1~32768)��ʼд������256���ֽڵ�����
//pBuffer:				���ݴ洢������1~256
//PageNum:				ҳ��1~32768
//NumByteToWrite:	1~256
void W25QXX_Write_Page(u8* pBuffer,u16 PageNum,u16 NumByteToWrite)
{
		u16 i;  
		u32 WriteAddr=(PageNum-1)*256;
    W25QXX_Write_Enable();                  	//SET WEL 
		W25QXX_CS=0;                            	//ʹ������   
    SPI2_ReadWriteByte(W25X_PageProgram);      	//����дҳ����   
    SPI2_ReadWriteByte((u8)((WriteAddr)>>16)); 	//����24bit��ַ    
    SPI2_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI2_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPI2_ReadWriteByte(pBuffer[i]);//ѭ��д��  
		W25QXX_CS=1;                            	//ȡ��Ƭѡ 
		W25QXX_Wait_Busy();					   		//�ȴ�д�����
} 

/*���*/
//��һ����(1~2048)��ʼд������2048���ֽڵ�����
//pBuffer:				���ݴ洢������1~4096
//SectorNum:				ҳ��1~2048
//NumByteToWrite:	1~4096
//Mode��					1Ϊ���ǣ�0Ϊ������	����ָ������ȫ�滻��������ָָ�滻�����ݵ��ǲ���
uint8_t W25QXX_RdBuff[4096];				//��ȡ����
uint8_t W25QXX_WrBuff[4096];				//д�뻺��
void W25QXX_Write_Sector(u8* pBuffer,u16 SectorNum,u16 NumByteToWrite,u8 Mode)
{
	u16 i,j;  
	u32 WRAddr=(SectorNum-1)*4096;
	u16 PageNum=(SectorNum-1)*16+1;
	//��ȡ
	W25QXX_Read(W25QXX_RdBuff,WRAddr,4096);
	//����
	W25QXX_Erase_Sector(WRAddr);
	//�������滻����
	for(i=0;i<4096;i++)
	{
		if(Mode)
		{
			if(i<NumByteToWrite)	W25QXX_WrBuff[i]=pBuffer[i];
			else	W25QXX_WrBuff[i]=W25QXX_RdBuff[i];
		}
		else
		{
			if(i<NumByteToWrite&&pBuffer[i])	W25QXX_WrBuff[i]=pBuffer[i];
			else	W25QXX_WrBuff[i]=W25QXX_RdBuff[i];
		}
	}
	//��д
	for(j=0;j<16;j++)
	{
//		W25QXX_Write_Enable();                  	//SET WEL 
//		W25QXX_CS=0;                            	//ʹ������
//		SPI2_ReadWriteByte(W25X_PageProgram);      	//����дҳ����   
//		SPI2_ReadWriteByte((u8)((WRAddr)>>16)); 	//����24bit��ַ    
//		SPI2_ReadWriteByte((u8)((WRAddr)>>8));   
//		SPI2_ReadWriteByte((u8)WRAddr);   
//		for(i=0;i<256;i++)SPI2_ReadWriteByte(W25QXX_WrBuff[i+j*256]);//ѭ��д��  
//		W25QXX_CS=1;                            	//ȡ��Ƭѡ 
//		W25QXX_Wait_Busy();					   		//�ȴ�д�����
//		
		W25QXX_Write_Page(&W25QXX_WrBuff[256*j],PageNum,256);
		PageNum+=1;
	}
} 


//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();                 	 	//SET WEL 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            	//ʹ������   
    SPI2_ReadWriteByte(W25X_ChipErase);        	//����Ƭ��������  
		W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
		W25QXX_Wait_Busy();   				   		//�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ��ɽ��������ʱ��:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
	W25QXX_Write_Enable();                  	//SET WEL 	 
	W25QXX_Wait_Busy();   
	W25QXX_CS=0;                            	//ʹ������   
	SPI2_ReadWriteByte(W25X_SectorErase);      	//������������ָ�� 
	SPI2_ReadWriteByte((u8)((Dst_Addr)>>16));  	//����24bit��ַ    
	SPI2_ReadWriteByte((u8)((Dst_Addr)>>8));   
	SPI2_ReadWriteByte((u8)Dst_Addr);  
	W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
	W25QXX_Wait_Busy();   				   		//�ȴ��������
}  
//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);  		// �ȴ�BUSYλ���
}  
//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
  	W25QXX_CS=0;                           	 	//ʹ������   
    SPI2_ReadWriteByte(W25X_PowerDown);        //���͵�������  
	W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
    delay_us(3);                               //�ȴ�TPD  
}   
//����
void W25QXX_WAKEUP(void)   
{  
  	W25QXX_CS=0;                            	//ʹ������   
    SPI2_ReadWriteByte(W25X_ReleasePowerDown);	//  send W25X_PowerDown command 0xAB    
	W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
    delay_us(3);                            	//�ȴ�TRES1
}   


/*����д������״̬�Ĵ���д����*/
void W25QXX_Write_Protect();				//����д����
void W25QXX_SR_Protect();						//״̬�Ĵ���д����
