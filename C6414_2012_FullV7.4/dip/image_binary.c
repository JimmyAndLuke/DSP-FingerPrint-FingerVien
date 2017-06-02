/******************************************************************************
 * �ļ�����image_binary.c
 * ��  �ܣ�һЩͼ���ֵ(0,1��0,255)������
******************************************************************************/
#include "dip_header/image_binary.h"


//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <string.h>


/******************************************************************************
  * ���ܣ�ͼ��̶���ֵ��ֵ��
  * ������image       ָ��ͼ��
  *       thr_value   ��ֵ
  * ���أ�������
******************************************************************************/
FunError_t ImageBinarize(Image_t image, const uint8_t thr_value)
{
    int32_t n;
    uint8_t *pimg = ImageGetBuffer(image);
    int32_t size = ImageGetSize(image);
    if (pimg==NULL)
        return FunMemory;
    /* ѭ������ */
    for (n = 0; n < size; n++, pimg++)
    {
        /* ��ֵ�� */
        *pimg = (*pimg < thr_value)?(uint8_t)0xFF:(uint8_t)0x00;
    }
    return ImageSetFlag(image, ImageBinarized);
}

/******************************************************************************
  * ���ܣ�ͼ��̶���ֵ��ֵ��(0,1)
  * ������image       ָ��ͼ��
  *       thr_value   ��ֵ
  * ���أ�������
******************************************************************************/
FunError_t ImageBinarizeOZ(Image_t image, const uint8_t thr_value)
{
    int32_t n;
    uint8_t *pimg = ImageGetBuffer(image);
    int32_t size = ImageGetSize(image);
    if (pimg==NULL)
        return FunMemory;
    /* ѭ������ */
    for (n = 0; n < size; n++, pimg++)
    {
        /* ��ֵ�� */
        *pimg = (*pimg < thr_value)?(uint8_t)1:(uint8_t)0;
    }
    return ImageSetFlag(image, ImageBinarized);
}

/******************************************************************************
  * ���ܣ�ͼ��̶���ֵ����(�����˹̶���ֵ��ֵ�������������Ĺ���)
  * ������image         ָ��ͼ��
  *       thr_value     ��ֵ
  *       max_value	    ��ĳЩ��ֵ���Ͳ���ʱ,ȡ�õ����ֵ
  *       thr_type		��ֵ��������
  * ���أ�������
******************************************************************************/
FunError_t ImageThreshold(Image_t image, const uint8_t thr_value, const uint8_t max_value, const int32_t thr_type)
{
    int32_t n;
    uint8_t *pimg = ImageGetBuffer(image);
    int32_t size = ImageGetSize(image);
    if (pimg==NULL)
        return FunMemory;
    /* ѭ������ */
    for (n = 0; n < size; n++, pimg++)
    {
        /* ��ֵ�� */
		switch (thr_type) {
		case THR_WB:	//>thr_value: max_value, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)max_value):((uint8_t)0x00);
			break;
		case THR_WBI:	//>thr_value: 0, else: max_value
			*pimg = (*pimg > thr_value)?((uint8_t)0x00):((uint8_t)max_value);
			break;
		case THR_OZ:	//>thr_value: 1, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)1):((uint8_t)0);
			break;
		case THR_OZI:	//>thr_value: 0, else: 1
			*pimg = (*pimg > thr_value)?((uint8_t)0):((uint8_t)1);
			break;
		case THR_TRUNC:		//>thr_value: thr_value, else: *pimg
			*pimg = (*pimg > thr_value)?((uint8_t)thr_value):((uint8_t)(*pimg));
			break;
		case THR_ZERO:		//>thr_value: *pimg, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)(*pimg)):((uint8_t)0x00);
			break;
		case THR_ZEROI:		//>thr_value: *pimg, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)0x00):((uint8_t)(*pimg));
			break;
		default :			//>thr_value: max_value, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)max_value):((uint8_t)0x00);
			break;
		}
    }
    return ImageSetFlag(image, ImageBinarized);
}

/******************************************************************************
  * ���ܣ�ͼ���ֵ��,ʹ��ͼ��������ֵ��Ϊ��ֵ
  * ������image     ָ��ͼ��
  *       x0		��ȡͼ�񲿷ֵĿ�ʼx����
  *       y0		��ȡͼ�񲿷ֵĿ�ʼy����
  *       dx		��ȡͼ�񲿷ֵĿ��
  *       dy		��ȡͼ�񲿷ֵĸ߶�
  *		  dir		��ֵ����ʽ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  * �㷨����:
  *		  �������ȡ������ͼ�������ƽ���Ҷ���Ϊ��ֵ	
******************************************************************************/
FunError_t ImageOverallBinary
(
 Image_t image, 
 const int32_t x0, 
 const int32_t y0, 
 const int32_t dx,
 const int32_t dy,
 const int32_t dir
 )
{
	uint8_t* p1  = ImageGetBuffer(image);
	uint8_t *pS;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
	uint32_t average;
	int32_t x, y;
	uint32_t total;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}
	//

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//��������
		fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}
	total = dx*dy;
	average = 0;
	for (y = y0; y < y0+dy; y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			average += *(pS + x);
		}
	}

	average /= total;
#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOverall: thr_value = %d\n", average);
#endif

	for (y = y0; y < y0+dy; y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			//if (dir == 0) 
			//	*(pS + x) = *(pS + x) > average ? 0 : 1;
			//else
			//*(pS + x) = *(pS + x) > average ? 1 : 0;
			*(pS + x) =*(pS + x) > average ? upper_thr : under_thr;
		}
	}

	return FunOK;
}


/******************************************************************************
  * ���ܣ�ͼ���ֵ�˲�������ͨ�������ֵʵ��
  * ������image     ָ��ͼ��
  *       size      �����ڴ�С(2*r+1)
  *		  dir		��ֵ����ʽ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       �߽�Ӱ��,�����������������ͼ��ʵ���ϱ��ü�ȥ��size�к�size��
******************************************************************************/
FunError_t ImageMeanBinary(Image_t image, const int32_t size, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c,c0;
	int32_t sx, sy;
    Image_t im2;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* ��С */
    a = size*size;	/* ��� */    
    if (a==0)
	return FunBadParameter;
	
    /* ����ͼ����м��� */
    ImageCopy(im2, image);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
	//for (y = s; y < h - s; y++)
 //   for (x = s; x < w - s; x++)
	for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
    {
		c = 0;
		sx = x - s;
		sy = y - s;
		if (y < s || y >= h-s ||\
			x < s || x >= w-s) {
			p1[pitch*y + x] = 0;
			continue;
		} 
		//�Ż�ǰ
		//for (q=-s;q<=s;q++)
		//for (p=-s;p<=s;p++)
		//{
  //  		 c += p2[(x+p)+(y+q)*pitch2];
		//}
		//�Ż���
		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
		}
		//�Ż�ǰ
		//c0 = p1[x+y*pitch];
		//c = c/a;
		//p1[x+y*pitch] = c0>c?0:1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//�Ż���
		c0 = p1[x+y*pitch]*a;
		//if (dir == 0)
		//	p1[x + y*pitch] = c0>c ? 0 : 1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//else 
		//	p1[x + y*pitch] = c0>c ? 1 : 0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		p1[x + y*pitch]= c0 > c ? upper_thr : under_thr;

		//if (OZ_WB == OZ) {
		//	p1[x+y*pitch] = c0>c?0:1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//} else if (OZ_WB == WB) {
		//	p1[x+y*pitch] = c0>c?0:255;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//}
    }
    
    ImageDestroy(im2);
    return FunOK;
}

/******************************************************************************
  * ���ܣ�ͼ���ֵ�˲�������ͨ�������ֵʵ��
  * ������image     ָ��ͼ��
  *       size      �����ڴ�С(2*r+1)
  *		  dir		��ֵ����ʽ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *		  ͼ���Ƚ���ֱ������,�ڽ���ģ�����
  *		  ��˿�,����ģ�������û�б仯
******************************************************************************/
FunError_t ImageMeanBinaryV1(Image_t image, const int32_t size, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c,c0;
	int32_t sx, sy;
    Image_t im2;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* ��С */
    a = size*size;	/* ��� */    
    if (a==0)
	return FunBadParameter;
	
    /* ����ͼ����м��� */
    //ImageCopy(im2, image);
	ImageExtendCopy(im2, image, size);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
    for (y = s; y < h+s; y++)
    for (x = s; x < w+s; x++)
    {
		c = 0;
		sx = x - s;
		sy = y - s;

		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
		}
		//c0 = p1[sx+sy*pitch]*a;
		c0 = p2[x+y*pitch2]*a;
		//if (dir == 0)
		//	p1[sx+sy*pitch] = c0>c?0:1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//else 
		//	p1[sx+sy*pitch] = c0>c?1:0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		p1[sx+sy*pitch] = c0>c?upper_thr:under_thr;

		//if (OZ_WB == OZ) {
		//	p1[sx+sy*pitch] = c0>c?0:1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//} else if (OZ_WB == WB) {
		//	p1[sx+sy*pitch] = c0>c?0:255;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//}
    }
    
    ImageDestroy(im2);
    return FunOK;
}


/******************************************************************************
  * ���ܣ�ͼ��ͳ���˲�������ͨ�������ֵʵ��
  * ������image     ͼ��
  *       size      �˲���ģ���С(2*r+1)
  *       thre_val  ��ֵ
  *		  dir		��ֵ����ʽ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       �߽�Ӱ��,�����������������ͼ��ʵ���ϱ��ü�ȥ��size�к�size��
******************************************************************************/
FunError_t ImageStatisticsFilter(Image_t image, const int32_t size, const int32_t thre_val, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c;
    Image_t im2;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* ��С */
    a = size*size;	/* ��� */    
    if (a==0)
	return FunBadParameter;
	
    /* ����ͼ����м��� */
    ImageCopy(im2, image);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
    for (y = s; y < h-s; y++)
    for (x = s; x < w-s; x++)
    {
		c = 0;

		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
		}

		//if (dir == 0)
		//	p1[x+y*pitch] = c>=thre_val?0:1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//else 
		//	p1[x+y*pitch] = c>=thre_val?1:0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		p1[x+y*pitch] = c>= thre_val?upper_thr:under_thr;

		//if (OZ_WB == OZ)
		//	p1[x+y*pitch] = c>=thre_val?1:0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//else if (OZ_WB == WB)
		//	p1[x+y*pitch] = c>=thre_val?255:0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
    }
    
    ImageDestroy(im2);
    return FunOK;
}


/******************************************************************************
  * ���ܣ�ͼ��Niblack����,�ֲ���̬��ֵ�㷨
  * ������image     ͼ��
  *       size      ģ�洰�ڴ�С(2*r+1)
  *		  ratio		Niblack����ϵ��
  *		  dir		��ֵ����ʽ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       �߽�Ӱ��,�����������������ͼ��ʵ���ϱ��ü�ȥ��size�к�size��
  * �㷨����: 
  *       һ�ּ���Ч�ľֲ���̬��ֵ�㷨,��ͼ���е�ÿһ��,��rxr������,
  *		  �������������ص�ľ�ֵ�ͷ���,Ȼ����T(x,y) = m(x,y) + k x s(x,y)
  *		  ��Ϊ��ֵ,���ж�ֵ��.
  *		  T(x,y)Ϊ�õ���ֵ,m(x,y)Ϊ�õ�rxr���������صľ�ֵ,s(x,y)Ϊ��׼����
  *		  kΪ����ϵ��
******************************************************************************/
FunError_t ImageNiBlack(Image_t image, const int32_t size, const double ratio, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c,c1;
    Image_t im2;
	double average = 0.0;
	double variance = 0.0;
	uint8_t  temp0 = 0;
	uint8_t  temp1 = 0;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* ��С */
    a = size*size;	/* ��� */    
    if (a==0)
	return FunBadParameter;
	
    /* ����ͼ����м��� */
    ImageCopy(im2, image);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
    for (y = s; y < h-s; y++)
    for (x = s; x < w-s; x++)
    {
		c = 0;
		c1 = 0;
		average = 0.0;
		variance = 0.0;
		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
			c1 += p2[p+q*pitch2] * p2[p+q*pitch2];

		}

		average = (double)c / (double)a;
		variance = sqrt((double)c1 / (double)a);
		//
		//for (q = y-s; q <= y+s; q++)
		//for (p = x-s; p <= x+s; p++)
		//{
		//	variance += (p2[p+q*pitch2] - average)*(p2[p+q*pitch2] - average);
		//}

		//variance = sqrt(variance / a);
		temp1 = (uint8_t)(average + ratio * variance);		
		//p1[x+y*pitch] = temp1;
		temp0 = p1[x+y*pitch];
		//if (dir == 0)
		//	p1[x+y*pitch] = temp0 > temp1 ? 0 : 1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//else 
		//	p1[x+y*pitch] = temp0 > temp1 ? 1 : 0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		p1[x+y*pitch] = temp0 > temp1 ? upper_thr : under_thr;
    }

    ImageDestroy(im2);
    return FunOK;
}


/******************************************************************************
  * ���ܣ�ͼ��Otsu�㷨(���ɷ��������䷽�),������ֵ��ԭͼ��ֳ�ǰ������������ͼ��
  * ������image     ͼ��
  *       x0		��ȡͼ�񲿷ֵĿ�ʼx����
  *       y0		��ȡͼ�񲿷ֵĿ�ʼy����
  *       dx		��ȡͼ�񲿷ֵĿ��
  *       dy		��ȡͼ�񲿷ֵĸ߶�
  *		  dir		��ֵ����ʽ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  * �㷨����: 
  *       һ�ּ���Ч�ľֲ���̬��ֵ�㷨,��ͼ���е�ÿһ��,��rxr������,
  *       ��tΪǰ���뱳���ķָ���ֵ��ǰ������ռͼ�����Ϊw0��ƽ���Ҷ�Ϊu0��
  *       �������� ռͼ�����Ϊw1��ƽ���Ҷ�Ϊu1��
  *       ��ͼ�����ƽ���Ҷ�Ϊ��u=w0*u0+w1*u1
  *       ǰ���ͱ���ͼ��ķ��
  *       g=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u)=w0*w1*(u0-u1)*(u0-u1),�˹�ʽΪ���ʽ
  *       �ɲ��ո����ۿα������g�Ĺ�ʽҲ������������е�sb�ı��ʽ��������g���ʱ��
  *       ������Ϊ��ʱǰ���ͱ���������󣬴�ʱ�ĻҶ�t�������ֵ   
  *       sb = w1*w2*(u1-u0)*(u0-u1)
******************************************************************************/
FunError_t ImageOtsu
	(
	 Image_t image, 
	 const int32_t x0, 
	 const int32_t y0, 
	 const int32_t dx, 
	 const int32_t dy,
	 const int32_t dir
	 )
{
	uint8_t* p1  = ImageGetBuffer(image);
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
	int32_t hist[256];	// ͼ��ֱ��ͼ��256����
	int32_t i, x, y;
	//int32_t total;                     //totalΪ�ܺͣ��ۼ�ֵ
	uint8_t gray;
	uint8_t *pS;
	int32_t n, n1, n2, gmin, gmax;
	int32_t thr_value = 1; // ��ֵ
	double m1, m2, sum, csum, fmax, sb;	//sbΪ��䷽�fmax�洢��󷽲�ֵ
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

	gmin=255; 
	gmax=0;

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//��������
		fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}

	//��ֱ��ͼ��0
	for (i = 0; i < 256; i++)
		hist[i] = 0;
	//����ֱ��ͼ
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			hist[gray]++;
		}
	}

	//for (i = 0; i < 256; i++)
	//	printf("%d ", hist[i]);
	//printf("\n");
	//ֱ��ͼƽ����
	//for (i = 0; i < 256; i++)
	//{
	//	total = 0;
	//	for (j = -2; j <= 2; j++)     //�븽��2���Ҷ���ƽ������tֵӦȡ��С��ֵ
	//	{
	//		gray = i + j;
	//		if (gray < 0)                              //Խ�紦��
	//			gray = 0;
	//		if (gray > 255)
	//			gray = 255;
	//		total += hist[gray];    //totalΪ�ܺͣ��ۼ�ֵ
	//	}
	//	//ƽ����,���2��+�м�1��+�ұ�2���Ҷ�,��5��,�����ܺͳ���5,�����0.5��������ֵ
	//	hist[i] = (int32_t)((float)total / 5.0 + 0.5);
	//}

	//����ֵ
	sum = csum = 0.0;
	n = 0;
	//�����ܵ�ͼ��ĵ����������أ�Ϊ����ļ�����׼��
	for (i = 0; i < 256; i++) {
		//x*f(x)�����أ�Ҳ����ÿ���Ҷȵ�ֵ�������������һ����Ϊ���ʣ���sumΪ���ܺ�
		sum += (double)(i*hist[i]);	
		//nΪͼ���ܵĵ�������һ��������ۻ�����
		n += hist[i];						
	}

	if (!n) {
		// if n has no value, there is problems
		fprintf (stderr, "there is no value.\n");
		return FunBadParameter;
	}

	fmax = -1.0;	 //��䷽��sb������Ϊ��������fmax��ʼֵ
	n1 = 0;
	for (i = 0; i < 256; i++) {	//��ÿ���Ҷȣ���0��255������һ�ηָ�����䷽��sb
		n1 += hist[i];		//n1Ϊ�ڵ�ǰ��ֵ��ǰ��ͼ��ĵ���

		if (!n1)			//û�зֳ�ǰ����
			continue; 
		n2 = n - n1;		//n2Ϊ����ͼ��ĵ���
		if (n2 == 0)		//n2Ϊ0��ʾȫ�����Ǻ�ͼ����n1=0������ƣ�
			break;			//֮��ı���������ʹǰ���������ӣ����Դ�ʱ�����˳�ѭ��

		csum += (double)(i * hist[i]);	//ǰ���ġ��Ҷȵ�ֵ*����������ܺ�
		m1 = csum / n1;					//m1Ϊǰ����ƽ���Ҷ�
		m2 = (sum - csum) / n2;			 //m2Ϊ������ƽ���Ҷ�
		//sbΪ��䷽��,���չ�ʽ,�����n1, n2Ӧ����n1/n��n2/n,�����Խ����Ӱ��
		sb = (double)n1 * (double) n2 * (m1 - m2) * (m1 - m2);
		if (sb > fmax) {	//����������䷽�����ǰһ���������䷽��
			fmax = sb;
			thr_value = i;	//ȡ�����䷽��ʱ��Ӧ�ĻҶȵ�i���������ֵ
		}
	}

#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOtst: thr_value = %d gmin=%d gmax=%d\n",thr_value, gmin, gmax);
#endif

	//��ֵ��
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			//if (dir == 0)
			//	*(pS + x) = (gray > thr_value) ? 0 : 1;
			//else 
			//	*(pS + x) = (gray > thr_value) ? 1 : 0;
			*(pS + x) = (gray > thr_value) ? upper_thr : under_thr;
		}
	}
	return FunOK;
}

//��������Otsu����,��һ�������ֵ,Ȼ�����ڴ���ֵ
//�����Ͻ����µ�һ��Otsu����
FunError_t ImageOtsuV1
	(
	 Image_t image, 
	 const int32_t x0, 
	 const int32_t y0, 
	 const int32_t dx, 
	 const int32_t dy,
	 const int32_t dir
	 )
{
	uint8_t* p1  = ImageGetBuffer(image);
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
	int32_t hist[256];	// ͼ��ֱ��ͼ��256����
	int32_t i, x, y;
	//int32_t total;                     //totalΪ�ܺͣ��ۼ�ֵ
	uint8_t gray;
	uint8_t *pS;
	int32_t n, n1, n2, gmin, gmax;
	int32_t thr_value = 1; // ��ֵ
	int32_t thr_value1 = 1;
	double m1, m2, sum, csum, fmax, sb;	//sbΪ��䷽�fmax�洢��󷽲�ֵ
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

	gmin=255; 
	gmax=0;

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//��������
		fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}

	//��ֱ��ͼ��0
	for (i = 0; i < 256; i++)
		hist[i] = 0;
	//����ֱ��ͼ
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			hist[gray]++;
		}
	}


	//����ֵ
	sum = csum = 0.0;
	n = 0;
	//�����ܵ�ͼ��ĵ����������أ�Ϊ����ļ�����׼��
	for (i = 0; i < 256; i++) {
		//x*f(x)�����أ�Ҳ����ÿ���Ҷȵ�ֵ�������������һ����Ϊ���ʣ���sumΪ���ܺ�
		sum += (double)(i*hist[i]);	
		//nΪͼ���ܵĵ�������һ��������ۻ�����
		n += hist[i];						
	}

	if (!n) {
		// if n has no value, there is problems
		fprintf (stderr, "there is no value.\n");
		return FunBadParameter;
	}

	fmax = -1.0;	 //��䷽��sb������Ϊ��������fmax��ʼֵ
	n1 = 0;
	for (i = 0; i <256; i++) {	//��ÿ���Ҷȣ���0��255������һ�ηָ�����䷽��sb
		n1 += hist[i];		//n1Ϊ�ڵ�ǰ��ֵ��ǰ��ͼ��ĵ���

		if (!n1)			//û�зֳ�ǰ����
			continue; 
		n2 = n - n1;		//n2Ϊ����ͼ��ĵ���
		if (n2 == 0)		//n2Ϊ0��ʾȫ�����Ǻ�ͼ����n1=0������ƣ�
			break;			//֮��ı���������ʹǰ���������ӣ����Դ�ʱ�����˳�ѭ��

		csum += (double)(i * hist[i]);	//ǰ���ġ��Ҷȵ�ֵ*����������ܺ�
		m1 = csum / n1;					//m1Ϊǰ����ƽ���Ҷ�
		m2 = (sum - csum) / n2;			 //m2Ϊ������ƽ���Ҷ�
		//sbΪ��䷽��,���չ�ʽ,�����n1, n2Ӧ����n1/n��n2/n,�����Խ����Ӱ��
		sb = (double)n1 * (double) n2 * (m1 - m2) * (m1 - m2);
		if (sb > fmax) {	//����������䷽�����ǰһ���������䷽��
			fmax = sb;
			thr_value = i;	//ȡ�����䷽��ʱ��Ӧ�ĻҶȵ�i���������ֵ
		}
	}

#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOtst: thr_value = %d gmin=%d gmax=%d\n",thr_value, gmin, gmax);
#endif

	//���µõ��ĻҶȷ�Χ�ٴν���otsu����
	sum = csum = 0.0;
	n = 0;
	//�����ܵ�ͼ��ĵ����������أ�Ϊ����ļ�����׼��
	for (i = thr_value; i < 256; i++) {
		//x*f(x)�����أ�Ҳ����ÿ���Ҷȵ�ֵ�������������һ����Ϊ���ʣ���sumΪ���ܺ�
		sum += (double)(i*hist[i]);	
		//nΪͼ���ܵĵ�������һ��������ۻ�����
		n += hist[i];						
	}

	if (!n) {
		// if n has no value, there is problems
		fprintf (stderr, "there is no value.\n");
		return FunBadParameter;
	}

	fmax = -1.0;	 //��䷽��sb������Ϊ��������fmax��ʼֵ
	n1 = 0;

	for (i = thr_value; i < 256; i++) {	//��ÿ���Ҷȣ���0��255������һ�ηָ�����䷽��sb
		n1 += hist[i];		//n1Ϊ�ڵ�ǰ��ֵ��ǰ��ͼ��ĵ���

		if (!n1)			//û�зֳ�ǰ����
			continue; 
		n2 = n - n1;		//n2Ϊ����ͼ��ĵ���
		if (n2 == 0)		//n2Ϊ0��ʾȫ�����Ǻ�ͼ����n1=0������ƣ�
			break;			//֮��ı���������ʹǰ���������ӣ����Դ�ʱ�����˳�ѭ��

		csum += (double)(i * hist[i]);	//ǰ���ġ��Ҷȵ�ֵ*����������ܺ�
		m1 = csum / n1;					//m1Ϊǰ����ƽ���Ҷ�
		m2 = (sum - csum) / n2;			 //m2Ϊ������ƽ���Ҷ�
		//sbΪ��䷽��,���չ�ʽ,�����n1, n2Ӧ����n1/n��n2/n,�����Խ����Ӱ��
		sb = (double)n1 * (double) n2 * (m1 - m2) * (m1 - m2);
		if (sb > fmax) {	//����������䷽�����ǰһ���������䷽��
			fmax = sb;
			thr_value1 = i;	//ȡ�����䷽��ʱ��Ӧ�ĻҶȵ�i���������ֵ
		}
	}

#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOtst: thr_value1 = %d gmin=%d gmax=%d\n",thr_value1, gmin, gmax);
#endif

	//��ֵ��
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			//*(pS + x) = (gray > thr_value1) ? 0 : 1;
			*(pS + x) = (gray > thr_value1) ? upper_thr : under_thr;
		}
	}
	return FunOK;
}





/******************************************************************************
*******************************************************************************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
*******************************************************************************
******************************************************************************/


/******************************************************************************
  * ���ܣ�ͼ�����ݵĻ��ڷ�������ܶ�ֵ��
  * ������pSrc				����ǰ�󾰷ָ��ͼ�������ָ��	
  *		  pOrient			����ǰ�󾰷ָ�ķ�������ָ��
  *	      pGrads			����ǰ�󾰷ָ���ݶȷ�ֵ����ָ��
  *		  width				ͼ����
  *		  height			ͼ��߶�
  *		  pitch				ͼ��ÿ���ֽ���
  *		  dir				ͼ���ֵ������
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       ָ��ͼ���ֵ�������ַ���:�Ҷ���ֵ�ָ(���õ���ֵ�ָ�)������
  *		  ��ֵ�����������.
  *		  ���ܶ�ֵ�����������:
  *			ԭ��:λ�ڳ��е����ӱ�Ȼ�ܵ���������.ͬ��,ָ�����߳�(����)�е�
  *				 ָ��΢��Ҳ���Կ���������������,��ӵ�г�������.��ô,��ĳһ
  *				 ������,��ĳһ��ָ��΢�������߷�����,��Ȼ��ͬ��ָ��΢��.��
  *				 ��ĳһ�����ڼ���ĳ������߷����ϵĵ㻹�����ڼ�,��Ҳͬ��.
  *			����:1.���������ϵĺڵ�,�����߷���ĸ�������Ӧ�ö��Ǻڵ�,��Ҷ�
  *				   ֵ�ĺͽ�С;���ߴ�ֱ�����ϸ����Ķ��ǰ׵�,��Ҷ�ֵ�ϴ�.
  *				 2.����������֮��İ׵�,�����߷���ĸ�������Ӧ�ö��ǰ׵�,��Ҷ�
  *				   ֵ�ĺͽϴ�;���ߴ�ֱ�����ϸ����Ķ��Ǻڵ�,��Ҷ�ֵ��С.
  *				   �ɴ˿ɵ�:����һ����,�������ҶȺ�С�ڷ���ҶȺ�,�ж�Ϊ�ڵ���
  *				   ����.��֮,��Ϊ�׵��ڹ���.
  *		    ʵ��:1.��f(x0,y0)Ϊ�õ�ĻҶ�ֵ,�䷽��ΪO(x0,y0),wΪ����Χ
  *				   HΪ��������ֵ֮��:H = sum(f(x,x/cos(O(x0,y0))))  (x=-w/2...w/2)
  *				   VΪ��������ֵ֮��:V = sum(f(x,x/sin(O(x0,y0))))  (x=-w/2...w/2)
  *				 2.���V>H,�õ��ڼ���,��֮,�ڹ���
  *				 3.ʵ��������,���ǵ��������,������ҶȺ�ʱ,��ÿһ�㶼������Ȩֵ
  *				   ���ü�Ȩƽ���ķ������������
  *				   �����߷����ߵ��ȨֵΪ:			Hw=1/7(2,2,3,4,3,2,2)
  *				   �����߷���ֱ�����ߵ��ȨֵΪ:	Vw=1/7(1,1,1,1,1,1,1)
  * �㷨: 
  *		  1.��÷�������.�����Ĳ���pOrient��Ϊ��������,���Ҫȷ���ȼ���
  *		    �õ�pOrient(����GetOrientation���)
  *		  2.��pOrient���ݵõ�ÿ������߽Ƕ�,������AngleToDirection�����������
  *		    ����
  *		  3.�����߷����g_direction_xy�����������������,��ö�Ӧ�����ϵ������
  *		  4.�ֱ����ü�Ȩ�˲���Hw��Vw������ˮƽ����,��ֱ������м�Ȩ�˲�
  *		  5.�������ߺʹ�ֱ�����ߵȵ��ļ�Ȩ�˲�ֵ,�ж�ͼ����������ɫ.
  *	�ܽ�: 
  *       �����㷨(ģ���С�̶�7x7):
  *			  (1)Ϊ�˼ӿ��ٶ�,��Gabor�����Ƴ�ģ��,��ģ�������Gabor����,��:
  *		         �����OrientBinary����.
  *			  (2)����Ϊ��ά����ģ������Ҳ�ܺ�ʱ,�ʽ�����ģ���Ϊ�����ཻ��
  *			     �߶���ģ��,������ģ������,��������С�ܶ�.
  *			  (3)�����õ��������˲�ģ����:		Hw=1/7(2,2,3,4,3,2,2)
  *							 �����˲�ģ����:		Vw=1/7(1,1,1,1,1,1,1)
  *	P.S.: ����OrientEnhance��ʵ����֮����
******************************************************************************/
void OrientBinary
(
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 uint8_t *pGrads,
 int32_t width, 
 int32_t height, 
 int32_t pitch, 
 int32_t dir
)
{
	int32_t x, y;
	int32_t i;
	int32_t d = 0;
	int32_t sum = 0;
	int32_t hsum = 0;	// ���߷����ϵ�7����ļ�Ȩ��
	int32_t vsum = 0;	// ���߷���Ĵ�ֱ�����ϵ�7����ļ�Ȩ��	
	// ���߷����ϵ�7�����Ȩֵ
	int32_t Hw[7] = {2, 2, 3, 4, 3, 2, 2};
	// ���߷���Ĵ�ֱ�����ϵ�7�����Ȩֵ
	int32_t Vw[7] = {1, 1, 1, 1, 1, 1, 1};

	int32_t Hv = 0;		// ���߷����ϵ�7����ļ�Ȩƽ��ֵ
	int32_t Vv = 0;		// ���߷���Ĵ�ֱ�����ϵ�7����ļ�Ȩƽ��ֵ
	int32_t tempY = 0;
	uint8_t *pS = NULL;		// ָ��ͼ�����ص�ָ��
	uint8_t *pT = NULL;		//pTempָ��
	uint8_t *pOri = NULL;	//���߷���ָ��
	uint8_t *pTemp = NULL;	//��ʱ���ݻ�����
	//uint32_t under_thr = 0;
	//uint32_t upper_thr = 1;

	// ĳ����Χ8����ĵ�ַƫ��
	int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t exit = 1;
	int32_t n = 0;
	int32_t num = 0;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}
	
	pTemp = (uint8_t *)malloc(sizeof(uint8_t)*width*height);

	if (pTemp == NULL)
		return;

	tempY = 0;
	for(y = 0; y < height; y++) {
		//�Ż�ǰ
		//tempY = y*pitch;	
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = pSrc + tempY + x;			
			//����õ�ǳ��ڣ�������ʱ���������øõ�Ϊ�ڵ㣬ֵΪ0
			if(*pS < 4) {
				*(pTemp + tempY + x) = 0;
				continue;
			}

			// �������߷���ķ�������������Ϊ12������
			d = AngleToDirection(*pOri);
			// ���㵱ǰ�������߷����ϵļ�Ȩƽ��ֵ
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++) {
				// �����Ƿ�Խ��
				if((y+g_direction_xy[d][i][1] < 0) || \
				   (y+g_direction_xy[d][i][1] >= height) || \
				   (x+g_direction_xy[d][i][0] < 0) || \
				   (x+g_direction_xy[d][i][0] >= width)) {	
					   continue;
				}
				sum += Hw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0) {
				Hv = sum/hsum;
			} else {
				Hv = 255;
			}

			// ���߷���Ĵ�ֱ���������
			d = (d+6)%12;
			// ���㵱ǰ�������߷���Ĵ�ֱ�����ϵļ�Ȩƽ��ֵ
			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++) {
				if((y+g_direction_xy[d][i][1] < 0) || \
				   (y+g_direction_xy[d][i][1] >= height) || \
				   (x+g_direction_xy[d][i][0] < 0) || \
				   (x+g_direction_xy[d][i][0] >= width)) {
					   continue;
				}
				sum += Vw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum != 0) {
				Vv = sum/vsum;
			} else {
				Vv = 255;
			}

			//�Ƚ����߼��䴹ֱ����Ĵ�С
			if(Hv < Vv) {
				// ���߷����ϼ�Ȩƽ��ֵ��С���õ�ǰ��Ϊ�ڵ�
				//*(pTemp + tempY + x) = 0;
				*(pTemp + tempY + x) = under_thr;
			} else {
				// ���߷����ϼ�Ȩƽ��ֵ�ϴ����õ�ǰ��Ϊ�׵�
				//*(pTemp + tempY + x) = 255;
				*(pTemp + tempY + x) = upper_thr;
			}
		}
		//�Ż���
		tempY += pitch;
	}

	//����ʱ�����������ݿ�����ԭʼͼ�����ݻ�����,ע�͵���һ��,����pTemp
	//����Ϊ����Զ�ֵ��ָ��ͼ�����ȥ���Դ������
	//memcpy(pSrc, pTemp, sizeof(uint8_t)*width*height);

	//�Զ�ֵ��ָ��ͼ�����ȥ����
	n = 0;
	num = 0;
	exit = 1;
	// ѭ������ֱ��������ϻ��ߴ����������8
	while(exit && n < 8) {
		exit = 0;
		n++;
		//tempY = pitch;
		tempY = 0;
		//for(y = 1; y < height-1; y++) {
		for(y = 0; y < height; y++) {
			//�Ż�ǰ
			//tempY = y*pitch
			//for(x = 1; x < width-1; x++) {
			for(x = 0; x < width; x++) {
				//��ֹԽ��
				if ((x < 1) || (x >= width-1) || \
					(y < 1) || (y >= height-1)) {
					*(pSrc + tempY + x) = upper_thr;	//�Ա�Ե�����޸�Ϊ��ֵ���ı�����
					continue;
				}
				// �����ĵ㲻����
				if(*(pGrads + tempY + x) == 0) {
					*(pSrc + tempY + x) = upper_thr;	//�Ա��������޸�Ϊ��ֵ���ı�����
					continue;
				}
				// ͳ�Ƶ�ǰ����Χ������ͬ���͵�ĸ���
				num = 0;
				//pS = pSrc + tempY + x;
				pT = pTemp + tempY + x;
				for(i = 0; i < 8; i++) {
					//if(*(pS+SiteD8[i]) == *pS) {
					if(*(pT+SiteD8[i]) == *pT) {
						num++;
					}
				}
				
				if(num < 2) {
					//��ͬ�����С�ڶ���ı䵱ǰ������(0-->0,255-->1)
					//*(pTemp+temp+x) = 255 - *pS;
					//*(pSrc + tempY + x) = 255 - *pT;
					if ((*(pTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = upper_thr;
					else
						*(pSrc + tempY + x) = under_thr;
					exit = 1;
				} else {	//���򲻸ı�(0-->0,255-->1)
					//*(pTemp+temp+x) = *pS;
					if ((*(pTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = under_thr;
					else
						*(pSrc + tempY + x) = upper_thr;
				}

			}
			//�Ż���
			tempY += pitch;
		}
	}

	if (pTemp != NULL) {
		free(pTemp);
		pTemp = NULL;
	}

}


/******************************************************************************
  * ���ܣ������ݶȶ�ָ��ͼ�����ǰ���뱳���ķָ�
  * ������image			����ǰ�󾰷ָ��ָ��ͼ��[Out]
  *       image_ori		����ǰ�󾰷ָ�ķ���[In]
  *		  image_grads	����ǰ�󾰷ָ���ݶ�(�����ж����ص���ǰ�����Ǳ���)[In]
  *       dir			��ֵ������
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       ָ��ͼ���ֵ�������ַ���:�Ҷ���ֵ�ָ(���õ���ֵ�ָ�)������
  *		  ��ֵ�����������.
  *		  ���ܶ�ֵ�����������:
  *			ԭ��:λ�ڳ��е����ӱ�Ȼ�ܵ���������.ͬ��,ָ�����߳�(����)�е�
  *				 ָ��΢��Ҳ���Կ���������������,��ӵ�г�������.��ô,��ĳһ
  *				 ������,��ĳһ��ָ��΢�������߷�����,��Ȼ��ͬ��ָ��΢��.��
  *				 ��ĳһ�����ڼ���ĳ������߷����ϵĵ㻹�����ڼ�,��Ҳͬ��.
  *			����:1.���������ϵĺڵ�,�����߷���ĸ�������Ӧ�ö��Ǻڵ�,��Ҷ�
  *				   ֵ�ĺͽ�С;���ߴ�ֱ�����ϸ����Ķ��ǰ׵�,��Ҷ�ֵ�ϴ�.
  *				 2.����������֮��İ׵�,�����߷���ĸ�������Ӧ�ö��ǰ׵�,��Ҷ�
  *				   ֵ�ĺͽϴ�;���ߴ�ֱ�����ϸ����Ķ��Ǻڵ�,��Ҷ�ֵ��С.
  *				   �ɴ˿ɵ�:����һ����,�������ҶȺ�С�ڷ���ҶȺ�,�ж�Ϊ�ڵ���
  *				   ����.��֮,��Ϊ�׵��ڹ���.
  *		    ʵ��:1.��f(x0,y0)Ϊ�õ�ĻҶ�ֵ,�䷽��ΪO(x0,y0),wΪ����Χ
  *				   HΪ��������ֵ֮��:H = sum(f(x,x/cos(O(x0,y0))))  (x=-w/2...w/2)
  *				   VΪ��������ֵ֮��:V = sum(f(x,x/sin(O(x0,y0))))  (x=-w/2...w/2)
  *				 2.���V>H,�õ��ڼ���,��֮,�ڹ���
  *				 3.ʵ��������,���ǵ��������,������ҶȺ�ʱ,��ÿһ�㶼������Ȩֵ
  *				   ���ü�Ȩƽ���ķ������������
  *				   �����߷����ߵ��ȨֵΪ:			Hw=1/7(2,2,3,4,3,2,2)
  *				   �����߷���ֱ�����ߵ��ȨֵΪ:	Vw=1/7(1,1,1,1,1,1,1)
******************************************************************************/
FunError_t ImageOrientBinary
(
 Image_t image,
 Image_t image_ori,
 Image_t image_grads,
 const int32_t dir
)
{
	//��ȡָ������,��������,�ݶ�����ָ��
	uint8_t *pSrc  = ImageGetBuffer(image);
	uint8_t *pOri = ImageGetBuffer(image_ori);
	uint8_t *pGrads = ImageGetBuffer(image_grads);
    int32_t   width   = ImageGetWidth (image);
    int32_t   height   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);

	if (pSrc == NULL || pOri == NULL || pGrads == NULL)
		return FunMemory;

	OrientBinary(pSrc, pOri, pGrads, width, height, pitch, dir);

	return FunOK;
}








/******************************************************************************
  * ���ܣ�ͼ���ֵ����(OZ��ֵ��ڰ׶�ֵ����)
  * ������pSrc        ͼ�����Ϊ��ֵ�����ͼ������
  * ������dir         ��1:OZ-->WB, 0:WB-->OZ
  * ���أ�������
******************************************************************************/
FunError_t BinaryExchange(uint8_t *pSrc, const int32_t w, int32_t h, const int32_t dir)
{
	//uint8_t* p1  = ImageGetBuffer(image);
 //   int32_t   w   = ImageGetWidth (image);
 //   int32_t   h   = ImageGetHeight(image);
 //   int32_t pitch = ImageGetPitch (image);
	int32_t i;
	int32_t size = w * h;
	uint8_t temp;

	for (i = 0; i < size; i++) {
		temp = *pSrc;
		if (dir) {	//�� OZ->WB(TOWB)
			*pSrc = (temp == 0) ? 0 : 255;
		} else {	//�� WB->OZ(TOOZ)
			*pSrc = (temp == 0) ? 0 : 1;
		}
		pSrc++;
	}
	return FunOK;
}


/******************************************************************************
  * ���ܣ�ͼ���ֵ����(OZ��ֵ��ڰ׶�ֵ����)
  * ������
  *       pSrc      ͼ�����Ϊ��ֵ�����ͼ������
  *       w			ͼ����
  *       h			ͼ��߶�
  *       pitch		ͼ��ÿ���ֽ���
  *       x0		��ȡͼ�񲿷ֵĿ�ʼx����
  *       y0		��ȡͼ�񲿷ֵĿ�ʼy����
  *       dx		��ȡͼ�񲿷ֵĿ��
  *       dy		��ȡͼ�񲿷ֵĸ߶�
  *       dir       ��1:OZ-->WB, 0:WB-->OZ
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  * �㷨����: 
******************************************************************************/
FunError_t BinaryExchangeV1
	(
	 uint8_t *pSrc, 
	 const int32_t w, 
	 const int32_t h, 
	 const int32_t pitch,
	 const int32_t x0, 
	 const int32_t y0, 
	 const int32_t dx, 
	 const int32_t dy, 
	 const int32_t dir
	 )
{
	int32_t i, j;
	uint8_t temp;
	uint8_t *pS;

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//��������
		//fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}

	for (j = y0; j < (y0+dy); j++) {
		pS = pSrc + j*pitch;
		for (i = x0; i < (x0+dx); i++) {
			temp = *(pS + i);
			if (dir) {	//�� OZ->WB(TOWB)
				*(pS+i) = (temp == 0) ? 0 : 255;
			} else {	//�� WB->OZ(TOOZ)
				*(pS+i) = (temp == 0) ? 0 : 1;
			}
		}
	}
	return FunOK;
}

