/******************************************************************************
 * �ļ�����z_camera.h
 * ���ܣ�  ����ָ�ƺ�ָ������ͷ�ɼ�ͼ��	
******************************************************************************/

#include "bsp_header/z_camera.h"

#include "bsp_header/z_cpld_cmd.h"
#include <csl_edma.h>

/**************************************************
��������camera_reset
��  ����û��
��  �أ�û��
��  �ã�������ͷ��λʵ������FIFO��λ��
***************************************************/
//void camera_reset  (void)
//{
//    idt72v36110_reset();		//FIFO�ֲ���λ����ַ����
//}
//�ú��������Ч�ʡ�
#define camera_reset   idt72v36110_reset

/***************************************************
*��������camera_capture
*��  ����flag ��ʶ�ɼ�����ʲôͼ��
*        FINGER_PRINT ָ��ͼ��
*        FINGER_VEIN  ָ����ͼ��
*��  �أ�û��
*��  �ã��ɼ�һ��ͼ��FIFO������EDMA���͵�SDRAM��
*ע  �⣺����ɼ�����ͼ�����ݻ�û��������ġ�
***************************************************/
void camera_capture(uint32_t flag)
{
	/*��λ����ͷ*/
	camera_reset();


	/*Ҫ�ɼ�ͼ����ָ����ʱ*/
	if(flag==FINGER_VEIN) {
	  /*��ʼ�ɼ�*/
	  FINGER_VEIN_CAPTURE ;//ָ���ɼ�ָ����,��ʼ�ɼ�

	  /*����Ҫ�ȴ�һ��ʱ��*/
	  _delay_ms(50);		//Ҫ�㹻��,�ܹ�����ȫ�����ݲɼ����,

	  /*����EDMA�¼���FIFO��������ݶ���SDRAM*/
	  EDMA_setChannel(hEdmaCha5);

	  _delay_ms(1);

	}

	/*Ҫ�ɼ�ͼ����ָ��ʱ*/
	else if(flag==FINGER_PRINT) {
	   /*��ʼ�ɼ�*/
	   //FINGER_D0307_LED_ON ;
	   asm ( " NOP " ) ;

	   FINGER_PRINT_CAPTURE ;//ָ���ɼ�ָ��,��ʼ�ɼ�

	   /*����Ҫ�ȴ�һ��ʱ��*/
	   _delay_ms(100);		//Ҫ�㹻��,�ܹ�����ȫ�����ݲɼ����,

	   /*����EDMA�¼���FIFO��������ݶ���SDRAM*/
	   EDMA_setChannel(hEdmaCha7);

	}
}

/***********************************************************
��������camera_init
��  ����û��
��  �أ�û��
��  �ã���ʼ������ͷ�Ĺ���������ʵ�ʹ�����ʹ�ܶ�Ӧ��EDMAͨ��
************************************************************/
void camera_init(void)
{
    EDMA_disableChaining(hEdmaCha5);   //��ֹEDMA������
    EDMA_enableChannel(hEdmaCha5);     //����EDMA
    
    EDMA_disableChaining(hEdmaCha7);  
    EDMA_enableChannel(hEdmaCha7);     
}

