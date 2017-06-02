/******************************************************************************
 * �ļ�����image_segment.c
 * ���ܣ�  һЩͼ��ķָ��㷨
 * ˵��:   
        �������ֵĽ���:
		    ǰ׺:Image    (��ʾ������һ��ͼ���ǱȽ�ͨ�õ�)    (image)
			     FP       (��ʾ������ָ��ͼ��Ƚ�����)          (fp)
				 FV       (��ʾ�����Ծ���ͼ��Ƚ�ʹ��)          (fv)
			��׺:	 
				 LL       (��ʾ����Ϊ�ײ㺯��,���ϲ㺯������)   (ll,lowlevel)
				 V?       (��ʾ�����������汾)                  (Ver?,ver?)
				 A?       (��ʾͬ�����ܲ�ͬ�����ĺ���)          (Alt?,alt?)
				 W?       (��ʾͬ�����ܲ�ͬ�����ĺ���)          (Way?,way?)
				 OZ       (��ʾ����������������ͼ������Ϊ1(One),0(Zero)�Ķ�ֵ)
******************************************************************************/

#include "dip_header/image_segment.h"
//#include "../../bsp/bsp_header/z_mytype.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include "image_base.h"
//#include "image_enhance_filter.h"


//FunError_t GradsRSegment
//(
// uint8_t *pSrc,  
// uint8_t *pGrads, 
// const int32_t size, 
// const int32_t step, 
// const int32_t threshold, 
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
//)
//{
//	int32_t	x, y, i, j, k;
//	int32_t r = size / 2;
//	int32_t num = 0;
//	int32_t tempY;
//	int32_t min_x, max_x;
//	int32_t mem_size = width*height;
//	int32_t threshold1, sum, max_sum, min_max, pos, max_pos, min_pos;
//	int32_t max_d[2], pos_d[2];
//	threshold1 = 0;
//#define MASK_W		10
//#define MASK_H		50
//	max_sum = 0;
//	min_max = 0;
//	sum = 0;
//	pos = 0;
//	max_pos = 0;
//	min_pos = 255;
//	//for (i = width-1; i > MASK_W; i--) {
//	//	sum = 0;
//	//	for (j = height - 1; j > height - 1 - MASK_H; j--) {
//	//		for (k = 0; k < MASK_W; k++) {
//	//			sum += pGrads[j*pitch + i - k];
//	//		}
//	//	}
//	//	if (sum > max_sum) {
//	//		max_sum = sum;
//	//		pos = i;
//	//		//if (pos > max_pos) {
//	//		//	max_pos = pos;
//	//		//}
//	//		//if (pos < min_pos) {
//	//		//	min_pos = pos;
//	//		//}
//	//	}
//	//}
//	//max_d[0] = 0;
//	//pos_d[0] = 0;
//	//for (i = 2; i < width - 1; i++) {
//	//	sum = pGrads[i+1]+pGrads[i]-pGrads[i-1]-pGrads[i-2];
//	//	if (max_d[0] < sum) {
//	//		for (k = 5; k >= 1; k--) {
//	//			max_d[k] = max_d[k-1];
//	//			pos_d[k] = pos_d[k-1];
//	//		}
//	//		//max_d[1] = max_d[0];
//	//		//pos_d[1] = pos_d[0];
//	//		max_d[0] = sum;
//	//		pos_d[0] = i;
//	//	}
//	//}
//
//	//threshold1 = min_max / (3);
//	//min_pos = pos_d[0];
//	//max_pos = pos_d[0];
//	//for (k = 1; k <= 5; k++) {
//	//	if (pos_d[k]>max_pos) {
//	//		max_pos = pos_d[k];
//	//	}
//	//	if (pos_d[k]<min_pos) {
//	//		min_pos = pos_d[k];
//	//	}
//	//}
//	////if (pos_d[0] > pos_d[1]) {
//	////	min_pos = pos_d[1];
//	////	max_pos = pos_d[0];
//	////} else {
//	////	min_pos = pos_d[0];
//	////	max_pos = pos_d[1];
//	////}
//	//min_x = 255;
//	//max_x = 0;
//
//	tempY = 0;
//	for (y = 0; y < height; y++) {
//		//for (x = 0; x < width; x++) {
//		for (x = 0;  x < width; x++) {
//			//if (x < min_pos || x > max_pos) {
//			//	*(pGrads + y*pitch + x) = 255;
//			if(*(pGrads + y*pitch + x) < threshold) {
//				*(pGrads + y*pitch + x) = 255;			//������Ϊ��ɫ
//				//if (min_x > x) {
//				//	min_x = x;
//				//}
//			} else {
//				break;//continue;
//			}
//		}
//		for (x = width-1; x >= 0; x--) {
//			if (*(pGrads+y*pitch+x) < threshold) {
//				*(pGrads + y*pitch + x) = 255;			//������Ϊ��ɫ
//			} else {
//				break;//continue;
//			}
//		}
//		tempY += pitch;
//	}
//
//
//	// ���ǰ���������С���������5��֮һ�����ʾǰ������̫С�����ش���
//	//if(num < height * width/5)
//	//	return FunFailure;
//
//	////�������
//	tempY = 0;
//	for(y = 0; y < height; y++) {
//		//�Ż�ǰ:
//		//tempY = y * pitch;
//		for(x = 0; x < width; x++) {	
//			// ����Ǳ����������øõ�ҶȺͷ���Ϊ�׵�
//			if (x < 15 || x > width - 15 || y < 20) {
//				*(pSrc + tempY + x) = 0;
//				//continue;
//			}
//			//if(*(pGrads + tempY + x) == 255) {
//			//	*(pSrc + tempY + x) = 0;					//��Ե����Ϊ����(��ɫ)	
//			//}
//		}
//		//�Ż���
//		tempY += pitch;
//	}
//	return FunOK;
//
//}

//#define MASK_H		20
//#define MASK_W		4
////�����ַָ�
//void FVRSegment
//(
// uint8_t *pDst,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x_pos_y_l[FV_HEIGHT];
//	int32_t x_pos_y_r[FV_HEIGHT];
//	int32_t y_min, y_max;
//	int32_t max_value = 0;
//	int32_t max_value_l, max_value_r;
//	int32_t x_pos_l, x_pos_r;
//	int32_t sum;
//	int32_t i, j, k;
//	int32_t tempJ;
//	uint8_t *pS, *pD;
//
//	for (i = 0; i < FV_HEIGHT; i++) {
//		x_pos_y_l[i] = 0;
//		x_pos_y_r[i] = 0;
//	}
//	
//	//�ҳ��ϱ߽�y_min
//	tempJ = 0; 
//	max_value = 0;
//	y_min = 0;
//	for (j = 0; j < height / 2; j++) {
//		pS = pSrc + tempJ;
//		sum = 0;
//		for (i = 0; i < width; i++) {
//			sum += *(pS + pitch*3 + i) + *(pS + pitch*2 + i) - 
//				   *(pS + pitch   + i) - *(pS +           i);  
//		}
//		if (sum > max_value) {
//			max_value = sum;
//			y_min = j+3;
//		}
//		
//		tempJ += pitch;
//	}
//
//	//�ҳ��±߽�y_max
//	//tempJ = (height/2)*pitch; 
//	//max_value = 0;
//	//y_max = 0;
//	//for (j = height/2; j < height-3; j++) {
//	//	pS = pSrc + tempJ;
//	//	sum = 0;
//	//	for (i = 0; i < width; i++) {
//	//		sum += *(pS + pitch   + i) + *(pS +           i) - 
//	//			   *(pS + pitch*3 + i) - *(pS + pitch*2 + i);  
//	//	}
//	//	if (sum > max_value) {
//	//		max_value = sum;
//	//		y_max = j;
//	//	}
//	//	
//	//	tempJ += pitch;
//	//}
//	y_max = height - 1;
//
//	tempJ = y_min * pitch;
//	for (j = y_min; ((j <= y_max - MASK_H)); j++) {
//		pS = pSrc + tempJ;
//		max_value_l = 0;
//		max_value_r = 0;
//		for (i = 0; i <= width - MASK_W; i++) {
//			sum = 0;
//			for (k = 0; k < MASK_H; k++) {
//				sum += *(pS+k*pitch+i+2) + *(pS+k*pitch+i+3) - 
//					   *(pS+k*pitch+i  ) - *(pS+k*pitch+i+1) ;
//			}
//			if (sum > max_value_l) {
//				if (i < width/2) {
//					max_value_l = sum;
//					x_pos_l = i;//i+3;
//				}
//			}
//			if (sum < max_value_r) {
//				if (i > width/2) {
//					max_value_r = sum;
//					x_pos_r = i+3;//i;
//				}
//			}
//		}
//		x_pos_y_l[j] = x_pos_l;
//		x_pos_y_r[j] = x_pos_r;
//
//		tempJ += pitch;
//	}
//
//
//	//�ó��ָ�����(����255,ǰ��0);
//#if 0
//	//ÿ�е����ұ߽绥����ͬ
//	tempJ = 0; 
//	for (j = 0; j < height; j++) {
//		pS = pDst + tempJ;
//		if (j < y_min || j > y_max) {		//���±߽���ı�����Ϊ255
//			for (i = 0; i < width; i++) {
//				*(pS + i) = 255;
//			}
//		} else if (j <= height - MASK_H) {	//���ұ߽���ı�����Ϊ255
//			for (i = 0; i < width; i++) {
//				if ((i < x_pos_y_l[j]) || (i > x_pos_y_r[j])) {
//					*(pS + i) = 255;
//				} 
//			}
//		} else if (j >= height - MASK_H) {	//���ұ߽���ı�����Ϊ255
//			for (i = 0; i < width; i++) {
//				if ((i < x_pos_y_l[height - MASK_H])|| \
//					(i > x_pos_y_r[height - MASK_H])) {
//					*(pS + i) = 255;
//				} 
//			}
//		}
//
//		tempJ += pitch;
//	}
//#endif
//
//	//ÿ�е����ұ߽�:�������ұ߽��е�������Сֵ
//	//max_value_l = x_pos_y_l[y_min];
//	//max_value_r = x_pos_y_r[y_min];
//	//for (j = y_min; j <= y_max - MASK_H; j++) {
//	//	if (x_pos_y_l[j] > max_value_l) {
//	//		max_value_l = x_pos_y_l[j];
//	//	}
//	//	if (x_pos_y_r[j] < max_value_l) {
//	//		max_value_r = x_pos_y_r[j];
//	//	}
//	//}
//	
//	//ÿ�е����ұ߽�:���ֵ
//	max_value_l = 0;
//	max_value_r = 0;
//	for (j = y_min; j <= y_max - MASK_H; j++) {
//		max_value_l += x_pos_y_l[j];
//		max_value_r += x_pos_y_r[j];
//	}
//	max_value_l /= (y_max-MASK_H-y_min+1);
//	max_value_r /= (y_max-MASK_H-y_min+1);
//
//
//	tempJ = 0; 
//	for (j = 0; j < height; j++) {
//		pD = pDst + tempJ;
//		pS = pSrc + tempJ;
//		if (j < y_min || j > y_max) {		//���±߽���ı�����Ϊ255
//			for (i = 0; i < width; i++) {
//				*(pD + i) = 255;
//				*(pS + i) = 0;
//			}
//		} else {							
//			for (i = 0; i < width; i++) {	//���ұ߽���ı�����Ϊ255
//				if ((i < max_value_l) || (i > max_value_r)) {
//					*(pD + i) = 255;
//					*(pS + i) = 0;
//				} else {
//					*(pD + i) = 0;			//ǰ����Ϊ0
//				}
//			}
//		}
//
//		tempJ += pitch;
//	}
//
//}



/******************************************************************************
  * ���ܣ���ȡͼ�������,�����лҶ�������Ϊ�µ�ͼ������
  * ������pDst			�����ͼ������
  *		  pSrc			����ǰͼ������
  *		  cur_type		������������
  *		  size			���㵼��ʱ�õ������سߴ�(��������ʹ�����ص�)
  *		  thr_type	    ����ĵ����ʽ��лҶ�����ʱ�ķ���
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  *		  pitch			ͼ������ÿ���ֽ���
  * ���أ�������
  * ˵��: ���������Ĵ���,ͼ�����ݲ�����ԭ��������,�������ʽ��лҶ�������һ��
  *		  ��ͼ��.
  *		  �߽�Ӱ��,�����������������ͼ��ʵ���ϱ��ü�ȥ��2*size�к�2*size��
  * �㷨: 
  *		  1.�������ʹ�ʽ,����ÿһ�������
  *		  2.�ʵ���ȷ���Ҷ���ʱ�Ĺ�ʽ,��:
  *		    NewGray(x, y) = (H(x,y) - Hmin) * 256 / (Hmax-Hmin)
  *			����NewGray(x,y),H(x,y),Hmin,Hmax�ֱ��ʾ(x,y)����µĻҶ�ֵ,
  *			��������,����ͼ����������������е���С,���ֵ
  * ����:
  *		  1 - A finger-vein verification system using mean curvature:
  *		      Wonseok Song...
  *			  Pattern Recognition Letters 32 (2011) 1541�C1547
  *       2 - Finger vein extraction using gradient normalization and 
  *			  principal curvature:
  *			  Joon Hwan Choi...
******************************************************************************/
void CurvatureSegment
(
 uint8_t *pDst,
 uint8_t *pSrc,
 int32_t cur_type, 
 int32_t size, 
 int32_t thr_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	int32_t temp;
	double fx, fy, fxx, fxy, fyy, f2x, f2y;

	int32_t r = size / 2;
	double size1 = 1.0 / (double)size;	//�ȼ��㵹��,��������ɳ˷�
	//int32_t width, height, pitch;
	//int32_t width = ImageGetWidth(image);
	//int32_t height = ImageGetHeight(image);
	//int32_t pitch = ImageGetPitch(image);
	//uint8_t *pDst = ImageGetBuffer(image);
 
	//unsigned char *pSrc;
	unsigned char *pS;
 
	int32_t tempD;
	int32_t i;
	double min_cur, max_cur;		//������������ʵ����,��Сֵ
	double hn, hd;	//����, ��ĸ
	double H, H1, H2;
	//double *cur_value = (double *)malloc(sizeof(double)*width*height);	//ÿ������ֵ������


	//ѭ������ÿ������ֵ,���洢��cur_value��
	//for (y = size; y < height - size; y++) {
	for (y = 0; y < height; y++) {
		temp = pitch * y;
		//for (x = size; x < width - size; x++) {
		for (x = 0; x < width; x++) {
			if (y < size || y >= height - size ||\
				x < size || x >= width - size) {
				*(cur_value + temp + x) = 0.0;
				continue;
			}
			//if (y < 30 || x < 25 || x > width - 25) {
			//	*(cur_value + temp + x) = 0.0;
			//	continue;
			//}
			pS = pSrc + temp + x;

			//����һ��,���׵���
			fx  = (*(pS - r) - *(pS + r)) * (size1);
			fy  = (*(pS - pitch * r) - *(pS + pitch * r)) * (size1);
			fxx = ((*pS + *pS - *(pS + size) - *(pS - size)) * (size1));
			fyy = ((*pS + *pS - *(pS + pitch * size) - *(pS - pitch * size)) * (size1));
			fxy = ((*(pS - pitch * r + r) + *(pS + pitch * r - r))-(*(pS - pitch * r - r) + *(pS + pitch * r + r)));
			fxy = fxy*size1;
		  
			f2x = fx * fx;
			f2y = fy * fy;

			//ƽ������
			if (cur_type == CUR_MEAN) {
				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//������1, 2
			if (cur_type == CUR_PRI1 || cur_type == CUR_PRI2) {
				//ƽ������
				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H1 = (hn / hd);
				else
					H1 = 0;

				//��˹����
				hn = fxx * fyy - fxy*fxy;
				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
				if (hd != 0)
					H2 = (hn / hd);
				else
					H2 = 0;

				if (cur_type == CUR_PRI1)
					H = H1 + sqrt((double)(H1*H1 - H2));
				else
					H = H1 - sqrt((double)(H1*H1 - H2));
			}

			//��˹����
			if (cur_type == CUR_GAUS) {
				hn = fxx * fyy - fxy*fxy;
				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//��������
			if (cur_type == CUR_TEND) {
				hn  = (fxx*f2x + fyy*f2y + 2.0*fx*fy*fxy);
				hd  = (f2x+f2y)*(1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//��������
			if (cur_type == CUR_STRI) {
				hn  = (fxx*f2y + fyy*f2x - 2.0*fx*fy*fxy);
				hd  = (f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//Kmax,Kmin
			if (cur_type == CUR_MAX || cur_type == CUR_MIN) {
				hn  = (fxx + fyy) * 0.5;
				hd  = sqrt((double)((fxx-fyy)*(fxx-fyy)*0.25 + fxy*fxy));
				if (cur_type == CUR_MAX)
					H = hn + hd;
				else
					H = hn - hd;
			}

			*(cur_value + temp + x) = (H);	//�洢ÿ������ֵ
		}
	}

	//��ȡ���е����ʵ����,��С����
	min_cur = 0;	
	max_cur = 0;

	//ֱ���������Сֵ��Ϊ���ʵķ�Χ
	if (thr_type == 0) {
		for (i = 0; i < width * height; i++) {
			if (cur_value[i] < min_cur) {
				min_cur = cur_value[i];
			}
			if (cur_value[i] > max_cur) {
				max_cur = cur_value[i];
			}
		}
	}

	//�Ҷȱ任�������ʵķ�Χֱ��ӳ�䵽0-255
	//if (thr_type == 0 || thr_type == 1) {
		for (y = 0; y < height; y++) {
			temp = pitch * y;
			for (x = 0; x < width; x++) {
				if (y < size || y >= height - size ||\
					x < size || x >= width - size) {
					*(pDst + temp + x ) = 0;
					continue;
				}
				if (thr_type == 1 || thr_type == 0) {
					if (cur_value[temp + x] <= min_cur) {
						tempD = 0;
					} 
					else if (cur_value[temp + x] >= max_cur) {
						tempD = 255;
					} 
					else if ((cur_value[temp+x] <= min_cur/15.0)) {
						if (cur_value[temp+x] <= min_cur/2.0)
							tempD = 0;
						else
							tempD = (int32_t)((cur_value[temp+x]+cur_value[temp+x]-min_cur)*256.0/(max_cur-min_cur));
					}
					else {
						tempD = (int32_t)((cur_value[temp + x]*2.0-min_cur) * 256.0 / (max_cur-min_cur));
					}
				}

				if (tempD < 0)
					tempD = 0;
				if (tempD > 255)
					tempD = 255;
				*(pDst + temp + x) = tempD;
			}
		}
	//}

	////�ͷ�
	//if (cur_value != NULL) {
	//	free(cur_value);
	//	cur_value = NULL;
	//}

}

//void CurvatureSegmentV1
//(
// uint8_t *pDst,
// uint8_t *pSrc,
// uint8_t *pSeg,
// int32_t cur_type, 
// int32_t size, 
// int32_t thr_type,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x, y;
//	int32_t temp;
//	double fx, fy, fxx, fxy, fyy, f2x, f2y;
//
//	int32_t r = size / 2;
//	double size1 = 1.0 / (double)size;	//�ȼ��㵹��,��������ɳ˷�
//
//	unsigned char *pS;
// 
//	int32_t tempD;
//	int32_t i;
//	double min_cur, max_cur;		//������������ʵ����,��Сֵ
//	double hn, hd;	//����, ��ĸ
//	double H, H1, H2;
//	//double *cur_value = (double *)malloc(sizeof(double)*width*height);	//ÿ������ֵ������
//
//
//	//ѭ������ÿ������ֵ,���洢��cur_value��
//	for (y = 0; y < height; y++) {
//		temp = pitch * y;
//		for (x = 0; x < width; x++) {
//			if (y < size || y >= height - size ||\
//				x < size || x >= width - size) {
//				*(cur_value + temp + x) = 0.0;
//				continue;
//			}
//			if (*(pSeg + temp + x) == 255) {
//				*(cur_value + temp + x) = 0.0;
//				continue;
//			}
//			pS = pSrc + temp + x;
//
//			//����һ��,���׵���
//			fx  = (*(pS - r) - *(pS + r)) * (size1);
//			fy  = (*(pS - pitch * r) - *(pS + pitch * r)) * (size1);
//			fxx = ((*pS + *pS - *(pS + size) - *(pS - size)) * (size1));
//			fyy = ((*pS + *pS - *(pS + pitch * size) - *(pS - pitch * size)) * (size1));
//			fxy = ((*(pS - pitch * r + r) + *(pS + pitch * r - r))-(*(pS - pitch * r - r) + *(pS + pitch * r + r)));
//			fxy = fxy*size1;
//		  
//			f2x = fx * fx;
//			f2y = fy * fy;
//
//			//ƽ������
//			if (cur_type == CUR_MEAN) {
//				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
//				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
//				if (hd != 0)
//					H = (hn / hd);
//				else
//					H = 0;
//			}
//
//			//������1, 2
//			if (cur_type == CUR_PRI1 || cur_type == CUR_PRI2) {
//				//ƽ������
//				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
//				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
//				if (hd != 0)
//					H1 = (hn / hd);
//				else
//					H1 = 0;
//
//				//��˹����
//				hn = fxx * fyy - fxy*fxy;
//				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
//				if (hd != 0)
//					H2 = (hn / hd);
//				else
//					H2 = 0;
//
//				if (cur_type == CUR_PRI1)
//					H = H1 + sqrt((double)(H1*H1 - H2));
//				else
//					H = H1 - sqrt((double)(H1*H1 - H2));
//			}
//
//			//��˹����
//			if (cur_type == CUR_GAUS) {
//				hn = fxx * fyy - fxy*fxy;
//				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
//				if (hd != 0)
//					H = (hn / hd);
//				else
//					H = 0;
//			}
//
//			*(cur_value + temp + x) = (H);	//�洢ÿ������ֵ
//		}
//	}
//
//	//��ȡ���е����ʵ����,��С����
//	min_cur = 0;	
//	max_cur = 0;
//
//	//ֱ���������Сֵ��Ϊ���ʵķ�Χ
//	if (thr_type == 0) {
//		for (i = 0; i < width * height; i++) {
//			if (cur_value[i] < min_cur) {
//				min_cur = cur_value[i];
//			}
//			if (cur_value[i] > max_cur) {
//				max_cur = cur_value[i];
//			}
//		}
//	}
//
//	//�Ҷȱ任�������ʵķ�Χֱ��ӳ�䵽0-255
//	//if (thr_type == 0 || thr_type == 1) {
//		for (y = 0; y < height; y++) {
//			temp = pitch * y;
//			for (x = 0; x < width; x++) {
//				if (y < size || y >= height - size ||\
//					x < size || x >= width - size) {
//					*(pDst + temp + x ) = 0;
//					continue;
//				}
//				if (*(pSeg + temp + x) == 255) {
//					*(pDst + temp + x ) = 0;
//					continue;
//				}
//
//				if (thr_type == 1 || thr_type == 0) {
//					if (cur_value[temp + x] <= min_cur) {
//						tempD = 0;
//					} 
//					else if (cur_value[temp + x] >= max_cur) {
//						tempD = 255;
//					} 
//					else if ((cur_value[temp+x] <= min_cur/15.0)) {
//						if (cur_value[temp+x] <= min_cur/2.0)
//							tempD = 0;
//						else
//							tempD = (int32_t)((cur_value[temp+x]+cur_value[temp+x]-min_cur)*256.0/(max_cur-min_cur));
//					}
//					else {
//						tempD = (int32_t)((cur_value[temp + x]*2.0-min_cur) * 256.0 / (max_cur-min_cur));
//					}
//				}
//
//				if (tempD < 0)
//					tempD = 0;
//				if (tempD > 255)
//					tempD = 255;
//				*(pDst + temp + x) = tempD;
//			}
//		}
//
//}



/******************************************************************************
*******************************************************************************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
*******************************************************************************
******************************************************************************/


//#define UP_EDGE			12
//#define DOWN_EDGE		FP_HEIGHT - 10
//#define LEFT_EDGE		27
//#define RIGHT_EDGE		FP_WIDTH - 10
//
////ȥ��ָ��ͼ���Ե���ĺڱ�
//void FPBlackSegment
//(
// //uint8_t *pDst,
// uint8_t *pSrc,
// //uint8_t *pGrads,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x, y;
//	int32_t tempY = 0;
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if ((y >= UP_EDGE) && (y <= DOWN_EDGE) && \
//				(x >= LEFT_EDGE) && ( x <= RIGHT_EDGE)) {
//				continue;
//			} 
//			*(pSrc + tempY + x) = 255;
//			//*(pGrads + tempY + x) = 0;
//		}
//		tempY += pitch;
//	}
//}
//
//
//#define UP_EDGE_ORG			35
//#define DOWN_EDGE_ORG		FP_HEIGHT_ORG - 30
//#define LEFT_EDGE_ORG		70
//#define RIGHT_EDGE_ORG		FP_WIDTH_ORG - 30
//
////ȥ��ָ��ͼ���Ե���ĺڱ�
//void FPBlackSegmentOrg
//(
// //uint8_t *pDst,
// uint8_t *pSrc,
// //uint8_t *pGrads,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x, y;
//	int32_t tempY = 0;
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if ((y >= UP_EDGE_ORG) && (y <= DOWN_EDGE_ORG) && \
//				(x >= LEFT_EDGE_ORG) && ( x <= RIGHT_EDGE_ORG)) {
//				continue;
//			} 
//			*(pSrc + tempY + x) = 255;
//			//*(pGrads + tempY + x) = 0;
//		}
//		tempY += pitch;
//	}
//}


/******************************************************************************
  * ���ܣ������ݶȶ�ָ��ͼ�����ݽ���ǰ���뱳���Ĵַָ�
  * ������pSrc			���ָ��ͼ������(�ָ��,����������255)[Out]
  *       pOrientation	���ָ�ķ���(�ָ��,������������255)[Out]
  *		  pGrads		���ָ�ͼ����ݶ�(�����ж����ص���ǰ�����Ǳ���)[In]
  *       size			���ݶȽ�����(ƽ��)���ڴ�С(2*r+1)
  *		  step			���ݶȽ�����(ƽ��)�Ĳ���
  *		  threshold		�ָ���ֵ(�����ص���ݶȷ�ֵ��֮�Ƚ�)
  *		  width			ͼ�����ݿ��
  *		  height		ͼ�����ݸ߶�
  *		  pitch			ͼ������ÿ���ֽ���
  * ���أ�������
  *	˵��: ָ��ͼ���ǰ��������ݶ�һ�㶼�Ƚϴ�(�ڰ������������),�����������ݶȶ��Ƚ�
  *		  С.��������ݶȽ��и߶�ƽ��,ȥ���ݶ�ͼ�������,Ȼ�����ʵ�����ֵ�Ϳ����ж�
  *		  �õ�Ϊǰ�����Ǳ���.ȷ����ֵ�Ĳ�������:
  *		  1.��ֵ��ѡ����ͼ�������й�.���ڹ�ѧͼ��,��Ϊ�Ƚ�ƽ��,������ֵA�Ƚ�С,ͨ��
  *			ȡ30-40.���ͼ�񲻹�ƽ��,������ȶ�ͼ�����ƽ������,������ֵ��Լȡ50����
  *			(�������ʱȡ��80)
  *		  2.�õ�λ�����ϵ��ݶ���ֵ��Ϊ�Ҷ��ݶ�����,���ݶȷ�ֵT(x,y),��Ҫ���㵥λ����
  *			�ڵ�ƽ���ݶ���Ϊ��������ݶȷ�ֵ,�����ݶȷ�ֵ����ƽ��(��)�˲�
  *		  3.��:T(x,y)>A,��(x,y)��ǰ����,�����ڱ���
  * �㷨: 
  *		  1.���ô˺���ǰ,����Ҫ�ȼ�������ָ��ͼ����ݶ�ֵpGrads
  *		  2.��������:
  *			(1)�ȶ��ݶ�ֵ����ƽ���˲�
  *			(2)���߽��ݶ���Ϊ255(ǰ��),���ԷǱ߽���������threshold���зָ�,��ÿ���
  *			   �ݶ�ֵ��Ϊ0(����)��255(ǰ��)
  *			(3)�ж�ǰ�����򲻻�̫С,���򷵻ش���
  *			(4)���ݷָ����ݶ�ֵ0(����)�ֱ��ָ��ͼ�����ݺͷ���������255(����)
******************************************************************************/
FunError_t FPGradsRSegment
(
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 uint8_t *pGrads, 
 const int32_t size, 
 const int32_t step, 
 const int32_t threshold, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
)
{
	//int32_t	x, y;
	////int32_t r = size / 2;
	//int32_t num = 0;
	//int32_t tempY;
	//
	//BufferCopyV1(fp_src_copy.pimg, pGrads, FP_WH_SIZE);
	////BufferCopy32(fp_src_copy.pimg, pGrads, FP_WH_SIZE32);
	//
	//// �Է��򳡷�ֵͼ����и߶�ƽ���˲�
	////SoftenMean(pGrads, pFPTemp, width, height, pitch, size, step);
	//MeanSmooth(pGrads, fp_src_copy.pimg, width, height, pitch, size, step);

	//// ͼ���Ե������Ϊ����
	//for (y = 0; y < height; y++) {
	//	*(pGrads + y*pitch) = 255;
	//	*(pGrads + y*pitch + pitch - 1) = 255;			//��Ե����Ϊ����(��ɫ)
	//}
	//for (x = 0; x < width; x++) {
	//	*(pGrads + x) = 255;
	//	*(pGrads + (height-1)*pitch + x) = 255;			//��Ե����Ϊ����(��ɫ)
	//}

	//for (y = 1; y < height-1; y++) {
	//	for (x = 1; x < width-1; x++) {
	//		//if ((y < UP_EDGE) || (y > DOWN_EDGE) || \
	//		//	(x < LEFT_EDGE) || ( x > RIGHT_EDGE)) {
	//		//	*(pGrads + y*pitch + x) = 0;			//������Ϊ��ɫ
	//		//} else {
	//		// ���ݷ�ֵ����ֵ��С�ж��Ƿ�Ϊ��������
	//			if(*(pGrads + y*pitch + x) < threshold) {
	//				*(pGrads + y*pitch + x) = 0;			//������Ϊ��ɫ
	//			} else {
	//				*(pGrads + y*pitch + x) = 255;			//ǰ����Ϊ��ɫ
	//				num++;
	//			}
	//		//}
	//	}
	//}

	//// ���ǰ���������С���������ʮ��֮һ�����ʾǰ������̫С�����ش���
	//if(num < height * width/10)
	//	return FunFailure;

	////�������
	//tempY = 0;
	//for (y = 0; y < height; y++) {
	//	//�Ż�ǰ:
	//	//tempY = y * pitch;
	//	for (x = 0; x < width; x++) {	
	//		// ����Ǳ����������øõ�ҶȺͷ���Ϊ�׵�
	//		if (*(pGrads + tempY + x) == 0) {
	//			*(pSrc + tempY + x) = 255;					//��Ե����Ϊ����(��ɫ)	
	//			*(pOrientation + tempY + x) = 255;			//��Ե����Ϊ����(��ɫ)
	//		}
	//	}
	//	//�Ż���
	//	tempY += pitch;
	//}
	//return FunOK;
	int32_t	x, y;
	//int32_t r = size / 2;
	int32_t num = 0;
	int32_t tempY;

	BufferCopyV1(fp_src_copy.pimg, pGrads, FP_WH_SIZE);
	//BufferCopy32(fp_src_copy.pimg, pGrads, FP_WH_SIZE32);

	// �Է��򳡷�ֵͼ����и߶�ƽ���˲�
	//SoftenMean(pGrads, pFPTemp, width, height, pitch, size, step);
	MeanSmooth(pGrads, fp_src_copy.pimg, width, height, pitch, size, step);

	// ͼ���Ե������Ϊ����
	for (y = 0; y < height; y++) {
		*(pGrads + y*pitch) = 255;
		*(pGrads + y*pitch + pitch - 1) = 255;			//��Ե����Ϊ����(��ɫ)
	}
	for (x = 0; x < width; x++) {
		*(pGrads + x) = 255;
		*(pGrads + (height-1)*pitch + x) = 255;			//��Ե����Ϊ����(��ɫ)
	}

	for (y = 1; y < height-1; y++) {
		tempY = y*pitch;
		for (x = 1; x < width-1; x++) {
			//if ((y < UP_EDGE) || (y > DOWN_EDGE) || \
			//	(x < LEFT_EDGE) || ( x > RIGHT_EDGE)) {
			//	*(pGrads + y*pitch + x) = 0;			//������Ϊ��ɫ
			//} else {
			// ���ݷ�ֵ����ֵ��С�ж��Ƿ�Ϊ��������
			//if(*(pGrads + y*pitch + x) < threshold) {
			//	*(pGrads + y*pitch + x) = 0;			//������Ϊ��ɫ
			//} else {
			//	*(pGrads + y*pitch + x) = 255;			//ǰ����Ϊ��ɫ
			//	num++;
			//}
			if(*(pGrads + tempY + x) < threshold) {
				*(pGrads + tempY + x) = 0;			//������Ϊ��ɫ
			} else {
				*(pGrads + tempY + x) = 255;			//ǰ����Ϊ��ɫ
				num++;
			}
			//}
		}
	}

	// ���ǰ���������С���������ʮ��֮һ�����ʾǰ������̫С�����ش���
	//if(num < height * width/10)
	//	return FunFailure;

	//�������
	tempY = 0;
	for (y = 0; y < height; y++) {
		//�Ż�ǰ:
		//tempY = y * pitch;
		for (x = 0; x < width; x++) {	
			// ����Ǳ����������øõ�ҶȺͷ���Ϊ�׵�
			if (*(pGrads + tempY + x) == 0) {
				*(pSrc + tempY + x) = 255;					//��Ե����Ϊ����(��ɫ)	
				*(pOrientation + tempY + x) = 255;			//��Ե����Ϊ����(��ɫ)
			}
		}
		//�Ż���
		tempY += pitch;
	}
	return FunOK;

}














