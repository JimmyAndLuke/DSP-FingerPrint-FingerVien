/******************************************************************************
* �ļ�����image_feature.c
* ��  �ܣ���Ҫʵ��ͼ���������ȡ
******************************************************************************/
#include "dip_header/image_feature.h"

#include <math.h>


/************************************************************************
* ���ƣ�FVMinutiaSetExtractLowLevel
* ���ܣ���ϸ��ͼ������ȡϸ�ڵ㣬�����浽�����С�
*       �����ϸ�ڵ㼯�ϱ����㹻�����̫С�ˣ����˺��ֹͣ����ϸ�ڵ㡣
* ������minutia      ϸ�ڵ㼯�ϣ���������ϸ�ڵ�
*       image        ϸ�����ͼ��
* ���أ�������
* �㷨��
*          ע�⣺(1)ͼ���ǰ����"1",������"0"
*                (2)ͼ������ȫϸ����ͼ�񣬼�û���κ�����ĵ㡣
*
*          һ����p��8������ͼ��ʾ
*          ----------
*          |x4|x3|x2|
*          ----------
*          |x5|p |x1|
*          ----------
*          |x6|x7|x8|
*          ----------
*        
*          ��p�㼰������ͬʱ������������ʱp���������㡣
*
*          (1)p����"1",����ǰ�����Ǳ�����
*
*          (2)p���8����"1"�ĵ���Ϊ1,3,����4��
*
*             1)p���8����"1"�ĵ���Ϊ1��p���Ƕ˵㡣
*             2)p���8����"1"�ĵ���Ϊ3��p���������򽻲�㡣
*             3)p���8����"1"�ĵ���Ϊ4��p���������򽻲�㡣
*************************************************************************/
//static FunError_t FVMinutiaSetExtractLowLevel
//(
// pFVMinutiaSet_t minutia,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	//int32_t w      = ImageGetWidth(image);
//	//int32_t h      = ImageGetHeight(image);
//	//int32_t pitch  = ImageGetPitch(image);
//	//uint8_t* p    = ImageGetBuffer(image);
//	int32_t   x, y;
//	//int32_t i,j;
//	//int32_t all_cnt;    //������������
//	//int32_t epoint32_t_cnt; //�˵������
//	//int32_t jpoint32_t_cnt; //����������
//	int32_t t_h;
//	int32_t t_w;
//	int32_t temp1,temp2;
//	int32_t x1,x2,x3,x4,x5,x6,x7,x8; 
//	int32_t nbminutia;
//	t_h=height-1;
//	t_w=width-1;
//#undef  PSRC	
//#define PSRC(x, y)		pSrc[(x)+(y)*pitch]
//	//all_cnt   =0;
//	//epoint32_t_cnt=0;
//	//jpoint32_t_cnt=0;
//
//	//if (p==NULL)
//	//	return FunMemory;
//
//	//(void)FVMinutiaSetEmpty(minutia);
//	nbminutia = 0;
//	for(y=1;y<t_h;y++){
//		for(x=1;x<t_w;x++){
//
//			if(PSRC(x, y)==0){
//				continue;
//			}
//
//			x1=PSRC(x+1, y  ); //x1
//			x2=PSRC(x+1, y+1); //x2
//			x3=PSRC(x  , y+1); //x3
//			x4=PSRC(x-1, y+1); //x4
//			x5=PSRC(x-1, y  ); //x5
//			x6=PSRC(x-1, y-1); //x6
//			x7=PSRC(x  , y-1); //x7
//			x8=PSRC(x+1, y-1); //x8
//
//			temp1=x1+x2+x3+x4+x5+x6+x7+x8;
//			//temp2=abs(x1-x2)+abs(x2-x3)+abs(x3-x4)+abs(x4-x5)+
//			//  abs(x5-x6)+abs(x6-x7)+abs(x7-x8)+abs(x8-x1);	//����ϸ������ȫϸ��???
//			temp2=(x1&x2)+(x2&x3)+(x3&x4)+(x4&x5)+
//				(x5&x6)+(x6&x7)+(x7&x8)+(x8&x1);				//������ȫϸ��???
//
//			if(temp1==1){
//				//(void)MinutiaSetAdd(minutia, x, y,
//				//	MinutiaTypeEnd);
//				minutia->FVMinutiaArr[nbminutia].type = MinutiaTypeEnd;
//				minutia->FVMinutiaArr[nbminutia].x = x;
//				minutia->FVMinutiaArr[nbminutia].y = y;
//				//minutia->nbminutia++;
//				nbminutia++;
//				continue;
//			}
//
//			if(temp1>=3&&temp2==0){
//				//P(x, y) = 0;
//				//(void)MinutiaSetAdd(minutia, x, y,
//				//	MinutiaTypeFork);
//				minutia->FVMinutiaArr[nbminutia].type = MinutiaTypeFork;
//				minutia->FVMinutiaArr[nbminutia].x = x;
//				minutia->FVMinutiaArr[nbminutia].y = y;
//				//minutia->nbminutia++;
//				nbminutia++;
//			}
//
//			//nbminutia = MinutiaSetGetCount(minutia);
//			if (nbminutia >= FV_MAX_MINUTIA_NUM) {
//				return FunOK;
//			}
//
//		}//end for (j=1...
//	}//end for (i=1...
//
//	minutia->nbminutia = nbminutia;
//
//	return FunOK;
//}


/************************************************************************
* ���ƣ�FVMinutiaSetExtractLowLevel
* ���ܣ���ϸ��ͼ������ȡϸ�ڵ㣬�����浽�����С�
*       �����ϸ�ڵ㼯�ϱ����㹻�����̫С�ˣ����˺��ֹͣ����ϸ�ڵ㡣
* ������minutia      ϸ�ڵ㼯�ϣ���������ϸ�ڵ�
*       image        ϸ�����ͼ��
*       area_thr         ���ݸ����������Ĳ���,�����ж���ֹ������,
*                    ����������ֵ������ֵarea_thrʱ����ֹ��ǰɨ�衣             
* ���أ�������
* ���ã����Ѿ�ϸ������û���޼�ë�̵�ͼ����д���ֱ����ȡ�������㡣
* �㷨��
*          ��һ������ͼ�����������Ԥ��ȡ��
*          �ڶ������������������𲽽��бȶԣ��趨һ����������α������ȥ����
*          ��������ȥ��α�����������ȡһ�������㡣 
*************************************************************************/
//FunError_t FVMinutiaSetExtractOZ
//(
// pFVMinutiaSet_t minutia,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch,
// const int32_t area_thr
// )
//{
//	int32_t i;
//	//int32_t x, y;
//	int32_t nbminutia;
//	//Minutia_t* min;
//	uint8_t part_area[256];//��ǰ�˵��ɨ�������
//
//	//Ԥ��ȡ,0,1��ʹ��,��Ϊ��SkeletonBurrMarkOZ�б�ǵĹ�ϵ
//	part_area[0]=255;
//	part_area[1]=255;
//	for (i = 2; i < 256; i++){
//		part_area[i]=0;
//	}
//
//	FVMinutiaSetExtractLowLevel(minutia, pSrc, width, height, pitch);
//
//	nbminutia = minutia->nbminutia;
//
//	for (i = 0; i < nbminutia; i++){
//
//		if (minutia->FVMinutiaArr[i].type == MinutiaTypeFork)
//			continue;
//		//�������������㡣
//		SkeletonBurrMarkOZ(pSrc, pitch,
//			minutia->FVMinutiaArr[i].x,
//			minutia->FVMinutiaArr[i].y,
//			i+2,
//			&part_area[i+2],
//			area_thr
//			);
//		/*if(i>=255){
//		printf("pixel_get_feature_ex���������!\n");
//		}*/
//	}
//
//	//�������������㡣
//	SkeletonBurrClearOZ(pSrc, width, height, pitch, part_area, area_thr);
//
//	//������ȡһ�������㡣
//	FVMinutiaSetExtractLowLevel(minutia, pSrc, width, height, pitch);
//
//	return FunOK;
//}



void FVMinutiaSetDilateOZ
(
 uint8_t *pSrc,
 pFVMinutiaSet_t minutia,	
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	int32_t x1, y1;
	int32_t i;
	int32_t m, n;
	for (i = 0; i < minutia->nbminutia; i++) {
		x = minutia->FVMinutiaArr[i].x;
		y = minutia->FVMinutiaArr[i].y;

		for (m = -3; m <= 3; m++) {
			for (n = -3; n <= 3; n++) {
				x1 = x+n;
				y1 = y+m;
				if ((x1 < 0) || (x1 >= width) || \
					(y1 < 0) || (y1 >= height)) {
					continue;
				}
				*(pSrc + y1*pitch + x1) = 1;
			}
		}


	}

}

void FPMinutiaSetDilateOZ
(
 uint8_t *pSrc,
 pFPMinutiaSet_t minutia,	
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	int32_t x1, y1;
	int32_t i;
	int32_t m, n;
	for (i = 0; i < minutia->nbminutia; i++) {
		x = minutia->FPMinutiaArr[i].x;
		y = minutia->FPMinutiaArr[i].y;

		for (m = -3; m <= 3; m++) {
			for (n = -3; n <= 3; n++) {
				x1 = x+n;
				y1 = y+m;
				if ((x1 < 0) || (x1 >= width) || \
					(y1 < 0) || (y1 >= height)) {
					continue;
				}
				*(pSrc + y1*pitch + x1) = 0;
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


//!!!!!!!!!!!!ע��!!!!!!!!!!!!
//����ȡ����ʱ,ǰ��ɫΪ0,ͼ����0,1��ֵͼ��,��Ҫ����Ϊ:
#define BACKCOLOR		1
#define BINA_TYPE		1
//����ȡ����ʱ,ǰ��ɫΪ0,ͼ����0,255��ֵͼ��,��Ҫ����Ϊ:
//#define BACKCOLOR		255
//#define BINA_TYPE		255
#define RBACKCOLOR		255

/************************************************************************
* ���ܣ����ݵ�ĵ�ַ,������õ���ͼ���е�x����
* ������pPos				ָ��õ�ĵ�ַ
*		  pSrc				ָ��Դͼ��������
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
* ���أ��õ���ͼ���е�x����
* ˵��: 
*************************************************************************/
int32_t  M_PX(uint8_t *pPos, uint8_t *pSrc, uint32_t pitch)
{
	return ((pPos - pSrc) % pitch);
}

/************************************************************************
* ���ܣ����ݵ�ĵ�ַ,������õ���ͼ���е�y����
* ������pPos				ָ��õ�ĵ�ַ
*		  pSrc				ָ��Դͼ��������
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
* ���أ��õ���ͼ���е�y����
* ˵��: 
*************************************************************************/
int32_t  M_PY(uint8_t *pPos, uint8_t *pSrc, uint32_t pitch)
{
	return ((pPos - pSrc) / pitch);
}

/************************************************************************
* ���ܣ���������������,��ȡ����֮�䷽�򳡵ı仯
* ������angle1			�Ƕ�1
*		  angle2			�Ƕ�2
*		  flag				��������� 1:���ǵ�, ����:���ĵ�
* ���أ����򳡱仯�Ƕ�
* ˵��: 
*************************************************************************/
#define ORICHG	10
int32_t GetOrientChange(const int32_t angle1, const int32_t angle2, const uint8_t flag)
{
	int32_t  d;
	d = angle2 - angle1;
	if(flag == 1) {	//���ǵ�
		if(d < 0)
			d += ORICHG;
	} else {		//���ĵ�
		if(d > 0)
			d -= ORICHG;
	}
	return d;
}

/************************************************************************
* ���ܣ���ȡָ��ͼ��������
* ������minutia			ϸ�ڵ㼯��
*		  pOrientation		�����ָ�(����·�ָ�(�ַָ�)FPImageGradsRSegment)
*							���ͼ����
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  flag				��������� 1:���ǵ�, ����:���ĵ�
* ���أ�void
* ˵��: �ַָ�:�ָ�ROI�뱳��,ϸ�ָ�:ROI����������·�����·�ķָ�
* �㷨: 
*		  ԭ��: һ����,����������,����Χ�ķ��򳡱仯����.
*				�������ĵ�����ǵ����ȡ���ǻ������ԭ��.
*		    Ŀǰ��ȡָ��ͼ������㷽���кܶ��֣�������õ��ǻ���Poincare
*		  Index�ķ������÷���ͨ������ָ��ͼ��ķ���ͼ����ȡ����㡣
*		  �ڴ˶���Poincare IndexΪһ����������ϵĵ�(��Լ25��)�ķ���仯֮
*		  ��.��ָ�Ʒ���ͼ�Ϸ��������ʱ��һȦ,�������ϵ����ص㷽��仯֮��
*		  Ϊ0,��õ��Ӧ�����ص�����ͨ��.����Ϊ1/2,��õ��Ӧ�����ص������ĵ�,
*		  ��Ϊ-1/2,��õ��Ӧ�����ص������ǵ�
*		    �����ص�ķ��� Sita����[0, PI],��ɢ�����η�����ߵĳ���ΪL,���߳���
*		  ����̫С,��������α�����,̫������ܰ�����������.���������Χ
*		  �Ƶ����ص�(x,y)��Poincare Indexͨ�����¹�ʽ����:
*			Poincare(i,j)=1/(2PI)*Sigma<0,L-1>Delta(k)
*						   PI-Beta(k)	Beta(k)>=PI/2
*				Delta(k) = PI+Beta(k)   Beta(k)<=-PI/2
*						   Beta(k)		����
*		  			����Beta(k)=Sita((k+1)modL)-Sita(k).
*		  	  Ϊ�˼�Poincare Index��ȡ�����,�����߲���5x5�ķ���,
*		  		D12	D11	D10
*		  	D1	d1	d8	d7	D9
*		  	D2	d2	i,j	d6	D8
*		  	D3	d3	d4	d5	D7
*		  		D4	D5	D6
*		  	�ֱ������d��DΪ�뾶�������򳡲�ĺ�.
*		    ��5x5������,����Poincare Indexֵ,��(i,j)Ϊ����,��˳ʱ�뷽��
*		  �γɱպ�����D1,D2,...D12�ֱ��ʾ�õ�ķ���.�ñպ����ߵ�Poincare
*		  Indexֵ:
*					Poincare(i,j)=Sigma<1,12>|Di-D((i+1)mod12)|
*		  ͬ����3x3������:
*					Poincare(i,j)=Sigma<1,8>|di-d((i+1)mod8)|
*		    ����һЩָ��ͼ���������������,���ܴ���α�����,Ϊ������α�����.ֻ����
*		  3x3��5x5���������Poincareֵ(���ĵ�Ϊ1/2�����ǵ�Ϊ-1/2)��ͬ��ʱ��,
*		  �����������������.
*		    �����õ�����㸽�����������,�������ǵľ�ֵ��Ϊ���յ������
*************************************************************************/
void FPMinutiaSetExtractSingularity
(
 pFPMinutiaSet_t minutia,
 uint8_t *pOrientation, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const uint8_t flag 
 )
{
//	int32_t x, y, i;
//	int32_t num;			//��¼��������
//	int32_t sum1, sum2;		//3x3,5x5����ķ��򳡲�ֵ֮��
//	int32_t d;
//	uint8_t *pOri;			//ĳ�㷽��ָ��
//	int32_t ori_value;		//ĳ�㷽��ֵ
//	int32_t a1, a2;			//�Ƕ�
//	Point_t temp_arr[30];	//����������ݴ�,һ�㲻�ᳬ��30��,
//	//�����õ������������FP_MAX_SINGULARYTY_NUM����30
//	//int32_t nbminutia;
//	int32_t value;			//Poincareֵ
//	double dis;
//	int32_t found = 0;		//�Ƿ��ҵ�������־
//	int32_t bg_flag = 0;	//�������Ƿ��б�����־
//
//	//��ĳ��Ϊ����,3/2Ϊ�뾶��ƫ����(offset_x,offset_y)
//	int32_t    D3[8][2] = {
//		-1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
//	};
//	//��ĳ��Ϊ����,5/2Ϊ�뾶��ƫ����(offset_x,offset_y)
//	int32_t    D5[12][2] = {
//		-2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
//	};
//	//��ĳ��Ϊ����,7/2Ϊ�뾶��ƫ����(offset_x,offset_y)
//	int32_t    D7[24][2] = {
//		-3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
//		3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
//	};
//
//	num = 0;
//	if (flag == 1) {		//���ǵ�
//		value = ORICHG;
//	} else {			 //���ĵ�	
//		value = -ORICHG;
//	}
//
//	//memset(temp_arr, 0, sizeof(temp_arr));	//��ʼ����������飬����
//	for (i = 0; i < 30; i++) {
//		temp_arr[i].x = 0;
//		temp_arr[i].y = 0;
//	}
//
//	//���Ϊ7,�뾶7/2=3,���Ǳ߽����3��ʼ
//	for (y = 3; y < height-3; y++) {
//		for (x = 3; x < width-3; x++) {			//��������ͼ
//			pOri = pOrientation + y*pitch + x;		//���ĳ��ķ���ָ��
//			ori_value = *pOri;					//��ȡĳ��ķ��򳡵�ֵ
//
//			//ǰ����㷽�򳡺ʹַָ�ʱ,���ֱ�������ķ����趨Ϊ��255��
//			//if(ori_value == backcolor) {		//���Ǳ���������������һ��ѭ��
//			if (ori_value == 255)				//���Ǳ���������������һ��ѭ��
//				continue;
//
//			bg_flag = 0;									
//			for (i = 0; i < 24; i++) {//���ڰ뾶Ϊ7���������б���,��������һ��ѭ��
//				if(pOri[D7[i][1]*pitch + D7[i][0]]==255) {
//					bg_flag = 1;			
//					break;
//				}
//			}
//			if (bg_flag)
//				continue;
//
//			//����3x3�����Poincareֵ
//			sum1 = 0;
//			for (i = 0; i < 8; i++) {
//				//����ĵõ��ķ��򳡽Ƕ�/24����Ϊ
//				//ǰ����㷽�򳡵�ʱ���õ���12������
//				//ǰ����㷽�򳡵õ��ĽǶ���0-180֮��
//				//[180/24]=7,�����Ƕ�֮��Ϊ(-14, 14)
//				//����+-10������,���Ϊ(���ǵ�Ϊ��+10)
//				//���Ƕ�֮���Ϊ(-4, 14)
//				a1 = pOri[D3[i][1]*pitch + D3[i][0]]/24;
//				a2 = pOri[D3[(i+1)%8][1]*pitch + D3[(i+1)%8][0]]/24;
//				//GetOrientChange�����+-10Ӧ����24, 12�й�
//				d = GetOrientChange(a1, a2, flag);
//				//���5Ҳ��10,24,12�й�
//				if (abs(d) > 5) 
//					break;
//				sum1 += d;
//			}
//			//����5x5�����Poincareֵ
//			sum2 = 0;
//			for (i = 0; i < 12; i++) {
//				a1 = pOri[D5[i][1]*pitch + D5[i][0]]/24;
//				a2 = pOri[D5[(i+1)%12][1]*pitch + D5[(i+1)%12][0]]/24;
//				d = GetOrientChange(a1, a2, flag);
//
//				if(abs(d) > 5)
//					break;
//				sum2 += d;
//			}
//
//			//������Ȧ�ķ��򳡲�ֵ��ͬ,�˵�Ϊ�����
//			if (sum2 == value && sum1 == value) {
//				found = 0;
//				//�ȶ����ҵ����������֮ǰ�ҵ��������
//				for(i = 0; i < num; i++) {
//					dis = sqrt((double)((x - temp_arr[i].x)*(x - temp_arr[i].x) +
//						(y - temp_arr[i].y)*(y - temp_arr[i].y)));
//					//��������֮ǰ�ҵ���������ص�,����ƽ��λ����Ϊԭ������������
//					if(dis < 4) {		
//						temp_arr[i].x = (temp_arr[i].x + x)/2;
//						temp_arr[i].y = (temp_arr[i].y + y)/2;
//						found = 1;		//�����ҵ���־Ϊ1(û�ҵ�)
//						break;
//					}
//				}
//
//				//��û�з�����֮ǰ��������ص�,����Ϊ�µ������,��¼����
//				if (!found) {		//�ҵ����µ������,��ӵ�������ݴ�������
//					temp_arr[num].x = x;
//					temp_arr[num].y = y;
//					num++;
//					//���������������������ƣ���ֹͣѰ�������
//					if(num >= FP_MAX_SINGULARYTY_NUM) {	
//						goto GS_OUT;
//					}
//				}
//			}
//		}
//	}
//
//GS_OUT:
//
//	//nbminutia = minutia->nbminutia;
//	for (i = 0; i < num; i++) {	//���ҵ�������������������
//
//		x = temp_arr[i].x;
//		y = temp_arr[i].y;
//
//		//�ж�������Ƿ��ڱ�Ե����,����,������
//		if (((x + 0.0) / width < 0.1) || ((x + 0.0) / width > 0.9)) 
//			continue;
//		if (((y + 0.0) / height < 0.1 ) || ((y + 0.0) / height > 0.9))
//			continue;
//
//		//���ҵ����������ӵ�����������
//		if (flag == 1)	{	//���ǵ�
//			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeDelta, 0);
//			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeDelta;
//			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
//			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
//			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
//			minutia->nbminutia++;
//		} else {				//���ĵ�
//			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeCore, 0);
//			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeCore;
//			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
//			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
//			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
//			minutia->nbminutia++;
//		}
//		//nbminutia++;
//	}

	int32_t x, y, i;
	int32_t num;			//��¼��������
	int32_t sum1, sum2;		//3x3,5x5����ķ��򳡲�ֵ֮��
	int32_t d;
	uint8_t *pOri;			//ĳ�㷽��ָ��
	int32_t ori_value;		//ĳ�㷽��ֵ
	int32_t a1, a2;			//�Ƕ�
	Point_t temp_arr[30];	//����������ݴ�,һ�㲻�ᳬ��30��,
	//�����õ������������FP_MAX_SINGULARYTY_NUM����30
	//int32_t nbminutia;
	int32_t value;			//Poincareֵ
	//double dis;
	int32_t dis;
	int32_t found = 0;		//�Ƿ��ҵ�������־
	int32_t bg_flag = 0;	//�������Ƿ��б�����־

	//��ĳ��Ϊ����,3/2Ϊ�뾶��ƫ����(offset_x,offset_y)
	int32_t    D3[8][2] = {
		-1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
	};
	//��ĳ��Ϊ����,5/2Ϊ�뾶��ƫ����(offset_x,offset_y)
	int32_t    D5[12][2] = {
		-2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
	};
	//��ĳ��Ϊ����,7/2Ϊ�뾶��ƫ����(offset_x,offset_y)
	int32_t    D7[24][2] = {
		-3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
		3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
	};

	num = 0;
	if (flag == 1) {		//���ǵ�
		value = ORICHG;
	} else {			 //���ĵ�	
		value = -ORICHG;
	}

	//memset(temp_arr, 0, sizeof(temp_arr));	//��ʼ����������飬����
	for (i = 0; i < 30; i++) {
		temp_arr[i].x = 0;
		temp_arr[i].y = 0;
	}

	//���Ϊ7,�뾶7/2=3,���Ǳ߽����3��ʼ
	for (y = 3; y < height-3; y++) {
		for (x = 3; x < width-3; x++) {			//��������ͼ
			pOri = pOrientation + y*pitch + x;		//���ĳ��ķ���ָ��
			ori_value = *pOri;					//��ȡĳ��ķ��򳡵�ֵ

			//ǰ����㷽�򳡺ʹַָ�ʱ,���ֱ�������ķ����趨Ϊ��255��
			//if(ori_value == backcolor) {		//���Ǳ���������������һ��ѭ��
			if (ori_value == 255)				//���Ǳ���������������һ��ѭ��
				continue;

			bg_flag = 0;									
			for (i = 0; i < 24; i++) {//���ڰ뾶Ϊ7���������б���,��������һ��ѭ��
				if(pOri[D7[i][1]*pitch + D7[i][0]]==255) {
					bg_flag = 1;			
					break;
				}
			}
			if (bg_flag)
				continue;

			//����3x3�����Poincareֵ
			sum1 = 0;
			for (i = 0; i < 8; i++) {
				//����ĵõ��ķ��򳡽Ƕ�/24����Ϊ
				//ǰ����㷽�򳡵�ʱ���õ���12������
				//ǰ����㷽�򳡵õ��ĽǶ���0-180֮��
				//[180/24]=7,�����Ƕ�֮��Ϊ(-14, 14)
				//����+-10������,���Ϊ(���ǵ�Ϊ��+10)
				//���Ƕ�֮���Ϊ(-4, 14)
				a1 = pOri[D3[i][1]*pitch + D3[i][0]]/24;
				a2 = pOri[D3[(i+1)%8][1]*pitch + D3[(i+1)%8][0]]/24;
				//GetOrientChange�����+-10Ӧ����24, 12�й�
				d = GetOrientChange(a1, a2, flag);
				//���5Ҳ��10,24,12�й�
				if (abs(d) > 5) 
					break;
				sum1 += d;
			}
			//����5x5�����Poincareֵ
			sum2 = 0;
			for (i = 0; i < 12; i++) {
				a1 = pOri[D5[i][1]*pitch + D5[i][0]]/24;
				a2 = pOri[D5[(i+1)%12][1]*pitch + D5[(i+1)%12][0]]/24;
				d = GetOrientChange(a1, a2, flag);

				if(abs(d) > 5)
					break;
				sum2 += d;
			}

			//������Ȧ�ķ��򳡲�ֵ��ͬ,�˵�Ϊ�����
			if (sum2 == value && sum1 == value) {
				found = 0;
				//�ȶ����ҵ����������֮ǰ�ҵ��������
				for(i = 0; i < num; i++) {
					//dis = sqrt((double)((x - temp_arr[i].x)*(x - temp_arr[i].x) +
					//	(y - temp_arr[i].y)*(y - temp_arr[i].y)));
					dis = ((x - temp_arr[i].x)*(x - temp_arr[i].x) +(y - temp_arr[i].y)*(y - temp_arr[i].y));
					//��������֮ǰ�ҵ���������ص�,����ƽ��λ����Ϊԭ������������
					//if(dis < 4) {	
					if (dis < 16) {
						temp_arr[i].x = (temp_arr[i].x + x)/2;
						temp_arr[i].y = (temp_arr[i].y + y)/2;
						found = 1;		//�����ҵ���־Ϊ1(û�ҵ�)
						break;
					}
				}

				//��û�з�����֮ǰ��������ص�,����Ϊ�µ������,��¼����
				if (!found) {		//�ҵ����µ������,��ӵ�������ݴ�������
					temp_arr[num].x = x;
					temp_arr[num].y = y;
					num++;
					//���������������������ƣ���ֹͣѰ�������
					if(num >= FP_MAX_SINGULARYTY_NUM) {	
						goto GS_OUT;
					}
				}
			}
		}
	}

GS_OUT:

	//nbminutia = minutia->nbminutia;
	for (i = 0; i < num; i++) {	//���ҵ�������������������

		x = temp_arr[i].x;
		y = temp_arr[i].y;

		//�ж�������Ƿ��ڱ�Ե����,����,������
		//if (((x + 0.0) / width < 0.1) || ((x + 0.0) / width > 0.9)) 
		//	continue;
		//if (((y + 0.0) / height < 0.1 ) || ((y + 0.0) / height > 0.9))
		//	continue;
		if ((x < width/10) || (x   > width*9/10)) 
			continue;
		if ((y < height/10 ) || ((y) > height*9/10))
			continue;


		//���ҵ����������ӵ�����������
		if (flag == 1)	{	//���ǵ�
			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeDelta, 0);
			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeDelta;
			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
			minutia->nbminutia++;
		} else {				//���ĵ�
			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeCore, 0);
			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeCore;
			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
			minutia->nbminutia++;
		}
		//nbminutia++;
	}

	//����FPMinutiaSetExtractEndAndFork�����FPMinutiaSetExtractSingularityǰ
	//����ȡָ�������㼯ǰ,Ӧ���ȳ�ʼ��minutia->nbminutia = 0;
	//minutia->nbminutia += nbminutia;
}

/************************************************************************
* ���ܣ��жϵ�(x,y)��ֱ߽������r����
* ������pOrietation		�ַָ��ͼ��������
*		  x					�����x
*		  y					�����y
*		  r					�߽���ֵr
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  rbackcolor		�ֱ���ɫ��ɫ(ָ�ַָ���ROI�������ɫ)
* ���أ�1: ���� 0: ��
* ˵��: ����Ĵֱ߽���ָ�ַָ��ROI�������ROI����ı߽�.
*		  û�н���ͼ�������Խ�紦��,��˵��ô˺���Ҫ��֤����Խ��
*************************************************************************/
int32_t IsAtEdge
(
 uint8_t *pOrietation, 
 const int32_t x, 
 const int32_t y, 
 const int32_t r, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch, 
 const int32_t rbackcolor
 ) 
{
	int32_t i, j;
	int32_t flag = 1;

	for (i = -r; i <= r && flag; i++) {			//�����Ͳ���ʹ��goto��
		for (j = -r; j <= r && flag; j++) {
			//û�н���Խ�紦��,��˵��ô˺���Ҫ��֤����Խ��
			//if(y+i<0 || y+i>=height || x+j<0 || x+j>=width) {	
			//	continue;
			//}
			//ǰ����㷽�򳡺ͷָ�ʱ,����������ķ����趨Ϊ��255
			if (*(pOrietation + (y+i)*pitch + x + j) == rbackcolor) {
				flag = 0;		
				break;		//���ǰ����ж�û��ʹ��&&flag,��breakֻ��
				//���������ѭ��,Ҫ��������Ҫ�õ�goto����
				//������һ��ʹ��&&flag����Ϊһ���ж�����.
			}
		}
	}
	return flag;
}

/************************************************************************
* ���ܣ��жϵ�(x,y)�ķ��򳡱仯�Ƿ����
* ������pOrietation		�ַָ��ͼ��������
*		  x					�����x
*		  y					�����y
*		  site				��(x,y)ΪԲ��,�뾶Ϊr��Բ�����е�ĵ�ַƫ��
*		  site_num			��(x,y)ΪԲ��,�뾶Ϊr��Բ�����е�ĸ���
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  ori_thr		    ���򳡱仯�Ƿ���ҵ���ֵ
* ���أ�1: ������ 0: ����
* ˵��: ����Ĵֱ߽���ָ�ַָ��ROI�������ROI����ı߽�.
*		  û�н���ͼ�������Խ�紦��,��˵��ô˺���Ҫ��֤����Խ��
*************************************************************************/
int32_t IsOriChgViolent
(
 uint8_t *pOrietation, 
 const int32_t x, 
 const int32_t y, 
 int32_t *site, 
 const int32_t site_num,
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch, 
 const int32_t ori_thr
 ) 
{
	int32_t i;
	int32_t flag = 1;
	int32_t sum = 0;
	//û�н���Խ�紦��,��˵��ô˺���Ҫ��֤����Խ��
	for (i = 0; i < site_num; i++) {	//����뾶Ϊ5��28����ķ��򳡱任
		sum += GetAngle90In180(*(pOrietation+y*pitch+site[(i+1)%site_num]+x), *(pOrietation+y*pitch+site[i]+x));
	}
	//�趨ori_thr��Ϊ���ұ仯����ֵ
	if (sum > ori_thr)
		flag = 0;
	return flag;
}




/************************************************************************
* ���ܣ���ȡͼ��Ĵ�ĩ�ҵ�ʹֲַ��
* ������pSrc				ָ��Դͼ��������
*		  pOrientation		ָ��Դͼ��ַָ��ķ���
*		  pFork				�ֲ������洢����
*		  fork_num			�ֲ����Ŀ
*		  pEnd				ĩ�ҵ�����洢����
*		  end_num			ĩ�ҵ���Ŀ
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  r					�߽���ֵr(����Ĭ��16)
*		  ori_thr			���򳡱仯���ҳ̶�(Ĭ�ϰ뾶Ϊ5�ĵ�ı仯Ϊ96)
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  rbackcolor		�ֱ���ɫ��ɫ(ָ�ַָ���ROI�������ɫ)(Ĭ��255)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ�0:��ȷ��ȡ,1:����
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*		    ������Ѱ���������ʱ������ȥ������ͼ���Ե(�ֱ߽�)����Χ���򳡾��ұ仯
*		  ��α������
* �㷨: 
*		  1.����ͼ���ÿ����,���ж��Ƿ�Ϊ�ֲ���ĩ�ҵ�(IsFork��IsEnd����)
*		  2.���Ƕ˵��ĩ�ҵ�,���ж��Ƿ�����߽���ֵr(IsAtEdge)��
*		    ��Χ�����Ƿ�仯����(IsOriChgViolent).ֻҪ��һ��������,
*		  	���Ϊα������,����ӵ��洢������,���������в���1.����,����3.
*		  3.�洢�õ�����굽�洢������,����¼�洢������Ŀ.
*		  4.ֱ������������ͼ��,����.
*************************************************************************/
int32_t GetRawEndAndFork
(
 uint8_t *pSrc,
 uint8_t *pOrientation,
 Point_t *pFork,
 int32_t *fork_num,
 Point_t *pEnd,
 int32_t *end_num,
 const int32_t width,
 const int32_t height,
 const int32_t pitch
 //const int32_t r,
 //const int32_t ori_thr
 //const int32_t forecolor,
 //const int32_t rbackcolor,
 //const int32_t bina_type,
 )
{
	int32_t x, y;
	int32_t r = 16;			//��Ե�趨Ϊ16
	int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	int32_t rbackcolor = 255;//���򳡱���ɫΪ�׵�
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	int32_t bina_type = BINA_TYPE;
	int32_t ori_thr = 96;	//���򳡱任���ҳɶ�
	int32_t min_num = 0;
	int32_t min_num1 = 0;
	//uint8_t *pOri;
	uint8_t *pNow;
	int32_t tempY;
	int32_t flag;		//α��������, 0:α������,1:��
	//ĳ��ΪԲ�ģ��뾶Ϊ5��Բ�����е�ĵ�ַƫ��
	//int32_t	SiteR5[28] = {
	//	-5, pitch-5, 2*pitch-5, 3*pitch-4, 4*pitch-3, 5*pitch-2, 5*pitch-1, 5*pitch,
	//	5*pitch+1, 5*pitch+2, 4*pitch+3, 3*pitch+4, 2*pitch+5, pitch+5, 5, -pitch+5,
	//	-2*pitch+5, -3*pitch+4, -4*pitch+3, -5*pitch+2, -5*pitch+1, -5*pitch,
	//	-5*pitch-1, -5*pitch-2, -4*pitch-3, -3*pitch-4, -2*pitch-5, -pitch-5
	//}; 
	int32_t SiteR5[28];
	//ĳ����Χ8����ĵ�ַƫ��
	//int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	//int32_t SiteD8[8];
	
	SiteR5[0] = -5;		SiteR5[1] = pitch-5;	SiteR5[2] = 2*pitch-5;
	SiteR5[3] = 3*pitch-4;	SiteR5[4] = 4*pitch-3;	SiteR5[5] = 5*pitch-2;
	SiteR5[6] = 5*pitch-1;	SiteR5[7]=5*pitch;
	SiteR5[8] = 5*pitch+1;	SiteR5[9] = 5*pitch+2;	SiteR5[10]= 4*pitch+3;
	SiteR5[11] = 3*pitch+4;	SiteR5[12] = 2*pitch+5;	SiteR5[13] = pitch+5;
	SiteR5[14] = 5;	SiteR5[15] = -pitch+5;
	SiteR5[16] = -2*pitch+5;	SiteR5[17] = -3*pitch+4;	SiteR5[18] = -4*pitch+3;
	SiteR5[19] = -5*pitch+2;	SiteR5[20] = -5*pitch+1;	SiteR5[21] = -5*pitch;
	SiteR5[22] = -5*pitch-1;	SiteR5[23] = -5*pitch-2;	SiteR5[24] = -4*pitch-3;
	SiteR5[25] = -3*pitch-4;	SiteR5[26] = -2*pitch-5;	SiteR5[27] = -pitch-5;
	
	//SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	//SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	//SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	//�Ż���
	tempY = (r+1)*pitch;	//ǰ���������������㿿��ǰ����Ե���������r=16,
	//��˴�(r+1)��ʼ
	for (y = (r+1); y < height-(r+1); y++) {
		//�Ż�ǰ:
		//tempY = y*pitch;
		for (x = (r+1); x < width-(r+1); x++) {
			pNow = pSrc + tempY + x;
			//pOri = pOrientation + tempY + x;

			//if(*pNow != 0) {			//���Ǻڵ�(ǰ����)�򲻿���
			if (*pNow != forecolor) {	//���Ǻڵ�(ǰ����)�򲻿���
				continue;
			}

			//if (min_type == 1) {
			//�ǽ����
			if(IsFork(pNow, width, bina_type)) {	
				//����Ƿ񿿽���Ե, ������Ե�򲻿���
				flag = IsAtEdge(pOrientation, x, y, r, pitch, rbackcolor);
				//���õ���Χ�����Ƿ�仯����,
				//�仯�����򲻿���,��Ϊ�ܿ�������ٵ�
				flag &= IsOriChgViolent(pOrientation, x, y, SiteR5, 28, pitch, ori_thr);
				//�ﵽ����Ҫ�����¼�����õ�
				if(flag) {	
					pFork[min_num].x = x;
					pFork[min_num].y = y;
					min_num++;
					//��������Ѿ��������������Ŀ���򷵻ش���
					if(min_num >= FP_MAX_RAW_MINUTIA_NUM) {
						min_num = 0;
						return 1;
					}
				}
			}
			//} else {
			// ����Ƕ˵�
			else if (IsEnd(pNow, width, bina_type)) {
				// ����Ƿ񿿽���Ե, ������Ե�򲻿���
				flag = IsAtEdge(pOrientation, x, y, r, pitch, rbackcolor);

				//���õ���Χ�����Ƿ�仯����,
				//�仯�����򲻿���,��Ϊ�ܿ�������ٵ�
				flag &= IsOriChgViolent(pOrientation, x, y, SiteR5, 28, pitch, ori_thr);

				//�ﵽ����Ҫ�����¼�����õ�
				if(flag) {				
					pEnd[min_num1].x = x;
					pEnd[min_num1].y = y;
					min_num1++;
					// ��������Ѿ��������������Ŀ���򷵻ش���
					if(min_num1 >= FP_MAX_RAW_MINUTIA_NUM) {
						min_num1 = 0;
						return 1;
					}
				}
			}
			//}
		}
		//�Ż���
		tempY += pitch;
	}
	*fork_num = min_num;
	*end_num = min_num1;

	return 0;
}

/************************************************************************
* ���ܣ����αĩ�ҵ�
* ������pSrc				ָ��Դͼ��������
*		  pMinutia			��������ȡ������������洢����
*		  minutia_num		��������Ŀ
*		  fixed_dis			������֮��̶���С����
*		  var_dis			������֮�䶯̬��С����
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ�ûʲô����
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*		    ��������˾����С��α������Ͷ���֮��ĵ�α������
* �㷨: 
*		  1.��������������ȡһ��������1(A1)��2(B1),���ȼ�������֮��ľ���,
*		    ����С�����,������ȡ��һ��������.��֮,���벽��2
*		  2.������,���ж��Ƿ�Ϊһ���Ͽ������ߵ�����α����:
*		    �����߸�������,�ֱ��ҵ��������������ϵ�A2,B2.����A1A2�ĽǶ�angle1,
*		    B1B2�ĽǶ�angle2�����ǶȲ�Ϊ���,����α������.��֮,���벽��3
*		  3.����A1B1�ĽǶ�angle3.�ֱ��ж�angle1,angle2��angle3�ĽǶ�.
*		    ���ϴ�,����α������.��֮,���벽��4.
*		  4.��α������������Ϊ(0,0),����������һ��������.
*		    ֱ��������������������,����.
*************************************************************************/
int32_t ClearFakeEnd
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 const int32_t fixed_dis,
 const int32_t var_dis,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 )
{
	//int32_t i, j;
	//int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	////int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	////int32_t bina_type = 255;//0,255�Ķ�ֵ����
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	//uint8_t *pNow;
	//uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	//int32_t xDis, yDis;		//������ѭ����trace_len���ȵĵ������
	//int32_t xi, yi, xj, yj;	//��һ,�ڶ����˵������
	//int32_t flag;		//α��������, 0:α������,1:��
	//int32_t angle1, angle2, angle3, angle4;
	//double d; 

	//for (i = 0; i < minutia_num-1; i++) {
	//	flag = 1;
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	for (j = i+1; j < minutia_num; j++) {
	//		xj = pMinutia[j].x;
	//		yj = pMinutia[j].y;
	//		//�������˵�ľ���
	//		d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));

	//		//�����㹻��������һ���˵�
	//		if (d > fixed_dis && d > var_dis) {	//var_dis�ǿɱ仯�ĺ��ʵ���С����ֵ
	//			continue;
	//		}
	//		//����̫С,����������Ϊ(0��0)
	//		if (d <= var_dis) {
	//			pMinutia[j].x = 0;
	//			pMinutia[j].y = 0;
	//			flag = 0;
	//			continue;
	//		}

	//		//���һ���˵��������ߵĽǶ�
	//		pNow = pSrc + yi*pitch + xi;

	//		//��ȡ������ѭ����trace_len���ȵĵ�ĵ�ַ
	//		//if(GetByDis(pNow, &pDis, 8) != 0)
	//		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
	//			break;	//�ɶ˵㿪ʼ,���û���ҵ�,
	//		}			//����㲻��������������в���,ֱ��break,�������ּ�

	//		//��ȡ������ѭ����trace_len���ȵĵ������
	//		xDis = M_PX(pDis, pSrc, pitch);	
	//		yDis = M_PX(pDis, pSrc, pitch);
	//		angle1 = XY2Angle(xi, yi, xDis, yDis);

	//		//��ڶ����˵��������ߵĽǶ�
	//		pNow = pSrc + yj*pitch + xj;

	//		//��ȡ������ѭ����trace_len���ȵĵ�ĵ�ַ
	//		//if(GetByDis(pNow, &pDis, 8) != 0)
	//		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
	//			continue;	//�ɶ˵㿪ʼ,���û���ҵ�,
	//		}				//�������Ч,ֱ��continue,�������μ��

	//		//��ȡ������ѭ����trace_len���ȵĵ������
	//		xDis = M_PX(pDis, pSrc, pitch);
	//		yDis = M_PX(pDis, pSrc, pitch);
	//		angle2 = XY2Angle(xj, yj, xDis, yDis);

	//		//�������Ƕȼ�ľ���
	//		angle3 = GetAngle360In360(angle1, angle2);
	//		//��������Ƕȼ�����,�������������
	//		if (angle3 > 270 || angle3 < 90) {
	//			continue;
	//		}

	//		//�������˵����ߵĽǶ�
	//		angle3 = XY2Angle(xi, yi, xj, yj);
	//		//���һ���˵����������ߵļн�
	//		angle3 = GetAngle360In360(angle1, angle3);
	//		// ����нǽϴ�������ٵ�
	//		if (angle3 < 150 || angle3 > 210) {
	//			continue;
	//		}

	//		//��ڶ����˵����������ߵļн�
	//		angle4 = XY2Angle(xj, yj, xi, yi);
	//		angle4 = GetAngle360In360(angle2, angle4);
	//		//����нǽϴ�������ٵ�
	//		if (angle4 < 150 || angle4 > 210) {	
	//			continue;
	//		}

	//		//�����ʾ����������ͬһ�������ϵĶ��Ѵ��������˵�,������ԭ��
	//		pMinutia[j].x = 0;
	//		pMinutia[j].y = 0;
	//		flag = 0;
	//	}

	//	//��ʾ����������ͬһ�������ϵĶ��Ѵ��������˵�,������ԭ��
	//	if (flag == 0) {	
	//		pMinutia[i].x = 0;
	//		pMinutia[i].y = 0;
	//	}
	//}
	//return flag;
	int32_t i, j;
	int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	//int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	uint8_t *pNow;
	uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	int32_t xDis, yDis;		//������ѭ����trace_len���ȵĵ������
	int32_t xi, yi, xj, yj;	//��һ,�ڶ����˵������
	int32_t flag = 0;		//α��������, 0:α������,1:��
	int32_t angle1, angle2, angle3, angle4;
	//double d; 

	int32_t d;
	int32_t d_fixed_dis = fixed_dis *fixed_dis;
	int32_t d_var_dis = var_dis *var_dis;

	for (i = 0; i < minutia_num-1; i++) {
		flag = 1;
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		for (j = i+1; j < minutia_num; j++) {
			xj = pMinutia[j].x;
			yj = pMinutia[j].y;
			//�������˵�ľ���
			//d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));

			d = ((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj));

			//�����㹻��������һ���˵�
			if (d > d_fixed_dis && d > d_var_dis) {	//var_dis�ǿɱ仯�ĺ��ʵ���С����ֵ
				continue;
			}
			//����̫С,����������Ϊ(0��0)
			if (d <= d_var_dis) {
				pMinutia[j].x = 0;
				pMinutia[j].y = 0;
				flag = 0;
				continue;
			}

			//���һ���˵��������ߵĽǶ�
			pNow = pSrc + yi*pitch + xi;

			//��ȡ������ѭ����trace_len���ȵĵ�ĵ�ַ
			//if(GetByDis(pNow, &pDis, 8) != 0)
			if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
				break;	//�ɶ˵㿪ʼ,���û���ҵ�,
			}			//����㲻��������������в���,ֱ��break,�������ּ�

			//��ȡ������ѭ����trace_len���ȵĵ������
			xDis = M_PX(pDis, pSrc, pitch);	
			yDis = M_PX(pDis, pSrc, pitch);
			angle1 = XY2Angle(xi, yi, xDis, yDis);

			//��ڶ����˵��������ߵĽǶ�
			pNow = pSrc + yj*pitch + xj;

			//��ȡ������ѭ����trace_len���ȵĵ�ĵ�ַ
			//if(GetByDis(pNow, &pDis, 8) != 0)
			if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
				continue;	//�ɶ˵㿪ʼ,���û���ҵ�,
			}				//�������Ч,ֱ��continue,�������μ��

			//��ȡ������ѭ����trace_len���ȵĵ������
			xDis = M_PX(pDis, pSrc, pitch);
			yDis = M_PX(pDis, pSrc, pitch);
			angle2 = XY2Angle(xj, yj, xDis, yDis);

			//�������Ƕȼ�ľ���
			angle3 = GetAngle360In360(angle1, angle2);
			//��������Ƕȼ�����,�������������
			if (angle3 > 270 || angle3 < 90) {
				continue;
			}

			//�������˵����ߵĽǶ�
			angle3 = XY2Angle(xi, yi, xj, yj);
			//���һ���˵����������ߵļн�
			angle3 = GetAngle360In360(angle1, angle3);
			// ����нǽϴ�������ٵ�
			if (angle3 < 150 || angle3 > 210) {
				continue;
			}

			//��ڶ����˵����������ߵļн�
			angle4 = XY2Angle(xj, yj, xi, yi);
			angle4 = GetAngle360In360(angle2, angle4);
			//����нǽϴ�������ٵ�
			if (angle4 < 150 || angle4 > 210) {	
				continue;
			}

			//�����ʾ����������ͬһ�������ϵĶ��Ѵ��������˵�,������ԭ��
			pMinutia[j].x = 0;
			pMinutia[j].y = 0;
			flag = 0;
		}

		//��ʾ����������ͬһ�������ϵĶ��Ѵ��������˵�,������ԭ��
		if (flag == 0) {	
			pMinutia[i].x = 0;
			pMinutia[i].y = 0;
		}
	}
	return flag;
}

/************************************************************************
* ���ܣ���ȡ������ĩ�ҵ�
* ������pSrc				ָ��Դͼ��������
*		  pMinutia			����α�����������������������洢����
*		  minutia_num		��������Ŀ
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ�0��ʾ����,��Ҫ������̬����С����var_dis 1:��ȷ
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*			���ú���ǰ�ȵ���CleanFakeEnd��ȡpMinutiaָ��������洢����
* �㷨: 
*		  �ҵ����������,�����߿��Ƿ�trace_len�ĵ��Ƿ�Ϊǰ��ɫ(ȥ��ë��)
*		  ��α������.�������¼,������ȥ��α����
*************************************************************************/
int32_t GetRealEnd
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 )
{
	int32_t i, j;
	int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	//int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	uint8_t *pNow;
	uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	int32_t xi, yi;	//��һ,�ڶ����˵������
	int32_t flag;		//α��������, 0:α������,1:��

	//ͳ���µĶ˵���Ŀ
	flag = 1;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		//����Ч�˵�
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;

		if (xi == 0 || yi == 0) {
			continue;
		}

		//�������ҵ���8����
		pNow = pSrc + yi*pitch + xi;
		//if(GetByDis(pNow, &pDis, 8) != 0)
		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
			continue;
		}

		j++;
		//����˵���Ŀ���ǹ���,����Ҫ������̬����С����var_dis,
		//�������������Χû�е�������ķ�Χ���,���������Ŀ�������
		//if(j >= FP_MAX_MINUTIA_NUM) {
		if (j >= FP_MAX_END_NUM) {
			flag = 0;	//flag == 0��ʾ����,��Ҫ������̬����С����var_dis
			break;
		}
	}

	return flag;
}

/************************************************************************
* ���ܣ�������ĩ�ҵ���ӵ������㼯MinutiaSet��
* ������minutia			��¼������������㼯
*		  pSrc				ָ��Դͼ��������
*		  pOrientation		ָ��Դͼ��ַָ��ķ���
*		  pMinutia			��������ȡ������������洢����
*		  minutia_num		��������Ŀ
*		  trilen			�����������Բ�뾶
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ��ֲ����Ŀ
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*		    ��������˾����С��α������Ͷ���֮��ĵ�α������
* �㷨: 
*		  1.��������A�����߸����ҵ�trace_len(8)�ĵ�B,����AB�ĽǶ�angle1
*			����A�㷽��angle2�Ƚϵȵ�temp_angle��Ϊ������A�ĽǶ�����Angle
*		  2.�������Բ�뾶trilen��A������ͽǶ�Angle����A�����Բ���������ε�
*		    ������������ķ���temp_triangle[3]��ΪA����������ĽǶ�����
*		  3.����MinutiaSetAddV2��A���������ӵ������㼯��
*************************************************************************/
int32_t FPAddEnd
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc, 
 uint8_t *pOrientation,
 Point_t *pMinutia,
 const int32_t minutia_num,
 const int32_t trilen,
 //const int32_t trace_len,
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 )
{
	//int32_t i, j;
	//int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	////int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	////int32_t bina_type = 255;//0,255�Ķ�ֵ����
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	//int32_t xDis, yDis;		//������ѭ����trace_len���ȵĵ������
	//uint8_t *pNow;
	//uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	//int32_t xi, yi;			//��һ,�ڶ����˵������
	//int32_t x11, y11;
	////int32_t flag;			//α��������, 0:α������,1:��
	//int32_t angle1, angle2, angle3;
	//int32_t temp_angle;
	//MinutiaType_t temp_type;
	//int32_t temp_triangle[3];
	////int32_t nbminutia;
	//double a; 

	////j = minutia->nbminutia;
	////nbminutia = 0;
	//j = 0;
	//for (i = 0; i < minutia_num; i++) {
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	//����Ч�˵�
	//	if (xi == 0 || yi == 0) {
	//		continue;
	//	}
	//	//�������ҵ���8����
	//	pNow = pSrc + yi*pitch + xi;
	//	//if(GetByDis(pNow, &pDis, 8) != 0)
	//	if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
	//		//�������ҵ���8�����Ƿ�Ϊǰ����
	//		continue;
	//	}

	//	//��õ���˵����ߵĽǶ�
	//	//��ȡ������ѭ����trace_len���ȵĵ������
	//	xDis = M_PX(pDis, pSrc, pitch);
	//	yDis = M_PX(pDis, pSrc, pitch);
	//	angle1 = XY2Angle(xi, yi, xDis, yDis);

	//	angle2 = *(pOrientation + yi*pitch + xi);

	//	angle3 = GetAngle360In360(angle1, angle2);

	//	//�����Ƕ�:0-360
	//	if(angle3 > 90 && angle3 < 270) {	//����ɶ۽�,���ʾ�������㷽����õ㷽�򳡷����෴
	//		temp_angle = angle2 + 180;
	//	} else { //��������,���ʾ�������㷽����õ㷽�򳡷�����ͬ
	//		temp_angle = angle2;
	//	}

	//	//���������νǶ�(0-180)
	//	a = temp_angle / M_EPI + M_PI/4.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[0] = *(pOrientation + y11*pitch + x11);

	//	a += M_PI*2/3.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[1] = *(pOrientation + y11*pitch + x11);
	//	a += M_PI*2/3.0;

	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[2] = *(pOrientation + y11*pitch + x11);

	//	//��������
	//	temp_type = MinutiaTypeEnd;
	//	//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
	//	minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
	//	minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
	//	minutia->nbminutia++;
	//	j++;
	//}

	////����FPMinutiaSetExtractEndAndFork�����FPMinutiaSetExtractSingularityǰ
	////����ȡָ�������㼯ǰ,Ӧ���ȳ�ʼ��minutia->nbminutia = 0;
	////minutia->nbminutia += j;

	//return j;
	int32_t i, j;
	int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	//int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	int32_t xDis, yDis;		//������ѭ����trace_len���ȵĵ������
	uint8_t *pNow;
	uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	int32_t xi, yi;			//��һ,�ڶ����˵������
	int32_t x11, y11;
	//int32_t flag;			//α��������, 0:α������,1:��
	int32_t angle1, angle2, angle3;
	int32_t temp_angle;
	MinutiaType_t temp_type;
	int32_t temp_triangle[3];
	//int32_t nbminutia;
	//double a; 
	int32_t a;
	int32_t temp_sin;
	int32_t temp_cos;


	//j = minutia->nbminutia;
	//nbminutia = 0;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		//����Ч�˵�
		if (xi == 0 || yi == 0) {
			continue;
		}
		//�������ҵ���8����
		pNow = pSrc + yi*pitch + xi;
		//if(GetByDis(pNow, &pDis, 8) != 0)
		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
			//�������ҵ���8�����Ƿ�Ϊǰ����
			continue;
		}

		//��õ���˵����ߵĽǶ�
		//��ȡ������ѭ����trace_len���ȵĵ������
		xDis = M_PX(pDis, pSrc, pitch);
		yDis = M_PX(pDis, pSrc, pitch);
		angle1 = XY2Angle(xi, yi, xDis, yDis);

		angle2 = *(pOrientation + yi*pitch + xi);

		angle3 = GetAngle360In360(angle1, angle2);

		//�����Ƕ�:0-360
		if(angle3 > 90 && angle3 < 270) {	//����ɶ۽�,���ʾ�������㷽����õ㷽�򳡷����෴
			temp_angle = angle2 + 180;
		} else { //��������,���ʾ�������㷽����õ㷽�򳡷�����ͬ
			temp_angle = angle2;
		}

		//���������νǶ�(0-180)
		//a = temp_angle / M_EPI + M_PI/4.0;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		a = temp_angle+45;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[0] = *(pOrientation + y11*pitch + x11);

		//a += M_PI*2/3.0;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		a += 120;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[1] = *(pOrientation + y11*pitch + x11);
		//a += M_PI*2/3.0;

		a += 120;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[2] = *(pOrientation + y11*pitch + x11);

		//��������
		temp_type = MinutiaTypeEnd;
		//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
		minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
		minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
		minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
		minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
		minutia->nbminutia++;
		if (minutia->nbminutia >= FP_MAX_MINUTIA_NUM) {
			break;
		}
		j++;
	}

	//����FPMinutiaSetExtractEndAndFork�����FPMinutiaSetExtractSingularityǰ
	//����ȡָ�������㼯ǰ,Ӧ���ȳ�ʼ��minutia->nbminutia = 0;
	//minutia->nbminutia += j;

	return j;
}

/************************************************************************
* ���ܣ����α�ֲ��
* ������pSrc				ָ��Դͼ��������
*		  pMinutia			��������ȡ������������洢����
*		  minutia_num		��������Ŀ
*		  var_dis			������֮�䶯̬��С����
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ�ûʲô����
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*		    ��������˾����С��α������
* �㷨: 
*		  1.��������������ȡһ��������1(A1)��2(B1),���ȼ�������֮��ľ���,
*		    ����С�����,��α������������Ϊ(0,0),����������һ��������.
*		    ֱ��������������������,����.
*************************************************************************/
int32_t ClearFakeFork
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 //const int32_t fixed_dis,
 const int32_t var_dis,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 )
{
	//int32_t i, j;
	////int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	////int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	////int32_t bina_type = 255;//0,255�Ķ�ֵ����
	////int32_t bina_type = BINA_TYPE;
	////int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	////uint8_t *pNow;
	//int32_t xi, yi, xj, yj;	//��һ,�ڶ����˵������
	//int32_t flag;		//α��������, 0:α������,1:��
	//double d;

	////ȥ������̫���Ĳ��
	//for (i = 0; i < minutia_num-1; i++) {
	//	flag = 1;
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	for(j = i+1; j < minutia_num; j++) {
	//		xj = pMinutia[j].x;
	//		yj = pMinutia[j].y;
	//		d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));

	//		if (d <= var_dis-2) {
	//			pMinutia[j].x = 0;
	//			pMinutia[j].y = 0;
	//			flag = 0;
	//		}
	//	}
	//	if (flag == 0) {
	//		pMinutia[i].x = 0;
	//		pMinutia[i].y = 0;
	//	}
	//}
	//return flag;
	int32_t i, j;
	//int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	//int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	//uint8_t *pNow;
	int32_t xi, yi, xj, yj;	//��һ,�ڶ����˵������
	int32_t flag = 0;		//α��������, 0:α������,1:��
	//double d;

	int32_t d;
	int32_t d_var_dis = (var_dis-2)*(var_dis-2);

	//ȥ������̫���Ĳ��
	for (i = 0; i < minutia_num-1; i++) {
		flag = 1;
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		for(j = i+1; j < minutia_num; j++) {
			xj = pMinutia[j].x;
			yj = pMinutia[j].y;
			//d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));
			d = ((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj));

			if (d <= d_var_dis) {
				pMinutia[j].x = 0;
				pMinutia[j].y = 0;
				flag = 0;
			}
		}
		if (flag == 0) {
			pMinutia[i].x = 0;
			pMinutia[i].y = 0;
		}
	}
	return flag;
}

/************************************************************************
* ���ܣ���ȡ�����ķֲ��
* ������pSrc				ָ��Դͼ��������
*		  pMinutia			����α�����������������������洢����
*		  minutia_num		��������Ŀ
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  backcolor		    ͼ�����ݱ�������ɫ(Ĭ��255)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ�0��ʾ����,��Ҫ������̬����С����var_dis 1:��ȷ
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*			���ú���ǰ�ȵ���CleanFakeEnd��ȡpMinutiaָ��������洢����
* �㷨: 
*		  �ҵ����������,����Ƿ�Ϊ��ķֲ��,�����򱣴�
*************************************************************************/
int32_t GetRealFork
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t backcolor,
 //const int32_t bina_type,
 )
{
	int32_t i, j;
	int32_t k, n;
	int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	//int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	int32_t backcolor = BACKCOLOR;
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	uint8_t *pNow;
	int32_t xi, yi;	//��һ,�ڶ����˵������
	int32_t flag;		//α��������, 0:α������,1:��
	//// ĳ����Χ8����ĵ�ַƫ��
	//int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t SiteD8[8];
	uint8_t *tempPtr[8];
	
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;
	
	//ͳ���µ������Ĳ��
	flag = 1;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		//����Ч���
		if (xi == 0 || yi == 0) {
			continue;
		}
		pNow = pSrc + yi*pitch + xi;

		tempPtr[0] = pNow;
		//*tempPtr[0] = 255;			//��Ϊ������
		*tempPtr[0] = backcolor;		//��Ϊ������

		//����Ƿ��������
		n = 0;
		for (k = 0; k < 8; k++) {
			if(*(pNow + SiteD8[k]) == 0) {
				tempPtr[n+1] = pNow + SiteD8[k];
				//*tempPtr[n+1] = 255;	//��Ϊ������
				*tempPtr[n+1] = backcolor;	//��Ϊ������
				n++;
			}
		}
		for (k = 0; k < 4; k++) {
			//*tempPtr[k] = 0;			//�ָ�4��Ϊǰ����
			*tempPtr[k] = forecolor;	//�ָ�4��Ϊǰ����
		}
		if (n != 3) {
			continue;
		}
		j++;

		//����������������ǹ���,����Ҫ����var_dis,
		//�������������Χû�е�������ķ�Χ���,���������Ŀ�������
		//if(EndNum + j >= FP_MAX_MINUTIA_NUM) {
		//if (j >= FP_MAX_MINUTIA_NUM) {
		if (j >= FP_MAX_FORK_NUM) {
			flag = 0;	//flag == 0��ʾ����,��Ҫ������̬����С����var_dis
			break;
		}
	}
	return flag;
}

/************************************************************************
* ���ܣ��������ֲ����ӵ������㼯MinutiaSet��
* ������minutia			��¼������������㼯
*		  pSrc				ָ��Դͼ��������
*		  pOrientation		ָ��Դͼ��ַָ��ķ���
*		  pMinutia			��������ȡ������������洢����
*		  minutia_num		��������Ŀ
*		  trilen			�����������Բ�뾶
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  backcolor		    ͼ�����ݱ�������ɫ(Ĭ��255)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ��ֲ����Ŀ
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
*		    ��������˾����С��α������Ͷ���֮��ĵ�α������
* �㷨: 
*		  1.��������A�����߸����ҵ�trace_len(8)�ĵ�B,C,D
*		  2.�����������d0,d1,d2.������С����Ķ�Ӧ���߷���,�ɴ˵õ����߷���
*		    ����E.
*		  3.����E��A��ĽǶ�angle1����A�㷽��angle2�Ƚϵõ�temp_angle
*			��Ϊ������A�ĽǶ�����Angle
*		  4.�������Բ�뾶trilen��A������ͽǶ�Angle����A�����Բ���������ε�
*		    ������������ķ���temp_triangle[3]��ΪA����������ĽǶ�����
*		  5.����MinutiaSetAddV2��A���������ӵ������㼯��
*************************************************************************/
int32_t FPAddFork
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc, 
 uint8_t *pOrientation,
 Point_t *pMinutia,
 const int32_t minutia_num,
 const int32_t trilen,
 //const int32_t trace_len,
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t backcolor,
 //const int32_t bina_type,
 )
{
	//int32_t i, j;
	//int32_t n, k;
	//int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	////int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	//int32_t backcolor = BACKCOLOR;
	////int32_t bina_type = 255;//0,255�Ķ�ֵ����
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	////������ѭ����trace_len���ȵĵ������
	//int32_t xDis0, yDis0, xDis1, yDis1, xDis2, yDis2;		
	//uint8_t *pNow;
	////uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	//uint8_t *tempPtr[8];
	//uint8_t *disPtr[3];
	////int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	//int32_t xi, yi;			//��һ,�ڶ����˵������
	//int32_t x11, y11;
	//int32_t x21, y21;
	////int32_t flag;			//α��������, 0:α������,1:��
	//int32_t angle1, angle2, angle3;
	//int32_t temp_angle;
	//MinutiaType_t temp_type;
	//int32_t temp_triangle[3];

	//double d0, d1, d2, a; 
	//int32_t SiteD8[8];
	//SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	//SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	//SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	////j = minutia->nbminutia;
	//j = 0;
	//for (i = 0; i < minutia_num; i++) {
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	if (xi == 0 || yi == 0) {
	//		continue;
	//	}

	//	pNow = pSrc + yi*pitch + xi;

	//	tempPtr[0] = pNow;
	//	//*tempPtr[0] = 255;				//��Ϊ������
	//	*tempPtr[0] = backcolor;			//��Ϊ������
	//	//����Ƿ��������
	//	n = 0;
	//	for(k = 0; k < 8; k++) {
	//		if(*(pNow + SiteD8[k]) == 0) {
	//			tempPtr[n+1] = pNow + SiteD8[k];
	//			//*tempPtr[n+1] = 255;	//��Ϊ������
	//			*tempPtr[n+1] = backcolor;	//��Ϊ������
	//			n++;
	//		}
	//	}
	//	if(n != 3) {
	//		continue;
	//	}
	//	//�ҵ�����������������Ͼ���Ϊ8�ĵ�
	//	for(k = 0; k < 3; k++) {
	//		GetPointByDis(tempPtr[k+1], &disPtr[k], trace_len, pitch, forecolor, bina_type);
	//	}

	//	for(k = 0; k < 4; k++) {
	//		//*tempPtr[k] = 0;	//�ָ�4��Ϊǰ����
	//		*tempPtr[k] = forecolor;	//�ָ�4��Ϊǰ����
	//	}

	//	//���������������ľ���
	//	xDis0 = M_PX(disPtr[0], pSrc, pitch);
	//	yDis0 = M_PY(disPtr[0], pSrc, pitch);
	//	xDis1 = M_PX(disPtr[1], pSrc, pitch);
	//	yDis1 = M_PY(disPtr[1], pSrc, pitch);
	//	xDis2 = M_PX(disPtr[2], pSrc, pitch);
	//	yDis2 = M_PY(disPtr[2], pSrc, pitch);

	//	d0 = sqrt((double)(xDis1-xDis2)*(xDis1-xDis2) + (yDis1-yDis2)*(yDis1-yDis2));

	//	d1 = sqrt((double)(xDis0-xDis2)*(xDis0-xDis2) + (yDis0-yDis2)*(yDis0-yDis2));

	//	d2 = sqrt((double)(xDis1-xDis0)*(xDis1-xDis0) + (yDis1-yDis0)*(yDis1-yDis0));

	//	//������̵ı߶�Ӧ���ǲ��߷���
	//	if(d0 < d1 && d0 < d2) {
	//		//disPtr[1],disPtr[2]
	//		x11 = xDis1;
	//		y11 = yDis1;
	//		x21 = xDis2;
	//		y21 = yDis2;
	//		//pDis = disPtr[0];
	//	} else if(d1 < d0 && d1 < d2) {
	//		//disPtr[0],disPtr[2]
	//		x11 = xDis0;
	//		y11 = yDis0;
	//		x21 = xDis2;
	//		y21 = yDis2;
	//		//pDis = disPtr[1];
	//	} else {
	//		//disPtr[0],disPtr[1]
	//		x11 = xDis0;
	//		y11 = yDis0;
	//		x21 = xDis1;
	//		y21 = yDis1;
	//		//pDis = disPtr[2];
	//	}

	//	//����̱��е��������ߵķ�����õ㷽�򳡷���ļн�
	//	angle1 = XY2Angle(xi, yi, (x11+x21)/2, (y11+y21)/2);

	//	angle2 = *(pOrientation + yi*pitch + xi);

	//	angle3 = GetAngle360In360(angle1, angle2);

	//	//�����Ƕ�:0-360
	//	// ����ɶ۽ǣ����ʾ�������㷽����õ㷽�򳡷����෴
	//	if(angle3 > 90 && angle3 < 270) {
	//		temp_angle = angle2 + 180;
	//	} else {// �������ǣ����ʾ�������㷽����õ㷽�򳡷�����ͬ
	//		temp_angle = angle2;
	//	}

	//	//���������νǶ�(0-180)	
	//	//��¼��������Ϊ�������Բ�뾶Ϊtrilen������������������ķ���
	//	a = temp_angle / M_EPI + M_PI/4.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[0] = *(pOrientation+y11*pitch+x11);

	//	a += M_PI*2/3.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[1] = *(pOrientation+y11*pitch+x11);

	//	a += M_PI*2/3.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[2] = *(pOrientation+y11*pitch+x11);

	//	//��������
	//	temp_type = MinutiaTypeFork;

	//	//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
	//	minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
	//	minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
	//	minutia->nbminutia++;
	//	j++;
	//}

	////����FPMinutiaSetExtractEndAndFork�����FPMinutiaSetExtractSingularityǰ
	////����ȡָ�������㼯ǰ,Ӧ���ȳ�ʼ��minutia->nbminutia = 0;
	////minutia->nbminutia += j;

	//return j; // �����Ŀ
	int32_t i, j;
	int32_t n, k;
	int32_t forecolor = 0;	//ͼ��ǰ��ɫΪ�ڵ�
	//int32_t backcolor = 255;//���򳡱���ɫΪ�׵�
	int32_t backcolor = BACKCOLOR;
	//int32_t bina_type = 255;//0,255�Ķ�ֵ����
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//������ѭ���ĳ���:��Ϊ8
	//������ѭ����trace_len���ȵĵ������
	int32_t xDis0, yDis0, xDis1, yDis1, xDis2, yDis2;		
	uint8_t *pNow;
	//uint8_t *pDis;			//������ѭ����trace_len���ȵĵ�ĵ�ַ
	uint8_t *tempPtr[8];
	uint8_t *disPtr[3];
	//int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t xi, yi;			//��һ,�ڶ����˵������
	int32_t x11, y11;
	int32_t x21, y21;
	//int32_t flag;			//α��������, 0:α������,1:��
	int32_t angle1, angle2, angle3;
	int32_t temp_angle;
	MinutiaType_t temp_type;
	int32_t temp_triangle[3];

	//double d0, d1, d2, a, a1; 
	
	int32_t d0, d1, d2;
	//double a, a1;
	int32_t a, temp_cos, temp_sin;

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	//j = minutia->nbminutia;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		if (xi == 0 || yi == 0) {
			continue;
		}

		pNow = pSrc + yi*pitch + xi;

		tempPtr[0] = pNow;
		//*tempPtr[0] = 255;				//��Ϊ������
		*tempPtr[0] = backcolor;			//��Ϊ������
		//����Ƿ��������
		n = 0;
		for(k = 0; k < 8; k++) {
			if(*(pNow + SiteD8[k]) == 0) {
				tempPtr[n+1] = pNow + SiteD8[k];
				//*tempPtr[n+1] = 255;	//��Ϊ������
				*tempPtr[n+1] = backcolor;	//��Ϊ������
				n++;
			}
		}
		if(n != 3) {
			continue;
		}
		//�ҵ�����������������Ͼ���Ϊ8�ĵ�
		for(k = 0; k < 3; k++) {
			GetPointByDis(tempPtr[k+1], &disPtr[k], trace_len, pitch, forecolor, bina_type);
		}

		for(k = 0; k < 4; k++) {
			//*tempPtr[k] = 0;	//�ָ�4��Ϊǰ����
			*tempPtr[k] = forecolor;	//�ָ�4��Ϊǰ����
		}

		//���������������ľ���
		xDis0 = M_PX(disPtr[0], pSrc, pitch);
		yDis0 = M_PY(disPtr[0], pSrc, pitch);
		xDis1 = M_PX(disPtr[1], pSrc, pitch);
		yDis1 = M_PY(disPtr[1], pSrc, pitch);
		xDis2 = M_PX(disPtr[2], pSrc, pitch);
		yDis2 = M_PY(disPtr[2], pSrc, pitch);

		//d0 = sqrt((double)(xDis1-xDis2)*(xDis1-xDis2) + (yDis1-yDis2)*(yDis1-yDis2));

		//d1 = sqrt((double)(xDis0-xDis2)*(xDis0-xDis2) + (yDis0-yDis2)*(yDis0-yDis2));

		//d2 = sqrt((double)(xDis1-xDis0)*(xDis1-xDis0) + (yDis1-yDis0)*(yDis1-yDis0));

		d0 = (xDis1-xDis2)*(xDis1-xDis2) + (yDis1-yDis2)*(yDis1-yDis2);
		d1 = (xDis0-xDis2)*(xDis0-xDis2) + (yDis0-yDis2)*(yDis0-yDis2);
		d2 = (xDis1-xDis0)*(xDis1-xDis0) + (yDis1-yDis0)*(yDis1-yDis0);

		//������̵ı߶�Ӧ���ǲ��߷���
		if(d0 < d1 && d0 < d2) {
			//disPtr[1],disPtr[2]
			x11 = xDis1;
			y11 = yDis1;
			x21 = xDis2;
			y21 = yDis2;
			//pDis = disPtr[0];
		} else if(d1 < d0 && d1 < d2) {
			//disPtr[0],disPtr[2]
			x11 = xDis0;
			y11 = yDis0;
			x21 = xDis2;
			y21 = yDis2;
			//pDis = disPtr[1];
		} else {
			//disPtr[0],disPtr[1]
			x11 = xDis0;
			y11 = yDis0;
			x21 = xDis1;
			y21 = yDis1;
			//pDis = disPtr[2];
		}

		//����̱��е��������ߵķ�����õ㷽�򳡷���ļн�
		angle1 = XY2Angle(xi, yi, (x11+x21)/2, (y11+y21)/2);

		angle2 = *(pOrientation + yi*pitch + xi);

		angle3 = GetAngle360In360(angle1, angle2);

		//�����Ƕ�:0-360
		// ����ɶ۽ǣ����ʾ�������㷽����õ㷽�򳡷����෴
		if(angle3 > 90 && angle3 < 270) {
			temp_angle = angle2 + 180;
		} else {// �������ǣ����ʾ�������㷽����õ㷽�򳡷�����ͬ
			temp_angle = angle2;
		}

		//���������νǶ�(0-180)	
		//��¼��������Ϊ�������Բ�뾶Ϊtrilen������������������ķ���
		//a = temp_angle / M_EPI + M_PI/4.0;
		//a1 = cos(a);
		//a1 = a1*trilen;
		a = temp_angle+45;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		temp_triangle[0] = *(pOrientation+y11*pitch+x11);

		//a += M_PI*2/3.0;
		a += 120;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[1] = *(pOrientation+y11*pitch+x11);

		//a += M_PI*2/3.0;
		a += 120;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[2] = *(pOrientation+y11*pitch+x11);

		//��������
		temp_type = MinutiaTypeFork;

		//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
		minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
		minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
		minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
		minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
		minutia->nbminutia++;
		if (minutia->nbminutia >= FP_MAX_MINUTIA_NUM) {
			break;
		}
		j++;
	}

	//����FPMinutiaSetExtractEndAndFork�����FPMinutiaSetExtractSingularityǰ
	//����ȡָ�������㼯ǰ,Ӧ���ȳ�ʼ��minutia->nbminutia = 0;
	//minutia->nbminutia += j;

	return j; // �����Ŀ
}

/************************************************************************
* ���ܣ���ȡָ������ĩ�ҵ�ͷֲ�㵽�����㼯MinutiaSet��
* ������minutia			��¼����ĩ�ҵ�ͷֲ��������㼯
*		  pSrc				ָ��Դͼ��������
*		  pOrientation		ָ��Դͼ��ַָ��ķ���
*		  pMinutia			��������ȡ������������洢����
*		  minutia_num		��������Ŀ
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
*		  r					�߽���ֵr(����Ĭ��16)
*		  ori_thr			���򳡱仯���ҳ̶�(Ĭ�ϰ뾶Ϊ5�ĵ�ı仯Ϊ96)
*		  fixed_dis			������֮��̶���С����(Ĭ��16)
*		  var_dis			������֮�䶯̬��С����(��ʼĬ��7)
*		  trace_len			���߸��ٳ���(Ĭ��Ϊ8)
*		  trilen			�����������Բ�뾶(Ĭ��16)
*		  rbackcolor		�ֱ���ɫ��ɫ(ָ�ַָ���ROI�������ɫ)(Ĭ��255)
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  backcolor		    ͼ�����ݱ�������ɫ(Ĭ��255)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
* ���أ��ֲ����Ŀ
* ˵��:   ��Щ��������ʹ����Ĭ�ϵ�ֵ,û��������Ϊ�β�,Ҫʹ��ʱֻ�轫ע��
*		  ȥ��,���ҽ�������ͷ���õ�Ĭ��ֵע�͵�����.
* �㷨: 
*		  1.��������ͼ��,��ȡ���зֲ���ĩ�ҵ�(GetRawEndAndFork).�����õ�
*			�������Ѿ�ȥ����Ե�����α�����ͷ��򳡾��ұ任��α����
*		  2.�ֱ��ĩ�ҵ�ͷֲ�����α����ȥ�������
*			 ĩ�ҵ�:(1)ĩ�ҵ�α����ȥ��(ClearFakeEnd),��Ҫȥ�����������α�������
*					   ����֮��ĵ�α������
*					(2)��ȡ��ʵ��ĩ�ҵ�(GetRealEnd),��Ҫȥ���̵�����
*				       (ë��,�̰�,ճ�ŵ�)α������.���к�������ֵbGood����ӳ��
*					   ������֮�䶯̬��С����var_dis�Ƿ����ú���.��������Ҫ�޸�
*					(3)���ĩ�ҵ㼰�������������㼯��(FPAddEnd)
*			 �ֲ��:(1)�ֲ��α����ȥ��(ClearFakeFork),��Ҫȥ�����������α������
*					(2)��ȡ��ʵ�ķֲ��(GetRealFork),��Ҫȥ���̵�����
*				       (ë��,�̰�,ճ�ŵ�)α���������к�������ֵbGood����ӳ��
*					   ������֮�䶯̬��С����var_dis�Ƿ����ú���.��������Ҫ�޸�
*					(3)���ĩ�ҵ㼰�������������㼯��(FPAddFork)
*		  3.����bGood�����Ƿ���Ҫ����var_dis.
*			���bGood==0,��Ҫ����var_dis,�������в���2,
*			��֮bGood==1,���벽��4
*			�����������loopnum�ﵽһ��ֵ(32)��û�кܺõ�Ч������벽��4.
*		  4.����ָ������ĩ�ҵ�ͷֲ�����ȡ.
*	P.S : α�����������
*	�ο�����:]
*		1.����DSP��ָ��ʶ��ϵͳ�о�--������	(21-23)	<����˶ʿ����>
*		  ȥ��α������ʱ��Ҫ�������߼�࣬������ָ���ߵļ������Ժܴ�
*		  ��������ȡ���߼��ʱ���ö�̬��ֵ����ȡָ�����ߵļ�࣬��ϸ����ָ��
*		  ͼ����������ֱ��ˮƽ����ֱ�ߣ���ָ�Ƽ����ཻ�������Ϊ X [ M ]����һ
*		  �������ݺ�����Ķ�ά���顣����ȡָ�Ƹ�������֮�����ƽ��ֵ
*		  ������ʱ�������߸��ټ���������ĳһ�����ߣ��Ը�
*		  �����߹��ĵ�����һ��������и��ټ�¼��һ�������У��������е�Ԫ�Ĵ�
*		  ���Ǳ����ٵ����ص��������ϵĴ���ÿ����Ԫ��¼�˱����ٵ����ص����
*		  ���꣬������͸õ�����ͣ����� 1 ��ʾ�˵㣻2 ��ʾ�����㣻3 ��ʾ�ֲ�
*		  �㣩���������߸��ټ���ȥ��Ϊ�����㡣
*		  (1)�� ȥ��ë��
*		  ë�����ڶ�ָ��ͼ���ֵ��ʱ�������������ģ�����ȡϸ��������
*		  ʱ��ë�̱���Ϊһ���˵��һ���ֲ�㣬�Ҷ��ߵľ���ܽ���ȥ��ë�̵���
*		  �����£�
*		  ����ѡȡ���еķֲ�㣬������ֲ洦���������ߣ��������߸��ټ�
*		  �����������ֵ����T1���Ƿ����һ���˵㣬����⵽�����Ķ˵㣬
*		  ��õ���α�����㣬ɾ���õ㵽�ֲ����������ص㼴��ȥ��ë�̡�
*		  (2)�� ȥ������
*		  ��������ָ�Ʋɼ������У��ɼ�������ָ�Ƚ���������ġ�����ȡ����
*		  ��ʱ����Ϊ�����˵㣬���������˵�ľ���ܽ���ȥ�����Ƶ��㷨���£�
*		  ����ѡȡ���еĶ˵㣬�������߸��ټ����������߷���������ֵ����
*		  T2���Ƿ���ڶ˵㣬�����������Ķ˵㣬��õ���α�����㣬ɾ����
*		  �������˵�֮�����ص�ȥ�����ơ�
*		  (3)�� ȥ��С��
*		  С���Ƕ�ֵ��ͼ��ģ�����ڶ�ֵ�����߳��ֿն�����ģ�����ȡ��ϸ������
*		  �����Ϊ�����ֲ�㣬��ˣ�ȥ��С�����㷨���£�
*		  ����ѡȡ���еķֲ�㣬�������߸��ټ�������������������������
*		  ֵ����T3���Ƿ���ڷֲ�㣬�����������ķֲ�㣬��õ���α����
*		  �㣬ȥ���������ֲ��������ߡ�
*		  (4)�� ȥ��αС��
*		  ���ɼ�������ָ�ڰ�ѹʱ���������ȣ��ǵ�����֮���໥ճ�����γ�α
*		  С�š�������ȡ��ϸ�����������Ϊ�����ֲ�㣬���������ֲ���������
*		  ���������ڵ����߼�����ֱ���������㷨���£�
*		  ����ѡȡ���еķֲ�㣬�������߸��ټ�������������������������
*		  ֵ����T4���Ƿ���ڷֲ�㣬�����������ķֲ�㣬��õ���α����
*		  �㣬ȥ���������ֲ��������ߡ�
*		  (5)�� ȥ�����ߵļ��
*		  ���ɼ�������ָ�Ƚϸɵ�����£��ɼ���ָ�ƻ�������ߵļ�ϣ�����
*		  �����Ϊ�������������Ǿ���ܽ��Ķ˵㡣���Դ�ʱ�����������߸��ټ�
*		  ������ʱ�������ж��������˵����ߵķ�����˵�����С�������ߵķ����
*		  �Ƿ�Ϊ0��+-PI ���������������˵��Ϊα�����㣬ɾ��������α�����㡣
*		  (6)�� ȥ��ָ�Ʊ�Ե��α������
*		  ָ��ͼ���Ե����������󲿷���α�����㣬��Щ�̲��������ߵ���
*		  �㣬��������ͼ���С����ʹ��һ���������޷���ʾ��ɵġ�ȥ����Щ����
*		  ����㷨��һ��ѡȡ���еĶ˵�ͷֲ�㣬���䵽�߽�ľ���С��Ԥ���趨
*		  ����ֵ����õ�Ϊα�����㣬ɾ���õ㼴�ɡ�
*		2.��ͨVisual C++ָ��ģʽʶ��ϵͳ�㷨��ʵ��--��� (147-161)<2008��12�µ�һ��>
*************************************************************************/
int32_t FPMinutiaSetExtractEndAndFork
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 //const int32_t r,
 //const int32_t ori_thr
 //const int32_t fixed_dis,
 //const int32_t var_dis,
 //const int32_t trace_len,
 //const int32_t trilen,
 //const int32_t rbackcolor,
 const int32_t forecolor,
 const int32_t backcolor,
 const int32_t bina_type
 )
{
	int32_t i;
	//int32_t r = 16;			//���������㿿��ǰ����Ե���������
	//int32_t ori_thr = 96;	//���򳡱仯���ҳ̶�
	int32_t fixed_dis = 16;	//�������������������ľ���
	int32_t var_dis = 7;	//�������������������ľ���,��bGood�����Ƿ���Ҫ����
	//int32_t trace_len = 8;	//���߸��ٳ���(Ĭ��Ϊ8)
	int32_t trilen = 16;	//�����������Բ�뾶

	int32_t tempForkNum;
	int32_t tempEndNum;
	int32_t ForkNum;
	int32_t EndNum;

	int32_t bGood = 0;	//�����ֵ�Ƿ������,ʹ��������Ŀ������Χ��
	int32_t loopnum;	//ѭ������,���ѭ����Ϊ32


	//��ʱ����������
	Point_t tempFork[FP_MAX_RAW_MINUTIA_NUM];
	Point_t tempEnd[FP_MAX_RAW_MINUTIA_NUM];
	Point_t ForkArr[FP_MAX_RAW_MINUTIA_NUM];
	Point_t EndArr[FP_MAX_RAW_MINUTIA_NUM];

	// ��ʼ����ʱ����������
	for (i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++){
		tempFork[i].x = 0;
		tempFork[i].y = 0;
		tempEnd[i].x = 0;
		tempEnd[i].y = 0;
		ForkArr[i].x = 0;
		ForkArr[i].y = 0;
		EndArr[i].x = 0;
		EndArr[i].y = 0;
	}

	//��һ��Ѱ�����ж˵�Ͳ��	
	ForkNum = 0; 
	EndNum = 0; 

	GetRawEndAndFork(pSrc, pOrientation, ForkArr, &ForkNum, EndArr, &EndNum, width, height, pitch);

	//��ʼ����ʱ������,׼��ѭ������������������������С����,ʹ֮����һ�����ʵ�ֵ
	//��Ϊ���������ǳ��ܼ��ĵط����п����������ܲ�ĵط�
	for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
		tempEnd[i] = EndArr[i];
	}
	for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
		tempFork[i] = ForkArr[i];
	}
	tempForkNum = ForkNum;
	tempEndNum = EndNum;

	//ѭ������
	bGood = 0;
	loopnum = 0;	// �����Ĵ���
	//while(!bGood && loopnum < 32) {	//������32��
	while (!bGood && loopnum < 8) {
		loopnum++;	// ����������һ
		//�õ��µ�����������
		for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
			EndArr[i].x = tempEnd[i].x;
			EndArr[i].y = tempEnd[i].y;
		}
		for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
			ForkArr[i].x = tempFork[i].x;
			ForkArr[i].y = tempFork[i].y;
		}
		//�µ���������
		ForkNum = tempForkNum;	//���
		EndNum = tempEndNum;	//�˵�

		//ȥ����ٵĶ˵�
		bGood = 1;
		ClearFakeEnd(pSrc, EndArr, EndNum, fixed_dis, var_dis, pitch);

		bGood = GetRealEnd(pSrc, EndArr, EndNum, pitch);
		//����var_dis
		if(!bGood) {
			var_dis++; // ��һ
			continue;
		}

		EndNum = FPAddEnd(minutia, pSrc, pOrientation, EndArr, EndNum, trilen, pitch);

		ClearFakeFork(pSrc, ForkArr, ForkNum, var_dis, pitch);

		bGood = GetRealFork(pSrc, ForkArr, ForkNum, pitch);

		if(!bGood) {
			var_dis++; // ��һ
			continue;
		}

		ForkNum = FPAddFork(minutia, pSrc, pOrientation, ForkArr, ForkNum, trilen, pitch);

	}
	//���ѭ��32�ζ����ܵõ������������ʾͼ����������ش���
	//if(loopnum >= 32) {
	if (loopnum >= 8) {
		//MinutiaSetEmpty(minutia);
		//minutia->nbminutia = 0;
		return 1;
	}

	//��������Ŀ̫���򷵻ش���
	if(ForkNum + EndNum < 8) {
		//MinutiaSetEmpty(minutia);
		minutia->nbminutia = 0;
		return 1;
	}

	return 0;
}

/******************************************************************************
* ���ܣ���ϸ��ͼ������ȡϸ�ڵ㣬�����浽�����С�
* ������minutia			ϸ�ڵ㼯�ϣ���������ϸ�ڵ�
*		  pSrc				ͼ������
*       pOri				����ǰ�󾰷ָ�ķ���
*		  forecolor		    ͼ������ǰ����ɫ(Ĭ��0)
*		  backcolor		    ͼ�����ݱ�������ɫ(Ĭ��255)
*		  rbackcolor		�ֱ���ɫ��ɫ(ָ�ַָ���ROI�������ɫ)(Ĭ��255)
*		  bina_type			ͼ���ֵ����1:(0,1)������:(0,255)(Ĭ��255)
*		  width				ͼ�����ݿ��
*		  height			ͼ�����ݸ߶�
*		  pitch				ͼ������ÿ���ֽ���
* ���أ�������
* ˵��: 
*		  1.��ȡ�����(FPMinutiaSetExtractSingularity)
*		  2.��ȡĩ�ҵ�ͷֲ��(FPMinutiaSetExtractEndAndFork)
******************************************************************************/
FunError_t FPMinutiaSetExtract
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc,
 uint8_t *pOri,
 const int32_t forecolor,
 const int32_t backcolor,
 const int32_t bina_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	//minutia->nbminutia = 0;

	//FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 0);
	//FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 1);
	//FPMinutiaSetExtractEndAndFork(minutia, pSrc, pOri, width, height, pitch, forecolor, backcolor, bina_type);
	int32_t err = 0;
	minutia->nbminutia = 0;

	FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 0);
	FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 1);
	err = FPMinutiaSetExtractEndAndFork(minutia, pSrc, pOri, width, height, pitch, forecolor, backcolor, bina_type);
	if (err == 1) {
		return FunError;
	}
	if (minutia->nbminutia > 60) {
		minutia->nbminutia = 60;
		return FunError;
	}

	return FunOK;
}

