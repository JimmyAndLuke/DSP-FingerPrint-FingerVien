

#include "bsp_header\z_gt23l32s4w.h"

//char PY_mb_o     []  = {"Ŷ"}; //�����ַ�

/*****************************************************************
*��������GT23L32S4W_init
*��  ����û��
*��  �أ�û��
*˵  ������ʼ��GT23L32S4WӲ������������
*        ����GT23L32S4WоƬ��McBSP�ĳ�ʼ��
*****************************************************************/
void gt23l32s4w_init(void)
{
	/*McBSP��ʼ��*/

	McBSP2_SPCR =  0x01001000;//bit24 bit12
	McBSP2_RCR  =  0x00040000;//bit18
	McBSP2_XCR  =  0x00040000;//bit18
	McBSP2_SPGR =  0x20000063;
	McBSP2_PCR  =  0x00000F03;
	
    McBSP2_SPCR |= ((1<<FRST) | (1<<GRST));
	_delay_us(1);
	McBSP2_SPCR |= ((1<<RRST) | (1<<XRST));
	_delay_us(1);

    /*GT23L32S4WƬѡ������GPIO��Ӧ�ܽ��ø�*/
	GT23L32S4W_CS_OFF ;
}

/*****************************************************************
*��������mcbsp2_rw_byte
*��  ����data
*��  �أ�data
*˵  ����
*****************************************************************/
uint8_t Mcbsp2_RW_Byte(uint8_t data)
{
	uint32_t spcr = 0;
    
	McBSP2_DXR = data;
	while ((spcr&0x00000002) != 0x00000002) // check if the Receiver is ready ?
	{
		spcr = McBSP2_SPCR;   
	}
	data = McBSP2_DRR;

	return data;
}
/*******************************************************************
*��������gt23l32s4w_get_font
*��  ����uint32_t addr  :��ȡ���ݵ���ʼ��ַ�������ַ����Ϊ��Ч��ַ��
*        uint32_t count :��ȡ���ݵ��������ֽ�Ϊ��λ��������������0
*        uint8_t  *buf  :ָ���Ŷ�ȡ�����ݵĻ�����ָ�롣���ָ�����
*                        ָ��һ����Ч���������㹻��Ļ�������
*��  �أ�û��
*˵  ������GT23L32S4WоƬ��addr��ַ��ʼ��ȡcount�ֽڵ����ݴ�ŵ�buf
*        ���Ļ�������
*        �����������֣�
********************************************************************/
void Gt23l32s4w_Get_Font(uint32_t addr, uint32_t count, uint8_t *buf)
{
	uint8_t  tmp;
	uint32_t i;

	/*Ƭѡ�õ�*/
	GT23L32S4W_CS_ON; //ʹ���ֿ�оƬ
	_delay_ms(1);
	Mcbsp2_RW_Byte(0x0B);
	tmp = (uint8_t)(addr>>16) ;

	Mcbsp2_RW_Byte(tmp);
	tmp = (uint8_t)(addr>>8) ;

	Mcbsp2_RW_Byte(tmp);
	tmp = (uint8_t)(addr) ;

	Mcbsp2_RW_Byte(tmp);

	Mcbsp2_RW_Byte(0xFF);//dummy byte

	for (i = 0; i < count; i++)
	{
		buf[i] = Mcbsp2_RW_Byte(0xff);

	}
    /*Ƭѡ�ø�*/
    GT23L32S4W_CS_OFF;
}

//void Gt23l32s4w_Test (uint8_t *buf)
//{
//	uint32_t LSB ;
//	uint32_t MSB ;
//	uint32_t Address ;
//
//	MSB = ( uint32_t ) ( PY_mb_o[0] ) & 0x000000ff ;
//	LSB = ( uint32_t ) ( PY_mb_o[1] ) & 0x000000ff ;
//	
//	Address=0x68190;//24*24
//	if (MSB>=0xA4 && MSB<=0Xa8 && LSB>=0xA1)
//	{
//		Address = Address;
//	}else if (MSB>=0xA1 && MSB<=0Xa9 && LSB>=0xA1)
//	{
//		Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1))*72 + Address;
//	}else if (MSB>=0xB0 && MSB<=0xF7 && LSB>=0xA1)
//	{
//		Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*72 + Address;
//	}
//	Gt23l32s4w_Get_Font(Address, 72, buf);	
//
//}












