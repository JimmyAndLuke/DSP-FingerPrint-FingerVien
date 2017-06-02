/******************************************************************************
 * �ļ�����image_miscellaneous.c
 * ��  �ܣ�һЩ������ͼ�����
******************************************************************************/


#include "dip_header/image_miscellaneous.h"
//#include "../../bsp/bsp_header/z_mytype.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#undef  P
#define P(x, y)   p[(x) + (y)*pitch]
/************************************************************************
* ���ܣ��ԹǼ�ͼ�����ɨ�貢���
* ������p         ָ��Դͼ��������
*       pitch     ÿ������ռ�ֽ���
*       x         �˵�x����(���ӵ�x����)
*		  y         �˵�y����(���ӵ�y����)
*       part_num  ��ǰɨ���ı��
*       part_area ������¼��ͨ�����С�ļ�����
*       area_thr  �����ж���ֹ������,����������ֵ������ֵarea_thrʱ����ֹ��ǰɨ��
* ���أ�void
* ˵��: ����ͼ������Ϊ��ֵ����(0,1),��ͼ���ǹ��������
*       �����(x,y)�����ǹ�����ͼ��Ķ˵�����
* �㷨: 
*       1.����������ӵ�����(x,y)��ʼ����ɨ��,
*       2.�������ӵ�8�������ͨ�����¼����������:
*         (1)������ͨ�������ֹ����area_thr
*         (2)�Ƕ˵�
*			(3)���Ž����ĵ�
*         (4)���ӵ��ǽ����
*         ������������Ҫ��,���˳�����,����,����3
*       3.Ѱ����һ������,�����˷���ĵ���Ϊ��һ�����ӵ�,���ز���1
*       4.���ϵ���,ֱ����ֹ����.(��ֹ����Ϊ2�еļ�������)
*************************************************************************/
//void SkeletonBurrMarkOZ
//(
// uint8_t *p,
// const int32_t pitch,
// const int32_t   x,
// const int32_t   y,
// const int32_t   part_num, //��ͨ����ı��
// uint8_t *part_area,  //����ֵ����¼��ͨ����Ĵ�С
// const int32_t   area_thr
// )
//{
//	static int32_t x1,x2,x3,x4,x5,x6,x7,x8;
//	static int32_t temp1,temp2;
//
//	//1.����������ӵ�����(x,y)��ʼ����ɨ��
//	//ֱ���ж��Ƿ�Ϊ0,����ܿ��˱�Ǻ���ֵ��Ϊ(0,1)��ֵ,
//	//��ImageConditionThiningOZ��������Ա�ǵĴ���������ͬ��֮��
//	x1=((P(x+1, y  )==0)?0:1); //x1
//	x2=((P(x+1, y+1)==0)?0:1); //x2
//	x3=((P(x  , y+1)==0)?0:1); //x3
//	x4=((P(x-1, y+1)==0)?0:1); //x4
//	x5=((P(x-1, y  )==0)?0:1); //x5
//	x6=((P(x-1, y-1)==0)?0:1); //x6
//	x7=((P(x  , y-1)==0)?0:1); //x7
//	x8=((P(x+1, y-1)==0)?0:1); //x8
//
//	//2.�������ӵ�8�������ͨ�����¼
//	temp1=x1+x2+x3+x4+x5+x6+x7+x8;
//
//	/*temp2=abs(x1-x2)+abs(x2-x3)+abs(x3-x4)+abs(x4-x5)+
//	abs(x5-x6)+abs(x6-x7)+abs(x7-x8)+abs(x8-x1);*/	//����ϸ������ȫϸ��???
//	temp2=(x1&x2)+(x2&x3)+(x3&x4)+(x4&x5)+
//		(x5&x6)+(x6&x7)+(x7&x8)+(x8&x1);					//������ȫϸ��???
//
//
//	//(4).����ǽ����,����������б��ɨ��,Ҳ�����,��Ϊ��������
//	//��˵���ɵĿ�����һ���������������һС��ë��,��Ҫȥ����.
//	if((temp1>=3) && (temp2==0)){ 
//		return;		//4.���ϵ���,ֱ����ֹ����.(��ֹ����Ϊ2�еļ�������)
//	}
//
//	++(*part_area);	   //��¼�Ǽܳ���
//	P(x, y)=part_num;  //��Ǹõ㡣
//
//	/*
//	//����һ���˵㡣
//	if((temp1==1)&&(*part_area)>1){
//	return;
//	}
//	//�ǰ��Ž����ĵ�
//	if(temp1>=3&&temp2!=0){
//	return;
//	}
//	//������һ������ֵ���˳���
//	if(*part_area>area_thr){
//	return;
//	}*/
//
//	//(1).�Ǽܳ��ȳ�����ֵ,����������б��ɨ��.�������㹻��,���ᱻɾ��
//	//(2).�뽻��㰤�ŵĵ�,����������б��ɨ��(ע��˵㱻���),���ᱻɾ��.�˴�������4��ͬ
//	//(3).����һ���˵�,����������б��ɨ��,��ʱ����С����ֵ�Ĺ���С�߶�,���ᱻɾ��
//	//����ѹ�������ñ�����������·������
//	if(((*part_area) > area_thr) ||\
//		((temp1>=3) && (temp2!=0)) ||\
//		((temp1==1) && ((*part_area)>1))) {	
//			return;		//4.���ϵ���,ֱ����ֹ����.(��ֹ����Ϊ2�еļ�������)
//	}
//
//	//3.Ѱ����һ������,�����˷���ĵ���Ϊ��һ�����ӵ�,���ز���1
//	//��ͨ�㣬ȡ����һ����������
//	x1=((P(x+1, y  )==1)?1:0); //x1
//	x2=((P(x+1, y+1)==1)?1:0); //x2
//	x3=((P(x  , y+1)==1)?1:0); //x3
//	x4=((P(x-1, y+1)==1)?1:0); //x4
//	x5=((P(x-1, y  )==1)?1:0); //x5
//	x6=((P(x-1, y-1)==1)?1:0); //x6
//	x7=((P(x  , y-1)==1)?1:0); //x7
//	x8=((P(x+1, y-1)==1)?1:0); //x8
//	//���㷽��
//	temp1=(x8<<7)|(x7<<6)|(x6<<5)|(x5<<4)|(x4<<3)|(x3<<2)|(x2<<1)|x1;
//
//	if(temp1==0){
//		return;//��һ�����Ѿ�����ǡ�
//	}
//	//���ݷ������һ�������ɨ��
//	switch(temp1){
//	case 0x01: SkeletonBurrMarkOZ(p, pitch, x+1, y  , part_num, part_area, area_thr);
//		break;
//	case 0x02: SkeletonBurrMarkOZ(p, pitch, x+1, y+1, part_num, part_area, area_thr);
//		break;
//	case 0x04: SkeletonBurrMarkOZ(p, pitch, x  , y+1, part_num, part_area, area_thr);
//		break;
//	case 0x08: SkeletonBurrMarkOZ(p, pitch, x-1, y+1, part_num, part_area, area_thr);
//		break;
//	case 0x10: SkeletonBurrMarkOZ(p, pitch, x-1, y  , part_num, part_area, area_thr);
//		break;
//	case 0x20: SkeletonBurrMarkOZ(p, pitch, x-1, y-1, part_num, part_area, area_thr);
//		break;
//	case 0x40: SkeletonBurrMarkOZ(p, pitch, x  , y-1, part_num, part_area, area_thr);
//		break;
//	case 0x80: SkeletonBurrMarkOZ(p, pitch, x+1, y-1, part_num, part_area, area_thr);
//		break;
//	default:printf("SkeletonBurrMarkOZ�������󣬵�������%d\n",*part_area);
//		//	break;
//	}
//}


/************************************************************************
* ���ܣ���ɨ���Ǻ�ĹǼ�ͼ��������ë��
* ������p         ָ��Դͼ��������
*       w         ͼ����
*		  h         ͼ��߶�
*       pitch     ÿ������ռ�ֽ���
*       part_area ������¼��ͨ�����С�ļ�����
*       area_thr  �����ж���ֹ������,����������ֵ������ֵarea_thrʱ����ֹ��ǰɨ��
* ���أ�void
* ˵��: ����ͼ������Ϊ��ֵ����(0,1),��ͼ���ǹ��������
*       �����(x,y)�����ǹ�����ͼ��Ķ˵�����
*************************************************************************/
//void SkeletonBurrClearOZ
//(
// uint8_t *p,
// const int32_t   w,
// const int32_t   h,
// const int32_t   pitch,
// uint8_t *part_area,
// const int32_t   area_thr 
// )
//{
//	int32_t x,y;
//	for(y=0;y<h;y++){
//		for(x=0;x<w;x++){
//			switch(P(x, y))
//			{
//			case 0:
//			case 1:
//				break;
//			default:
//				P(x, y)=part_area[P(x, y)]>area_thr?1:0;
//			}//end switch
//		}//end for ( j=0...
//	}//end for ( i=0...
//}


/************************************************************************
* ���ܣ����ͼ�������
* ������p         ָ��Դͼ��������
*       w         ͼ����
*		  h         ͼ��߶�
* ���أ�void
* ˵��: ����ͼ������Ϊ��ֵ����(0,1)
*************************************************************************/
//void RemoveAcnode
//(
// uint8_t *p,
// const int32_t   w,
// const int32_t   h,
// const int32_t   pitch
// )
//{
//	int32_t x, y;
//	int32_t x1, x2, x3, x4, x5, x6, x7, x8;
//	int32_t temp1;
//	for (y = 1; y < h-1; y++) {
//		for (x = 1; x < w-1; x++) {
//			x1=P(x  , y+1); 
//			x2=P(x+1, y+1); 
//			x3=P(x+1, y  ); 
//			x4=P(x+1, y-1); 
//			x5=P(x  , y-1); 
//			x6=P(x-1, y-1); 
//			x7=P(x-1, y  ); 
//			x8=P(x-1, y+1); 
//			temp1 = (x1|x2|x3|x4|x5|x6|x7|x8);
//			P(x, y) = (P(x, y) & temp1);
//		}
//	}
//}

/******************************************************************************
  * ���ܣ�4������ͨ�������
  * ������pSrc			ͼ������ָ��(ͼ��Ϊ��ֵͼ��)
  *       width			����ͼ����
  *       height			����ͼ��߶�
  *       pitch			����ͼ��ÿ���ֽڸ���
  *       x				���ӵ�x����
  *       y				���ӵ�y����
  *       end_area		�ж���ֹ����,Ϊ0ʱ��ȫ���,����ֵʱ,��>end_area��ֹͣ���
  *       mark_gary		ʹ�ô�ֵ�����������ĻҶ�ֵ
  * ���أ������������
  * ˵��: ͼ��Ϊ��ֵͼ��,����һ��Ҫ��0,1��ֵ
  * �㷨:
  *       1.���ж�(x,y)������ɫ�����Ƿ�Ϊcolor_type���Ƿ������Ϊmark_gary,
  *         ���˳�,����벽��2
  *       2.�ӵ�i=y�п�ʼ,��������(j=0~width)�������ؽ���ɨ��,�ж�ɨ���
  *		  ��ǰ���Ƿ������Ϊmark_gary,������,��������2,ɨ����һ��.����,���벽��3
  *       3.�жϵ�ǰ��4�������Ƿ��е������ӵ���ͬһ����(temp_color)��û�б��,����
  *         ���벽��2.���ǽ��벽��4
  *       4.���4����ĵ�Ϊmark_gray,���������++.ͬʱ�ж�4����ĵ��Ƿ��ڵ�i��ǰ,
  *         ����,ʲô����.����,����yMin��bNew���.�ڱ���iɨ����Ϻ�,ʹi=yMin-1.
******************************************************************************/
int32_t FourNeighbor
(
 uint8_t *pSrc,
 const int32_t width,
 const int32_t height,
 const int32_t pitch,
 const int32_t x,
 const int32_t y,
 const int32_t color_type,
 const int32_t end_area,
 const uint8_t mark_gray
 )
{
	uint8_t *pS;
	int32_t i, j, k;
	int32_t yMin, tempy, bNew;
	int32_t temp_color;
	int32_t tempI;
	int32_t region_area = 0; //��ͨ�����

	//��,����,��,����...
	//int32_t	SiteD4[4] = {-1, -pitch, 1, pitch};
	int32_t SiteD4[4];
	SiteD4[0] = -1;	SiteD4[1] = -pitch;	SiteD4[2] = 1;	SiteD4[3] = pitch;

	//�������ӵ����ɫֵ
	temp_color = pSrc[y*pitch+x];
	
	//1.���ж�(x,y)������ɫ�����Ƿ�Ϊcolor_type���Ƿ������Ϊmark_gary
	if ((temp_color == color_type) && temp_color != mark_gray) {
		pSrc[y*pitch+x] = mark_gray;
	} else {
		return region_area;
	}

	region_area = 1;

	//2.�ӵ�i=y�п�ʼ,��������(j=0~width)�������ؽ���ɨ��,�ж�ɨ���
	//��ǰ���Ƿ������Ϊmark_gary
	for (i = y; i < height; i++) {
		bNew = 0;
        yMin = i;
		tempI = i*pitch;
		pS = pSrc + tempI;
		for (j = 0; j < width; j++) {
			if ((*(pS+j) == mark_gray)) {
				for (k = 0; k < 4; k++) {
					//��ֹԽ��
					if ((tempI+j+SiteD4[k]) < 0 || \
						(tempI+j+SiteD4[k]) > ((width)*(height))) {
							continue;
					}

					//3.�жϵ�ǰ��8�������Ƿ��е������ӵ���ͬһ����(color_type)
					//��û�б��
					if (((*(pS+j+SiteD4[k])) == color_type) && \
						((*(pS+j+SiteD4[k])) != mark_gray)) {

						//4.���8����ĵ�Ϊmark_gray,���������++.
						//ͬʱ�ж�8����ĵ��Ƿ��ڵ�i��ǰ
						(*(pS+j+SiteD4[k])) = mark_gray;
						region_area++;

						if ((end_area != 0) && (region_area > end_area)) {
							return region_area;
						}

						tempy = (tempI+j+SiteD4[k]) / pitch;
						if (tempy <= yMin) {
							yMin = tempy;
							if(bNew == 0) {
								bNew = 1;
							}
						}
					}			
				}
			}
		}

		if(bNew) {
			i= yMin - 1;
        }
	}

	return region_area;

}

/******************************************************************************
  * ���ܣ�ͼ��������ͨ������
  * ������
  *		  pSrc			ͼ������ָ��(ͼ��Ϊ��ֵͼ��)
  *		  region_num	��ͨ����������(�����Ԫ��ֵ��Ӧ�ı�������С)
  *       width			����ͼ����
  *       height		����ͼ��߶�
  *       pitch			����ͼ��ÿ���ֽڸ���
  * ���أ�
  * ˵��: ��ǵ������Ŵ�2��ʼ,����ԭͼ����Ϊ0��ֵ��Ϊż�����(2,4,...)
  *		  ԭͼ����Ϊ1��ֵ��Ϊ�������(3,5,...)
  *		  һ��������region_num����RegionAreaFilter��������С����ȥ�봦��
  * �㷨: 1.��ͼ��������������,�����������ɨ�貢����8����(4����)��亯�����б��
  *		  2.���ݱ��ֵ��ͼ��������������,�����������ɨ�貢��¼��region_num������
******************************************************************************/
void RegionMarkOZ
(
 uint8_t *pSrc,
 int32_t *region_num,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	uint8_t *pS;
	//int32_t k;
	int32_t tempY = 0;
	int32_t mark_num1, mark_num2;
	mark_num1 = 3;
	mark_num2 = 2;

	//1.��ͼ��������������,�����������ɨ�貢����8����(4����)��亯�����б��
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (*(pSrc+y*pitch+x) == 1) {
				//EightNeighbor(pSrc, width, height, pitch, x, y, 0, mark_num1);
				FourNeighbor(pSrc, width, height, pitch, x, y, 1, 0, mark_num1);
				mark_num1+=2;
			}
			if (*(pSrc+y*pitch+x) == 0) {
				//EightNeighbor(pSrc, width, height, pitch, x, y, 0, mark_num2);
				FourNeighbor(pSrc, width, height, pitch, x, y, 0, 0, mark_num2);
				mark_num2+=2;
			}
		}
	}

	//2.���ݱ��ֵ��ͼ��������������,�����������ɨ�貢��¼��region_num������
	tempY = 0;
	for (y = 0; y < height; y++) {
		pS = pSrc + tempY;
		for (x = 0; x < width; x++) {
			region_num[*(pS+x)]++;
		}
		tempY += pitch;
	}
}

/******************************************************************************
  * ���ܣ�ͼ����������ȥ�봦��
  * ������
  *		  pSrc			������ǵ�ͼ������
  *		  region_num	��ͨ����������(�����Ԫ��ֵ��Ӧ�ı�������С)
  *		  fore_area_thr	ǰ��ɫ������ֵ
  *		  back_area_thr	����ɫ������ֵ
  *       width			����ͼ����
  *       height		����ͼ��߶�
  *       pitch			����ͼ��ÿ���ֽڸ���
  * ���أ�
  * ˵��: 
******************************************************************************/
void RegionAreaFilter
(
 uint8_t *pSrc,
 int32_t *region_num,
 const int32_t fore_area_thr,
 const int32_t back_area_thr,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch 
 )
{
	int32_t x, y;
	int32_t tempY;
	tempY = 0;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			switch (pSrc[tempY+x]) {
			case 0:
			case 1:
				//pSrc[tempY+x] = 0;
				break;
			default:
				if (pSrc[tempY+x]&0x01) {	//��ͨ����>fore_area_thr����Ϊ1
					pSrc[tempY+x] = ((region_num[pSrc[tempY+x]] > fore_area_thr) ? 1 : 0);
				} else {	//��ͨ����<back_area_thr����Ϊ1
					pSrc[tempY+x] = ((region_num[pSrc[tempY+x]] < back_area_thr) ? 1 : 0);
				}
				break;
			}
		}
		tempY += pitch;
	}
}




/******************************************************************************
*******************************************************************************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
************************����ĺ�����ָ�ƾ��н�ǿ��������***********************
*******************************************************************************
******************************************************************************/



/************************************************************************
  * ���ܣ�Ѱ�ҵ�ǰ�����һ��Ч��,��SkeletonBurrClearV1�ȵ���
  * ������pNow				��ǰ��ĵ�ַ[In]
  *		  width				ǰ����ĵ�ַ[In]
  *		  ppNext			��һ����ĵ�ַ��ָ��[Out]
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  *		  forecolor		    ͼ������ǰ����ɫ
  *		  backcolor		    ͼ�����ݱ�����ɫ
  * ���أ�0:��ȷ�ҵ�.1:û�ҵ����ҵ����
  * ˵��: ��SkeletonBurrClearV1����,��image_feature�еĺܶຯ������
*************************************************************************/
int32_t GetNext
(
 uint8_t *pNow, 
 uint8_t *pLast, 
 uint8_t **ppNext, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t forecolor
 )
{
	int32_t i;
	uint8_t *pS = NULL;
	int32_t n;
	uint8_t *Temp[8];	// ĳ����Χ8����ĵ�ַ
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;
	
	*ppNext = NULL;

	//�ҵ���ǰ����Χ���Ǻڵ�(ǰ����)���Ҳ���ǰ����ĺڵ�(ǰ����)�����浽����
	n = 0;
	for(i = 0; i < 8; i++) {
		pS = pNow + SiteD8[i];
		//if(*pS == 0 && pS != pLast) {
		if(*pS == forecolor && pS != pLast) {
			Temp[n] = pS;
			n++;
		}
	}

	if(n == 0) {		// û���ҵ������ڵ����ʾû�к�̵�
		*ppNext = NULL;
		return 1;
	} else if(n == 1) {	// �ҵ���һ��������Ϊ��̵�
		*ppNext = Temp[0];
		return 0;
	} else {			// �ҵ�������򷵻ش���
		*ppNext = NULL;
		return 1;
	}

	//return 0;
}

/************************************************************************
  * ���ܣ��ж����ڵ��Ƿ�Ϊ�����,��SkeletonBurrClearV1�ȵ���
  * ������pNow				��ǰ��ĵ�ַ[In]
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  *		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)
  * ���أ���Ϊ�����,����1.	��������0
  * ˵��: ��SkeletonBurrClearV1����,��image_feature�еĺܶຯ������
*************************************************************************/
int32_t IsFork
(
 uint8_t *pNow, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t bina_type
 )
{
	int32_t i, sum, sub_sum;
	//int32_t sum8;
	int32_t sub_sum8;
	// ĳ����Χ8����ĵ�ַƫ��
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;
	// 8������������������Ĳ�ľ���ֵ�ĺ����Ϊ6*255��Ϊ���
	sum = 0;
	sub_sum = 0;
	for(i = 0; i < 8; i++) {
		//�Ż�ǰ
		sub_sum += abs(*(pNow + SiteD8[(i+1)%8]) - *(pNow + SiteD8[i]));
		sum += *(pNow+SiteD8[i]);
	}

	//���ǽ����,���0-1�任3��(��Ч��1-0�任3��),
	//��˹���6�β�ֵ�任,�ܺ�Ϊ6*(|1-0|��|255-0|)
	if (bina_type == 1)	{	//0,1��ֵ 
		sub_sum8 = 6 * 1;
//		sum8 = 5;
	} else {				//0,255��ֵ
		sub_sum8 = 6 * 255;	
		//����ɫΪ255
//		sum8 = 5 * 255;
	}

	if(sub_sum == sub_sum8)
		return 1;
	else
		return 0;
}

/************************************************************************
  * ���ܣ��ж����ڵ��Ƿ�Ϊ�˵�,��SkeletonBurrClearV1�ȵ���
  * ������pNow				ϸ����ͼ��ĵ�ǰ��ĵ�ַ[In]
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  *		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)
  * ���أ���Ϊ�����,����1.	��������0
  * ˵��: ��SkeletonBurrClearV1����,��image_feature�еĺܶຯ������
*************************************************************************/
int32_t IsEnd
(
 uint8_t *pNow, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t bina_type
 )
{
	int32_t i, sum, sub_sum;
	//int32_t sum8, 
	int32_t sub_sum8;
	// ĳ����Χ8����ĵ�ַƫ��
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;


	// 8������������������Ĳ�ľ���ֵ�ĺ����Ϊ6*255��Ϊ���
	sum = 0;
	sub_sum = 0;
	//asum = 0;
	for(i = 0; i < 8; i++) {
		sub_sum += abs(*(pNow + SiteD8[(i+1)%8]) - *(pNow + SiteD8[i]));
		sum += *(pNow+SiteD8[i]);
	}


	//����ĩ�ҵ�,���0-1�任1��(��Ч��1-0�任1��),
	//��˹���2�β�ֵ�任,�ܺ�Ϊ2*(|1-0|��|255-0|)
	//�Ż�ǰ
	//if(sum == 255*2)
	if (bina_type == 1)	{//0,1��ֵ
		sub_sum8 = 2 * 1;
//		sum8 = 7;
	} else {				//0,255��ֵ
		sub_sum8 = 2 * 255;	
//		sum8 = 7*255;
	}
	//if(sub_sum == sub_sum8 && sum == sum8)
	if(sub_sum == sub_sum8)
		return 1;
	else
		return 0;
}


/************************************************************************
  * ���ܣ������߸����ҵ����뵱ǰ�����Ϊdis�ĵ�,�������ַ
  * ������pPoint			ϸ����ͼ��ĵ�ǰ��ĵ�ַ[In]
  *		  ppPos				���뵱ǰ��dis�ĵ�ĵ�ַ��ָ��[Out]
  *		  dis				���پ���(���ص����)
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  *		  forecolor		    ͼ������ǰ����ɫ
  *		  backcolor		    ͼ�����ݱ�����ɫ
  * ���أ����ҵ�����0, ����:����1
  * ˵��: ��image_feature�еĺܶຯ������
*************************************************************************/
int32_t  GetPointByDis
(
 uint8_t *pPoint, 
 uint8_t **ppPos, 
 int32_t dis,
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t forecolor,
 const int32_t bina_type
 )
{

	int32_t i, n;
	uint8_t *pNow = NULL;
	uint8_t *pLast = NULL;
	uint8_t *pNext = NULL;
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	*ppPos = NULL;

	// �ҵ���ǰ����Χ���Ǻڵ㲢�Ҳ���ǰ����ĺڵ㣬���浽����
	n = 0;
	for(i = 0; i < 8; i++) {
		//if(*(pPoint + SiteD8[i]) == 0)
		if(*(pPoint + SiteD8[i]) == forecolor) {
			pNow = pPoint + SiteD8[i];
			n++;
		}
	}
	if(n != 1) {	// ��Ŀ�������1�򷵻ش���
		return 1;
	}

	// �ҵ��ĺڵ��ַΪpNow
	// �˵���Ϊǰ����,��ַ���浽pLast
	pLast = pPoint; 
	// ѭ����dis�κ�̵�
	for(i = 0; i < dis; i++) {
		// ����ǲ��������ѭ��
		if(IsFork(pNow, pitch, bina_type)) {	
			break;
		}
		// �ɹ��ҵ���һ��������ĵ�ǰ���ǰ����
		if(GetNext(pNow, pLast, &pNext, pitch, forecolor) == 0) {	
			pLast = pNow;
			pNow = pNext;
		} else {
			break;
		}
	}

	// ����ҵ��ĵ�Ϊ��㣬�򷵻���ǰ����
	if(IsFork(pNow, pitch, bina_type)) {
		*ppPos = pLast;
	} else {			// ���򷵻ص�ǰ��
		*ppPos = pNow;
	}

	return 0;
}


/************************************************************************
  * ���ܣ������ϸ��ͼ���ж̰���ë��
  * ������pSrc				ָ��Դͼ��������
  *		  area_thr			�̰���ë�̵���󳤶�
  *		  width				ͼ�����ݿ��
  *		  height			ͼ�����ݸ߶�
  *		  pitch				ͼ������ÿ���ֽ���
  *		  forecolor		    ͼ������ǰ����ɫ
  *		  backcolor		    ͼ�����ݱ�����ɫ
  *		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)
  * ���أ�void
  * ˵��: �������������ԭ��,�������ú�����������ʽ(�ο�SkeletonBurrMarkOZ)
  *	�㷨: 1.����ͼ���ÿһ���ص�,������8����.
  *  		(1)��Ϊ�����ĵ����Ϊ������,�����벽��1������һ��ı���
  *			(2)��Ϊ�˵�,��¼�������ĳ����Ϊ�µĵ�,�����벽��2
  *		  2.�ɴ˵㿪ʼɨ��·��(���߸���)area_thr����.
  *		    (1)���˵��������(����IsFork�����ж�),ֱ�ӽ����˴θ���,���벽��4
  *			(2)��¼�˵��ַ,����Ѱ��һ��(����GetNext),
  *			   ���ҵ���һ��,�������в���2.
  *			   ����Ҳ�����һ��,����벽��3.
  *			   ����ɨ��·������area_thr.���벽��4
  *		  3.���ղ�ɨ�����·�����Ϊ������
  *		  4.������һ�����ص�,ֱ��ȫ����������.
  * ע��:����ͼ������Ϊ��ֵ����(0,1)��(0,255),��ǰ��ɫ����Ϊ0???
*************************************************************************/
void SkeletonBurrClearV1
(
 uint8_t *pSrc, 
 const int32_t area_thr, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const int32_t forecolor,
 const int32_t backcolor,
 const int32_t bina_type
 )
{
	int32_t	x, y;
	int32_t i, n, num;
	int32_t tempY;
	uint8_t *Line[25];			//��¼·��ÿ��ĵ�ַ,����25,ʵ��Ӧ�ø���area_thr
	//���ж�̬����
	uint8_t *pNow = NULL;		//ָ��ǰ��ָ��
	uint8_t *pLast = NULL;		//ָ��ǰ����ָ��(������һ����˵,������һ��pNowΪһֱ)
	uint8_t *pNext = NULL;		//ָ����һ��ָ��
	uint8_t *tempPtr[8];		//�����ݴ�8����ĵ�ַ,ʵ�����õ�ΪtempPtr[0]
	// ĳ����Χ8����ĵ�ַƫ��
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	tempY = 0;
	for(y = 0; y < height; y++) {
		//�Ż�ǰ
		//tempY = y*pitch;
		for(x = 0; x < width; x++) {
			pNow = pSrc + tempY + x;	//
			//if(*pNow != 0) {	//��ǰ����
			if(*pNow != forecolor) {	//��ǰ����
				continue;
			}

			Line[0] = pNow;				//��¼·���ϵĵ�һ���ַ
			// ͳ�Ƶ�ǰ�����Χ�ڵ�(ǰ����)����
			n = 0;
			for(i = 0; i < 8; i++) {
				pNext = pNow + SiteD8[i];
				//if(*pNext == 0) {
				if(*pNext == forecolor) {
					tempPtr[n] = pNext;	//��¼8����ĵ�ַ,ʵ�����õ�ΪtempPtr[0]
					n++;
				}
			}
			//�ڵ����Ϊ�㣬��ʾ��ǰ���ǹµ㣬��Ϊ��ɫ(������)
			if(n == 0) {
				//*pNow = 255;
				*pNow = backcolor;
				continue;
			}
			//�ڵ�(������)����Ϊ1����ʾΪ�˵�.
			//���ҽ���Ϊ�˵�ʱ�Ž���·������,�����м�������㲻��������
			else if(n == 1) {
				num = 0;
				pLast = pNow;			//���浱ǰ���ַ��Ϊ��һ���ַ
				pNow = tempPtr[0];		//��ȡ��һ���ַ������Ϊ��ǰ���ַ
				//�����߸���area_thr����
				for(i = 0; i < area_thr; i++) {
					// ����������������ѭ��
					if(IsFork(pNow, pitch, bina_type)) {
						break;
					}				
					num++;				//��¼ɨ��·����������
					Line[num] = pNow;	//ͬʱ��¼·���ϵĵ�ĵ�ַ
					//��ȡ��һ���ַ
					if(GetNext(pNow, pLast, &pNext, pitch, forecolor) == 0) {
						pLast = pNow;	//���浱ǰ���ַ��Ϊ��һ���ַ
						pNow = pNext;	//��ȡ��һ���ַ������Ϊ��ǰ���ַ
					} else {// ��������쳣����ѭ��
						break;
					}

				}

				// ���߽϶̣���ʾΪ�̰�������ë��,���(��Ϊ������)
				if(num < area_thr) {
					for(i = 0; i <= num; i++) {
						//*Line[i] = 255;
						*Line[i] = backcolor;
					}
				}

			}
		}
		//�Ż���
		tempY += pitch;
	}

	//return 0;
}


























