/******************************************************************************
 * �ļ�����image_enhance_filter.h
 * ���ܣ�  һЩ������ͼ����ǿ���˲�����
******************************************************************************/


#include "dip_header/image_enhance_filter.h"


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <string.h>


/******************************************************************************
  * ���ܣ�ͼ��������(ƽ��)������ͨ�������ֵʵ��
  * ������pDst      ƽ��(��)������
  *		  pSrc		��(ƽ��)ǰ����
  *		  width		���ݿ��
  *		  height	���ݸ߶�
  *		  pitch		ÿ���ֽ���
  *       size      ��(ƽ��)���ڴ�С(2*r+1)
  *		  step		��(ƽ��)����
  * ���أ�
******************************************************************************/
void MeanSmooth
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t width,
 const int32_t height,
 const int32_t pitch,
 const int32_t size, 
 const int32_t step
 )
{
	int32_t x,y,r,p,q;
	int32_t sum, num;
	r = size/2;	
	for (y = r; y < height-r; y++) {
		for (x = r; x < width-r; x++) {
			sum = 0;
			num = 0;
			//�Ż�ǰ
			//for (q=-r;q<=r;q+=step) {
			//	for (p=-r;p<=r;p+=step) {
   // 				 sum += pSrc[(x+p)+(y+q)*pitch];
			//		 num++;
			//	}
			//}
			//�Ż���
			for (q = y-r; q <= y+r; q+=step) {
				for (p = x-r; p <= x+r; p+=step) {
					sum += pSrc[p+q*pitch];
					num++;
				}
			}

			pDst[x+y*pitch] = sum/num;
		}
	}
}

/******************************************************************************
  * ���ܣ�ͼ��������(ƽ��)������ͨ�������ֵʵ��
  * ������pDst      ƽ��(��)������
  *		  pSrc		��(ƽ��)ǰ����
  *		  width		���ݿ��
  *		  height	���ݸ߶�
  *		  pitch		ÿ���ֽ���
  *       size      ��(ƽ��)���ڴ�С(2*r+1)
  *		  step		��(ƽ��)����
  * ���أ�
******************************************************************************/
void MeanSmoothV1
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t width,
 const int32_t height,
 const int32_t pitch,
 const int32_t size, 
 const int32_t step
 )
{
	int32_t x,y,r,p,q;
	int32_t sum, num;
	r = size/2;	
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if ((y < r) || (y >= height - r) ||\
				(x < r) || (x >= width - r)) {
				pDst[x+y*pitch] = 0;
				continue;
			}
			sum = 0;
			num = 0;
			//�Ż�ǰ
			//for (q=-r;q<=r;q+=step) {
			//	for (p=-r;p<=r;p+=step) {
   // 				 sum += pSrc[(x+p)+(y+q)*pitch];
			//		 num++;
			//	}
			//}
			//�Ż���
			for (q = y-r; q <= y+r; q+=step) {
				for (p = x-r; p <= x+r; p+=step) {
					sum += pSrc[p+q*pitch];
					num++;
				}
			}

			pDst[x+y*pitch] = sum/num;
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

//7x7����ֿ�ģ��,��ĳ��(x0,y0)Ϊ����,�Ե�������Ϊ
//������λ��12�������ϵĵ��ƫ��(x0,y0)������ֵ(off_x,off_y)
//12:12������ 
//7:7x7ģ�� 
//2:��ʾƫ��(off_x,off_y)����ֵ.ǰ���Ϊoff_x,�����Ϊoff_y
int g_direction_xy[12][7][2] = {
	-3, 0,  -2, 0,  -1, 0,   0, 0,   1, 0,   2, 0,   3, 0,
	-3,-1,  -2,-1,  -1, 0,   0, 0,   1, 0,   2, 1,   3, 1,
	-3,-2,  -2,-1,  -1,-1,   0, 0,   1, 1,   2, 1,   3, 2,
	-3,-3,  -2,-2,  -1,-1,   0, 0,   1, 1,   2, 2,   3, 3,
	-2,-3,  -1,-2,  -1,-1,   0, 0,   1, 1,   1, 2,   2, 3,
	-1,-3,  -1,-2,   0,-1,   0, 0,   0, 1,   1, 2,   1, 3,
	 0,-3,   0,-2,   0,-1,   0, 0,   0, 1,   0, 2,   0, 3,
	-1, 3,  -1, 2,   0, 1,   0, 0,   0,-1,   1,-2,   1,-3,
	-2, 3,  -1, 2,  -1, 1,   0, 0,   1,-1,   1,-2,   2,-3,
	-3, 3,  -2, 2,  -1, 1,   0, 0,   1,-1,   2,-2,   3,-3,
	-3, 2,  -2, 1,  -1, 1,   0, 0,   1,-1,   2,-1,   3,-2,
	-3, 1,  -2, 1,  -1, 0,   0, 0,   1, 0,   2,-1,   3,-1
};

/******************************************************************************
  * ���ܣ��ɽǶ��������,�õ�����Ϊ����ֿ�����(g_direction_xy)������,������
  * ������angle		ĳ������߷���Ƕ�(0-180)
  * ���أ�����
  * ˵��: 
******************************************************************************/
int32_t AngleToDirection(int32_t angle)
{
	if((angle>=173) || (angle<8))
		return 0;
	else
		return ((angle-8)/15 + 1);
}

/******************************************************************************
  * ���ܣ�ͼ�����ݵķ�����ǿ(��GaborС����ǿ�㷨���������ٶ��ݱ����)
  * ������pSrc				����ǿͼ�������ָ��	
  *		  pOrient			��������ָ��(����GetOrientation���)
  *		  width				ͼ����
  *		  height			ͼ��߶�
  *		  pitch				ͼ��ÿ���ֽ���
  * ���أ�������
  * ˵��: 1.���÷��򳡼��㺯������õ�ͼ��ÿ��(x,y)�ķ���
  *		  2.Ȼ����÷�����ǿ����(����ͼ��ǿ��С����ǿ)��ͼ����з�����ǿ,
  *		  3.���յõ�������ǿ���ͼ��.
  *		  ����ָ��ͼ�񳡳��ۺ�GaborС����������,�����ͼ���������ǿ����.
  *			����ָ��ͼ�񳡳��ۿ��Ի��"����"��"Ƶ�ʳ�"
  *			����GaborС������,�����ڸ�λ�÷����϶�ͼ�������ǿ,���ֲ�ͼ����
  *			���ߵĶ��ѵȲ���.
  * �㷨: 
  *		  1.��÷�������.�����Ĳ���pOrient��Ϊ��������,���Ҫȷ���ȼ���
  *		    �õ�pOrient(����GetOrientation���)
  *		  2.��pOrient���ݵõ�ÿ������߽Ƕ�,������AngleToDirection�����������
  *		    ����
  *		  3.�����߷����g_direction_xy�����������������,��ö�Ӧ�����ϵ������
  *		  4.�ֱ�����ƽ���˲���Hw��Vw������ˮƽ�������ƽ���˲�,��ֱ���������
  *			�˲�.
  *	�ܽ�: ��ÿһ�����Gabor��������,����ʵ��������ǿ��Ч��.��:
  *		  ImageEnhanceGabor�Ⱥ���.
  *       �����㷨(ģ���С�̶�7x7):
  *			  (1)Ϊ�˼ӿ��ٶ�,��Gabor�����Ƴ�ģ��,��ģ�������Gabor����,��:
  *		         �����OrientEnhance����.
  *			  (2)����ΪGabor����ģ������Ҳ�ܺ�ʱ,�ʽ�����ģ���Ϊ�����ཻ��
  *			     �߶���ģ��,������ģ������,��������С�ܶ�.
  *			  (3)�����õ��������˲�ģ����:		Hw=1/7( 1, 1,1,1,1, 1, 1)
  *							 �����˲�(��)ģ����	Vw=1/7(-3,-1,3,9,3,-1,-3)
  *	P.S.: ����OrientBinary��ʵ����֮����
******************************************************************************/
void OrientEnhance
(
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 const int32_t width, 
 const int32_t height,
 const int32_t pitch 
)
{
	int32_t x, y;
	int32_t i;
	int32_t d = 0;
	int32_t sum = 0;
	// ���߷����Ͻ���ƽ���˲���ƽ���˲���
	int32_t Hw[7] = {1, 1, 1, 1, 1, 1, 1};
	// ���߷���Ĵ�ֱ�����Ͻ������˲������˲���
	int32_t Vw[7] = {-3, -1, 3, 9, 3, -1, -3};
	int32_t hsum = 0;
	int32_t vsum = 0;
	int32_t tempY = 0;
	uint8_t  *pS;
	uint8_t  *pOri;
	//uint8_t pFPTemp[FP_HEIGHT*FP_WIDTH];
	uint8_t *pFPTemp = fp_src_copy.pimg;

	//uint8_t *pFPTemp = new uint8_t[width * height];
	//uint8_t *pFPTemp = (uint8_t *)malloc(sizeof(uint8_t)*width*height);

	// ���߷����Ͻ���ƽ���˲�
	tempY = 0;
	for(y = 0; y < height; y++) {
		//�Ż�ǰ
		//tempY = y*pitch;	
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = pSrc + tempY + x;
			// ���߷��������
			d = AngleToDirection(*pOri);
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++) {
				//��ֹԽ��
				if((y+g_direction_xy[d][i][1] < 0) ||\
				   (y+g_direction_xy[d][i][1] >= height) ||\
				   (x+g_direction_xy[d][i][0] < 0) ||\
				   (x+g_direction_xy[d][i][0] >= width)) {
					continue;
				}
				sum += Hw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0) {
				*(pFPTemp + tempY + x) = (uint8_t)(sum/hsum);
			} else {
				*(pFPTemp + tempY + x) = 255;			//��Ե����Ϊ����(��ɫ)
			}
		}
		//�Ż���
		tempY += pitch;
	}

	// ���߷���Ĵ�ֱ�����Ͻ������˲�
	tempY = 0;
	for(y = 0; y < height; y++) {
		//�Ż�ǰ
		//tempY = y*pitch;
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = fp_src_copy.pimg + tempY + x;//pFPTemp + tempY + x;	
			// ���߷���Ĵ�ֱ���������
			d = (AngleToDirection(*pOri)+6) % 12;
			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++) {
				//��ֹԽ��
				if((y+g_direction_xy[d][i][1] < 0) ||\
				   (y+g_direction_xy[d][i][1] >= height) ||\
				   (x+g_direction_xy[d][i][0] < 0) ||\
				   (x+g_direction_xy[d][i][0] >= width)) {
					continue;
				}
				sum += Vw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum > 0) {
				sum /= vsum;
				if(sum > 255) {
					*(pSrc + tempY + x) = 255;			//��Ե����Ϊ����(��ɫ)
				} else if(sum < 0) {
					*(pSrc + tempY + x) = 0;
				} else {
					*(pSrc + tempY + x) = (uint8_t)sum;
				}
			} else {
				*(pSrc + tempY + x) = 255;				//��Ե����Ϊ����(��ɫ)
			}
		}
		//�Ż���
		tempY += pitch;
	}

	//if (pFPTemp != NULL) {
	//	free(pFPTemp);
	//	pFPTemp = NULL;
	//}

}

