


#include"bsp_header\z_iLCD.h"


static uint16_t pic[16384] ;
static uint16_t iLCD_display_BUF[iLCD_Y_MAX][iLCD_X_MAX] ;
inline static void iLCD_WriteCmd (uint16_t cmd)
{   
//����ΪҺ��7783������������������д�����ȵͺ��
#ifdef _7783_
	LCD_CMD_BEGIN ; //дָ�ʼ
	_74HC573_LE_H ; //д��8λ��ʼ
	*((unsigned short*)(0x6c000040))= cmd ;//BEA6//CE0
	_74HC573_LE_L ; //д��8λ��ʼ
	*((unsigned short*)(0x6c000040))= (cmd>>8);//BEA6//CE0
	LCD_TRANSFER_END ; //д���
#endif
//����ΪҺ��7783������������������д�����ȵͺ��

//����ΪҺ��ILI9320(������8λģʽ)������д�����ȸߺ��
#ifdef ILI9320
	LCD_CMD_BEGIN ; //дָ�ʼ
	*((unsigned short*)(0x6c000040))= (cmd>>8) ;//BEA6//CE0
	*((unsigned short*)(0x6c000040))= cmd ;//BEA6//CE0
	LCD_TRANSFER_END ; //д���
#endif
//����ΪҺ��ILI9320(������8λģʽ)������д�����ȸߺ��
} 

inline static void iLCD_WriteData(uint16_t data)//
{
//����ΪҺ��7783������������������д�����ȵͺ��
#ifdef _7783_
	LCD_DATA_BEGIN ; //д���ݿ�ʼ
	_74HC573_LE_H ; //д��8λ��ʼ
	*((unsigned short*)(0x6c000040))=data;//BEA6//CE0
	_74HC573_LE_L ; //д��8λ��ʼ
	*((unsigned short*)(0x6c000040))=(data>>8);//BEA6//CE0
	LCD_TRANSFER_END ; //д���
#endif
//����ΪҺ��7783������������������д�����ȵͺ��

//����ΪҺ��ILI9320(������8λģʽ)������д�����ȸߺ��
#ifdef ILI9320
	LCD_DATA_BEGIN ; //дָ�ʼ
	*((unsigned short*)(0x6c000040))= (data>>8) ;//BEA6//CE0
	*((unsigned short*)(0x6c000040))= data ;//BEA6//CE0
	LCD_TRANSFER_END ; //д���
#endif
//����ΪҺ��ILI9320(������8λģʽ)������д�����ȸߺ��
}

void iLCD_WriteReg(uint16_t Index,uint16_t Data)
{  
    //_delay_ms(1);
	iLCD_WriteCmd(Index);
	//_delay_ms(1);
	iLCD_WriteData(Data);
}
/************************************************
��������Lcdд��ʼ����
���ܣ�����Lcd�������� ִ��д����
��ڲ�������
����ֵ����
************************************************/
void iLCD_WriteStart(void)
{
	iLCD_WriteCmd( 0x0022 ) ;
}
/******************************************************************
** ��������: LCD�����㶨λ����
** ��������: ָ��320240Һ���ϵ�һ����Ϊд���ݵ���ʼ��
** ��ڲ���: y ���� 0~239
**           x ���� 0~319
** ���ز���: ��
*******************************************************************/
void iLCD_SetCursor( int16_t y ,int16_t x )
{ 
	iLCD_WriteReg(0x20,y);
	iLCD_WriteReg(0x21,x);//
}
/******************************************************************
** ��������: LCDȫ����������
** ��������: ��LCD������Ϊָ����ɫ
** ��ڲ���: color ָ��LCDȫ����ɫ RGB(5-6-5)
** ���ز���: ��
******************************************************************/
void iLCD_Clear(uint16_t color)
{
	uint32_t temp;
  
	iLCD_WriteReg(0x0050,0x00);   //ˮƽGRAM��ʼλ��
	iLCD_WriteReg(0x0051,239);     //ˮƽGRAM��ֹλ��
	iLCD_WriteReg(0x0052,0);   //��ֱGRAM��ʼλ��
	iLCD_WriteReg(0x0053,319);     //��ֱGRAM��ֹλ��
	
	iLCD_SetCursor(0,0);
	iLCD_WriteStart();

	for (temp = 0;  temp < ( iLCD_Y_MAX * iLCD_X_MAX ) ; temp++)
	{
		iLCD_WriteData(color);
	}
	asm ( "	nop" ) ;
}
/******************************************************************
** ��������: LCD��ʼ��
** ��������: LCD��ʼ��
** ��ڲ���: ��
** ���ز���: ��
*******************************************************************/
void iLCD_Init(void)
{
	LCD_BAKCLIGHT_ON ;//������
	LCD_INSIDE_RESET ;//��λ�������٣�
	LCD_SET ;		  //DSP���ڲ�Һ��д���ݣ�д����֮ǰһ��Ҫ����䣩
//�ͺţ�7783
#ifdef _7783_
	iLCD_WriteReg(0x00FF,0x0001);
	iLCD_WriteReg(0x00F3,0x0008);
	iLCD_WriteReg(0x0001,0x0100);
	iLCD_WriteReg(0x0002,0x0700);
	iLCD_WriteReg(0x0003,0x1018);  //0x1030
	iLCD_WriteReg(0x0008,0x0302);
	iLCD_WriteReg(0x0008,0x0207);
	iLCD_WriteReg(0x0009,0x0000);
	iLCD_WriteReg(0x000A,0x0000);
	iLCD_WriteReg(0x0010,0x0000);  //0x0790
	iLCD_WriteReg(0x0011,0x0005);
	iLCD_WriteReg(0x0012,0x0000);
	iLCD_WriteReg(0x0013,0x0000);
	_delay_ms(50);
	iLCD_WriteReg(0x0010,0x12B0);
	_delay_ms(50);
	iLCD_WriteReg(0x0011,0x0007);
	_delay_ms(50);
	iLCD_WriteReg(0x0012,0x008B);
	_delay_ms(50);
	iLCD_WriteReg(0x0013,0x1700);
	_delay_ms(50);
	iLCD_WriteReg(0x0029,0x0022);
	
	//################# void Gamma_Set(void) ####################//
	iLCD_WriteReg(0x0030,0x0000);
	iLCD_WriteReg(0x0031,0x0707);
	iLCD_WriteReg(0x0032,0x0505);
	iLCD_WriteReg(0x0035,0x0107);
	iLCD_WriteReg(0x0036,0x0008);
	iLCD_WriteReg(0x0037,0x0000);
	iLCD_WriteReg(0x0038,0x0202);
	iLCD_WriteReg(0x0039,0x0106);
	iLCD_WriteReg(0x003C,0x0202);
	iLCD_WriteReg(0x003D,0x0408);
	_delay_ms(50);
	
	
	iLCD_WriteReg(0x0050,0x0000);		
	iLCD_WriteReg(0x0051,0x00EF);		
	iLCD_WriteReg(0x0052,0x0000);		
	iLCD_WriteReg(0x0053,0x013F);		
	iLCD_WriteReg(0x0060,0xA700);		
	iLCD_WriteReg(0x0061,0x0001);
	iLCD_WriteReg(0x0090,0x0033);				
	iLCD_WriteReg(0x002B,0x000B);		
	iLCD_WriteReg(0x0007,0x0133);
	_delay_ms(50);
	iLCD_Clear( BLUE ) ;

	LCD_RT_DISPLAY ; //DSP���ڲ�Һ��д������ϣ���Һ�����߽���AL422B��ʼʵʱ��ʾ
					//ÿ��DSP���ڲ�Һ��д�����ݶ�Ҫ����䡣��������
#endif

//�ͺ�ILI9320
#ifdef ILI9320
	iLCD_WriteReg( 0x00E5 , 0x8000 ) ;
    iLCD_WriteReg( 0x0000 , 0x0001 ) ;
	_delay_ms( 10 ) ;
	iLCD_WriteReg( 0x0000 , 0x0000 ) ;
	iLCD_WriteReg( 0x0001 , 0x0100 ) ;
	iLCD_WriteReg( 0x0002 , 0x0700 ) ;
	iLCD_WriteReg( 0x0003 , 0x1018 ) ;////////////

	iLCD_WriteReg( 0x0004 , 0x0000 ) ;
	iLCD_WriteReg( 0x0008 , 0x0207 ) ;
	iLCD_WriteReg( 0x0009 , 0x0000 ) ;
	iLCD_WriteReg( 0x000A , 0x0000 ) ;
	iLCD_WriteReg( 0x000C , 0x0001 ) ; //�˴����ýӿ����� 16λ system�ӿ�
	iLCD_WriteReg( 0x000D , 0x0000 ) ;
	iLCD_WriteReg( 0x000F , 0x0000 ) ;

	_delay_ms( 10 ) ;
	iLCD_WriteReg( 0x0007 , 0x0101 ) ;
	_delay_ms( 10 ) ;
	//��Դ����
	iLCD_WriteReg( 0x0010 , 0x0000 ) ;
	iLCD_WriteReg( 0x0011 , 0x0000 ) ;
	iLCD_WriteReg( 0x0012 , 0x0000 ) ;
	iLCD_WriteReg( 0x0013 , 0x0000 ) ;
	_delay_ms( 200 ) ;
	iLCD_WriteReg( 0x0010 , 0x17b0 ) ;
	iLCD_WriteReg( 0x0011 , 0x0137 ) ;
	_delay_ms( 50 ) ;
	iLCD_WriteReg( 0x0012 , 0x0139 ) ;
	_delay_ms( 50 ) ;
	iLCD_WriteReg( 0x0013 , 0x1700 ) ;
	iLCD_WriteReg( 0x0029 , 0x000c ) ;
	_delay_ms( 50 ) ;

	iLCD_WriteReg( 0x0030 , 0x0000 ) ;
	iLCD_WriteReg( 0x0031 , 0x0507 ) ;
	iLCD_WriteReg( 0x0032 , 0x0104 ) ;
	iLCD_WriteReg( 0x0035 , 0x0105 ) ;
	iLCD_WriteReg( 0x0036 , 0x0404 ) ;
	iLCD_WriteReg( 0x0037 , 0x0603 ) ;
	iLCD_WriteReg( 0x0038 , 0x0004 ) ;
	iLCD_WriteReg( 0x0039 , 0x0007 ) ;
	iLCD_WriteReg( 0x003c , 0x0501 ) ;
	iLCD_WriteReg( 0x003d , 0x0404 ) ;
	iLCD_WriteReg( 0x0050 , 0 ) ;	//ˮƽGRAM��ʼλ��
	iLCD_WriteReg( 0x0051 , 239 ) ;	//ˮƽGRAM��ֹλ��
	iLCD_WriteReg( 0x0052 , 0 ) ;	//��ֱGRAM��ʼλ��
	iLCD_WriteReg( 0x0053 , 319 ) ;	//��ֱGRAM��ֹλ��

	iLCD_WriteReg( 0x0060 , 0x2700 ) ;
	iLCD_WriteReg( 0x0061 , 0x0001 ) ;
	iLCD_WriteReg( 0x006A , 0x0000 ) ;

	iLCD_WriteReg( 0x0080 , 0x0000 ) ;
	iLCD_WriteReg( 0x0081 , 0x0000 ) ;
	iLCD_WriteReg( 0x0082 , 0x0000 ) ;
	iLCD_WriteReg( 0x0083 , 0x0000 ) ;
	iLCD_WriteReg( 0x0084 , 0x0000 ) ;
	iLCD_WriteReg( 0x0085 , 0x0000 ) ;

	iLCD_WriteReg( 0x0090 , 0x0010 ) ;
	iLCD_WriteReg( 0x0092 , 0x0000 ) ;
	iLCD_WriteReg( 0x0093 , 0x0003 ) ;
	iLCD_WriteReg( 0x0095 , 0x0110 ) ;
	iLCD_WriteReg( 0x0097 , 0x0000 ) ;
	iLCD_WriteReg( 0x0098 , 0x0000 ) ;

	iLCD_WriteReg( 0x0007 , 0x0173 ) ;
	_delay_ms( 10 ) ;
	
	iLCD_Clear( 0 ) ;

	LCD_RT_DISPLAY ; //DSP���ڲ�Һ��д������ϣ���Һ�����߽���AL422B��ʼʵʱ��ʾ
	                     //ÿ��DSP���ڲ�Һ��д�����ݶ�Ҫ����䡣��������
#endif
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�LCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color)
* ��    �ܣ����������е�һ�����ο���³�color��ɫ
* ��ڲ�����StartY      ��ֱ������ʼ����
*           StartX     ˮƽ������ʼ����
*           LongY       ��ֱ���򳤶�
*           LongX       ˮƽ���򳤶�
*			color		��ɫ
* ���ڲ�������
* ˵    ������������ϱ�������Ļ��Χ�ڣ�(StartY+LongY)<=240,(StartX+LongX)<=320
* ���÷�����LCD_Fill_Rect_Buf( 0,0,240,320,RED) ;
****************************************************************************/

void iLCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color)
{
	uint16_t x ,y ;

	for ( y = StartY ; y < ( StartY + LongY ) ; y++ )
	{
		for ( x = StartX ; x <= ( StartX + LongX ) ; x++ )
		{
			iLCD_display_BUF[y][x] = color;
		}
	}
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* ��    �ܣ�����ʾ��������ָ����������ݸ��µ�ָ����������
* ��ڲ�����StartY      ��ֱ������ʼ����
*           StartX     ˮƽ������ʼ����
*           LongY       ��ֱ���򳤶�
*           LongX       ˮƽ���򳤶�
* ���ڲ�������
* ˵    ������������ϱ�������Ļ��Χ�ڣ�(StartY+LongY)<=240,(StartX+LongX)<=320
* ���÷�����oLCD_Update_Rect_Screen( 0,0,240,320) ;
****************************************************************************/

void iLCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX )
{
	uint16_t x ,y ;

	iLCD_WriteReg(0x0050,StartY  );//
    iLCD_WriteReg(0x0051,StartY+LongY-1 );//
    iLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
    iLCD_WriteReg(0x0053,319-StartX);//

	iLCD_SetCursor(StartY,319-(StartX+LongX-1));
	iLCD_WriteStart();

//	iLCD_WriteData(iLCD_display_BUF[0][0]);//��һ������Ϊ��Чֵ������ָ����������
	for(y=StartY; y<(StartY+LongY); y++)
	{
		for(x=StartX; x<(StartX+LongX); x++)
		{
			iLCD_WriteData(iLCD_display_BUF[y][x]);
		}
	}
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* ��    �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
* ��ڲ�����StartY      ��ֱ������ʼ����
*           StartX     ˮƽ������ʼ����
*           LongY       ��ֱ���򳤶�
*           LongX       ˮƽ���򳤶�
            pic        ͼƬͷָ��
* ���ڲ�������
* ˵    ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ
*           ��������ϱ�������Ļ��Χ�ڣ�(StartY+LongY)<=240,(StartX+LongX)<=320
* ���÷�����oLCD_Draw_Picture( 0,0,240,320,(uint16_t*)gImage_pic) ;
****************************************************************************/
void iLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
{
  uint32_t  i;
  uint16_t  *ppic ;
  ppic = pic ;
  iLCD_WriteReg(0x0050,StartY  );//
  iLCD_WriteReg(0x0051,StartY+LongY-1 );//
  iLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
  iLCD_WriteReg(0x0053,319-StartX);//

  
  iLCD_SetCursor(StartY, 319-(StartX+LongX-1));
  iLCD_WriteStart();
	
//  oLCD_WriteData(*ppic); //д��һ������ʱ����ָ���������ڣ���������дһ������
  for (i=0;i<( LongY * LongX ) ;i++ )
  {
      iLCD_WriteData(*ppic++);
  }     
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�oLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t * *           LongX ,uint16_t CharColor , uint16_t CharBackColor , uint16_t *ChineseCode )
* ��    �ܣ���ʾ����
* ��ڲ�����StartY      ��ֱ������ʼ����
*           StartX     ˮƽ������ʼ����
*           LongY       ��ֱ���򳤶�
*           LongX       ˮƽ���򳤶ȣ�ӦΪ8�ı���
* ���ڲ�������
* ˵    ����ȡģ˳������ �ϵ��� ����8�����λ
*           ȡģ��������Ϊ8λ
* ���÷�����oLCD_Write_Chinese ( 0,0,16,16 , WHITE , BLACK , GB_16 ) ;
****************************************************************************/
void iLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ,uint16_t CharColor , uint16_t CharBackColor , uint8_t *ChineseCode )
{
	uint8_t  *pic ;
	uint8_t   ByteCounter , BitCounter ;
	pic = ChineseCode ;

	iLCD_WriteReg(0x0050,StartY  );//
	iLCD_WriteReg(0x0051,StartY+LongY-1 );//
	iLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
	iLCD_WriteReg(0x0053,319-StartX);//

	iLCD_SetCursor(StartY, 319-(StartX+LongX-1));
    iLCD_WriteStart();
//	iLCD_WriteData(*pic); //д��һ������ʱ����ָ���������ڣ���������дһ������
	for ( ByteCounter = 0 ; ByteCounter < ( LongY*LongX/8 ) ; ByteCounter++ )
	{
		for ( BitCounter = 0 ; BitCounter < 8 ; BitCounter++ )
		{
			if ( ( *pic & ( 0x80 >> BitCounter ) ) == 0x00 )
				iLCD_WriteData( CharBackColor ) ;
			else
				iLCD_WriteData( CharColor ) ;
		}
		pic++ ;
	}
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* ��    �ܣ�������Ļ������Ļ����ʾ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����oLCD���Թ��ܺ�����ʱ����
* ���÷�����LCD_Write_Screen () ;
****************************************************************************/
void iLCD_Test ( void )
{

//	iLCD_Fill_Rect_Buf(1,1,5,5 , 0x0000) ;
//	iLCD_Update_Rect_Screen ( 1,1,5,5 ) ;
	uint32_t i , j ;
	flash_select_page(1) ; //flashѡҳ
	j = 0 ;
	for ( i=0; i<0x8000; i+=2 ){
		pic[j] = flash_read_word( (FLASH_BASE_ADDR+i) ) ;
		j++ ;
	}
	iLCD_Draw_Picture( 0,192,128,128,pic) ;
	asm ( " NOP " ) ;
	asm ( " NOP " ) ;
}











