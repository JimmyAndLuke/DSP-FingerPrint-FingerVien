
#include "bsp_header\z_ds1302.h"
#include "bsp_header\z_sys_time.h"


inline static void DS1302_Dalay(void)
{
	_delay_us(5);
}
/*******************************************************************
�������ܣ���DS1302��һ�ֽ����ݳ���
��ڲ�����byte
********************************************************************/
static void DS1302_Write_Byte(uint8_t byte)
{
	uint8_t	count ;
	for ( count = 0; count < 8; count++ ){	
		DS1302_CLK_L ;
		if ( byte & 0x01 )
			DS1302_IO_H ;
		else
			DS1302_IO_L ;
		DS1302_Dalay();
		DS1302_CLK_H ;     //_____/--------		
		byte >>= 1;
	}
}
/*******************************************************************
�������ܣ���DS1302һ���ֽڳ���
���ڲ�����data
*******************************************************************/
static uint8_t DS1302_Read_Byte(void)
{
	uint8_t count ;
	uint8_t temp ;
	uint8_t data = 0 ;
	DS1302_IO_IN ; //IO SHOULD BE INPUT
	DS1302_Dalay();
	for ( count = 0; count < 8; count ++ ){
		data >>= 1;
		DS1302_CLK_H ;
		DS1302_Dalay();
		DS1302_CLK_L ;
		DS1302_Dalay();
		temp = DS1302_IO_VAL ;
		if ( temp ) data |= 0x80;
	}
	DS1302_IO_OUT ;//IO RESET TO BE OUTPUT
	return data ;
}
/*******************************************************************
�������ܣ���DS1302ĳ��ַдһ�ֽ����ݳ���
��ڲ�����addr,data
*******************************************************************/
static void DS1302_Write_Addr(uint8_t addr,uint8_t data)
{
	DS1302_RST_L ;
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_RST_H ;
	DS1302_Dalay();
	DS1302_Write_Byte( addr ) ;
	DS1302_Dalay();
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_Write_Byte( data ) ;
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_RST_L ;
}
/******************************************************************
�������ܣ���DS1302��ַ���� ����ΪBCD��
��ڲ�����addr 
******************************************************************/
//static 
uint8_t DS1302_Read_Addr(uint8_t addr)
{
	uint8_t  data;
	
	DS1302_RST_L ;
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_RST_H ;
	DS1302_Dalay();
	DS1302_Write_Byte( addr ) ;
	DS1302_Dalay();
	data = DS1302_Read_Byte() ;
	DS1302_Dalay();
	DS1302_CLK_L ;
	DS1302_RST_L ;

	return data;
}
/******************************************************************
�������ܣ���ʼ��DS1302����
*******************************************************************/
void ds1302_init(void)
{

	asm ( " NOP " ) ;
	///�趨ʱ��
	DS1302_Write_Addr( CONTROL|WRITE , UPROTECT ) ;

	//DS1302_Write_Addr( SECOND|WRITE , 0x30 ) ;
	//DS1302_Write_Addr( MINUTE|WRITE , 0x20 ) ;
	//DS1302_Write_Addr( HOUR|WRITE , 0x22 ) ;
	//DS1302_Write_Addr( DAY|WRITE , 0x04 ) ;
	//DS1302_Write_Addr( MONTH|WRITE , 0x06 ) ;
	//DS1302_Write_Addr( WEEK|WRITE , 0x01 ) ;
	//DS1302_Write_Addr( YEAR|WRITE , 0x12 ) ;

	DS1302_Write_Addr( CONTROL|WRITE , PROTECT ) ;

}
/******************************************************************
�������ܣ�DS1302�޸�ʱ��
*******************************************************************/
uint8_t DS1302_Set_Time(time_t *systime)
{
	if (systime == NULL)
	{
		return FALSE;
	}
	else
	{
		DS1302_Write_Addr(CONTROL|WRITE, UPROTECT);	          //�������Ĵ������ڶ�ʱ�ӻ�RAMдǰWPһ��ҪΪ0,��������
		DS1302_Write_Addr(YEAR|WRITE, systime->year);    //��
		DS1302_Write_Addr(WEEK|WRITE, systime->week);    //����
		DS1302_Write_Addr(MONTH|WRITE, systime->month);   //��
		DS1302_Write_Addr(DAY|WRITE, systime->day);     //��
		DS1302_Write_Addr(HOUR|WRITE, systime->hour);    //ʱ
		DS1302_Write_Addr(MINUTE|WRITE, systime->minute);  //��
		DS1302_Write_Addr(SECOND|WRITE, systime->second);  //��
		DS1302_Write_Addr(CONTROL|WRITE, PROTECT);          //д�����Ĵ���
	}
	
	return TRUE;
}
/******************************************************************
�������ܣ���DS1302ʱ�����
���ڲ�����
******************************************************************/
uint8_t DS1302_Get_Time(time_t *systime)
{
	if (systime == NULL)
	{
		return FALSE;
	}
	else
	{
		systime->second = DS1302_Read_Addr(SECOND|READ);  //����
		systime->minute = DS1302_Read_Addr(MINUTE|READ);  //��
		systime->hour   = DS1302_Read_Addr(HOUR|READ);  //ʱ
		systime->day    = DS1302_Read_Addr(DAY|READ);  //��
		systime->month  = DS1302_Read_Addr(MONTH|READ);  //��
		systime->week   = DS1302_Read_Addr(WEEK|READ);  //����
		systime->year   = DS1302_Read_Addr(YEAR|READ);  //��
	}
	
	return TRUE;
}


















