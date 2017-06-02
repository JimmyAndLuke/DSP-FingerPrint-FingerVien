/******************************************************************************
 * �ļ�����image_segment.h
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


#if !defined __IMAGE_SEGMENT_H
#define __IMAGE_SEGMENT_H

#include "../../bsp/bsp_header/z_mytype.h"
#include "../../sys/sys_header/sys_global.h"

#ifdef __cplusplus
extern "C" {
#endif

//�������Ͷ���:
#define CUR_MEAN	0
#define CUR_PRI1	1
#define CUR_PRI2	2
#define CUR_GAUS	3
#define CUR_TEND	4
#define CUR_STRI	5
#define CUR_MAX		6
#define CUR_MIN		7

#define FP_SEGMENT_W		13
#define FP_SOFTEN_S			2
#define FP_SEGMENT_TH		80



FunError_t GradsRSegment
(
 uint8_t *pSrc,  
 uint8_t *pGrads, 
 const int32_t size, 
 const int32_t step, 
 const int32_t threshold, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
);

void FVRSegment
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );


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
 );


void CurvatureSegmentV1
(
 uint8_t *pDst,
 uint8_t *pSrc,
 uint8_t *pSeg,
 int32_t cur_type, 
 int32_t size, 
 int32_t thr_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );



/******************************************************************************
*******************************************************************************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
*******************************************************************************
******************************************************************************/


//ȥ��ָ��ͼ���Ե���ĺڱ�
void FPBlackSegment
(
 //uint8_t *pDst,
 uint8_t *pSrc,
 //uint8_t *pGrads,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );

void FPBlackSegmentOrg
(
 //uint8_t *pDst,
 uint8_t *pSrc,
 //uint8_t *pGrads,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );

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
);









#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_SEGMENT_H */

