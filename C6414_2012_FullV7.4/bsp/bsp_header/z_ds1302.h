#ifndef __DS1302_H__
#define __DS1302_H__

#include <csl_gpio.h>
#include "z_mytype.h"
#include "z_sys_time.h"
#include "z_cpld_cmd.h"

/*=========ʱ��оƬ������DS1302��================*/
/*--Ӳ������--*/
//DS1302_CLK-->GP9		����ʼ�������
//DS1302_IO -->GP0		����ʼ�������
//DS1302_RST-->GP3		����ʼ�������
/*===========================================*/
extern  GPIO_Handle hGpio;

#define DS1302_IO			GPIO_PIN0
#define DS1302_CLK			GPIO_PIN9
#define DS1302_RST			GPIO_PIN3

#define DS1302_IO_IN		GPIO_pinDirection( hGpio , DS1302_IO , GPIO_INPUT )
#define DS1302_IO_OUT		GPIO_pinDirection( hGpio , DS1302_IO , GPIO_OUTPUT )

#define	DS1302_IO_H			GPIO_pinWrite( hGpio , DS1302_IO , 1 )
#define	DS1302_IO_L			GPIO_pinWrite( hGpio , DS1302_IO , 0 )

#define	DS1302_CLK_H		GPIO_pinWrite( hGpio , DS1302_CLK , 1 )
#define	DS1302_CLK_L		GPIO_pinWrite( hGpio , DS1302_CLK , 0 )

#define	DS1302_RST_H		GPIO_pinWrite( hGpio , DS1302_RST , 1 )
#define	DS1302_RST_L		GPIO_pinWrite( hGpio , DS1302_RST , 0 )

//����һ��32λ��ֵ:0��1
#define	DS1302_IO_VAL		GPIO_pinRead ( hGpio , DS1302_IO )
//BCD��תΪʮ����
#define BCD_TO_BIN(val)		( (val) = ( (val) >> 4 )*10 + ( (val)&15 ) )
//ʱ�Ӷ�д����
#define WRITE				0x00
#define READ				0x01
//ʱ�ӵ�ַ����
#define SECOND				0x80	//���ַ
#define MINUTE				0x82	//�ֵ�ַ
#define HOUR				0x84	//Сʱ
#define DAY					0x86	//����
#define MONTH				0x88	//��
#define	WEEK				0x8a	//����
#define YEAR				0x8c	//��
#define CONTROL				0x8e	//���ƼĴ���������д������
#define CHARGE				0x90	//
#define BURST				0xbe
//��������
#define STOP				0x80	//ֹͣ����
#define START				0x00	//��������
#define AM_PM				0x80	//ʱ����ʽѡ��
#define PROTECT				0x80	//д����
#define UPROTECT			0x00	//ȡ��д����

typedef struct {
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned char week;
	unsigned char year;
	unsigned char rsv;//����
} time_t;

inline static void DS1302_Dalay(void) ;
static void DS1302_Write_Byte(uint8_t byte) ;
static uint8_t DS1302_Read_Byte(void) ;
static void DS1302_Write_Addr(uint8_t addr,uint8_t data) ;
//static 
uint8_t DS1302_Read_Addr(uint8_t addr) ;
void ds1302_init(void) ;
uint8_t DS1302_Set_Time(time_t *systime) ;
uint8_t DS1302_Get_Time(time_t *systime) ;


















#endif 


