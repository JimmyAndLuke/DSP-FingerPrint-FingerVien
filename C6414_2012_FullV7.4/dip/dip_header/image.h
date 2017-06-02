/******************************************************************************
 * �ļ�����image.h
 * ���ܣ�  ʵ����ָ��ͼ��Ļ�������
******************************************************************************/

#if !defined __IMAGE_H
#define __IMAGE_H

/* �������Ͷ��� */
#include "../../bsp/bsp_header/z_mytype.h"

#ifdef __cplusplus
extern "C" {
#endif

/* �������Щ�ӿ�ʵ����˽�еģ�����Ϊ�û���֪��ʹ�������ṩ�ĺ�������ͼ�� */
typedef Handle_t ImageHandle_t;


/* ����ͼ������ */
typedef enum
{
    ImageGray      = 0,	/* 8-bit�Ҷ�ͼ�� */
	ImageColor	   = 1, /* 32-bit�Ҷ�ͼ��*/
    ImageBinarized = 2,	/* ��ֵ��ͼ��    */
    ImageThinned   = 3	/* ϸ��ͼ��      */
} ImageFlag_t;

/* ָ��ͼ��ṹ��256���Ҷ�ͼ */
typedef struct Image_t
{
    uint8_t       *pimg;         /*  8-bitͼ������һάָ��*/  
	uint8_t		  **ppimg;		 /*	 8-bitͼ�������άָ��*/  
    int32_t       width;         /*  ���            */
    int32_t       height;        /*  �߶�            */
	int32_t       pitch;         /*  �ھ�:ÿ���ֽ��� */
	int32_t		  size;			 /*  ͼ���С(h*pitch)*/	
    ImageFlag_t  flags;          /*  ���            */
} Image_t;


//����ͼ��:��ͼ��ṹ���ʼ��
void ImageCreate
(
 Image_t *image, 
 void *data, 
 int32_t width, 
 int32_t height, 
 int32_t pitch, 
 ImageFlag_t flags
 );


//ͼ������ֵΪvalue
void ImageFlood(Image_t *image, const uint8_t value);


//����ͼ����
void ImageSetFlags(Image_t *image, ImageFlag_t flags);


//ͼ�񿽱�
void ImageCopy(Image_t *dst_image, Image_t *src_image);
void ImageCopy32(Image_t *dst_image, Image_t *src_image);

void BufferCopy32(uint32_t *pDst, uint32_t *pSrc, unsigned int size);
void BufferCopyV1(uint8_t *pDst, uint8_t *pSrc, unsigned int size) ;









#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */

