

#include "bsp_header\z_bsp.h"

GPIO_Handle hGpio;


/**********************************************************
*��ʼ������֧�ֿ������оƬ������Һ����
***********************************************************/
void bsp(void)
{
	CSL_init();     //��ʼ������
	CSL_cfgInit() ; //��������
	gpio_init() ;  //GPIO��ʼ��
	interrupt_init (); //�жϳ�ʼ��
	
	idt72v36110_init() ; //FIFO��ʼ����ȫ�ָ�λ
	cmos_CF400G_init() ; //ָ��ͷCF400G��ʼ��
//	cmos_D0307_init() ;  //ָ��ͷD0307 ��ʼ��
	//cmos_OV7670_init() ; //���Ӿ�ͷOV7670��ʼ��

	//ds1302_init() ;	
	flash_init() ;
	oLCD_Init() ;
	//iLCD_Init() ;
	ZLG7290_I2C_Init () ;
	gt23l32s4w_init() ;
	

}
/*===================�жϳ�ʼ��=============*/
//�ⲿ�ж�6		-->		ָ��ͷI2C��ʼ��
//�ⲿ�ж�4		-->		�����ж�
void interrupt_init (void)
{
	IRQ_globalEnable();

	IRQ_clear(IRQ_EVT_EXTINT6);	//����жϱ�־
	IRQ_clear(IRQ_EVT_EXTINT4);	
	IRQ_enable(IRQ_EVT_EXTINT6);//ʹ���ж�
	IRQ_enable(IRQ_EVT_EXTINT4);
}
/*===========GPIO��ʼ��===============*/
//ZLG7290_SDA-->GP10	����ʼ�������
//ZLG7290_SCL-->GP11	�������
//ZLG7290_INT-->GP4     ���ж����룩
//CPLD����ָ��ͷI2C��ʼ��ʱ�ж����-->GP6		�����룩
//DS1302_CLK-->GP9		����ʼ�������
//DS1302_IO -->GP0		����ʼ�������
//DS1302_RST-->GP3		����ʼ�������
void gpio_init(void)
{
	hGpio=GPIO_open(GPIO_DEV0,GPIO_OPEN_RESET);
	GPIO_configArgs(
		hGpio,//GPIO_Handle hGpio,
		0x00000000,//Uint32 gpgc,
		0x00000E59,//Uint32 gpen,
		0x00000E09,//Uint32 gpdir,
		0x00000000,//Uint32 gpval,//����ֵ�����ֵ
		0x00000000,//Uint32 gphm,
		0x00000000,//Uint32 gplm,
		0x00000010 //Uint32 gppol //INT4�½��ش���
	);
}
