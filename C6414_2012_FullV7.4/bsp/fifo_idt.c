
#include "bsp_header\z_fifo_idt.h"

/********************************************************
*��������idt72v36110_init
*��  ����û��
*��  �أ�û��
*��  �ã���FIFOоƬIDT72V36110��ʼ����FIFOȫ�ָ�λ��
**********************************************************/
void idt72v36110_init(void)
{
	FIFO_MASTER_RESET_ON ;
	_delay_ms ( 100 ) ;
	FIFO_MASTER_RESET_OFF ;
}
/********************************************************
*��������idt72v36110_reset
*��  ����û��
*��  �أ�û��
*��  �ã���FIFOоƬIDT72V36110��λ,FIFO�ľֲ���λ
**********************************************************/
void idt72v36110_reset(void)
{
	FIFO_PARTIAL_RESET_ON ;
	_delay_ms ( 100 ) ;
	FIFO_PARTIAL_RESET_OFF ;
}
