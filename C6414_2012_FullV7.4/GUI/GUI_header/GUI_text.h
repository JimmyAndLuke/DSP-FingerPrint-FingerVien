/******************************************************************************
 * �ļ�����image.h
 * ���ܣ�  ʵ����ָ��ͼ��Ļ�������
******************************************************************************/

#if !defined __GUI_TEXT_H
#define __GUI_TEXT_H

/* �������Ͷ��� */
#include "../../bsp/bsp_header/z_mytype.h"


#include "GUI.h"

#ifdef __cplusplus
extern "C" {
#endif

//typedef struct area_t{
//	int32_t x0;   //���Ͻ�x����
//	int32_t y0;   //���Ͻ�y����
//	int32_t x1;   //���½�x����
//	int32_t y1;   //���½�y����
//}area_t;
//
//typedef area_t rect_t;
//
//typedef struct font_t{
//	uint16_t height;
//	uint16_t width;
//	uint32_t type;
//}font_t;
//
//
//typedef struct pen_t{
//	uint16_t width;    //���ʵ�ֱ�߿��
//	uint16_t forecolor;//ǰ��ɫ
//	uint16_t backcolor;//����ɫ
//	uint16_t style;    //���ʷ��
//}pen_t;


//���ֵ��������(GB2312����)
#define macro_font_cn_11x12_dot    0x00000001u
#define macro_font_cn_15x16_dot    0x00000002u
#define macro_font_cn_24x24_dot    0x00000004u
#define macro_font_cn_32x32_dot    0x00000008u
//������չ�ַ��ĵ�������(GB2312���� ��λ��Χ:0xA1A1~0xABC0)
#define macro_font_ecn_6x12_dot    0x00000010u
#define macro_font_ecn_8x16_dot    0x00000020u
#define macro_font_ecn_12x24_dot   0x00000040u
#define macro_font_ecn_16x32_dot   0x00000080u

//ascii��ı���(��λ��Χ:0x20~0x7f)

#define macro_font_ascii_6x12_dot  0x00000100u
#define macro_font_ascii_8x16_dot  0x00000200u
#define macro_font_ascii_12x24_dot 0x00000400u
#define macro_font_ascii_16x32_dot 0x00000800u
#define macro_font_ascii_5x7_dot   0x00001000u
#define macro_font_ascii_7x8_dot   0x00002000u


//ϵͳ�ṩ�Ľ������������������
#define macro_font_style_small   (macro_font_cn_11x12_dot|\
	                              macro_font_ecn_6x12_dot|\
								  macro_font_ascii_6x12_dot)

#define macro_font_style_middle  (macro_font_cn_15x16_dot|\
	                              macro_font_ecn_8x16_dot|\
								  macro_font_ascii_8x16_dot)

#define macro_font_style_big     (macro_font_cn_24x24_dot |\
	                              macro_font_ecn_12x24_dot|\
								  macro_font_ascii_12x24_dot)

#define macro_font_style_huge    (macro_font_cn_32x32_dot |\
	                              macro_font_ecn_16x32_dot|\
								  macro_font_ascii_16x32_dot)


//��ͨ�������������
#define macro_font_style_normal  macro_font_style_middle

//���ʷ��Ϊ͸��,����ǰ����Ϊ����ָ���Ļ��ʱ���û���ô�,��ǰ�������б��������ͼ
#define macro_pen_style_lucency  0x0001u

//���ʷ��Ϊ����,����ͼʱ�������Ƚ�������Ϊ����ɫ��Ȼ���ڱ���ɫ��ͼ
#define macro_pen_style_overlap  0x0002u

	//���ֵ��������(GB2312����)
//#define FONT_CN_11X12_DOT      0x00000001u
//#define FONT_CN_15X16_DOT      0x00000002u
//#define FONT_CN_24X24_DOT      0x00000004u
//#define FONT_CN_32X32_DOT      0x00000008u
//	//������չ�ַ��ĵ�������(GB2312���� ��λ��Χ:0xA1A1~0xABC0)
//#define FONT_ECN_6X12_DOT      0x00000010u
//#define FONT_ECN_8X16_DOT      0x00000020u
//#define FONT_ECN_12X24_DOT     0x00000040u
//#define FONT_ECN_16X32_DOT     0x00000080u
//
//	//ascii��ı���(��λ��Χ:0x20~0x7f)
//#define FONT_ASCII_6X12_DOT    0x00000100u
//#define FONT_ASCII_8X16_DOT    0x00000200u
//#define FONT_ASCII_12X24_DOT   0x00000400u
//#define FONT_ASCII_16X32_DOT   0x00000800u
//#define FONT_ASCII_5X7_DOT     0x00001000u
//#define FONT_ASCII_7X8_DOT     0x00002000u
//
//#define FONT_STYLE_SMALL       (FONT_CN_11X12_DOT|\
//	FONT_ECN_6X12_DOT|\
//	FONT_ASCII_6X12_DOT)
//
//#define FONT_STYLE_MIDDLE      (FONT_CN_15X16_DOT|\
//	FONT_ECN_8X16_DOT|\
//	FONT_ASCII_8X16_DOT)
//
//#define FONT_STYLE_BIG         (FONT_CN_24X24_DOT|\
//	FONT_ECN_12X24_DOT|\
//	FONT_ASCII_12X24_DOT)
//
//#define FONT_STYLE_HUGE        (FONT_CN_32X32_DOT|\
//	FONT_ECN_16X32_DOT|\
//	FONT_ASCII_16X32_DOT)
//
////��ͨ�������������
//#define FONT_STYLE_NORMAL       FONT_STYLE_MIDDLE

#define macro_get_cn_dot_type(font_type)       ((font_type)&0x0000000fu)
#define macro_get_ecn_dot_type(font_type)      ((font_type)&0x000000f0u)
#define macro_get_ascii_dot_type(font_type)    ((font_type)&0x00000f00u)


//��Щ�ж�������little-ending��������������ֻ����Ϊ�ж�����������Ϊ��ֵ;

#define macro_is_ecn_char(ch)    ((ch)>=0xAAA1&&(ch)<=0xABC0)
#define macro_is_cn_char(ch)     ((ch)>0xa1a0&&!macro_is_ecn_char(ch))
#define macro_is_ascii_char(ch)  ((ch)<0x7f)

//ȡ��һ���ֵĸ߰벿�ֻ��ߵͰ벿��
#define macro_low_word(ch)       ((ch)&0x00ff)
#define macro_high_word(ch)      ((ch)>>8)


//ˮƽ���뷽ʽ
#define macro_text_h_align_center   0x00000001u
#define macro_text_h_align_left     0x00000002u
#define macro_text_h_align_right    0x00000004u
//��ֱ���뷽ʽ
#define macro_text_v_align_center   0x00010000u
#define macro_text_v_align_top      0x00020000u
#define macro_text_v_align_bottom   0x00040000u
#define macro_get_text_v_align(v)   ((v)&0xffff0000u)
#define macro_get_text_h_align(h)   ((h)&0x0000ffffu)






//�ı��������
//void gui_putchar      (char ch ,int32_t x,int32_t y);
//void gui_put_char(uint16_t ch ,int x,int y);
//void gui_text_out     (char*str,int32_t x,int32_t y);
//void gui_text_out     (char*str,int32_t x,int32_t y);
//void gui_text_out_c   (char*str,int32_t x,int32_t y ,int32_t count);
//void gui_text_out_rect(char*str,rect_t *rect,uint32_t style);
//
////���豸��صĲ���������һ���ṩ���豸�޹صĲ���
////void     gui_set_font(font_t *font);
//void 	 gui_set_font(font_t *font);
//void     gui_get_font(font_t *font);
//void     gui_set_pen (pen_t *pen);
//void     gui_get_pen (pen_t *pen);





#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */

