/******************************************************************************
 * �ļ�����image_base.c
 * ���ܣ�  һЩ������ͼ�����
******************************************************************************/


#include "dip_header/image_base.h"
#include "dip_header/image.h"


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <string.h>

//#pragma warning (disable:4996)



/******************************************************************************
  * ���ܣ�ͼ��Ҷȹ�һ
  * ������pDst			�����ͼ������
  *		  pSrc			����ǰͼ������
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  *		  pitch			ͼ������ÿ���ֽ���
  * ���أ�
  * �㷨: ImgNew(x,y)=[(ImgOld(x,y)-min_gray)*255]/(max_gray-min_gray);
******************************************************************************/
void GrayNormalize
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 )
{
	int32_t i, temp;
	int32_t min_gray, max_gray, max_min;
	uint8_t *p1 = pSrc;
	int32_t size = src_width * src_height;

	//�����,��С�Ҷ�
	max_gray = 0;
	min_gray = 255;
	for (i = 0; i < size; i++) {
		min_gray = (*p1) > min_gray ? min_gray : (*p1);
		max_gray = (*p1) < max_gray ? max_gray : (*p1);
		p1++;
	}

	//���,������max_gray;
	max_min = max_gray - min_gray;
	for (i = 0; i < size; i++) {
		//if ((*p) < (uint8_t)min_gray) {
		//		*p = 0;
		//	} else if ((*p) > (uint8_t)max_gray){
		//		*p = 255;
		//	} else {
				temp = pSrc[i];
				temp -= min_gray;
				temp = (temp * 255) / max_min;
				pDst[i] = (uint8_t)temp;
			//}
		//pSrc++;
	}
}


//void GrayNormalizeV1
//(
// uint8_t *pDst, 
// uint8_t *pSrc,
// uint8_t *pSeg,
// const int32_t src_width,
// const int32_t src_height,
// const int32_t src_pitch
// )
//{
//	int32_t i, temp;
//	int32_t min_gray, max_gray, max_min;
//	uint8_t *p1 = pSrc;
//	int32_t size = src_width * src_height;
//
//	//�����,��С�Ҷ�
//	max_gray = 0;
//	min_gray = 255;
//	for (i = 0; i < size; i++) {
//		if (*(pSeg+i) == 255) {
//			p1++;
//			continue;
//		}
//		min_gray = (*p1) > min_gray ? min_gray : (*p1);
//		max_gray = (*p1) < max_gray ? max_gray : (*p1);
//		p1++;
//	}
//
//	//���,������max_gray;
//	max_min = max_gray - min_gray;
//	for (i = 0; i < size; i++) {
//		//if ((*p) < (uint8_t)min_gray) {
//		//		*p = 0;
//		//	} else if ((*p) > (uint8_t)max_gray){
//		//		*p = 255;
//		//	} else {
//		if (*(pSeg+i) == 255) {
//			continue;
//		}
//				temp = pSrc[i];
//				temp -= min_gray;
//				temp = (temp * 255) / max_min;
//				pDst[i] = (uint8_t)temp;
//			//}
//		//pSrc++;
//	}
//}


/******************************************************************************
  * ���ܣ�ͼ����ݶȼ����ֵ����,����ݶȷ�ֵ����(��ͼ���ݶȻ�ȡ��������)
  * ������pDst				�������
  *		  pSrc				��������
  *       width				����ͼ����
  *		  height			����ͼ��߶�
  * ���أ�
******************************************************************************/
void HalfWidthHeight(uint8_t *pDst, uint8_t *pSrc, const int32_t width, const int32_t height)
{
	//int32_t	x, y;
	//uint8_t *pS;
	//uint8_t *pD;
	//int32_t	sum;
	////int32_t SiteD8[8] = {width-1, width, width+1, 1, -width+1, -width, -width-1, -1};
	//int32_t SiteD8[8];
	//SiteD8[0] = width-1;
	//SiteD8[1] = width;
	//SiteD8[2] = width+1;
	//SiteD8[3] = 1;
	//SiteD8[4] = -width+1;
	//SiteD8[5] = -width;
	//SiteD8[6] = -width-1;
	//SiteD8[7] = -1;
	////���ұ�Ե���� 
	//for(y = 0; y < height; y+=2) {
	//	pS = pSrc + y*width;
	//	pD = pDst + (y/2)*(width/2);
	//	*pD = *pS;
	//	pS = pSrc + y*width + width - 1;
	//	pD = pDst + (y/2)*(width/2) + (width/2 - 1);
	//	*pD = *pS;
	//}
	////���±�Ե����
	//for(x = 0; x < width; x+=2) {
	//	pS = pSrc + x;
	//	pD = pDst + x/2;
	//	*pD = *pS;
	//	pS = pSrc + (height-1)*width + x;
	//	pD = pDst + (height/2-1)*(width/2) + x/2;
	//	*pD = *pS;
	//}

	//// �Ǳ�Ե�����ø�˹ģ����ȡ��Ƶ��Ϣ
	//// 1 2 1
	//// 2 4 2
	//// 1 2 1
	//for(y = 2; y < height-2; y += 2) {
	//	for(x = 2; x < width-2; x += 2) {
	//		pS = pSrc + y*width + x;
	//		pD = pDst + (y/2)*(width/2) + x/2;
	//		sum = *pS*4 + *(pS + SiteD8[0]) +
	//			  *(pS + SiteD8[1])*2 + *(pS + SiteD8[2]) +
	//			  *(pS + SiteD8[3])*2 + *(pS + SiteD8[4]) +
	//			  *(pS + SiteD8[5])*2 + *(pS + SiteD8[6]) +
	//			  *(pS + SiteD8[7])*2;

	//		sum = sum>>4;
	//		*pD = (uint8_t)sum;
	//	}
	//}
	int32_t	x, y;
	uint8_t *pS;
	uint8_t *pD;
	int32_t	sum;
	int32_t tempY = 0, tempY2 = 0;
	//int32_t SiteD8[8] = {width-1, width, width+1, 1, -width+1, -width, -width-1, -1};
	int32_t SiteD8[8];
	SiteD8[0] = width-1;
	SiteD8[1] = width;
	SiteD8[2] = width+1;
	SiteD8[3] = 1;
	SiteD8[4] = -width+1;
	SiteD8[5] = -width;
	SiteD8[6] = -width-1;
	SiteD8[7] = -1;
	//���ұ�Ե���� 
	for(y = 0; y < height; y+=2) {
		pS = pSrc + y*width;
		//pD = pDst + (y/2)*(width/2);
		pD = pDst + (y>>1)*(width>>1);
		*pD = *pS;
		pS = pSrc + y*width + width - 1;
		//pD = pDst + (y/2)*(width/2) + (width/2 - 1);
		pD = pDst + (y>>1)*(width>>1) + ((width>>1) - 1);
		*pD = *pS;
	}
	//���±�Ե����
	for(x = 0; x < width; x+=2) {
		pS = pSrc + x;
		//pD = pDst + x/2;
		pD = pDst + (x>>1);
		*pD = *pS;
		pS = pSrc + (height-1)*width + x;
		//pD = pDst + (height/2-1)*(width/2) + x/2;
		pD = pDst + ((height>>1)-1)*(width>>1) + (x>>1);
		*pD = *pS;
	}

	// �Ǳ�Ե�����ø�˹ģ����ȡ��Ƶ��Ϣ
	// 1 2 1
	// 2 4 2
	// 1 2 1
	for(y = 2; y < height-2; y += 2) {
		tempY = y*width;
		tempY2 = (y>>1)*(width>>1);
		for(x = 2; x < width-2; x += 2) {
			pS = pSrc + tempY + x;
			//pD = pDst + (y/2)*(width/2) + x/2;
			pD = pDst +  tempY2 + (x>>1);
			sum = *pS*4 + *(pS + SiteD8[0]) +
				*(pS + SiteD8[1])*2 + *(pS + SiteD8[2]) +
				*(pS + SiteD8[3])*2 + *(pS + SiteD8[4]) +
				*(pS + SiteD8[5])*2 + *(pS + SiteD8[6]) +
				*(pS + SiteD8[7])*2;

			sum = sum>>4;
			*pD = (uint8_t)sum;
		}
	}
}

/******************************************************************************
  * ���ܣ�ͼ�����ݵ����ź���(˫���Բ�ֵ��)--ʹ�ø�������,�ײ㺯��,��ͼ�����ź�������
  * ������pDst				���ź�ͼ������
  *       dst_width			���ź�ͼ����
  *		  dst_height		���ź�ͼ��߶�
  *		  dst_pitch			���ź�ͼ��ÿ���ֽ���
  *		  pSrc				����ǰͼ������
  *       src_width			����ǰͼ����
  *		  src_height		����ǰͼ��߶�
  *		  src_pitch			����ǰͼ��ÿ���ֽ���
  *		  inter_type		��ֵ����
  *		  image_type		ͼ������(8λ�Ҷ�or32λ��ɫ)
  * ���أ�������
  * ˵��: �����˱߽�����
  * �㷨: ʹ������ٲ�ֵ,˫���Բ�ֵʵ��ͼ�������
******************************************************************************/
//void SizeNormalize
//( 
// uint8_t *pDst, 
// const int32_t dst_width, 
// const int32_t dst_height,
// const int32_t dst_pitch,
// uint8_t *pSrc, 
// const int32_t src_width,
// const int32_t src_height,
// const int32_t src_pitch,
// Interpolation_t inter_type,
// ImageFlag_t image_type
// )
//{
//	uint8_t *pS, *pD;		//ͼ������ָ��
//	//Ŀ��ͼ������(x, y)
//	int32_t x, y, k;
//	//Ŀ��ͼ�����ص�(x,y)���ӳ�������(tempx, tempy)
//	//(tempx, tempy)��С�������ٽ���4����ĺ�������
//	double tempx, tempy;
//	int32_t sx1, sx2, sy1, sy2;
//
//	//���ٽ�4����ĻҶ�ֵgray1,2,3,4
//	//gray5,6Ϊ��4����Ȩ�����õ��м�ֵ
//	int32_t gray1, gray2, gray3, gray4, gray5, gray6;
//
//	//4������ڼ���Ҷ�����ռ��Ȩ��
//	double dy,dx;
//	double bfx = (double)(src_width) / dst_width;
//	double bfy = (double)(src_height) / dst_height;
//
//	pS = pSrc;
//	pD = pDst;
//
//	//ͨ��˫���Բ�ֵ��ߴ��һ����Ŀ��ͼ��(x,y)�ĻҶ�ֵ
//	if (inter_type == InterLinear) {
//		for ( y = 0; y < dst_height; y++) {
//			tempy = y * bfy;		
//			sy1 = (int32_t)tempy;
//			sy2 = sy1 + 1;
//			dy = tempy - sy1;
//			for (x = 0; x < dst_width; x++) {
//
//				if (image_type == ImageGray) {
//					tempx = x * bfx;
//
//					sx1 = (int32_t)tempx;
//					sx2 = sx1 + 1;
//			
//					dx = tempx - sx1;
//
//				//ע��:���ӳ�����������(x,y)�п��ܳ�����Դͼ���
//				//��Χ(0��Width, 0��Height),���Դ��ڼ������	
//					if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
//						//1.������곬��ͼ������½�(��߾�������Χ)
//						gray6 = (*(pS + sy1*src_pitch + sx1));
//					} else if (sx1 >= src_width - 1) {
//						//2.���ͼ�������һ�����
//						gray1 = (*(pS + sy1*src_pitch + sx1));
//						gray3 = (*(pS + sy2*src_pitch + sx1));
//						gray6 = (int32_t)(gray1 * (1 - dy) + gray3 * dy);
//					} else if (sy1 >= src_height - 1) {
//						//3.���ͼ�������һ�����
//						gray1 = (*(pS + sy1*src_pitch + sx1));
//						gray2 = (*(pS + sy1*src_pitch + sx2));
//						gray6 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);	
//					} else {
//						gray1 = (*(pS + sy1*src_pitch + sx1));
//						gray2 = (*(pS + sy1*src_pitch + sx2));
//						gray3 = (*(pS + sy2*src_pitch + sx1));
//						gray4 = (*(pS + sy2*src_pitch + sx1));
//				
//						gray5 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);
//						gray6 = (int32_t)(gray3 * (1 - dx) + gray4 * dx);
//
//						gray6 = (int32_t)(gray5*(1 - dy) + gray6 * dy);
//					}
//					*(pD + y*dst_pitch + x) = (uint8_t)gray6;
//
//				} else if (image_type == ImageColor) {
//					tempx = x * bfx;
//					
//					sx1 = (int32_t)tempx;
//					sx2 = sx1 + 1;
//					
//					dx = tempx - sx1;
//
//					// ����32λ���ɫ��Ҫ�ֱ������ԭɫ
//					for (k = 0; k < 3; k++) {
//						//ע��:���ӳ�����������(x,y)�п��ܳ�����Դͼ���
//						//��Χ(0��Width, 0��Height),���Դ��ڼ������	
//						if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
//							//1.������곬��ͼ������½�(��߾�������Χ)
//							gray6 = (*(pS + sy1*src_pitch + sx1*4 + k));
//						} else if (sx1 >= src_width - 1) {
//							//2.���ͼ�������һ�����
//							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
//							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
//							gray6 = (int32_t)(gray1 * (1 - dy) + gray3 * dy);
//						} else if (sy1 >= src_height - 1) {
//							//3.���ͼ�������һ�����
//							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
//							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
//							gray6 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);	//����100��
//						} else {
//							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
//							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
//							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
//							gray4 = (*(pS + sy1*src_pitch + sx2*4 + k));
//					
//							gray5 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);//�ҶȷŴ�100��
//							gray6 = (int32_t)(gray3 * (1 - dx) + gray4 * dx);
//
//							gray6 = (int32_t)(gray5*(1 - dy) + gray6 * dy);
//						}
//						*(pD + y * dst_pitch + x*4 + k) = (uint8_t)gray6;
//					}
//				}
//			}
//		}
//	}
//}


/******************************************************************************
  * ���ܣ�ͼ�����ݵ����ź���(˫���Բ�ֵ��)--ʹ�ø�������,�ײ㺯��,��ͼ�����ź�������
  * ������pDst				���ź�ͼ������
  *       dst_width			���ź�ͼ����
  *		  dst_height		���ź�ͼ��߶�
  *		  dst_pitch			���ź�ͼ��ÿ���ֽ���
  *		  pSrc				����ǰͼ������
  *       src_width			����ǰͼ����
  *		  src_height		����ǰͼ��߶�
  *		  src_pitch			����ǰͼ��ÿ���ֽ���
  *		  inter_type		��ֵ����
  *		  image_type		ͼ������(8λ�Ҷ�or32λ��ɫ)
  * ���أ�������
  * ˵��: �����˱߽�����
  * �㷨: ʹ������ٲ�ֵ,˫���Բ�ֵʵ��ͼ�������
******************************************************************************/
#define SCALE 100	//ȥС����Ŵ�ȡ������:ȡֵ100,10000������Сû����,
						//����ͼ������Ŵ�Ļ���ʧ�������
void SizeNormalizeV1
( 
 uint8_t *pDst, 
 const int32_t dst_width, 
 const int32_t dst_height,
 const int32_t dst_pitch,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch,
 Interpolation_t inter_type,
 ImageFlag_t image_type
 )
{ 
	uint8_t *pS, *pD;		//ͼ������ָ��
	
	//Ŀ��ͼ������(x, y)
	int32_t x, y, k;
	//Ŀ��ͼ�����ص�(x,y)���ӳ�䲢����100��������(tempx, tempy)
	//(tempx, tempy)��С�������ٽ���4����ĺ�������
	int32_t tempx, tempy;
	int32_t sx1, sx2, sy1, sy2;
	
	//���ٽ�4����ĻҶ�ֵgray1,2,3,4
	//gray5,6Ϊ��4����Ȩ�����õ��м�ֵ
	int32_t gray1, gray2, gray3, gray4, gray5, gray6;
	
	//4������ڼ���Ҷ�����ռ��Ȩ��
	int32_t dy, dx;

	int32_t bfx = (src_width * SCALE) / dst_width;//���űȵĵ�����100��(100����ָSCALE,��һ������100)
	int32_t bfy = (src_height * SCALE) / dst_height;//���űȵĵ�����100��	

	pS = pSrc;
	pD = pDst;
	

	//ͨ��˫���Բ�ֵ��ߴ��һ����Ŀ��ͼ��(x,y)�ĻҶ�ֵ
	//ͨ��˫���Բ�ֵ��ߴ��һ����Ŀ��ͼ��(x,y)�ĻҶ�ֵ
	if (inter_type == InterLinear) {
		for ( y = 0; y < dst_height; y++) {
			tempy = y * bfy;	//Դͼ��y�����100��
			sy1 = tempy / SCALE;	
			sy2 = sy1 + 1;
			dy = tempy - sy1 * SCALE;//�����Ŵ�100��

			for (x = 0; x < dst_width; x++) {

				if (image_type == ImageGray) { //8λ�Ҷ�ͼ
					tempx = x * bfx;
					sx1 = tempx / SCALE;
					sx2 = sx1 + 1;
					dx = tempx - sx1 * SCALE;//�����Ŵ�100��

					//ע��:���ӳ�����������(x,y)�п��ܳ�����Դͼ���
					//��Χ(0��Width, 0��Height),���Դ��ڼ������
					if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
						//1.������곬��ͼ������½�(��߾�������Χ)
						gray6 = (*(pS + sy1*src_pitch + sx1));			
					} else if (sx1 >= src_width - 1) {
						//2.���ͼ�������һ�����
						gray1 = (*(pS + sy1*src_pitch + sx1));
						gray3 = (*(pS + sy2*src_pitch + sx1));
						gray6 = (int32_t)(gray1 * (SCALE - dy) + gray3 * dy);	//����100��
					} else if (sy1 >= src_height - 1) {
						//3.���ͼ�������һ�����
						gray1 = (*(pS + sy1*src_pitch + sx1));
						gray2 = (*(pS + sy1*src_pitch + sx2));
						gray6 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);	//����100��
					} else {
						gray1 = (*(pS + sy1*src_pitch + sx1));
						gray2 = (*(pS + sy1*src_pitch + sx2));
						gray3 = (*(pS + sy2*src_pitch + sx1));
						gray4 = (*(pS + sy2*src_pitch + sx1));
				
						gray5 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);
						gray6 = (int32_t)(gray3 * (SCALE - dx) + gray4 * dx);

						//gray6 = gray5 * (100 - dy) + gray6 * dy; //���Ŵ�100 * 100
						gray6 = dy * (gray6 - gray5) / SCALE + gray5; //�Ŵ�100
					}
					*(pD + y*dst_pitch + x) = (uint8_t)(gray6 / SCALE);				//�ָ�

				} else if (image_type == ImageColor) {	//24λ��32λ��ɫͼ
					tempx = x * bfx;
					sx1 = tempx / SCALE;
					sx2 = sx1 + 1;
					dx = tempx - sx1 * SCALE;//�����Ŵ�100��

					// ����32λ���ɫ��Ҫ�ֱ������ԭɫ
					for (k = 0; k < 3; k++) {
						//ע��:���ӳ�����������(x,y)�п��ܳ�����Դͼ���
						//��Χ(0��Width, 0��Height),���Դ��ڼ������	
						if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
							//1.������곬��ͼ������½�(��߾�������Χ)
							gray6 = (*(pS + sy1*src_pitch + sx1*4 + k));
						} else if (sx1 >= src_width - 1) {
							//2.���ͼ�������һ�����
							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
							gray6 = (int32_t)(gray1 * (SCALE - dy) + gray3 * dy);
						} else if (sy1 >= src_height - 1) {
							//3.���ͼ�������һ�����
							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
							gray6 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);	//����100��
						} else {
							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
							gray4 = (*(pS + sy1*src_pitch + sx2*4 + k));
					
							gray5 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);//�ҶȷŴ�100��
							gray6 = (int32_t)(gray3 * (SCALE - dx) + gray4 * dx);

							gray6 = dy * (gray6 - gray5) / SCALE + gray5; //�Ŵ�100
						}		
					
						gray6 /= SCALE;	//�ָ�
						*(pD + y * dst_pitch + x*4 + k) = (uint8_t)gray6;
					}
				}
			}
		}
	}

}

void SizeNormalizeV2
( 
 uint8_t *pDst, 
 const int32_t dst_width, 
 const int32_t dst_height,
 const int32_t dst_pitch,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch/*,
 Interpolation_t inter_type,
 ImageFlag_t image_type*/
 )
{ 
	uint8_t *pS, *pD;		//ͼ������ָ��
	
	int32_t x, y;
	pS = pSrc;
	pD = pDst;
	for (y = 0; y < dst_height; y++) {
		for (x = 0; x < dst_width; x++) {
			*(pD + y * dst_pitch + x) = *(pS + 2*y*src_pitch + x*2);
		}
	}

}

/******************************************************************************
  * ���ܣ�ͼ�����ݾ���,��ͼ����⺯������
  * ������pSrc		������ͼ������
  *       width		ͼ����
  *		  height    ͼ��߶�
  *		  pitch		ͼ��ÿ���ֽ���
  * ���أ�
******************************************************************************/
void Equalization(uint8_t *pSrc, const int32_t width, const int32_t height, const int32_t pitch)
{
	uint8_t *pS;
	int32_t i, j, temp;
	int32_t wh = width * height;
	int32_t hist[256];
	int32_t gray_map[256];	//ֱ��ͼ,�Ҷ�ӳ���
	//��ֱ��ͼ��0
	for (i = 0; i < 256; i++)
		hist[i] = 0;
	//����ֱ��ͼ
	for (i = 0; i < height; i++) {
		pS = pSrc + pitch*i;
		for (j = 0; j < width; j++) {
			hist[*(pS+j)]++;
		}
	}

	//ת����ʽ:D<B> = D<max> * sigma<0,x>(hist[i]) * 255 / A0 
	//(����iΪ�Ҷȼ�,hist[i]Ϊ��i���Ҷȵ����ظ���)
	//����Ҷ�ӳ���:gray_map[i] = sigma<0,x>(hist[i]) * 255 / A0; (A0 = width * height)
	temp = 0;
	for (i = 0; i < 256; i++) {
		temp += hist[i];
		gray_map[i] = (int32_t)(temp * 255 / wh);
	}

	for (i = 0; i < height; i++) {
		pS = pSrc + i * pitch;
		for (j = 0; j < width; j++) {
			*(pS+j) = gray_map[*(pS+j)];
		}
	}
}

//void EqualizationV1(uint8_t *pSrc, uint8_t *pSeg, const int32_t width, const int32_t height, const int32_t pitch)
//{
//	uint8_t *pS;
//	int32_t i, j, temp;
//	int32_t wh = width * height;
//	int32_t hist[256];
//	int32_t gray_map[256];	//ֱ��ͼ,�Ҷ�ӳ���
//	//��ֱ��ͼ��0
//	for (i = 0; i < 256; i++)
//		hist[i] = 0;
//	//����ֱ��ͼ
//	for (i = 0; i < height; i++) {
//		pS = pSrc + pitch*i;
//		for (j = 0; j < width; j++) {
//			if (*(pSeg + i*pitch +j) == 255) {
//				continue;
//			}
//			hist[*(pS+j)]++;
//		}
//	}
//
//	//ת����ʽ:D<B> = D<max> * sigma<0,x>(hist[i]) * 255 / A0 
//	//(����iΪ�Ҷȼ�,hist[i]Ϊ��i���Ҷȵ����ظ���)
//	//����Ҷ�ӳ���:gray_map[i] = sigma<0,x>(hist[i]) * 255 / A0; (A0 = width * height)
//	temp = 0;
//	for (i = 0; i < 256; i++) {
//		temp += hist[i];
//		gray_map[i] = (int32_t)(temp * 255 / wh);
//	}
//
//	for (i = 0; i < height; i++) {
//		pS = pSrc + i * pitch;
//		for (j = 0; j < width; j++) {
//			if (*(pSeg + i*pitch +j) == 255) {
//				continue;
//			}
//			*(pS+j) = gray_map[*(pS+j)];
//		}
//	}
//}

/******************************************************************************
  * ���ܣ�ͼ����ݶȼ����ֵ����,����ݶȷ�ֵ����(��ͼ���ݶȻ�ȡ��������)
  * ������pDst				�ݶȷ�ֵ(���)
  *		  pSrc				������Сһ���ͼ������(����)
  *       width				����ͼ����
  *		  height			����ͼ��߶�
  *       pitch				����ͼ��ÿ���ֽ���
  *		  size				ƫ������ģ��ߴ�
  *		  operator_type		��������
  * ���أ�
  * ˵��: 
  * �㷨: 
  *		  �ݶȼ���,���Ƕ�(x,y)����x,y��ƫ��dx,dy(�ɲο�������˹������ͼ����)
  *		  dx = f(x+1,y) - f(x,y), dy = f(x, y+1) - f(x, y)
  *		  �ݶȷ�ֵT(x,y) = sqrt(dx*dx + dy*dy) ���Ƶ���|dx|+|dy|
  *		  P.S.�ݶ����ӿ��ԴӶ��嵽�򵥵�Sobel�����ٵ����ӵ�Marr-Hildreth ����
******************************************************************************/
//void GetGrads
//(
// uint8_t *pDst, 
// uint8_t *pSrc, 
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch,
// const int32_t size,
// const int32_t operator_type
//)
//{
//	int32_t x, y, i, j;
//	int32_t vx, vy;		//x, y����ƫ��
//	uint8_t *pS;
//	uint8_t *pD;
//	int32_t	num;
//	int32_t gradSum;
//	int32_t grad;
//	int32_t r = size / 2;
//	
//	for(y = 0; y < height; y++) {
//		for(x = 0; x < width; x++) {			
//
//			pD = pDst + y*pitch + x;
//			num = 0;
//			gradSum = 0;
//			for(i = -r; i <= r; i++) {
//				//��ֹԽ��
//				if(y+i<1 || y+i>=height-1) 
//					continue;
//				for(j = -r; j <= r; j++) {
//					if(x+j<1 || x+j>=width-1) 
//						continue;
//
//					pS = pSrc + (y+i)*(pitch) + x + j;
//
//					//ʹ��Sobel������
//					if (operator_type == SOBEL_H) {
//						//-1 0 1; -2 0 2; -1 0 1;
//						gradSum += *(pS + pitch + 1) -  *(pS + pitch - 1) +
//								   *(pS + 1)*2 - *(pS - 1)*2 +
//								   *(pS - pitch + 1) - *(pS - pitch - 1);
//					} else if (operator_type == SOBEL_V) {	
//						//-1 -2 -1; 0 0 0; 1 2 1;
//						gradSum += *(pS + pitch - 1) - *(pS - pitch - 1) +
//								   *(pS + pitch)*2 - *(pS - pitch)*2 +
//								   *(pS + pitch + 1) - *(pS - pitch + 1);
//					} else if (operator_type == SOBEL_H1) {
//						//-1 2 -1; -1 2 -1; -1 2 -1;
//						gradSum += *(pS + pitch)*2  - *(pS + pitch + 1) - *(pS + pitch - 1) +
//								   *(pS)*2 - *(pS + 1) - *(pS - 1) + 
//								   *(pS-pitch)*2 - *(pS - pitch + 1) - *(pS - pitch - 1);
//					} else if (operator_type == SOBEL_V1) {
//						//-1 -1 -1; 2 2 2; -1 -1 -1;
//						gradSum += -*(pS + pitch)  - *(pS + pitch + 1) - *(pS + pitch - 1) +
//								   *(pS)*2 + *(pS + 1)*2 + *(pS - 1)*2 + 
//								   -*(pS-pitch) - *(pS - pitch + 1) - *(pS - pitch - 1);
//					} else if (operator_type == SOBEL_HV) {
//						vx = *(pS + pitch + 1) - *(pS + pitch - 1) +
//							 *(pS + 1) - *(pS - 1) +
//							 *(pS - pitch + 1) - *(pS - pitch - 1);
//						//��y����ƫ��
//						vy = *(pS + pitch - 1) - *(pS - pitch - 1) +
//							 *(pS + pitch)*2 - *(pS - pitch)*2 +
//							 *(pS + pitch + 1) - *(pS - pitch + 1);
//
//						//�����ݶȷ�ֵ:sqrt(vx^2+vy^2) = |vx| + |vy|
//						gradSum += (abs(vx)+abs(vy));		
//					}
//
//					num++;							//����������Ŀ+1
//				}
//			}
//
//			if(num == 0)
//				num = 1;
//			// ���ֵ�����浽pDst�У����ڷָ�ǰ������
//			grad = gradSum/num;
//			
//			if(grad > 255)
//				grad = 255;
//			if (grad < 0)
//				grad = 0;
//			
//			*pD = (uint8_t)grad;
//		}
//	}
//}


/******************************************************************************
  * ���ܣ�ͼ�����ݵķ��򳡼���,�����������(��ͼ���򳡻�ȡ��������)
  * ������pGrads			�ݶȷ�ֵ����(���)
  *       pOrientation		����ͼ��ֵ
  *		  pSrc				������Сһ���ͼ������(����)
  *       width				����ͼ����
  *		  height			����ͼ��߶�
  *		  pitch				����ͼ��ÿ���ֽ���
  *		  size				ƫ������ģ��ߴ�
  * ���أ�
  * ˵��: 
  *		  1.����HalfWidthHeight�������ͼ���������ø�˹ģ����ȡ��Ƶ��Ϣ����߼���
  *		  2.�������(���ú���GetOrientationFast(�˺���ֻʹ�ÿ�߼���������ͼ��))
******************************************************************************/
void GetGradsAndOrientationFast
(
 uint8_t *pGrads,
 uint8_t *pOrientation, 
 uint8_t *pSrc, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const int32_t  size
 )
{
	//int32_t  x, y, i, j;
	//int32_t  vx, vy, lvx, lvy;	//x, y����ƫ��, sin(2sita), cos(2sita)
	//int32_t r = size / 2;
	//uint8_t *pS = NULL;
	//uint8_t *pG = NULL;
	//uint8_t *pOri = NULL;
	//int32_t	angle, num;
	//int32_t gradSum;
	//int32_t grad;
	//double  fAngle;
	//
	////���ڼ����ݶȳ���Ϊ��ʱ,Ϊ����ٶ�,����Դͼ�������Ϊ��СΪһ����
	////����Դͼ����������1�����ص�Ӧ�ö�ӦĿ��ͼ���4����
	////pSrcָ�������ֻ��width/2 * height/2 ��,����߷ֱ�Ϊwidth/2, height/2
	////����x,y��Ŀ��ͼ�����ݵ�(������ݵ�)����,��Դͼ��������Ϊx/2,y/2��
	//for(y = 0; y < height/2; y++)
	//{
	//	for(x = 0; x < width/2; x++)
	//	{
	//		//����*2����ΪԴͼ��һ��Ҫ���Ŀ��ͼ���4��
	//		pOri = pOrientation + 2 * y * pitch + 2 * x;
	//		pG = pGrads + 2 * y * pitch + 2 * x;
	//		lvx = 0;
	//		lvy = 0;
	//		num = 0;
	//		gradSum = 0;
	//		for(i = -r; i <= r; i++)	// Ϊ����ٶȣ�����Ϊ1
	//		{
	//			//��ֹԽ��
	//			if(y+i<1 || y+i>=height/2-1) 
	//				continue;
	//			for(j = -r; j <= r; j++)	// Ϊ����ٶȣ�����Ϊ1
	//			{
	//				if(x+j<1 || x+j>=width/2-1) 
	//					continue;

	//				//ʹ��Sobel������
	//				pS = pSrc + (y+i)*(width/2) + x+j;
	//				//��x����ƫ��
	//				vx = *(pS + pitch/2 + 1) - *(pS + pitch/2 - 1) +
	//					 *(pS + 1)*2 - *(pS - 1)*2 +
	//					 *(pS - pitch/2 + 1) - *(pS - pitch/2 - 1);
	//				//��y����ƫ��
	//				vy = (*(pS + pitch/2 - 1) - *(pS - pitch/2 - 1) +
	//					 *(pS + pitch/2)*2 - *(pS - pitch/2)*2 +
	//					 *(pS + pitch/2 + 1) - *(pS - pitch/2 + 1));

	//				//�����ݶ�
	//				//�����ݶȷ�ֵ:sqrt(vx^2+vy^2) = |vx| + |vy|
	//				gradSum += (abs(vx)+abs(vy));		
	//				//���㷽��
	//				//������Χ����ݶ��ۼ���Ϊsin(2sita),cos(2sita)
	//				lvx += vx * vy * 2;		//sin(2sita)
	//				lvy += vx*vx - vy*vy;	//cos(2sita)
	//				num++;					//����������Ŀ+1
	//			}
	//		}

	//		if(num == 0) 
	//			num = 1;

	//		// �󻡶�
	//		fAngle = atan2(lvy, lvx);
	//		// �任��(0 - 2*pi)
	//		if(fAngle < 0)	fAngle += 2.0*M_PI;
	//		
	//		// �����߽Ƕ�
	//		fAngle = (fAngle*M_EPI*0.5 + 0.5);
	//		angle = (int32_t)fAngle;

	//		// ��Ϊ����sobel���ӣ����ԽǶ�ƫת�˶ȣ�����Ҫ��ת��õĽǶ�
	//		angle -= 135;
	//		// �Ƕȱ任��(-180)
	//		if(angle <= 0)	
	//			angle += 180;
	//		
	//		angle = 180-angle;

	//		//Դͼ��һ��Ҫ���Ŀ��ͼ���4��,�����4��ֵ��Ϊ��ͬ�Ľ��
	//		// �������߽Ƕ�
	//		*pOri = (uint8_t)angle;
	//		*(pOri + 1) = (uint8_t)angle;
	//		*(pOri + pitch) = (uint8_t)angle;
	//		*(pOri + pitch + 1) = (uint8_t)angle;

	//		// ���ֵ�����浽pDst�У����ڷָ�ǰ������
	//		grad = gradSum/num;
	//		
	//		if(grad > 255)
	//			grad = 255;
	//		//Դͼ��һ��Ҫ���Ŀ��ͼ���4��,�����4��ֵ��Ϊ��ͬ�Ľ��
	//		*pG = (uint8_t)grad;
	//		*(pG + 1) = (uint8_t)grad;
	//		*(pG + pitch) = (uint8_t)grad;
	//		*(pG + pitch + 1) = (uint8_t)grad;

	//	}
	//}
	int32_t  x, y, i, j;
	int32_t  vx, vy, lvx, lvy;	//x, y����ƫ��, sin(2sita), cos(2sita)
	int32_t r = size / 2;
	uint8_t *pS = NULL;
	uint8_t *pG = NULL;
	uint8_t *pOri = NULL;
	int32_t	angle, num;
	int32_t gradSum;
	int32_t grad;
	double  fAngle;

	int32_t tempY = 0;
	int32_t tempPitch = pitch>>1;

	//���ڼ����ݶȳ���Ϊ��ʱ,Ϊ����ٶ�,����Դͼ�������Ϊ��СΪһ����
	//����Դͼ����������1�����ص�Ӧ�ö�ӦĿ��ͼ���4����
	//pSrcָ�������ֻ��width/2 * height/2 ��,����߷ֱ�Ϊwidth/2, height/2
	//����x,y��Ŀ��ͼ�����ݵ�(������ݵ�)����,��Դͼ��������Ϊx/2,y/2��
	for(y = 0; y < height/2; y++)
	{
		tempY = 2*y*pitch;
		for(x = 0; x < width/2; x++)
		{
			//����*2����ΪԴͼ��һ��Ҫ���Ŀ��ͼ���4��
			//pOri = pOrientation + 2 * y * pitch + 2 * x;
			pOri = pOrientation + tempY + 2 * x;
			//pG = pGrads + 2 * y * pitch + 2 * x;
			pG = pGrads + tempY + 2*x;
			lvx = 0;
			lvy = 0;
			num = 0;
			gradSum = 0;
			for(i = -r; i <= r; i++)	// Ϊ����ٶȣ�����Ϊ1
			{
				//��ֹԽ��
				if(y+i<1 || y+i>=height/2-1) 
					continue;
				for(j = -r; j <= r; j++)	// Ϊ����ٶȣ�����Ϊ1
				{
					if(x+j<1 || x+j>=width/2-1) 
						continue;

					//ʹ��Sobel������
					//pS = pSrc + (y+i)*(width/2) + x+j;
					pS = pSrc + (y+i)*(tempPitch) + x+j;
					//��x����ƫ��
					//vx = *(pS + pitch/2 + 1) - *(pS + pitch/2 - 1) +
					//    *(pS + 1)*2 - *(pS - 1)*2 +
					//    *(pS - pitch/2 + 1) - *(pS - pitch/2 - 1);
					vx = *(pS + tempPitch + 1) - *(pS + tempPitch - 1) +
						*(pS + 1)*2 - *(pS - 1)*2 +
						*(pS - tempPitch + 1) - *(pS - tempPitch - 1);
					//��y����ƫ��
					//vy = (*(pS + pitch/2 - 1) - *(pS - pitch/2 - 1) +
					//    *(pS + pitch/2)*2 - *(pS - pitch/2)*2 +
					//    *(pS + pitch/2 + 1) - *(pS - pitch/2 + 1));
					vy = (*(pS + tempPitch - 1) - *(pS - tempPitch - 1) +
						*(pS + tempPitch)*2 - *(pS - tempPitch)*2 +
						*(pS + tempPitch + 1) - *(pS - tempPitch + 1));

					//�����ݶ�
					//�����ݶȷ�ֵ:sqrt(vx^2+vy^2) = |vx| + |vy|
					gradSum += (abs(vx)+abs(vy));		
					//���㷽��
					//������Χ����ݶ��ۼ���Ϊsin(2sita),cos(2sita)
					lvx += vx * vy * 2;		//sin(2sita)
					lvy += vx*vx - vy*vy;	//cos(2sita)
					num++;					//����������Ŀ+1
				}
			}

			if(num == 0) 
				num = 1;

			// �󻡶�
			fAngle = atan2(lvy, lvx);
			// �任��(0 - 2*pi)
			if(fAngle < 0)	//fAngle += 2.0*M_PI;
				fAngle += M_PI_X2;

			// �����߽Ƕ�
			//fAngle = (fAngle*M_EPI*0.5 + 0.5);
			fAngle = (M_EPI_2*fAngle + 0.5);
			angle = (int32_t)fAngle;

			// ��Ϊ����sobel���ӣ����ԽǶ�ƫת�˶ȣ�����Ҫ��ת��õĽǶ�
			angle -= 135;
			// �Ƕȱ任��(-180)
			if(angle <= 0)	
				angle += 180;

			angle = 180-angle;

			//Դͼ��һ��Ҫ���Ŀ��ͼ���4��,�����4��ֵ��Ϊ��ͬ�Ľ��
			// �������߽Ƕ�
			*pOri = (uint8_t)angle;
			*(pOri + 1) = (uint8_t)angle;
			*(pOri + pitch) = (uint8_t)angle;
			*(pOri + pitch + 1) = (uint8_t)angle;

			// ���ֵ�����浽pDst�У����ڷָ�ǰ������
			grad = gradSum/num;

			if(grad > 255)
				grad = 255;
			//Դͼ��һ��Ҫ���Ŀ��ͼ���4��,�����4��ֵ��Ϊ��ͬ�Ľ��
			*pG = (uint8_t)grad;
			*(pG + 1) = (uint8_t)grad;
			*(pG + pitch) = (uint8_t)grad;
			*(pG + pitch + 1) = (uint8_t)grad;

		}
	}
}


/******************************************************************************
  * ���ܣ�ͼ��̶���ֵ����(�����˹̶���ֵ��ֵ�������������Ĺ���)
  * ������image         ָ��ͼ��
  *       thr_value     ��ֵ
  *       max_value	    ��ĳЩ��ֵ���Ͳ���ʱ,ȡ�õ����ֵ
  *       thr_type		��ֵ��������
  * ���أ�������
******************************************************************************/
void Threshold
(
 uint8_t *pSrc,
 const uint8_t thr_value, 
 const uint8_t max_value, 
 const int32_t thr_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
    int32_t n;
	uint8_t *pimg = pSrc;
	int32_t size = (width * height);
    /* ѭ������ */
    for (n = 0; n < size; n++, pimg++) {
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
    //return ImageSetFlag(image, ImageBinarized);
}


/******************************************************************************
  * ���ܣ�ͼ���ֵ��,ʹ��ͼ��������ֵ��Ϊ��ֵ
  * ������pDst			��ֵ����ͼ������
  *		  pSrc			��ֵ��ǰͼ������
  *       x0			��ȡͼ�񲿷ֵĿ�ʼx����
  *       y0			��ȡͼ�񲿷ֵĿ�ʼy����
  *       dx			��ȡͼ�񲿷ֵĿ��
  *       dy			��ȡͼ�񲿷ֵĸ߶�
  *		  dir			��ֵ����ʽ
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
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
void OverallBinary
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t x0, 
 const int32_t y0, 
 const int32_t dx,
 const int32_t dy,
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	uint8_t *pS;
	uint8_t *pD;
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

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) || \
		(y0+dy > height) || (x0+dx) > width) {	//��������
		//fprintf (stderr, "bad input parameter.\n");
		//return FunBadParameter;
		return;
	}
	total = dx*dy;
	average = 0;
	for (y = y0; y < y0+dy; y++) {
		pS = pSrc + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			average += *(pS + x);
		}
	}

	average /= total;
#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOverall: thr_value = %d\n", average);
#endif

	for (y = y0; y < y0+dy; y++) {
		pS = pSrc + pitch*y;
		pD = pDst + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			//if (dir == 0) 
			//	*(pS + x) = *(pS + x) > average ? 0 : 1;
			//else
			//*(pS + x) = *(pS + x) > average ? 1 : 0;
			//*(pS + x) =*(pS + x) > average ? upper_thr : under_thr;
			*(pD + x) = *(pS + x) > average ? upper_thr : under_thr;
		}
	}
}



/******************************************************************************
  * ���ܣ�ͼ���ֵ��,ʹ��ͼ��������ֵ��Ϊ��ֵ
  * ������pDst			��ֵ����ͼ������
  *		  pSrc			��ֵ��ǰͼ������
  *		  pGrads		ͼ���ݶ�����,���ú���GetGrads���
  *       x0			��ȡͼ�񲿷ֵĿ�ʼx����
  *       y0			��ȡͼ�񲿷ֵĿ�ʼy����
  *       dx			��ȡͼ�񲿷ֵĿ��
  *       dy			��ȡͼ�񲿷ֵĸ߶�
  *		  dir			��ֵ����ʽ
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *		  pGrads���ú���GetGrads���
  * �㷨����:
  *		  �������ȡ������ͼ�������ƽ���Ҷ���Ϊ��ֵ	
******************************************************************************/
//void OverallBinaryGrads
//(
// uint8_t *pDst,
// uint8_t *pSrc,
// uint8_t *pGrads,
// const int32_t size,
// const int32_t dir,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	uint8_t *pS;
//	uint8_t *pD;
//	uint32_t average;
//	int32_t x, y;
//	//uint32_t total;
//	uint32_t num;
//	//dir == 1: >thr_value: 1, else: 0
//	//dir == 0: >thr_value: 0, else: 1 
//	//dir == 2: >thr_value: 0, else: 255
//	//dir == 3: >thr_value: 255, else: 0
//	uint32_t upper_thr, under_thr;
//	if (dir == 0) {
//		upper_thr = 0;
//		under_thr = 1;
//	} else if (dir == 1) {
//		upper_thr = 1;
//		under_thr = 0;
//	} else if (dir == 2) {
//		upper_thr = 0;
//		under_thr = 255;
//	} else if (dir == 3) {
//		upper_thr = 255;
//		under_thr = 0;
//	} else {
//		upper_thr = 1;
//		under_thr = 0;
//	}
//	//
//
//	//if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) || \
//	//	(y0+dy > height) || (x0+dx) > width) {	//��������
//	//	fprintf (stderr, "bad input parameter.\n");
//	//	//return FunBadParameter;
//	//}
//	//total = dx*dy;
//	average = 0;
//	num = 0;
//	//for (y = y0; y < y0+dy; y++) {
//	for (y = 0; y < height; y++) {
//		pS = pSrc + pitch*y;
//		//for (x = x0; x < x0+dx; x++) {
//		for (x = 0; x < width; x++) {
//			if (pGrads[y*pitch+x] == 255) {		//ͼ�񱳾�������ݶ�����Ϊ255
//				continue;
//			}
//			if (y < size || y >= height - size ||\
//				x < size || x >= width - size) {
//				continue;
//			}
//			average += *(pS + x);
//			num++;
//		}
//	}
//
//	//average /= total;
//	average /= num;
//#if defined __MY_DEBUG
//		fprintf(stderr,"# ImageOverall: thr_value = %d\n", average);
//#endif
//
//	//for (y = y0; y < y0+dy; y++) {
//	for (y = 0; y < height; y++) {
//		pS = pSrc + pitch*y;
//		pD = pDst + pitch*y;
//		for (x = 0; x < width; x++) {
//			if (pGrads[y*pitch+x] == 255) {	//��������Ϊ����·�෴����ɫ
//				*(pD + x) = *(pS + x) < average ? upper_thr : under_thr;
//				continue;
//			}
//			if (y < size || y >= height - size ||\
//				x < size || x >= width - size) {
//				*(pD + x) = *(pS + x) < average ? upper_thr : under_thr;
//				continue;
//			}
//
//			*(pD + x) = *(pS + x) > average ? upper_thr : under_thr;
//		}
//	}
//}

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
void MeanBinary
( 
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x,y,s,p,q,a,c,c0;
	//int32_t sx, sy;
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

    s = size/2;		/* ��С */
    a = size*size;	/* ��� */    

	for (y = 0; y < height; y++)
    for (x = 0; x < width; x++)
    {
		c = 0;
		//sx = x - s;
		//sy = y - s;
		if (y < s || y >= height-s ||\
			x < s || x >= width-s) {
			pDst[pitch*y + x] = 0;
			continue;
		} 

		//�Ż���
		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += pSrc[p+q*pitch];
		}

		c0 = pDst[x+y*pitch]*a;
		pDst[x + y*pitch]= c0 > c ? upper_thr : under_thr;

    }
    
}
/******************************************************************************
  * ���ܣ�ͼ������ͳ���˲�������ͨ�������ֵʵ��
  * ������pDst			�����ͼ������
  *		  pSrc			����ǰͼ������
  *       size			�˲���ģ���С(2*r+1)
  *       thre_val		��ֵ
  *		  dir			��ֵ����ʽ
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  *		  pitch			ͼ������ÿ���ֽ���
  * ���أ�������
  * ˵��: �˴��Ķ�ֵ��ָ0��1,����0��255,���޸��¾Ϳ���ʵ��0��255�Ķ�ֵ��
  *		  ��ֵ������ʽ:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       �߽�Ӱ��,�����������������ͼ��ʵ���ϱ��ü�ȥ��size�к�size��
******************************************************************************/
void StatisticsFilter
( 
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t size, 
 const int32_t thre_val, 
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
    int32_t x,y,s,p,q,c;
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

    s = size/2;		/* ��С */ 
   
    /* ����ͼ����м��� */
    
    for (y = s; y < height-s; y++)
    for (x = s; x < width-s; x++)
    {
		c = 0;

		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += pSrc[p+q*pitch];
		}

		//if (dir == 0)
		//	p1[x+y*pitch] = c>=thre_val?0:1;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		//else 
		//	p1[x+y*pitch] = c>=thre_val?1:0;	//�����޸�Ϊ255:0�Ϳ���ʵ�ֺڰ׶�ֵ��
		pDst[x+y*pitch] = c>= thre_val?upper_thr:under_thr;

    }
    
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
  * ���ܣ�ͼ������ͨ���㷨
  * ������pDst			��ֵ����ͼ������
  *		  pSrc			��ֵ��ǰͼ������
  *       size			�ṹԪ�سߴ�(�涨������ͬΪsize)
  *       tmpltA		�ṹԪ��
  *       tmpltSum		�ṹԪ��֮��
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  *		  pitch			ͼ������ÿ���ֽ���
  * ���أ�������
  * ˵��: ����ͼ��Ϊ(0,1)��ֵͼ��,���ͼ��ҲΪ(0,1)��ֵͼ��
  * �㷨��
  *          �����㷨��ϸ�ڣ�
  *          ���������ģ����ԭͼ���ϻ�������ģ�����ĵ��Ӧ��ԭͼ���ϵĵ�Ϊ1ʱ��
  *          ����ģ���ϵ�Ԫ������֮�غϵĵ���������(���ĵ����)��������Ľ��
  *          ����ȫΪ0ʱ������ģ���ԭͼ����л���������ǻ������Ӧ�Ľ����Ϊ1
  *          ����������ɨ��������ͼ��󽫱�ǵĵ���1���������һ�����Ͳ�����
******************************************************************************/
void UniDilateOZ
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 int32_t *tmpltA,
 const int32_t tmpltSum,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t i, j, k, x, y;
	int32_t temp = 0;
	int32_t r = size / 2;

	for (y = r; y < height - r; y++) {
		for (x = r; x < width - r; x++) {
			if (pSrc[y*pitch+x] == 0)
				continue;
			temp = 0;
			k = 0;
			for (j = y-r; j <= y+r; j++) {
				for (i = x-r; i <= x+r; i++) {
					if (tmpltA[k++] == 1)
						temp += pSrc[j*pitch+i];//P2(i, j);
				}
			} 
			k = 0;
			if (temp <= 1) {
				pDst[y*pitch+x] = 0;//P(x, y) = 0;//continue;
			} else {
				for (j = y-r; j <= y+r; j++) {
					for (i = x-r; i <= x+r; i++) {
						if (tmpltA[k++] == 1) {
							//P(i, j) = 1;
							pDst[j*pitch+i] = 1;
						}
					}
				} 
			}
		}
	}

}



/******************************************************************************
  * ���ܣ�ͼ��ʴͨ���㷨
  * ������pDst			�����ͼ������
  *		  pSrc			����ǰͼ������
  *       size			�ṹԪ�سߴ�(�涨������ͬΪsize)
  *       tmpltA		�ṹԪ��
  *       tmpltSum		�ṹԪ��֮��
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  *		  pitch			ͼ������ÿ���ֽ���
  * ���أ�������
  * ˵��: ����ͼ��Ϊ(0,1)��ֵͼ��,���ͼ��ҲΪ(0,1)��ֵͼ��
  * �㷨:   
  *          ��ʴ����ϸ�ڣ� 
  *          ���������ģ����ԭͼ���ϻ�������ģ�����ĵ��Ӧ��ԭͼ���ϵĵ�Ϊ1ʱ��
  *          ����ģ���ϵ�Ԫ������֮�غϵĵ���������(���ĵ����)��������Ľ��
  *          ����ȫΪ"1"ʱ�ͽ�ģ�����Ķ�Ӧ��ԭͼ��ĵ���б��Ϊ��ɾ�����������
  *          ���ȫ��Ϊ"1"ʱ�ͽ�ģ�����ĵĶ�Ӧԭͼ��ĵ㱣��Ϊ"1".
******************************************************************************/
void UniErodeOZ
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 int32_t *tmpltA,
 const int32_t tmpltSum,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t i, j, k, x, y;
	int32_t temp = 0;
	int32_t r = size / 2;

	for (y = r; y < height - r; y++) {
		for (x = r; x < width - r; x++) {
			if (pSrc[y*pitch+x] == 0)
				continue;

			temp = 0;
			k = 0;
			for (j = y-r; j <= y+r; j++) {
				for (i = x-r; i <= x+r; i++) {
					if (tmpltA[k++] == 1)
						temp += pSrc[j*pitch+i];//P2(i, j);
				}
			} 

			if (temp != tmpltSum) { 
				pDst[y*pitch+x] = 0;//P(x, y) = 0;//continue;
			} else {
			    //P(x, y) = 1;
				pDst[y*pitch+x] = 1;
			}
		}
	}
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
  *		    �õ�pOrient(����GetOrientationFast���)
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
	//���߷����ϵ�7�����Ȩֵ
	int32_t Hw[7] = {2, 2, 3, 4, 3, 2, 2};
	//���߷���Ĵ�ֱ�����ϵ�7�����Ȩֵ
	int32_t Vw[7] = {1, 1, 1, 1, 1, 1, 1};

	int32_t Hv = 0;		// ���߷����ϵ�7����ļ�Ȩƽ��ֵ
	int32_t Vv = 0;		// ���߷���Ĵ�ֱ�����ϵ�7����ļ�Ȩƽ��ֵ
	int32_t tempY = 0;
	uint8_t *pS;		// ָ��ͼ�����ص�ָ��
	//uint8_t *pT;		//pFPTempָ��
	uint8_t *pOri;	//���߷���ָ��
	//uint8_t pFPTemp[FP_HEIGHT*FP_WIDTH];
	uint8_t *pFPTemp = fp_src_copy.pimg;
	//uint8_t *pFPTemp;	//��ʱ���ݻ�����
	//uint32_t under_thr = 0;
	//uint32_t upper_thr = 1;

	//ĳ����Χ8����ĵ�ַƫ��
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t SiteD8[8];

	int32_t exit = 1;
	int32_t n = 0;
	int32_t num = 0;
	
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	
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
	
	//pFPTemp = (uint8_t *)malloc(sizeof(uint8_t)*width*height);

	//if (pFPTemp == NULL)
	//	return;

	tempY = 0;
	for(y = 0; y < height; y++) {
		//�Ż�ǰ
		//tempY = y*pitch;	
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = pSrc + tempY + x;			
			//����õ�ǳ��ڣ�������ʱ���������øõ�Ϊ�ڵ㣬ֵΪ0
			if(*pS < 4) {
				*(pFPTemp + tempY + x) = 0;
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
				//*(pFPTemp + tempY + x) = 0;
				*(pFPTemp + tempY + x) = under_thr;
			} else {
				// ���߷����ϼ�Ȩƽ��ֵ�ϴ����õ�ǰ��Ϊ�׵�
				//*(pFPTemp + tempY + x) = 255;
				*(pFPTemp + tempY + x) = upper_thr;
			}
		}
		//�Ż���
		tempY += pitch;
	}

	//����ʱ�����������ݿ�����ԭʼͼ�����ݻ�����,ע�͵���һ��,����pFPTemp
	//����Ϊ����Զ�ֵ��ָ��ͼ�����ȥ���Դ������
	//memcpy(pSrc, pFPTemp, sizeof(uint8_t)*width*height);

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
				//pT = pFPTemp + tempY + x;
				for(i = 0; i < 8; i++) {
					//if(*(pS+SiteD8[i]) == *pS) {
					//if(*(pT+SiteD8[i]) == *pT) {
					if (*(pFPTemp + tempY + x + SiteD8[i]) == *(pFPTemp + tempY + x)) {
						num++;
					}
				}
				
				if(num < 2) {
					//��ͬ�����С�ڶ���ı䵱ǰ������(0-->0,255-->1)
					//*(pFPTemp+temp+x) = 255 - *pS;
					//*(pSrc + tempY + x) = 255 - *pT;
					if ((*(pFPTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = upper_thr;
					else
						*(pSrc + tempY + x) = under_thr;
					exit = 1;
				} else {	//���򲻸ı�(0-->0,255-->1)
					//*(pFPTemp+temp+x) = *pS;
					if ((*(pFPTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = under_thr;
					else
						*(pSrc + tempY + x) = upper_thr;
				}

			}
			//�Ż���
			tempY += pitch;
		}
	}

	//if (pFPTemp != NULL) {
	//	free(pFPTemp);
	//	pFPTemp = NULL;
	//}

}




