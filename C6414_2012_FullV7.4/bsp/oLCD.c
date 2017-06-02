
#include"bsp_header\z_oLCD.h"

//static uint16_t pic[16384] ;
static uint16_t oLCD_display_BUF[oLCD_Y_MAX][oLCD_X_MAX] ;
//extern unsigned char gImage[33920] ;

inline static void oLCD_WriteCmd (uint16_t cmd)
{
    *((unsigned short*)(0x68000000))=cmd;
} 

inline static void oLCD_WriteData(uint16_t data)
{
    *((unsigned short*)(0x68000002))=data;
}

void oLCD_WriteReg(uint16_t Index,uint16_t Data)
{  
    //_delay_ms(1);
	oLCD_WriteCmd(Index);
	//_delay_ms(1);
	oLCD_WriteData(Data);
}

/************************************************
��������Lcdд��ʼ����
���ܣ�����Lcd�������� ִ��д����
��ڲ�������
����ֵ����
************************************************/
void oLCD_WriteStart(void)
{
	oLCD_WriteCmd( 0x0022 ) ;
}
/******************************************************************
** ��������: LCD�����㶨λ����
** ��������: ָ��320240Һ���ϵ�һ����Ϊд���ݵ���ʼ��
** ��ڲ���: x ���� 0~239
**           y ���� 0~319
** ���ز���: ��
*******************************************************************/
void oLCD_SetCursor( int16_t y ,int16_t x )
{ 
	oLCD_WriteReg(0x20,y);
	oLCD_WriteReg(0x21,x);
}
/******************************************************************
** ��������: LCDȫ����������
** ��������: ��LCD������Ϊָ����ɫ
** ��ڲ���: color ָ��LCDȫ����ɫ RGB(5-6-5)
** ���ز���: ��
******************************************************************/
void oLCD_Clear(uint16_t color)
{
	uint32_t temp;
  
	oLCD_WriteReg(0x0050,0x00);   //ˮƽGRAM��ʼλ��
	oLCD_WriteReg(0x0051,239);     //ˮƽGRAM��ֹλ��
	oLCD_WriteReg(0x0052,0);   //��ֱGRAM��ʼλ��
	oLCD_WriteReg(0x0053,319);     //��ֱGRAM��ֹλ��
	
	oLCD_SetCursor(0,0);
	oLCD_WriteStart();

	for (temp = 0;  temp < ( oLCD_Y_MAX * oLCD_X_MAX ) ; temp++) 
	{
		oLCD_WriteData(color);
	}
	asm ( "	nop" ) ;
}
/******************************************************************
** ��������: LCD��ʼ��
** ��������: LCD��ʼ��
** ��ڲ���: ��
** ���ز���: ��
*******************************************************************/
void oLCD_Init(void)
{
	LCD_BAKCLIGHT_ON ; 
	oLCD_WriteReg( 0x00E5 , 0x8000 ) ;
    oLCD_WriteReg( 0x0000 , 0x0001 ) ;
	_delay_ms( 10 ) ;
	oLCD_WriteReg( 0x0000 , 0x0000 ) ;
	oLCD_WriteReg( 0x0001 , 0x0100 ) ;
	oLCD_WriteReg( 0x0002 , 0x0700 ) ;
	oLCD_WriteReg( 0x0003 , 0x1018 ) ;////////////

	oLCD_WriteReg( 0x0004 , 0x0000 ) ;
	oLCD_WriteReg( 0x0008 , 0x0207 ) ;
	oLCD_WriteReg( 0x0009 , 0x0000 ) ;
	oLCD_WriteReg( 0x000A , 0x0000 ) ;
	oLCD_WriteReg( 0x000C , 0x0001 ) ; //�˴����ýӿ����� 16λ system�ӿ�
	oLCD_WriteReg( 0x000D , 0x0000 ) ;
	oLCD_WriteReg( 0x000F , 0x0000 ) ;

	_delay_ms( 10 ) ;
	oLCD_WriteReg( 0x0007 , 0x0101 ) ;
	_delay_ms( 10 ) ;
	//��Դ����
	oLCD_WriteReg( 0x0010 , 0x0000 ) ;
	oLCD_WriteReg( 0x0011 , 0x0000 ) ;
	oLCD_WriteReg( 0x0012 , 0x0000 ) ;
	oLCD_WriteReg( 0x0013 , 0x0000 ) ;
	_delay_ms( 200 ) ;
	oLCD_WriteReg( 0x0010 , 0x17b0 ) ;
	oLCD_WriteReg( 0x0011 , 0x0137 ) ;
	_delay_ms( 50 ) ;
	oLCD_WriteReg( 0x0012 , 0x0139 ) ;
	_delay_ms( 50 ) ;
	oLCD_WriteReg( 0x0013 , 0x1700 ) ;
	oLCD_WriteReg( 0x0029 , 0x000c ) ;
	_delay_ms( 50 ) ;

	oLCD_WriteReg( 0x0030 , 0x0000 ) ;
	oLCD_WriteReg( 0x0031 , 0x0507 ) ;
	oLCD_WriteReg( 0x0032 , 0x0104 ) ;
	oLCD_WriteReg( 0x0035 , 0x0105 ) ;
	oLCD_WriteReg( 0x0036 , 0x0404 ) ;
	oLCD_WriteReg( 0x0037 , 0x0603 ) ;
	oLCD_WriteReg( 0x0038 , 0x0004 ) ;
	oLCD_WriteReg( 0x0039 , 0x0007 ) ;
	oLCD_WriteReg( 0x003c , 0x0501 ) ;
	oLCD_WriteReg( 0x003d , 0x0404 ) ;
	oLCD_WriteReg( 0x0050 , 0 ) ;	//ˮƽGRAM��ʼλ��
	oLCD_WriteReg( 0x0051 , 239 ) ;	//ˮƽGRAM��ֹλ��
	oLCD_WriteReg( 0x0052 , 0 ) ;	//��ֱGRAM��ʼλ��
	oLCD_WriteReg( 0x0053 , 319 ) ;	//��ֱGRAM��ֹλ��

	oLCD_WriteReg( 0x0060 , 0x2700 ) ;
	oLCD_WriteReg( 0x0061 , 0x0001 ) ;
	oLCD_WriteReg( 0x006A , 0x0000 ) ;

	oLCD_WriteReg( 0x0080 , 0x0000 ) ;
	oLCD_WriteReg( 0x0081 , 0x0000 ) ;
	oLCD_WriteReg( 0x0082 , 0x0000 ) ;
	oLCD_WriteReg( 0x0083 , 0x0000 ) ;
	oLCD_WriteReg( 0x0084 , 0x0000 ) ;
	oLCD_WriteReg( 0x0085 , 0x0000 ) ;

	oLCD_WriteReg( 0x0090 , 0x0010 ) ;
	oLCD_WriteReg( 0x0092 , 0x0000 ) ;
	oLCD_WriteReg( 0x0093 , 0x0003 ) ;
	oLCD_WriteReg( 0x0095 , 0x0110 ) ;
	oLCD_WriteReg( 0x0097 , 0x0000 ) ;
	oLCD_WriteReg( 0x0098 , 0x0000 ) ;

	oLCD_WriteReg( 0x0007 , 0x0173 ) ;
	_delay_ms( 10 ) ;
	
	oLCD_Clear( BLACK ) ;
	asm( " NOP ");
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�LCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color )
* ��    �ܣ����������е�һ�����ص���³�color��ɫ
* ��ڲ�����Y      ��ֱ��������
*           X     ˮƽ��������
*			color		��ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����LCD_Fill_Pixel_Buf( 0 , 0 , RED ) ;
****************************************************************************/
void oLCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color )
{
	if ( ( x >= oLCD_X_MAX ) || ( y >= oLCD_Y_MAX ) )
	{
		return;
	}
	else
	{
		oLCD_display_BUF[y][x] = color ;
	}
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

void oLCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color)
{
	uint16_t x ,y ;

	for ( y = StartY ; y < ( StartY + LongY ) ; y++ )
	{
		for ( x = StartX ; x < ( StartX + LongX ) ; x++ )
		{
			oLCD_display_BUF[y][x] = color;
		}
	}
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�LCD_Fill_Full_Buf ( uint16_t color )
* ��    �ܣ���color��䵽������ʾ������
* ��ڲ�����color		��ɫ
* ���ڲ�������
* ˵    ��������LCD_Fill_Rect_Buf() ;����
* ���÷�����LCD_Fill_Full_Buf ( RED ) ;
****************************************************************************/
/**/
void oLCD_Fill_Full_Buf ( uint16_t color )
{
	uint16_t y ,x ;
	for ( y=0 ; y<oLCD_Y_MAX ; y++ )
	{
		for ( x=0 ; x<oLCD_X_MAX ; x++ )
		{
			oLCD_display_BUF[y][x] = color;
		}
	}
}
/****************************************************************************
* ��ʾģʽ������
* ��    �ƣ�oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* ��    �ܣ�������������������ˢ�µ���Ļ
* ��ڲ�����*buf   ��������
* ���ڲ�������
* ˵    ����
* ���÷�����oLCD_Update_Full_Screen(&oLCD_display_BUF[0][0]) ;
****************************************************************************/
/**/
void oLCD_Update_Full_Screen(uint16_t *buf)
{
	uint32_t i;
	oLCD_WriteReg(0x0050,0  );//
	oLCD_WriteReg(0x0051,239);//
	oLCD_WriteReg(0x0052,0  );//
	oLCD_WriteReg(0x0053,319);//

	oLCD_SetCursor(-1, 0);
    oLCD_WriteStart();
    
    oLCD_WriteData ( *( buf ) ) ;//д��һ������ʱ����ָ���������ڣ���������дһ������
	for( i = 0 ; i < ( oLCD_Y_MAX * oLCD_X_MAX ) ; i++ )
	{
		oLCD_WriteData ( *( buf + i ) ) ;
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
void oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
{
  uint32_t  i;
  uint16_t  *ppic ;
  ppic = pic ;
  oLCD_WriteReg(0x0050,StartY  );//
  oLCD_WriteReg(0x0051,StartY+LongY-1 );//
  oLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
  oLCD_WriteReg(0x0053,319-StartX);//

  
  oLCD_SetCursor(StartY-1, 319-(StartX+LongX-1));
  oLCD_WriteStart();
	
  oLCD_WriteData(*ppic); //д��һ������ʱ����ָ���������ڣ���������дһ������
  for (i=0;i<( LongY * LongX ) ;i++ )
  {
      oLCD_WriteData(*ppic++);
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

void oLCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX )
{
	uint16_t x ,y ;

	oLCD_WriteReg(0x0050,StartY  );//
    oLCD_WriteReg(0x0051,StartY+LongY-1 );//
    oLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
    oLCD_WriteReg(0x0053,319-StartX);//

	oLCD_SetCursor(StartY-1, 319-(StartX+LongX-1));
	oLCD_WriteStart();

	oLCD_WriteData(oLCD_display_BUF[0][0]);//��һ������Ϊ��Чֵ������ָ����������
	for(y=StartY; y<(StartY+LongY); y++)
	{
		for(x=StartX; x<(StartX+LongX); x++)
		{
			oLCD_WriteData(oLCD_display_BUF[y][x]);
		}
	}
}
/****************************************
��8λ�ĻҶ���ɫֵת����16λ����ɫֵ��
*****************************************/
uint16_t Color8_To_B16_565(uint8_t color)
{
     uint16_t t_color=0;
     uint16_t r=0;
     uint16_t g=0;
     uint16_t b=0;
     
     r=b=color>>3;
     g=color>>2;
     
     t_color=((r<<11)|(g<<5)|b);
     return t_color;
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
void oLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ,uint16_t CharColor , uint16_t CharBackColor , uint8_t *ChineseCode )
{
	uint8_t  *pic ;
	uint8_t   ByteCounter , BitCounter ;
	pic = ChineseCode ;

	oLCD_WriteReg(0x0050,StartY  );//
	oLCD_WriteReg(0x0051,StartY+LongY-1 );//
	oLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
	oLCD_WriteReg(0x0053,319-StartX);//

	oLCD_SetCursor(StartY-1, 319-(StartX+LongX-1));
    oLCD_WriteStart();
	oLCD_WriteData(*pic); //д��һ������ʱ����ָ���������ڣ���������дһ������
	for ( ByteCounter = 0 ; ByteCounter < ( LongY*LongX/8 ) ; ByteCounter++ )
	{
		for ( BitCounter = 0 ; BitCounter < 8 ; BitCounter++ )
		{
			if ( ( *pic & ( 0x80 >> BitCounter ) ) == 0x00 )
				oLCD_WriteData( CharBackColor ) ;
			else
				oLCD_WriteData( CharColor ) ;
		}
		pic++ ;
	}
}

void oLCD_Draw_Picture8(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX, uint16_t *pic)
{
  uint32_t  i;
  uint8_t  *ppic ;
  uint16_t color;
  ppic = (uint8_t *)pic ;

  oLCD_WriteReg(0x0050,StartY  );//
  oLCD_WriteReg(0x0051,StartY+LongY-1 );//
  oLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
  oLCD_WriteReg(0x0053,319-StartX);//

  
  oLCD_SetCursor(StartY-1, 319-(StartX+LongX-1));
  oLCD_WriteStart();
	
  oLCD_WriteData(*ppic); //д��һ������ʱ����ָ���������ڣ���������дһ������
  for (i=0;i<( LongY * LongX ) ;i++ )
  {
	  color = Color8_To_B16_565(*ppic++);
      oLCD_WriteData(color);
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
//void oLCD_Test ( void )
//{
//	uint32_t i , j ;
//	flash_select_page(1) ; //flashѡҳ
//	j = 0 ;
//	for ( i=0; i<0x8000; i+=2 ){
//		pic[j] = flash_read_word( (FLASH_BASE_ADDR+i) ) ;
//		j++ ;
//	}
//	oLCD_Draw_Picture( 0,192,128,128,pic) ;
//	asm ( " NOP " ) ;
//	asm ( " NOP " ) ;
//	
//}








