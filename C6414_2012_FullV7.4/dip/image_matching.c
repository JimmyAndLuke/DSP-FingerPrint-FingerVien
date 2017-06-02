/******************************************************************************
 * �ļ�����image_matching.c
 * ��  �ܣ�һЩ������ͼ��ƥ�����
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "dip_header/image_matching.h"
#include "dip_header/base_fun.h"

//#include "../../bsp/bsp_header/z_mytype.h"


/******************************************************************************
  * ���ܣ�����ͬ��(�ߴ�����һ��)ͼ���ģ��ƥ��
  * ������pSrc				ƥ��ͼ������
  *		  pTmplt			ģ��ͼ������
  *       match_percent		ƥ��Ȱٷֱ�(���ڲ���)
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  * ���أ�������
  * ˵��: 
  * �㷨:
******************************************************************************/
//FunError_t ImageTemplateMatching
//(
// uint8_t *pSrc,
// uint8_t *pTmplt,
// int32_t *match_percent,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
//)
//{	
//	int32_t x, y, count, percent, temp;
//	int32_t tempY;
//	uint8_t *pS, *pD;
//
//	count = 0;
//	percent = 0;
//	tempY = 0;
//	for (y = 0; y < height; y++) {
//		pS = pSrc + tempY;
//		pD = pTmplt + tempY;
//		for (x = 0; x < width; x++) {
//			count += *(pS + x);
//			percent += ((*(pS+x)) & (*(pD+x)));	
//		}
//		tempY += pitch;
//	}
//
//	temp = (percent*100)/count;
//	*(match_percent) = temp; 
//
//	//printf("ƥ����:%d, ����:%d, ƥ��ٷֱ�:%d\n", percent, count, temp); 
//	return FunOK;
//}

FunError_t ImageTemplateMatchingV1
(
 uint8_t *pSrc,
 uint8_t *pTmplt,
 int32_t *match_percent,
 int32_t r_x,
 int32_t step_x,
 int32_t r_y,
 int32_t step_y,
 int32_t angle,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{	
	int32_t x, y, i, j, count, percent, temp, max_percent;
	//int32_t tempY;
	uint8_t *pS, *pD;
#if 0	
	int32_t k;
	double sinv, cosv;
	int32_t j1, i1;
	pS = pSrc;
	pD = pTmplt;
	max_percent = 0;
	for (k = -angle; k <= angle; k++) {
		sinv = sin(k*M_PI/180.0);
		cosv = cos(k*M_PI/180.0);
		for (j = -r_y; j <= r_y; j += step_y) {
			for (i = -r_x ; i <= r_x; i += step_x) {
				count = 0;
				percent = 0;
				for (y = 0; y < height; y++) {
					for (x = 0; x < width; x++) {
						j1 = (int32_t)((y+j)*cosv - (x+i)*sinv);
						i1 = (int32_t)((y+j)*sinv + (x+i)*cosv);
						if (j1 < 0 || j1 >= height || i1 < 0 || i1 >= width) {
							continue;
						}
						count += *(pS + j1*pitch + i1);
						percent += ((*(pS + j1*pitch + i1)) & (*(pD+y*pitch+x)));	
					}
				} 
				temp = (percent*100)/count;
				if (temp > max_percent) {
					max_percent = temp;
				}
			}
		}
	}
#endif

#if 1
	max_percent = 0;
	for (j = -r_y; j <= r_y; j += step_y) {
		for (i = -r_x ; i <= r_x; i += step_x) {
			count = 0;
			percent = 0;
			for (y = 0; y < height; y++) {
				if ((y+j)<0 || (y+j)>=height) {
					continue;
				}
				pS = pSrc + (y+j)*pitch;
				pD = pTmplt + y*pitch;
				for (x = 0; x < width; x++) {
					if ((x+i)<0 || (x+i)>=width) {
						continue;
					}
					count += *(pS + x + i);
					percent += ((*(pS+x+i)) & (*(pD+x)));	
				}
			} 
			temp = (percent*100)/count;
			if (temp > max_percent) {
				max_percent = temp;
			}
		}
	}
#endif

	*(match_percent) = max_percent; 

	//printf("ƥ��ٷֱ�:%d\n",  max_percent); 
	return FunOK;
}

/******************************************************************************
  * ���ܣ�����ͬ��(�ߴ�����һ��)ͼ���ģ��ƥ��
  * ������pSrc				ƥ��ͼ������
  *       minutia1			��ƥ��ͼ����ȡ��ϸ�ڵ�
  *       minutiaT			ģ��ͼ���ϸ�ڵ�
  *       size				ϸ�ڵ�ƽ�Ƴߴ�
  *       pm_type			��ʱû����
  *       match_percent		ƥ��ٷֱ�(���ڲ���)
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  * ���أ�������
  * ˵��: ��ģ��ͼ���ϸ�ڵ����ͺ�����ƥ��ͼ�����غ϶�,������ٷֱ�
  * �㷨: ͨ���ƶ�ġ��ϸ�ڵ�,����������ƥ��ͼ���ϵ��غ϶�,�ҳ�ƽ��ϸ�ڵ��
  *		  �õ��������غ϶ȵ����ֵ��Ϊ��ģ��ͼ�����ƥ��ͼ����غ϶�,���
  *		  �����ƥ��ٷֱ�
******************************************************************************/
//FunError_t ImagePointMatching
//(
// uint8_t *pSrc,
// pFVMinutiaSet_t minutia, 
// pFVMinutiaSet_t minutiaT,
// const int32_t size,
// const int32_t pm_type,
// int32_t *match_percent,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
//)
//{
//	int32_t i , x, y, u, v;
//	int32_t r;
//	int32_t cnt_temp, cnt_max;	//�����ƥ�����Ŀ��ʱֵ�����ֵ
//	int32_t percent;			//���ݿ�˽����ƥ��İٷֱ�
//	int32_t percentT;			//ƥ��˽����ƥ��İٷֱ�
//	int32_t n, nT;				//�����㼯A,B�ĵ��� 
//
//	r = size / 2;
//	//��ȡnA,nB,minutiaA->FPMinutiaArr,minB
//	n = minutia->nbminutia;
//	nT = minutiaT->nbminutia;
//
//	cnt_temp = 0;
//	cnt_max = 0;
//	percent = 0;
//	percentT = 0;
//
//	//����,����غ϶�
//	for (u=-r; u<=r; u++) {
//		for (v=-r; v<=r; v++) {
//			for (i=0; i<nT; i++) {
//				x = minutiaT->FVMinutiaArr[i].x + v;
//				y = minutiaT->FVMinutiaArr[i].y + u;
//				//��ֹԽ��
//				if (x < 0 || x >= width ||\
//					y < 0 || y >= height) {
//					continue;
//				}
//
//				if (pSrc[y*pitch + x] == 1) {
//					cnt_temp++;
//				}
//			}
//			if (cnt_temp>cnt_max) {
//				cnt_max = cnt_temp;
//			}
//			cnt_temp = 0;
//		}
//	}
//
//	//����ƥ���
//	cnt_max *= 100;
//	//�������ݿ�˺�ƥ��ε�ƥ��ٷֱ�
//	percent   = cnt_max / n;
//	percentT = cnt_max / nT;
//	//����Ȩ�ظ�һ��
//	(*match_percent) = (percent>>1) + (percentT>>1);
//
//	return FunOK;
//}

/******************************************************************************
  * ���ܣ����㵥��Hausdorff����(�ײ㺯��)
  * ������A			�㼯A
  *       B			�㼯B
  *       nA		�㼯A�ĵ���
  *       nB		�㼯B�ĵ���
  *       hd_type	���ּ���Hausdorff������㷨
  *       pos_aB	���е㵽�㼯����D_aB��������ĵ�pos_aB��(ȡֵ0-nA)
  *					��:CHD�㷨
  *       pos_AB	���е㼯���㼯����d_AB��������ĵ�pos_AB��(ȡֵ0-nA),
  *					��:PHD,CHD,LTS-HD
  *       d_thr		�㼯���㼯����ֵ,��d_AB>d_thr,����d_AB=d_thr,��M-HD
  * ���أ�����Hausdorff����(h_AB)
  * ˵��: pos_aB,pos_AB,d_thr������������������hd_type�����õ�.����d_thr��ֻ��
  *		  M-HD�㷨��Ч.����ʱ��,������ȡ�κ�ֵ
  * �㷨:
  *		  ����HD��������:
  *			��֪�����㼯A={a1,a2,...,anA},B={b1,b2,...,bnB},nA��nB�ֱ���
  *			�㼯A,B�е�ĸ���,�������㼯֮���HD���붨��Ϊ:
  *			H(A,B) = max(h(A,B),h(B,A))								(1)
  *			����h(A,B) = max(min(||a-b||)) = max(D(a,B))			(2)
  *						 a(A b(B             a(A
  *				h(B,A) = max(min(||b-a||)) = max(D(b,A))			(3)
  *					     b(B a(A             b(B
  *			ע��:x(X��ʾx����X
  *				 d��d(a,b)��ʾ�㵽�����
  *				 D��D(a,B)��ʾ�㵽�㼯����
  *				 h��h(A,B)��ʾ�㼯���㼯����
  *			ʽ(1)��Ϊ˫��HD,ʽ(2),(3)�ֱ��Ϊ�ӵ㼯A���㼯B�ʹӵ㼯B���㼯A��
  *			����HD.��������˵���HD�Ϳ���ͨ��ȡ���ߵ����ֵ�õ�˫��HD��.
  *		  �����Ľ�HD�㷨����:
  *			PHD(Partial HD):
  *				�����е㵽�㼯����(D)��С��������,ȡ��k������ֵ��ΪPHD�ĵ���HD(h)	
  *			CHD(Censored HD):
  *				���Ƚ�����A������һ�㵽����B�����е�ľ���(d)��С����
  *				����, ȡ��q��������Ϊ�õ㵽����B�ľ���, 
  *				Ȼ�����м���A�еĵ㵽����B�ľ���(D)��С��������, 
  *				ȡ��p��������Ϊ����A������B�ĵ���HD
  *			MHD(Modified HD):
  *				�����е㵽�㼯����С����(D)��ƽ����Ϊ����HD. 
  *				MHD������Ч�ֿ���������,�������ں������ŵ����ܲ�����
  *			M-HD(M-estimation HD):
  *				�������̶��趨��ֵ�ĵ㵽�㼯����С����ֵ����̶�ֵ,
  *				Ȼ����ȡƽ����Ϊ����HD,�Ա������ڲ����������ص������ƫ��
  *			LTS-HD:
  *				���㵽�㼯�ľ�������, ȡǰh����ƽ��ֵ��Ϊ����HD, 
  *				�������������ڵ����ߴ��������ŵ�ͼ���нϺõ�Ч��
  *			WHD:(Weighted HD):
  *				���ݸ�������λ�ö�ͼ��ƥ��Ĳ�ͬ��Ҫ�Ը��費ͬ��Ȩֵ.
  *			�����㷨:
  *				1.Ϊ��С�����ĸ���,���������3x3�Ĵ��ڽ���ֵͼ��ת��Ϊ�Ҷ�ͼ��, 
  *				�ԻҶ�ͼ�����HD�ķ���;
  *				2.�������ƶȼ�Ȩ������ӦHD�㷨��
  *		  �㷨����:���ݾ���HD�Ķ���,����HD��Ҫ��Ϊ3��:
  *			1.����㵽��ľ���(d)
  *			2.����㵽�㼯�ľ���(D)
  *			3.����㼯���㼯�ľ���(h)
  *		  ���ָĽ��㷨�Ĺ�����༯���ڲ���3,ֻ��CHD�Բ���2���иĽ�.
  *		  ���ݵ�3���ļ��㷽��, ���Խ� HD �Ķ���������Ϊ��������. 
  *			1)ֱ��ȡĳһ���㵽�㼯�ľ���ֵ��Ϊ���� HD, �羭�� HD��PHD��CHD��
  *			  ���෽�����ڹ���������ĳһ���㵽�㼯�ľ���ֵ
  *			  ��������ܵ��������ڵ��ĸ���, ³���Բ�.
  *  		2)ȡĳһ���ֵ㵽�㼯�ľ���ֵ���㵥��HD, ��M-HD
  *			  �� LTS-HD. ���ڱ��ڵ����ֵĵ㵽�㼯����С��
  *			  ���ܵ����źܴ�, ���෽��ͨ����ȥ�Ƚϴ�ĵ㵽
  *			  �㼯����С����ֵ, �Ӷ�����˴����ڵ�ʱ�㷨��³����. 		
  *  		3) ������㵽�㼯�ľ����ƽ��ֵ��Ϊ���� HD, 
  *			  ��MHD��LTS-HD��M-HD��WHD,ȡ�㵽�㼯��ƽ����С������
  *			  �ֿ��������ŵ���Ч����,��ǿ���㷨��³����.	 
  *			ʵ����, ȡ���ֵ㵽�㼯����С�����ȡ�㵽�㼯��
  *		  ƽ����С������һ�Ի���ì�ܵ�����. ȡ���ֵ㵽�㼯�ľ���
  *		  ����Ҫ�����ܵ��޳����ŵ�, �������޳����ŵ��ͬʱ,
  *		  ��Ȼ�����˿����õĵ㵽�㼯��С����ĸ���,
  *		  �Ӷ��������㷨���ȶ���. ȡ�㵽�㼯��ƽ����С��������һ������, 
  *		  �����������е㵽�㼯����С����ֵ, �����ܱ�֤�㷨��³����,
  *		  �����ܵ��������ڵ��ȸ��ŵĵ㵽�㼯����С����Ҳ��������, 	   
  *		  ����ڼ��㾫���ϲ��ܴﵽ����. ����ķ�����һ�仰��������: 
  *			ȡ���ֵ㵽�㼯����С������ͨ�������㷨�ȶ�������ȡ���㾫
  *		  ��; ȡ�㵽�㼯��ƽ����С������ͨ�����ͼ��㾫������ȡ�㷨³����.
******************************************************************************/
//static int32_t HausdorffDistanceLL
//(
// Point_t *A, 
// Point_t *B, 
// const int32_t nA, 
// const int32_t nB,
// const int32_t hd_type,
// int32_t pos_aB,
// int32_t pos_AB,
// const int32_t d_thr
// )
//{
//	int32_t i, j, k;
//	int32_t dx, dy;
//	int32_t h_AB;
//	int32_t d_ab[FV_MAX_MINUTIA_NUM];
//	int32_t D_aB[FV_MAX_MINUTIA_NUM];
//	//int32_t *d_ab = (int32_t *)malloc(sizeof(int32_t)*nB);	//�㵽��ľ���
//	//int32_t *D_aB = (int32_t *)malloc(sizeof(int32_t)*nA);	//�㵽�㼯�ľ���
//
//	//if (d_ab == NULL || D_aB == NULL) 
//	//	return -1;
//
//	//��ʼ������Ϊ0
//	//for (i = 0; i < FV_MAX_MINUTIA_NUM; i++) {
//	//	d_ab[i] = 0;
//	//	D_aB[i] = 0;
//	//}
//
//	if (pos_aB >= nA) {
//		printf("pos_aB should be less than or equal to nA!\n");
//		pos_aB = nA - 1;
//	}
//	if (pos_AB >= nA) {
//		printf("pos_AB should be less than or equal to nA!\n");
//		pos_AB = nA - 1;
//	}
//
//	for (i = 0; i < nA; i++) {
//		//1.����㵽��ľ���d_ab
//		for (j = 0; j < nB; j++) {
//			//�ӿ�����,�������,������ƽ��
//			dx = A[i].x - B[j].x;
//			dy = A[i].y - B[j].y;
//			d_ab[j] = dx*dx + dy*dy;	
//		}
//		//2.����㵽�㼯�ľ���D_aB
//		if (hd_type == CHD) {					//CHD
//			my_sort((void*)d_ab, nB);
//			D_aB[i] = d_ab[pos_aB];
//		} else {
//			D_aB[i] = d_ab[0];
//			for (k = 1; k < nB; k++) {
//				if (d_ab[k] < D_aB[i])
//					D_aB[i] = d_ab[k];
//			}
//		}
//	}
//
//	//3.����㼯���㼯�ľ���h_AB
//	h_AB = 0;
//	if (hd_type == OHD) {						//����HD�㷨
//		h_AB = D_aB[0];
//		for (k = 1; k < nA; k++) {	//���е㵽�㼯D_aB�����ֵ��Ϊh_AB			
//			if (D_aB[k] > h_AB)
//				h_AB = D_aB[k];
//		}
//	} else if (hd_type == MHD) {				//MHD
//		//h_AB = 0;
//		for (k = 0; k < nA; k++) {	//���е㵽�㼯D_aB��ƽ��ֵ��Ϊh_AB
//			h_AB += D_aB[k];
//		}
//		h_AB /= nA;
//	} else if (hd_type == M_HD) {				//M-HD
//		//h_AB = 0;
//		for (k = 0; k < nA; k++) {	//���е㵽�㼯D_aB��ƽ��ֵ��Ϊh_AB
//			if (D_aB[k] > d_thr)	//�����趨��ֵ�ĸ���̶�ֵ(��ֵ)
//				D_aB[k] = d_thr;
//			h_AB += D_aB[k];
//		}
//		h_AB /= nA;
//	} else if (hd_type == PHD) {				//PHD
//		//h_AB = 0;
//		my_sort((void*)D_aB, nA);	//���е㵽�㼯D_aB�Ĵ�С����������
//		h_AB = D_aB[pos_AB];		//��pos_AB��ֵ��Ϊh_AB
//	} else if (hd_type == LTS_HD) {				//LTS-HD
//		//h_AB = 0;
//		my_sort((void*)D_aB, nA);
//		for (k = 0; k <= pos_AB; k++) {	//���е㵽�㼯D_aB�Ĵ�С���������
//			h_AB += D_aB[k];			//ǰpos_AB��ֵ��ƽ��ֵ��Ϊh_AB
//		}
//		h_AB /= (pos_AB+1);
//	} else if (hd_type == CHD) {				//CHD
//		//h_AB = 0;
//		my_sort((void*)D_aB, nA);	//���е㵽�㼯D_aB�Ĵ�С����������
//		h_AB = D_aB[pos_AB];		//��pos_AB��ֵ��Ϊh_AB
//	} else {								//����,ʹ�þ���HD
//		h_AB = D_aB[0];
//		for (k = 1; k < nA; k++) {
//			if (D_aB[k] > h_AB)
//				h_AB = D_aB[k];
//		}
//	}
//
//	//if (d_ab != NULL) {
//	//	free(d_ab);
//	//	d_ab = NULL;
//	//}
//	//if (D_aB != NULL) {
//	//	free(D_aB);
//	//	D_aB = NULL;
//	//}
//
//	return h_AB;
//
//}

/******************************************************************************
  * ���ܣ�����Hausdorff����,���õײ�HausdorffDistance����
  * ������A			�㼯A
  *       B			�㼯B
  *       nA		�㼯A�ĵ���
  *       nB		�㼯B�ĵ���
  *		  hd_dir    ����˫�����HD
  *       hd_type	���ּ���Hausdorff������㷨
  *       pos_aB	���е㵽�㼯����D_aB��������ĵ�pos_aB��(ȡֵ0-nA)
  *					��:CHD�㷨
  *       pos_AB	���е㼯���㼯����d_AB��������ĵ�pos_AB��(ȡֵ0-nA),
  *					��:PHD,CHD,LTS-HD
  *       d_thr		�㼯���㼯����ֵ,��d_AB>d_thr,����d_AB=d_thr,��M-HD
  * ���أ��㼯A��B��Hausdorff����(h_AB)
  * ˵��: pos_aB,pos_AB,d_thr������������������hd_type�����õ�.����d_thr��ֻ��
  *		  M-HD�㷨��Ч.����ʱ��,������ȡ�κ�ֵ
  * �㷨:
  *		  ����HD��������:
  *			��֪�����㼯A={a1,a2,...,anA},B={b1,b2,...,bnB},nA��nB�ֱ���
  *			�㼯A,B�е�ĸ���,�������㼯֮���HD���붨��Ϊ:
  *			H(A,B) = max(h(A,B),h(B,A))								(1)
  *			����h(A,B) = max(min(||a-b||)) = max(D(a,B))			(2)
  *						 a(A b(B             a(A
  *				h(B,A) = max(min(||b-a||)) = max(D(b,A))			(3)
  *					     b(B a(A             b(B
  *			ע��:x(X��ʾx����X
  *				 d��d(a,b)��ʾ�㵽�����
  *				 D��D(a,B)��ʾ�㵽�㼯����
  *				 h��h(A,B)��ʾ�㼯���㼯����
  *			ʽ(1)��Ϊ˫��HD,ʽ(2),(3)�ֱ��Ϊ�ӵ㼯A���㼯B�ʹӵ㼯B���㼯A��
  *			����HD.��������˵���HD�Ϳ���ͨ��ȡ���ߵ����ֵ�õ�˫��HD��.
  *		  �����Ľ�HD�㷨����:
  *			PHD(Partial HD):
  *				�����е㵽�㼯����(D)��С��������,ȡ��k������ֵ��ΪPHD�ĵ���HD(h)	
  *			CHD(Censored HD):
  *				���Ƚ�����A������һ�㵽����B�����е�ľ���(d)��С����
  *				����, ȡ��q��������Ϊ�õ㵽����B�ľ���, 
  *				Ȼ�����м���A�еĵ㵽����B�ľ���(D)��С��������, 
  *				ȡ��p��������Ϊ����A������B�ĵ���HD
  *			MHD(Modified HD):
  *				�����е㵽�㼯����С����(D)��ƽ����Ϊ����HD. 
  *				MHD������Ч�ֿ���������,�������ں������ŵ����ܲ�����
  *			M-HD(M-estimation HD):
  *				�������̶��趨��ֵ�ĵ㵽�㼯����С����ֵ����̶�ֵ,
  *				Ȼ����ȡƽ����Ϊ����HD,�Ա������ڲ����������ص������ƫ��
  *			LTS-HD:
  *				���㵽�㼯�ľ�������, ȡǰh����ƽ��ֵ��Ϊ����HD, 
  *				�������������ڵ����ߴ��������ŵ�ͼ���нϺõ�Ч��
  *			WHD:(Weighted HD):
  *				���ݸ�������λ�ö�ͼ��ƥ��Ĳ�ͬ��Ҫ�Ը��費ͬ��Ȩֵ.
  *			�����㷨:
  *				1.Ϊ��С�����ĸ���,���������3x3�Ĵ��ڽ���ֵͼ��ת��Ϊ�Ҷ�ͼ��, 
  *				�ԻҶ�ͼ�����HD�ķ���;
  *				2.�������ƶȼ�Ȩ������ӦHD�㷨��
  *		  �㷨����:���ݾ���HD�Ķ���,����HD��Ҫ��Ϊ3��:
  *			1.����㵽��ľ���(d)
  *			2.����㵽�㼯�ľ���(D)
  *			3.����㼯���㼯�ľ���(h)
  *		  ���ָĽ��㷨�Ĺ�����༯���ڲ���3,ֻ��CHD�Բ���2���иĽ�.
  *		  ���ݵ�3���ļ��㷽��, ���Խ� HD �Ķ���������Ϊ��������. 
  *			1)ֱ��ȡĳһ���㵽�㼯�ľ���ֵ��Ϊ���� HD, �羭�� HD��PHD��CHD��
  *			  ���෽�����ڹ���������ĳһ���㵽�㼯�ľ���ֵ
  *			  ��������ܵ��������ڵ��ĸ���, ³���Բ�.
  *  		2)ȡĳһ���ֵ㵽�㼯�ľ���ֵ���㵥��HD, ��M-HD
  *			  �� LTS-HD. ���ڱ��ڵ����ֵĵ㵽�㼯����С��
  *			  ���ܵ����źܴ�, ���෽��ͨ����ȥ�Ƚϴ�ĵ㵽
  *			  �㼯����С����ֵ, �Ӷ�����˴����ڵ�ʱ�㷨��³����. 		
  *  		3) ������㵽�㼯�ľ����ƽ��ֵ��Ϊ���� HD, 
  *			  ��MHD��LTS-HD��M-HD��WHD,ȡ�㵽�㼯��ƽ����С������
  *			  �ֿ��������ŵ���Ч����,��ǿ���㷨��³����.	 
  *			ʵ����, ȡ���ֵ㵽�㼯����С�����ȡ�㵽�㼯��
  *		  ƽ����С������һ�Ի���ì�ܵ�����. ȡ���ֵ㵽�㼯�ľ���
  *		  ����Ҫ�����ܵ��޳����ŵ�, �������޳����ŵ��ͬʱ,
  *		  ��Ȼ�����˿����õĵ㵽�㼯��С����ĸ���,
  *		  �Ӷ��������㷨���ȶ���. ȡ�㵽�㼯��ƽ����С��������һ������, 
  *		  �����������е㵽�㼯����С����ֵ, �����ܱ�֤�㷨��³����,
  *		  �����ܵ��������ڵ��ȸ��ŵĵ㵽�㼯����С����Ҳ��������, 	   
  *		  ����ڼ��㾫���ϲ��ܴﵽ����. ����ķ�����һ�仰��������: 
  *			ȡ���ֵ㵽�㼯����С������ͨ�������㷨�ȶ�������ȡ���㾫
  *		  ��; ȡ�㵽�㼯��ƽ����С������ͨ�����ͼ��㾫������ȡ�㷨³����.
******************************************************************************/
//int32_t HausdorffDistance
//(
// Point_t *A, 
// Point_t *B, 
// const int32_t nA, 
// const int32_t nB,
// const int32_t hd_dir,
// const int32_t hd_type,
// int32_t pos_aB,
// int32_t pos_AB,
// const int32_t d_thr
// )
//{
//	int32_t h_AB, h_BA;
//	
//	if (hd_dir == 1) {	//����
//		h_AB = HausdorffDistanceLL(A, B, nA, nB, hd_type, pos_aB, pos_AB, d_thr);
//	} else {
//		h_AB = HausdorffDistanceLL(A, B, nA, nB, hd_type, pos_aB, pos_AB, d_thr);
//		h_BA = HausdorffDistanceLL(B, A, nB, nA, hd_type, pos_aB, pos_AB, d_thr);
//
//		if (h_AB < h_BA)
//			h_AB = h_BA;
//	}
//
//	return h_AB;
//}

/******************************************************************************
  * ���ܣ���������ͼ��������㼯��HD
  * ������minutiaA	�����㼯A
  *       minutiaB	�����㼯B
  *		  hd_dir    ����˫�����HD
  *       hd_type	���ּ���Hausdorff������㷨
  *       pos_aB	���е㵽�㼯����D_aB��������ĵ�pos_aB��(ȡֵ0-nA)
  *					��:CHD�㷨
  *       pos_AB	���е㼯���㼯����d_AB��������ĵ�pos_AB��(ȡֵ0-nA),
  *					��:PHD,CHD,LTS-HD
  *       d_thr		�㼯���㼯����ֵ,��d_AB>d_thr,����d_AB=d_thr,��M-HD
  * ���أ�����ͼ��������㼯��HD
  * ˵��: pos_aB,pos_AB,d_thr������������������hd_type�����õ�.����d_thr��ֻ��
  *		  M-HD�㷨��Ч.����ʱ��,������ȡ�κ�ֵ
******************************************************************************/
//int32_t ImageMinutiaHD
//(
// pFVMinutiaSet_t minutiaA, 
// pFVMinutiaSet_t minutiaB, 
// const int32_t hd_dir,
// const int32_t hd_type,
// int32_t pos_aB,
// int32_t pos_AB,
// const int32_t d_thr
// )
//{
//	int32_t H_AB = 0, k;
//	int32_t nA, nB;					//�����㼯A,B�ĵ��� 
//	//Point_t *A, *B;					//�㼯A,B
//	Point_t A[FV_MAX_MINUTIA_NUM];
//	Point_t B[FV_MAX_MINUTIA_NUM];
//	//��ȡnA,nB,minutiaA->FPMinutiaArr,minB
//	nA = minutiaA->nbminutia;
//	nB = minutiaB->nbminutia;
//
//	//ΪA,B����ռ�
//	//A = (Point_t *)malloc(sizeof(Point_t) * nA);
//	//B = (Point_t *)malloc(sizeof(Point_t) * nB);
//
//	//��ʼ������Ϊ0
//	//for (k = 0; k < FV_MAX_MINUTIA_NUM; k++) {
//	//	A[k].x = 0;
//	//	A[k].y = 0;
//	//	B[k].x = 0;
//	//	B[k].y = 0;
//	//}
//
//	//��ʼ���㼯A,B
//	for (k = 0; k < nA; k++) {
//		A[k].x = minutiaA->FVMinutiaArr[k].x;
//		A[k].y = minutiaA->FVMinutiaArr[k].y;
//	}
//	for (k = 0; k < nB; k++) {
//		B[k].x = minutiaB->FVMinutiaArr[k].x;
//		B[k].y = minutiaB->FVMinutiaArr[k].y;
//	}
//
//	//����HD
//	H_AB = HausdorffDistance(A, B, nA, nB, hd_dir, hd_type, pos_aB, pos_AB, d_thr);
//
//	printf("the HD of MinutiaSet A&B is: %d\n", H_AB);
//
//	//if (A != NULL) {
//	//	free(A);
//	//	A = NULL;
//	//}
//	//if (B != NULL) {
//	//	free(B);
//	//	B = NULL;
//	//}
//	
//	return H_AB;
//}






/******************************************************************************
*******************************************************************************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
*******************************************************************************
******************************************************************************/


// Ϊ��ʡʱ�䣬�̾��������������ò��
int32_t  DisTbl[15][15] = {
	0, 1, 2, 3, 4, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	1, 1, 2, 3, 4, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	2, 2, 2, 3, 4, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	3, 3, 3, 4, 5, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	4, 4, 4, 5, 5, 6, 7,   8,  8,  9, 10,  11, 12, 13, 14,
	5, 5, 5, 5, 6, 7, 7,   8,  9, 10, 11,  12, 13, 13, 14,
	6, 6, 6, 6, 7, 7, 8,   9, 10, 10, 11,  12, 13, 14, 15,  
	7, 7, 7, 7, 8, 8, 9,   9, 10, 11, 12,  13, 14, 15, 16, 
	8, 8, 8, 8, 8, 9, 10, 10, 11, 12, 12,  13, 14, 15, 16, 
	9, 9, 9, 9, 9, 10,10, 11, 12, 12, 13,  14, 15, 15, 16,
	10,10,10,10,10,11,11, 12, 12, 13, 14,  14, 15, 16, 17,
	11,11,11,11,11,12,12, 13, 13, 14, 14,  15, 16, 17, 17,
	12,12,12,12,12,13,13, 14, 14, 15, 15,  16, 16, 17, 18,
	13,13,13,13,13,13,14, 15, 15, 15, 16,  17, 17, 18, 19,
	14,14,14,14,14,14,15, 16, 16, 16, 17,  17, 18, 19, 19
};


/************************************************************************
  * ���ܣ�ͼ����������׼(��ת�任)
  * ������minutia			ϸ�ڵ㼯��
  *		  align_minutia		������׼��������㼯��[out]
  *		  coreXY			��׼(��ת�任)���ĵ�
  *		  rotation			��ת�Ƕ�
  *		  transx			ˮƽƫ��
  *		  transy			��ֱƫ��
  * ���أ�void
  * ˵��: ��ָ��������һ���ĽǶȺ�λ�ý�������任��׼����,�Ӷ�ʵ��ͼ��ϸ�ڵ�
  *		  ����׼,Ϊ��һ��ͼ��ƥ��ͱȶ�����׼��.
  *		  ���ú���ǰע��ҪΪalign_minutia����ռ�
  * �㷨: 
*************************************************************************/
void MinutiaSetAlign
(
 pFPMinutiaSet_t minutia,
 pFPMinutiaSet_t align_minutia,
 Point_t coreXY, 
 int32_t rotation, 
 int32_t transx, 
 int32_t transy
 )
{
	int32_t i;
	int32_t x, y, angle;
	int32_t cx, cy;
	double rota, sinv, cosv;
	int32_t min_num;			//�����㼯��Ŀ

	min_num = minutia->nbminutia;

	//��ȡ��׼��������㼯�ϵ�ָ�뼰����Ŀ
	align_minutia->nbminutia = min_num;

	//����ת�������ĵ�����
	cx = coreXY.x;
	cy = coreXY.y;
	//��ת�Ļ���
	rota = rotation/M_EPI;
	//��ת���ȵ�sinֵ
	sinv = sin(rota);
	//��ת���ȵ�cosֵ
	cosv = cos(rota);
	
	//������׼(��ת�仯)��Ĳ���
	for (i = 0; i < min_num; i++) {
		//x = min[i].x;
		//y = min[i].y;
		//angle = min[i].angle;
		//����ת�����������
		//��ת����������·���
		//align_min->ptable[i].x = (int32_t)(cx + cosv*(x-cx) - sinv*(y-cy) + transx + 0.5);
		//align_min->ptable[i].y = (int32_t)(cy + sinv*(x-cx) + cosv*(y-cy) + transy + 0.5);
		//align_min->ptable[i].angle = (angle + rotation) % 360;
		//align_min->ptable[i].type = min[i].type;
		//align_min->ptable[i].triangle[0] = min[i].triangle[0];
		//align_min->ptable[i].triangle[1] = min[i].triangle[1];
		//align_min->ptable[i].triangle[2] = min[i].triangle[2];


		x = minutia->FPMinutiaArr[i].x;
		y = minutia->FPMinutiaArr[i].y;
		angle = minutia->FPMinutiaArr[i].angle;

		//����ת�����������
		//��ת����������·���
		align_minutia->FPMinutiaArr[i].x = (int32_t)(cx + cosv*(x-cx) - sinv*(y-cy) + transx + 0.5);
		align_minutia->FPMinutiaArr[i].y = (int32_t)(cy + sinv*(x-cx) + cosv*(y-cy) + transy + 0.5);
		align_minutia->FPMinutiaArr[i].angle = (angle + rotation) % 360;
		align_minutia->FPMinutiaArr[i].type = minutia->FPMinutiaArr[i].type;
		align_minutia->FPMinutiaArr[i].triangle[0] = minutia->FPMinutiaArr[i].triangle[0];
		align_minutia->FPMinutiaArr[i].triangle[1] = minutia->FPMinutiaArr[i].triangle[1];
		align_minutia->FPMinutiaArr[i].triangle[2] = minutia->FPMinutiaArr[i].triangle[2];

	}

}

/************************************************************************
  * ���ܣ���������ϵ�����ͼ�����������ƥ��(�ȶ�)
  * ������minutiaA			������׼����ƥ��ϸ�ڵ㼯��
  *		  minutiaT			ƥ��ģ��
  *		  pMatchResult		��׼����ṹ��ָ��
  *		  bound_box			���޺д�С
  *		  simi_thr			���ƶ���ֵ
  *		  match_mode		��׼ģʽ:1:����ģʽ
  * ���أ�void
  * ˵��: ��ָ��������һ���ĽǶȺ�λ�ý�������任��׼����,�Ӷ�ʵ��ͼ��ϸ�ڵ�
  *		  ����׼,Ϊ��һ��ͼ��ƥ��ͱȶ�����׼��.
  *		  ���ú���ǰע��ҪΪalign_minutia����ռ�
  * �㷨: 1.�����Ѿ���׼��ͼ�����ƥ��(�ȶ�)ʱ,�����ƶȾ���ָ��ͼ�����˽ṹ��ȶ�
  *		  ��һ�³̶�.���㹫ʽ:
  *			similarity = 4*score*������ƶ�*���������/(����������*����������)
  *		    (1)������ƥ��������������ϵĶ�Ӧ������ƥ��ɹ��ļ�¼.ƥ��ɹ�
  *		       �����ӷ���.�������Լ�����.��:�趨AΪ�н�������������ֵ(���޺�)
  *		       aΪ��ǰ�н�.��aԽ��,����Ӧ����С.�ʷ���=����+(A-a)
  *		    (2)���������:ƥ��ͼ���趨�����������
  *		    (3)��������:����ƥ��ͼ�����������ܺ�
  *		  2.�����ƶȴ���ĳ���ϸ����ֵ,����ͼ������.
  *		    ע��,���ڷ������㷽����һ��,���޺����õķ���(��С,�̶�,�ɱ�)
  *		  �õ������ƶ�Ҳ��һ��,�ϸ���ֵҲ��ͬ.
  *		    ���޺�ģ��:�ɷ�Ϊ�̶��ĺͿɱ��.������ù̶����޺�bound_box=10
*************************************************************************/
void MinutiaSetAlignMatch
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t match_mode
 )
{
	int32_t	i, j;
	uint8_t flagA[FP_MAX_MINUTIA_NUM];	//���minutiaA���������Ƿ��Ѿ���ƥ�����
	uint8_t flagT[FP_MAX_MINUTIA_NUM];	//���minutiaT���������Ƿ��Ѿ���ƥ�����

	int32_t	x1, y1, x2, y2;
	int32_t dis, angle;
	int32_t score, match_num, s;
	//int32_t step = 1;

	int32_t minA_num, minT_num;
	//Minutia_t *minutiaA->FPMinutiaArr,*minutiaT->FPMinutiaArr;		//�����㼯A,B


	//minA_num = MinutiaSetGetCount(minutiaA);
	//minutiaA->FPMinutiaArr = MinutiaSetGetBuffer(minutiaA);
	//minT_num = MinutiaSetGetCount(minutiaT);
	//minutiaT->FPMinutiaArr = MinutiaSetGetBuffer(minutiaT);
	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//�������
	//memset(flagA, 0, FP_MAX_MINUTIA_NUM);
	//memset(flagT, 0, FP_MAX_MINUTIA_NUM);
	for (i = 0; i < FP_MAX_MINUTIA_NUM; i++) {
		flagA[i] = 0;
		flagT[i] = 0;
	}

	score = 0;		//�ܷ�����
	match_num = 0;	//ƥ��������������

	//��ͬ�����������ƥ�����
	for (i = 0; i < minT_num; i++) {
		if(flagT[i])			//�Ƿ�����ƥ�����
			continue;
		for (j = 0; j < minA_num; j++) {
			if(flagA[j])		//�Ƿ�����ƥ�����
				continue;

			//�����������Ƿ���ͬ
			if (minutiaT->FPMinutiaArr[i].type != minutiaA->FPMinutiaArr[j].type)
				continue;

			//�����㷽��н�
			angle = GetAngle180In360(minutiaT->FPMinutiaArr[i].angle, minutiaA->FPMinutiaArr[j].angle);
			//�н�>=10��ƥ��
			if(angle >= bound_box)
				continue;

			x1 = minutiaT->FPMinutiaArr[i].x;
			y1 = minutiaT->FPMinutiaArr[i].y;
			x2 = minutiaA->FPMinutiaArr[j].x;
			y2 = minutiaA->FPMinutiaArr[j].y;
			//ˮƽ����>=10��ƥ��
			if(abs(x1-x2) >= bound_box)
				continue;
			//��ֱ����>=10��ƥ��
			if(abs(y1-y2) >= bound_box)
				continue;
			//���������ľ���
			dis = DisTbl[abs(y1-y2)][abs(x1-x2)];
			//dis = (int32_t)sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
			//����>=10��ƥ��
			if(dis >= bound_box)
				continue;

			//������������������ǣ���ʾ�Ѿ���ƥ�����
			flagA[j] = 1;
			flagT[i] = 1;

			//�ּܷ��ϴ������������ƥ�����
			//�˱���dis,angleԽ�󣬷���ԽС
			score += (bound_box-angle);
			score += (bound_box-dis);

			//ƥ������������һ
			match_num++;
			
			//����ǿ��ٱȶ�ģʽ
			if (match_mode == MATCH_MODE_FAST && match_num >= 8) {
				//�������ƶ�
				s = 4 * score * match_num * FP_MAX_MINUTIA_NUM / ((minA_num + minT_num) * ( minA_num + minT_num));
				//if (s > 100) {			//���ƶ��㹻���򷵻رȶԽ��
				if (s > simi_thr) {			//���ƶ��㹻���򷵻رȶԽ��
					pMatchResult->match_num = match_num;
					pMatchResult->rotation = 0;
					pMatchResult->similarity = s;
					pMatchResult->transX = 0;
					pMatchResult->transX = 0;
					return;
				}
			}
		}
	}

	//�ǿ���ƥ��ģʽ
	if (match_mode != MATCH_MODE_FAST) {
		//����ͼ��������¿��ܶ˵㴦��ɲ����㴦��ɶ˵�
		//�������Ϊ50%�������������ķ���
		for(i = 0; i < minT_num; i++) {
			if(flagT[i])		//�Ƿ�����ƥ�����
				continue;
			for(j = 0; j < minA_num; j++) {
				if(flagA[j])	//�Ƿ�����ƥ�����
					continue;

				//�Ƿ����Ͳ�ͬ
				if(minutiaT->FPMinutiaArr[i].type == minutiaA->FPMinutiaArr[j].type)
					continue; 

				//�����㷽��н�
				angle = GetAngle180In360(minutiaT->FPMinutiaArr[i].angle, minutiaA->FPMinutiaArr[j].angle);
				//�н�>=10��ƥ��
				if(angle >= bound_box)
					continue;

				x1 = minutiaT->FPMinutiaArr[i].x;
				y1 = minutiaT->FPMinutiaArr[i].y;
				x2 = minutiaA->FPMinutiaArr[j].x;
				y2 = minutiaA->FPMinutiaArr[j].y;
				//ˮƽ����>=10��ƥ��
				if(abs(x1-x2) >= bound_box)
					continue;
				//��ֱ����>=10��ƥ��
				if(abs(y1-y2) >= bound_box)
					continue;
				//���������ľ���
				dis = DisTbl[abs(y1-y2)][abs(x1-x2)];
				//dis = (int32_t)sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
				//����>=10��ƥ��
				if(dis >= bound_box)
					continue;

				//������������������ǣ���ʾ�Ѿ���ƥ�����
				flagA[j] = 1;
				flagT[i] = 1;
				//�ּܷ��ϴ������������ƥ�����
				score += ((bound_box-angle)/2);
				score += ((bound_box-dis)/2);
				// ƥ������������һ
				match_num++;

			}
		}								
	}

	//�������ƶȣ����رȶԽ��
	s = 4 * score * match_num * FP_MAX_MINUTIA_NUM / ((minA_num+minT_num)*(minA_num+minT_num));

	pMatchResult->match_num = match_num;
	pMatchResult->rotation = 0;
	pMatchResult->similarity = s;
	pMatchResult->transX = 0;
	pMatchResult->transX = 0;
}


/************************************************************************
  * ���ܣ����ĵ�ƥ��
  * ������minutiaA			������׼����ƥ��ϸ�ڵ㼯��
  *		  minutiaT			ƥ��ģ��
  *		  pMatchResult		��׼����ṹ��ָ��
  *		  bound_box			���޺д�С
  *		  simi_thr			���ƶ���ֵ
  *		  match_mode		��׼ģʽ:1:����ģʽ
  *		  pCoreA			ƥ��ͼ������ĵ��������㼯�е�λ��
  *		  coreA_num			ƥ��ͼ������ĵ����
  *		  pCoreT			ģ��ͼ������ĵ��������㼯�е�λ��
  *		  coreT_num			ģ��ͼ������ĵ����
  * ���أ�void
  * ˵��: ͼ���"����"��׼,��Ϊһ����Χ�ڵĴ�����׼
  *		  ָ��ͼ���������׼������:�ֲ���׼(CenteralMatching),
  *       �����(CoreMatching,DeltaMatching)��ȫ����׼(GlobalMatching),����Ҷ��
  *		  ����㷨:�������ĵ�����ǵ�.Ѱ��ͼ��������,���������λ�õ�ƫ�ƺ���ת
  *				   ��ͼ�������׼(MinutiaSetAlign)��ƥ��(MinutiaSetAlignMatch)
  *		  �ֲ���:�ڹ涨��һ����ͼ���м�����Ϊȡ�㷶Χ,�ֱ�ȡ��ͬ�ĵ������׼
  *				 ��ƥ��.
  *		  ȫ�ַ�:������ͼ��,�ֱ�ȥ��ͬ�ĵ������׼��ƥ��.
  *		  
  * �㷨: 1.��������ͼ�������������׼�Ĳ���(ƫ��,��ת�Ƕȵ�)
  *		  2.����ƥ�������㼯��minutiaA������׼(MinutiaSetAlign)
  *			�õ���׼��������㼯align_minutia
  *		  3.����׼��������㼯��ģ�����ƥ��(MinutiaSetAlignMatch)
  *			����ƥ�伯�ϲ���pMatchResult
  *		  4.�������������,�ҵ�����ƥ�伯����pMatchResult
*************************************************************************/
void CoreMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t match_mode,
 int32_t *pCoreA,
 int32_t coreA_num, 
 int32_t *pCoreT, 
 int32_t coreT_num 
 )
{
	int32_t i, j;
	int32_t rotation;
	//int32_t  num = 0;

	int32_t transx, transy;
	int32_t n, m;
	int32_t nn, mm;			//ƥ��ͼ���ģ��ͼ������ĵ��ܸ���

	iMatchingSet_t align_max;			//���ƶ����ıȶԽ��
	iMatchingSet_t g_match_result;		//���ձȶԽ��
	FPMinutiaSet_t align_minutia;		//��׼���ϸ�ڵ㼯��
	int32_t minA_num, minT_num;
	Point_t temp_core;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//��ʼ����õıȶԽ��
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;

	//�����ĵ������������Ϊͬһ���������ж���ȶ�
	for (nn = 0; nn < coreT_num; nn++) {
		for (mm = 0; mm < coreA_num; mm++) {
	
			n = pCoreT[nn];	//��ȡ���ĵ���ϸ�ڵ㼯���е�λ��
			m = pCoreA[mm];	//��ȡ���ĵ���ϸ�ڵ㼯���е�λ��

			//λ��ƫ��
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[n].y);

			for (i = 0; i < minA_num; i++) {
				for (j = 0; j < minT_num; j++) {
					
					//��Ϊ���ĵ�����ǵ�,����
					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeCore || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeCore)
						continue;
					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeDelta || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeDelta)
						continue;
					
					//������׼(��ת�任)�Ƕ�
					rotation = XY2Angle(minutiaT->FPMinutiaArr[j].x, minutiaT->FPMinutiaArr[j].y, minutiaA->FPMinutiaArr[i].x, minutiaA->FPMinutiaArr[i].y);
					
					//������׼(��ת�任)���ĵ�
					temp_core.x = minutiaA->FPMinutiaArr[i].x;
					temp_core.y = minutiaA->FPMinutiaArr[i].y;
					
					//����ƥ��ͼ�������׼minutiaA-->align_minutia
					MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);

					//�����������align_minutia��minutiaT��������ƥ��(�ȶ�)
					MinutiaSetAlignMatch(&align_minutia, minutiaT, &g_match_result,
						bound_box, simi_thr, match_mode);
						 

					//����ȶԽ������õıȶԽ�����ã������align_max
					if (g_match_result.similarity > align_max.similarity) {
						align_max.match_num = g_match_result.match_num;
						align_max.similarity = g_match_result.similarity;
						align_max.rotation = rotation;
						align_max.transX = transx;
						align_max.transY = transy;
						
						//����ǿ��ٱȶ�ģʽ�������ƶȴﵽһ���̶����˳�
						if (match_mode == MATCH_MODE_FAST && \
							align_max.match_num >= 8) {
							//if (align_max.similarity > 100) {
							if (align_max.similarity > simi_thr) {
								*pMatchResult = align_max;

								//�ͷ�Ϊ��׼���ϸ�ڵ㼯�Ϸ���ռ�
								//MinutiaSetDestroy(align_minutia);
								return;
							}
						}
					}
				}
			}
		}
	}


	//���ձȶԽ��
	*pMatchResult = align_max;
}


/************************************************************************
  * ���ܣ����ǵ�ƥ��
  * ������minutiaA			������׼����ƥ��ϸ�ڵ㼯��
  *		  minutiaT			ƥ��ģ��
  *		  pMatchResult		��׼����ṹ��ָ��
  *		  bound_box			���޺д�С
  *		  simi_thr			���ƶ���ֵ
  *		  match_mode		��׼ģʽ:1:����ģʽ
  *		  pDeltaA			ƥ��ͼ������ǵ��������㼯�е�λ��
  *		  deltaA_num		ƥ��ͼ������ǵ����
  *		  pDeltaT			ģ��ͼ������ǵ��������㼯�е�λ��
  *		  DeltaT_num		ģ��ͼ������ǵ����
  * ���أ�void
  * ˵��: ͼ���"����"��׼,��Ϊһ����Χ�ڵĴ�����׼
  *		  ָ��ͼ���������׼������:�ֲ���׼(CenteralMatching),
  *       �����(CoreMatching,DeltaMatching)��ȫ����׼(GlobalMatching),����Ҷ��
  *		  ����㷨:�������ĵ�����ǵ�.Ѱ��ͼ��������,���������λ�õ�ƫ�ƺ���ת
  *				   ��ͼ�������׼(MinutiaSetAlign)��ƥ��(MinutiaSetAlignMatch)
  *		  �ֲ���:�ڹ涨��һ����ͼ���м�����Ϊȡ�㷶Χ,�ֱ�ȡ��ͬ�ĵ������׼
  *				 ��ƥ��.
  *		  ȫ�ַ�:������ͼ��,�ֱ�ȥ��ͬ�ĵ������׼��ƥ��.
  *		  
  * �㷨: 1.��������ͼ�������������׼�Ĳ���(ƫ��,��ת�Ƕȵ�)
  *		  2.����ƥ�������㼯��minutiaA������׼(MinutiaSetAlign)
  *			�õ���׼��������㼯align_minutia
  *		  3.����׼��������㼯��ģ�����ƥ��(MinutiaSetAlignMatch)
  *			����ƥ�伯�ϲ���pMatchResult
  *		  4.�������������,�ҵ�����ƥ�伯����pMatchResult
*************************************************************************/
void DeltaMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t match_mode, 
 int32_t *pDeltaA,
 int32_t deltaA_num,
 int32_t *pDeltaT, 
 int32_t deltaT_num
 )
{
	//int32_t num = 0;
	int32_t n, m;
	int32_t nn, mm;		//ƥ��ͼ���ģ��ͼ������ǵ��ܸ���
	int32_t i, j;
	int32_t rotation;
	int32_t transx, transy;

	iMatchingSet_t align_max;			//���ƶ����ıȶԽ��
	iMatchingSet_t g_match_result;		//���ձȶԽ��
	FPMinutiaSet_t align_minutia;		//��׼���ϸ�ڵ㼯��

	int32_t minA_num, minT_num;
	Point_t temp_core;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//��ʼ����õıȶԽ��
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;


	//�����ǵ�����������Ϊͬһ���������ж���ȶ�
	for (nn = 0; nn < deltaT_num; nn++) {
		for (mm = 0; mm < deltaA_num; mm++) {
	
			n = pDeltaT[nn];	//��ȡ���ǵ���ϸ�ڵ㼯���е�λ��
			m = pDeltaA[mm];	//��ȡ���ǵ���ϸ�ڵ㼯���е�λ��
	
			//λ��ƫ��
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[n].y);

			for (i = 0; i < minA_num; i++) {
				for (j = 0; j < minT_num; j++) {
								
					//��Ϊ���ĵ�����ǵ�,����
					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeCore || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeCore) 
						continue;

					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeDelta || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeDelta) 
						continue;
	
					//������׼(��ת�任)�Ƕ�
					rotation = XY2Angle(minutiaA->FPMinutiaArr[i].x, minutiaA->FPMinutiaArr[i].y, minutiaT->FPMinutiaArr[j].x, minutiaT->FPMinutiaArr[j].y);
					
					//������׼(��ת�任)���ĵ�
					temp_core.x = minutiaA->FPMinutiaArr[i].x;
					temp_core.y = minutiaA->FPMinutiaArr[i].y;

					//����ƥ��ͼ�������׼minutiaA-->align_minutia
					MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);
					//�����������align_minutia��minutiaT��������ƥ��(�ȶ�)
					MinutiaSetAlignMatch(&align_minutia, minutiaT,&g_match_result,  
						bound_box, simi_thr, match_mode);

					//����ȶԽ������õıȶԽ�����ã������align_max
					if (g_match_result.similarity > align_max.similarity) {
						align_max.match_num = g_match_result.match_num;
						align_max.similarity = g_match_result.similarity;
						align_max.rotation = rotation;
						align_max.transX = transx;
						align_max.transY = transy;
						
						//����ǿ��ٱȶ�ģʽ�������ƶȴﵽһ���̶����˳�
						if (match_mode == MATCH_MODE_FAST && \
							align_max.match_num >= 8) {
							//if (align_max.similarity > 100) {
							if (align_max.similarity > simi_thr) {
								*pMatchResult = align_max;

								//�ͷ�Ϊ��׼���ϸ�ڵ㼯�Ϸ���ռ�
								//MinutiaSetDestroy(align_minutia);
								return;
							}
						}
					}
				}
			}
		}
	}

	//���ձȶԽ��
	*pMatchResult = align_max;

}


//���������ľ���
int32_t dist(int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
	return (int32_t)sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}


/************************************************************************
  * ���ܣ��ֲ�ƥ��
  * ������minutiaA			������׼����ƥ��ϸ�ڵ㼯��
  *		  minutiaT			ƥ��ģ��
  *		  pMatchResult		��׼����ṹ��ָ��
  *		  bound_box			���޺д�С
  *		  simi_thr			���ƶ���ֵ
  *		  angle_thr			�������˽ṹ�Ƕ����
  *		  central_thr		��������Χ��ֵ
  *		  match_mode		��׼ģʽ:1:����ģʽ
  * ���أ�void
  * ˵��: ͼ���"����"��׼,��Ϊһ����Χ�ڵĴ�����׼
  *		  ָ��ͼ���������׼������:�ֲ���׼(CenteralMatching),
  *       �����(CoreMatching,DeltaMatching)��ȫ����׼(GlobalMatching),����Ҷ��
  *		  ����㷨:�������ĵ�����ǵ�.Ѱ��ͼ��������,���������λ�õ�ƫ�ƺ���ת
  *				   ��ͼ�������׼(MinutiaSetAlign)��ƥ��(MinutiaSetAlignMatch)
  *		  �ֲ���:�ڹ涨��һ����ͼ���м�����Ϊȡ�㷶Χ,�ֱ�ȡ��ͬ�ĵ������׼
  *				 ��ƥ��.
  *		  ȫ�ַ�:������ͼ��,�ֱ�ȥ��ͬ�ĵ������׼��ƥ��.
  *		  
  * �㷨: 1.��������ͼ����������������򸽽�(CENTRALRADIUS)
  *			���������������׼�Ĳ���(ƫ��,��ת�Ƕȵ�)
  *		  2.����ƥ�������㼯��minutiaA������׼(MinutiaSetAlign)
  *			�õ���׼��������㼯align_minutia
  *		  3.����׼��������㼯��ģ�����ƥ��(MinutiaSetAlignMatch)
  *			����ƥ�伯�ϲ���pMatchResult
  *		  4.������������ͼ����������������򸽽��ĵ�,
  *			�ҵ�����ƥ�伯����pMatchResult
*************************************************************************/
void CentralMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t angle_thr,
 int32_t central_thr,
 int32_t match_mode
 )
{
	int32_t	m, n, a1, a2;
	int32_t	rotation;		//��ת�Ƕ�
	int32_t	transx, transy;	//λ��ƫ��

	//int32_t  num = 0;
	int32_t nx, ny;			//ϸ�ڵ���������
	int32_t mx, my;			//ϸ�ڵ���������
	int32_t Counter;

	iMatchingSet_t align_max;			//���ƶ����ıȶԽ��
	iMatchingSet_t g_match_result;		//���ձȶԽ��
	FPMinutiaSet_t align_minutia;			//��׼���ϸ�ڵ㼯��

	int32_t minA_num, minT_num;
	Point_t temp_core;


	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	// ��ʼ����õıȶԽ��
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;

	//����ϸ�ڵ���������
	nx = 0;
	ny = 0;
	for (n = 0; n < minT_num; n++) {
		nx += minutiaT->FPMinutiaArr[n].x;
		ny += minutiaT->FPMinutiaArr[n].y;
	}
	nx = nx / minT_num;
	ny = ny / minT_num;

	mx = 0;
	my = 0;
	for (m = 0; m < minA_num; m++) {
		mx += minutiaA->FPMinutiaArr[m].x;
		my += minutiaA->FPMinutiaArr[m].y;
	}
	mx = mx / minA_num;
	my = my / minA_num;


	Counter = 0;

	//����ͬ���͵�����������Ϊͬһ���������ж���ȶ�
	for (n = 0; n < minT_num; n++) {

		//������������Χ��ֵ�ĵ�����
		if (dist(nx, ny, minutiaT->FPMinutiaArr[n].x, minutiaT->FPMinutiaArr[n].y) > central_thr) 
			continue;

		for (m = 0; m < minA_num; m++) {

			//��Ϊ���ĵ�����ǵ�,����
			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeCore || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeCore)
				continue;

			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeDelta || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeDelta)
				continue;

			//��ͬ�����򲻱ȶ�
			if (minutiaA->FPMinutiaArr[m].type != minutiaT->FPMinutiaArr[n].type)
				continue;

			//������������Χ��ֵ�ĵ�����
			if (dist(mx, my, minutiaA->FPMinutiaArr[m].x, minutiaA->FPMinutiaArr[m].y) > central_thr) 
				continue;

			Counter++;

			if (match_mode == MATCH_MODE_FAST) {
				//�������������˽ṹ�ȶԣ������������׼
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].angle % 180);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].angle % 180);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[1]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[1]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}

				if (minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
				    minutiaT->FPMinutiaArr[n].triangle[2] != 255 && \
				    minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
				    minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[1], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[1], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}

				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[2] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
			}

			//alignFeature.MinutiaNum = 0;

			//������׼(��ת�任)�Ƕ�
			rotation = GetAngle360In360(minutiaA->FPMinutiaArr[m].angle, minutiaT->FPMinutiaArr[n].angle);

			//������׼ƫ��
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[m].y);
			
			//������׼(��ת�任)���ĵ�
			temp_core.x = minutiaA->FPMinutiaArr[m].x;
			temp_core.y = minutiaA->FPMinutiaArr[m].y;
	
			//����ƥ��ͼ�������׼minutiaA-->align_minutia
			MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);

			//�����������align_minutia��minutiaT��������ƥ��(�ȶ�)
			MinutiaSetAlignMatch(&align_minutia, minutiaT, &g_match_result, 
				 bound_box, simi_thr, match_mode);

			//����ȶԽ������õıȶԽ�����ã������align_max
			if (g_match_result.similarity > align_max.similarity) {
				align_max.match_num = g_match_result.match_num;
				align_max.similarity = g_match_result.similarity;
				align_max.rotation = rotation;
				align_max.transX = transx;
				align_max.transY = transy;
				
				// ����ǿ��ٱȶ�ģʽ�������ƶȴﵽһ���̶����˳�
				if (match_mode == MATCH_MODE_FAST && \
					align_max.match_num >= 8 ) {
					
					//if (align_max.similarity > 100) {
					if (align_max.similarity > simi_thr) {
						*pMatchResult = align_max;

						//�ͷ�Ϊ��׼���ϸ�ڵ㼯�Ϸ���ռ�
						//MinutiaSetDestroy(align_minutia);
						return;
					}
				}
			}
		}
	}
	
	//���ձȶԽ��
	*pMatchResult = align_max;
}


/************************************************************************
  * ���ܣ�ȫ��ƥ��
  * ������minutiaA			������׼����ƥ��ϸ�ڵ㼯��
  *		  minutiaT			ƥ��ģ��
  *		  pMatchResult		��׼����ṹ��ָ��
  *		  bound_box			���޺д�С
  *		  simi_thr			���ƶ���ֵ
  *		  angle_thr			�������˽ṹ�Ƕ����
  *		  match_mode		��׼ģʽ:1:����ģʽ
  * ���أ�void
  * ˵��: ͼ���"����"��׼,��Ϊһ����Χ�ڵĴ�����׼
  *		  ָ��ͼ���������׼������:�ֲ���׼(CenteralMatching),
  *       �����(CoreMatching,DeltaMatching)��ȫ����׼(GlobalMatching),����Ҷ��
  *		  ����㷨:�������ĵ�����ǵ�.Ѱ��ͼ��������,���������λ�õ�ƫ�ƺ���ת
  *				   ��ͼ�������׼(MinutiaSetAlign)��ƥ��(MinutiaSetAlignMatch)
  *		  �ֲ���:�ڹ涨��һ����ͼ���м�����Ϊȡ�㷶Χ,�ֱ�ȡ��ͬ�ĵ������׼
  *				 ��ƥ��.
  *		  ȫ�ַ�:������ͼ��,�ֱ�ȥ��ͬ�ĵ������׼��ƥ��.
  *		  
  * �㷨: 1.��������ͼ�����������������������׼�Ĳ���(ƫ��,��ת�Ƕȵ�)	
  *		  2.����ƥ�������㼯��minutiaA������׼(MinutiaSetAlign)
  *			�õ���׼��������㼯align_minutia
  *		  3.����׼��������㼯��ģ�����ƥ��(MinutiaSetAlignMatch)
  *			����ƥ�伯�ϲ���pMatchResult
  *		  4.������������ͼ����������ҵ�����ƥ�伯����pMatchResult	
*************************************************************************/
void  GlobalMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult,
 int32_t bound_box,
 int32_t simi_thr,
 int32_t angle_thr,
 int32_t match_mode
 )
{
	int32_t	m, n, a1, a2;
	int32_t	rotation;		//��ת�Ƕ�
	int32_t	transx, transy;	//λ��ƫ��
	//int32_t  num = 0;

	iMatchingSet_t align_max;			//���ƶ����ıȶԽ��
	iMatchingSet_t g_match_result;		//���ձȶԽ��
	FPMinutiaSet_t align_minutia;			//��׼���ϸ�ڵ㼯��
	//iMinutiaSet_t *palign;

	int32_t minA_num, minT_num;
	Point_t temp_core;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	// ��ʼ����õıȶԽ��
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;


	//����ͬ���͵�����������Ϊͬһ���������ж���ȶ�
	for (n = 0; n < minT_num; n++) {
		for (m = 0; m < minA_num; m++) {

			//��Ϊ���ĵ�����ǵ�,����
			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeCore || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeCore)
				continue;

			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeDelta || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeDelta)
				continue;

			//��ͬ�����򲻱ȶ�
			if (minutiaA->FPMinutiaArr[m].type != minutiaT->FPMinutiaArr[n].type)
				continue;

			if (match_mode == MATCH_MODE_FAST) {
				//�������������˽ṹ�ȶԣ������������׼
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].angle % 180);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].angle % 180);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[1]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[1]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[2] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[1], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[1], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[2] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
			}
			//alignFeature.MinutiaNum = 0;
			//palign->nbminutia = 0;
			
			//������׼(��ת�任)�Ƕ�
			rotation = GetAngle360In360(minutiaA->FPMinutiaArr[m].angle, minutiaT->FPMinutiaArr[n].angle);
			//������׼ƫ��
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[m].y);	
			//������׼(��ת�任)���ĵ�
			temp_core.x = minutiaA->FPMinutiaArr[m].x;
			temp_core.y = minutiaA->FPMinutiaArr[m].y;
			
			//����ƥ��ͼ�������׼minutiaA-->align_minutia
			MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);

			//�����������align_minutia��minutiaT��������ƥ��(�ȶ�)
			MinutiaSetAlignMatch(&align_minutia, minutiaT, &g_match_result, 
				 bound_box, simi_thr, match_mode);

			//����ȶԽ������õıȶԽ�����ã������align_max
			if (g_match_result.similarity > align_max.similarity) {
				align_max.match_num = g_match_result.match_num;
				align_max.similarity = g_match_result.similarity;
				align_max.rotation = rotation;
				align_max.transX = transx;
				align_max.transY = transy;
				
				//����ǿ��ٱȶ�ģʽ�������ƶȴﵽһ���̶����˳�
				if (match_mode == MATCH_MODE_FAST && \
					align_max.match_num >= 8) {
					//if (align_max.similarity > 100) {
					if (align_max.similarity > simi_thr) {
						*pMatchResult = align_max;

						return;
					}
				}
			}
		}
	}
	
	//���ձȶԽ��
	*pMatchResult = align_max;
}


/************************************************************************
  * ���ܣ������㼯��ƥ���ܺ���
  * ������minutiaA			������׼����ƥ��ϸ�ڵ㼯��
  *		  minutiaT			ƥ��ģ��
  *		  pMatchResult		��׼����ṹ��ָ��
  *		  bound_box			���޺д�С
  *		  simi_thr			���ƶ���ֵ
  *		  angle_thr			�������˽ṹ�Ƕ����
  *		  central_thr		��������Χ��ֵ
  *		  match_mode		��׼ģʽ:1:����ģʽ
  * ���أ�void
  * ˵��: ͼ���"����"��׼,��Ϊһ����Χ�ڵĴ�����׼
  *		  ָ��ͼ���������׼������:�ֲ���׼(CenteralMatching),
  *       �����(CoreMatching,DeltaMatching)��ȫ����׼(GlobalMatching),����Ҷ��
  *		  ����㷨:�������ĵ�����ǵ�.Ѱ��ͼ��������,���������λ�õ�ƫ�ƺ���ת
  *				   ��ͼ�������׼(MinutiaSetAlign)��ƥ��(MinutiaSetAlignMatch)
  *		  �ֲ���:�ڹ涨��һ����ͼ���м�����Ϊȡ�㷶Χ,�ֱ�ȡ��ͬ�ĵ������׼
  *				 ��ƥ��.
  *		  ȫ�ַ�:������ͼ��,�ֱ�ȥ��ͬ�ĵ������׼��ƥ��.
  *		  
  * �㷨: �ֱ�������ĵ�ƥ��(CoreMatching), ���ǵ�ƥ��(DeltaMatching)
  *		  �ֲ�ƥ��(CentralMatching)��ȫ��ƥ��(GlobalMatching)
*************************************************************************/
void  FPMinutiaSetMatching
(		  
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t angle_thr,
 int32_t central_thr,
 int32_t match_mode
 )
{

	//ϸ�ڵ㼯���е����ĵ�����ǵ�λ�ô洢����Ŀ�洢
	int32_t CoreA[FP_MAX_SINGULARYTY_NUM];
	int32_t CoreT[FP_MAX_SINGULARYTY_NUM];
	int32_t DeltaA[FP_MAX_SINGULARYTY_NUM];
	int32_t DeltaT[FP_MAX_SINGULARYTY_NUM];
	int32_t coreA_num;
	int32_t coreT_num;
	int32_t deltaA_num;
	int32_t deltaT_num;

	int32_t n, m;

	int32_t minA_num, minT_num;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//��ȡϸ�ڵ㼯���е����ĵ�����ǵ�λ�ô洢����Ŀ�洢
	coreA_num = 0;
	deltaA_num = 0;
	for (n = 0; n < FP_MAX_SINGULARYTY_NUM; n++) {
		CoreA[n] = 0;
		CoreT[n] = 0;
		DeltaA[n] = 0;
		DeltaT[n] = 0;
	}

	for (n = 0; n < minA_num; n++) {
		if (minutiaA->FPMinutiaArr[n].type == MinutiaTypeCore) {
			CoreA[coreA_num] = n;
			coreA_num++;
		}

		if (minutiaA->FPMinutiaArr[n].type == MinutiaTypeDelta) {
			DeltaA[deltaA_num] = n;
			deltaA_num++;
		}
	}

	coreT_num = 0;
	deltaT_num = 0;
	for (m = 0; m < minT_num; m++) {
		if (minutiaT->FPMinutiaArr[m].type == MinutiaTypeCore) {
			CoreT[coreT_num] = m;
			coreT_num++;
		}

		if (minutiaT->FPMinutiaArr[m].type == MinutiaTypeDelta) {
			DeltaT[deltaT_num] = m;
			deltaT_num++;
		}
	}

	//���ĵ�ƥ��
	if (coreA_num > 0 && coreT_num > 0) {
		CoreMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr,
			match_mode, CoreA, coreA_num, CoreT, coreT_num);

		// ����ǿ��ٱȶ�ģʽ�������ƶȴﵽһ���̶����˳�
		if (match_mode == MATCH_MODE_FAST && \
			pMatchResult->match_num >= 8) {
			//if (pMatchResult->similarity > 100) {		
			if (pMatchResult->similarity > simi_thr) {	
				return;
			}
		}
	}

	//���ǵ�ƥ��
	if (deltaA_num > 0 && deltaT_num > 0) {
		DeltaMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr,
			match_mode, DeltaA, deltaA_num, DeltaT, deltaT_num);

		//����ǿ��ٱȶ�ģʽ�������ƶȴﵽһ���̶����˳�
		if (match_mode == MATCH_MODE_FAST && pMatchResult->match_num >= 8) {
			//if (pMatchResult->similarity > 100) {		
			if (pMatchResult->similarity > simi_thr) {				
				return;
			}
		}
	} 

	//����ƥ��
	CentralMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr,
		angle_thr, central_thr, match_mode);
	if (match_mode == MATCH_MODE_FAST && \
		pMatchResult->match_num >= 8) {
		//if (pMatchResult->similarity > 100) {
		if (pMatchResult->similarity > simi_thr) {				
			return;
		}
	}

	//ȫ��ƥ��	
	GlobalMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr, angle_thr, match_mode);
	
}

