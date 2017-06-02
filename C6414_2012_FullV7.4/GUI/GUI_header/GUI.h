/******************************************************************************
 * �ļ�����image.h
 * ���ܣ�  ʵ����ָ��ͼ��Ļ�������
******************************************************************************/

#if !defined __GUI_H
#define __GUI_H


/* �������Ͷ��� */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../header.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_RES_FILE_COUNT		10


extern uint32_t gResFileTab[MAX_RES_FILE_COUNT];
extern uint8_t key_on;

typedef struct area_t{
	int32_t x0;   //���Ͻ�x����
	int32_t y0;   //���Ͻ�y����
	int32_t x1;   //���½�x����
	int32_t y1;   //���½�y����
}area_t;

typedef area_t rect_t;

typedef struct font_t{
	uint16_t height;
	uint16_t width;
	uint32_t type;
}font_t;


typedef struct pen_t{
	uint16_t width;    //���ʵ�ֱ�߿��
	uint16_t forecolor;//ǰ��ɫ
	uint16_t backcolor;//����ɫ
	uint16_t style;    //���ʷ��
}pen_t;


#define load_char_dot_matrix(ch,count,buf)  Gt23l32s4w_Get_Font(ch, count, buf)

#define gui_draw_pixel(y, x, color)			oLCD_Fill_Pixel_Buf(y, x, color)


//#define load_bitmap_8bpp(StartY, StartX, LongY, LongX, pic)		oLCD_Draw_Picture8(StartY, StartX, LongY, LongX, pic)


//#define load_bitmap_16bpp(StartY, StartX, LongY, LongX, pic)	oLCD_Draw_Picture(StartY, StartX, LongY, LongX, pic)

void load_bitmap_8bpp(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic);

void load_bitmap_16bpp(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic);

void gui_fill_rect_buf(rect_t *rect, uint16_t color);



void gui_draw_h_line(int32_t x0,int32_t y0,int32_t x1,uint16_t color);
void gui_draw_v_line(int32_t x0,int32_t y0,int32_t y1,uint16_t color);

void gui_draw_rect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color);


void gui_put_char(uint16_t ch ,int x,int y);
void gui_text_out     (char*str,int32_t x,int32_t y);
void gui_text_out     (char*str,int32_t x,int32_t y);
void gui_text_out_c   (char*str,int32_t x,int32_t y ,int32_t count);
void gui_text_out_rect(char*str,rect_t *rect,uint32_t style);

//���豸��صĲ���������һ���ṩ���豸�޹صĲ���
//void     gui_set_font(font_t *font);
void 	 gui_set_font(font_t *font);
void     gui_get_font(font_t *font);
void     gui_set_pen (pen_t *pen);
void     gui_get_pen (pen_t *pen);



void GuiInit(void);

void ShowTime(void) ;


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */

