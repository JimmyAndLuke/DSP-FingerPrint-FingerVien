#include "bsp_header\z_zlg7290.h"

extern uint8_t		key_on ;

void ZLG7290_I2C_Delay ( void )
{
//	_delay_ms(10) ;
	_delay_us(30) ;
}
void ZLG7290_I2C_Init ( void )
{	
//	KEY_RESET_ON ;
//	_delay_ms(20);
//	KEY_RESET_OFF;
//	_delay_ms(200);

	ZLG7290_SDA_EN ;
	ZLG7290_SCL_EN ;
	ZLG7290_SCL_OUT ;
	ZLG7290_SDA_OUT ;

	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
}
//SDA	-----\________
//SCL	---------\____
void ZLG7290_I2C_Start ( void )
{
	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_0 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_0 ;
	ZLG7290_I2C_Delay() ;
}
//SDA	____/---------
//SCL	/-------------
void ZLG7290_I2C_Stop ( void )
{
	ZLG7290_SDA_0 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
	_delay_ms(100) ;    //����һ�β���START֮ǰһ��Ҫ��һ������ʱ
}
void ZLG7290_I2C_Write ( uint8_t data )
{
	uint8_t   t = 8 ; 
	do
	{
		if ( data & 0x80 )
			ZLG7290_SDA_1 ;
		else ZLG7290_SDA_0 ;
		data <<= 1 ;
		ZLG7290_SCL_1 ;
		ZLG7290_I2C_Delay() ;
		ZLG7290_SCL_0 ;
		ZLG7290_I2C_Delay() ;
	}while ( --t != 0 ) ;
}
char ZLG7290_I2C_Read ( void )
{
	char dat  ;
	unsigned char t = 8 ;

	ZLG7290_SDA_1 ;//�ڶ�ȡ����֮ǰ��Ҫ��SDA ���� 
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_IN ;//����������Ϊ����
	do
	{
		ZLG7290_SCL_1 ;
		ZLG7290_I2C_Delay () ;
		dat <<= 1 ;
		if ( ZLG7290_SDA_VAL ) dat |= 0x01;
		ZLG7290_SCL_0 ;
		ZLG7290_I2C_Delay () ;
	} while ( --t != 0 );
	ZLG7290_SDA_OUT ;//����������Ϊ���
	return dat ;
}
uint32_t ZLG7290_I2C_GetAck ( void )
{
	uint32_t ack ;
	ZLG7290_SDA_1 ;	
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_IN ;//����������Ϊ����
	ack = ZLG7290_SDA_VAL ;
	ZLG7290_SCL_0 ;
	ZLG7290_I2C_Delay () ;
	ZLG7290_SDA_OUT ;//����������Ϊ���
	return ack; 
}
/****************************************************************************
* ��    �ƣ�ZLG7290_I2C_PutAck ( uint32_t ack )
* ��    �ܣ���������Ӧ��λ���Ӧ��λ
* ��ڲ�����ACK	0ʱ����������Ӧ��λ��1ʱ������������Ӧ��λ
* ���ڲ�������
* ˵    ���������ڽ�����ÿһ���ֽڵ����ݺ󣬶�Ӧ������Ӧ��λ 
*           �����ڽ��������һ���ֽڵ����ݺ�Ӧ��������Ӧ��λ 
* ���÷�����ZLG7290_I2C_PutAck ( 1 ) ;
****************************************************************************/
void ZLG7290_I2C_PutAck ( uint32_t ack )
{
	if ( ack )  
		ZLG7290_SDA_1 ;
	else
		ZLG7290_SDA_0 ;
	ZLG7290_I2C_Delay () ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay () ;
	ZLG7290_SCL_0 ;
	ZLG7290_I2C_Delay () ;
}
/****************************************************************************
* ��    �ƣ�ZLG7290_I2C_Gets
* ��    �ܣ�I2C�����ۺϽ��պ������Ӵӻ�����1���ֽڵ�����
* ��ڲ�����SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
*		    SubAddr�� �ӻ����ӵ�ַ
*          *dat��     ������յ�������
* ���ڲ�����0��	���ճɹ�
*			1���ڽ��չ����г����쳣
* ˵    ���������ڽ�����ÿһ���ֽڵ����ݺ󣬶�Ӧ������Ӧ��λ 
*           �����ڽ��������һ���ֽڵ����ݺ�Ӧ��������Ӧ��λ 
* ���÷�����
****************************************************************************/
uint32_t ZLG7290_I2C_Gets
(
	unsigned char SlaveAddr,
	unsigned char SubAddr,
	unsigned char SubMod ,
	char *data ,
	unsigned int  Size
)
{
	unsigned char i ;
	char a[3] ;
	//��鳤��
	if ( Size == 0 ) return 0 ;
	//׼���ӻ���ַ
	a[0] = ( SlaveAddr << 1 ) ;
	//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2 ;
	//������ӵ�ַ�Ĵӻ�����Ҫ�ȷ��ʹӻ���ַ���ӵ�ַ
	if (SubMod != 0)
	{
		//ȷ���ӵ�ַ
		if (SubMod==1)
		{
			a[1] = (char)(SubAddr);
		}
		else
		{
			a[1] = (char)(SubAddr >> 8);
			a[2] = (char)(SubAddr) ;
		}
		//���ʹӻ���ַ�����ŷ����ӵ�ַ
		SubMod ++ ;
		ZLG7290_I2C_Start() ;
		for (i=0;i<SubMod;i++)
		{
			ZLG7290_I2C_Write(a[i]) ;
			if (ZLG7290_I2C_GetAck())
			{
				ZLG7290_I2C_Stop() ;
				return 1 ;
			}
		}
	}
	ZLG7290_I2C_Start();
	//���ʹӻ���ַ
	ZLG7290_I2C_Write(a[0]+1) ;
	if (ZLG7290_I2C_GetAck())
	{
		ZLG7290_I2C_Stop() ;
		return 1 ;
	}
	//��������
	for (;;)
	{
		*data++ = ZLG7290_I2C_Read() ;
		if (--Size == 0)
		{
			ZLG7290_I2C_PutAck(1) ;
			break ;
		}
		ZLG7290_I2C_PutAck(0) ;
	}
	ZLG7290_I2C_Stop() ;
	return 0 ;
}
/****************************************************************************
* ��    �ƣ�ZLG7290_ReadReg(unsigned char RegAddr, uint32_t *dat)
* ��    �ܣ����Ĵ���
* ��ڲ�����RegAddr��ZLG7290���ڲ��Ĵ�����ַ
*       	*dat���������������
* ���ڲ�����0������
*	    	1������ZLG7290ʱ�����쳣
* ˵    ����
* ���÷�����
****************************************************************************/
uint32_t ZLG7290_ReadReg(unsigned char RegAddr, char *dat)
{
	uint32_t b;//
	b = ZLG7290_I2C_Gets(ZLG7290_I2C_ADDR,RegAddr,1,dat,1);
	return b;
}
/****************************************************************************
* ��    �ƣ�ZLG7290_Test_Key(void)
* ��    �ܣ���������
* ��ڲ�����
* ���ڲ�������ֵ
* ˵    ����������
* ���÷�����ZLG7290_Test_Key() ;
****************************************************************************/
char ZLG7290_Test_Key(void)
{
	char KeyValue;
	if ( key_on )		//����м�����
	{
		key_on = 0 ; //���������ʶ		
		 
		if ( !ZLG7290_ReadReg(ZLG7290_Key,&KeyValue) )//��ȡ��ֵ
		{
			key_on = 0 ; //���������ʶ	
			asm ( " NOP " ) ;
			return KeyValue ;
		}
		else
			return -1 ;
		
	}
	else
		return -1 ;
}
























