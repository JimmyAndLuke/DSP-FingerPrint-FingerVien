/******************************************************************************
 * �ļ�����sys_global.c
 * ���ܣ�  һЩϵͳ��ȫ�ֱ����Ͳ���
******************************************************************************/


#include "sys_header/sys_global.h"

//����ͼ����
Image_t fv_src_org;					//����Դͼ������
Image_t fv_src;						//
Image_t fv_src_copy;			
Image_t fv_dst;
Image_t fv_imageG;					//�����м�ͼ������

FVMinutiaSet_t fv_minutia;

//����ͼ������������
uint32_t fv_src_buf[FV_HEIGHT*FV_WIDTH/4];		
uint32_t fv_src_copy_buf[FV_WIDTH*FV_HEIGHT/4];	//����ͼ�������ݴ�����
uint32_t fv_dst_buf[FV_HEIGHT*FV_WIDTH/4];		

//#pragma DATA_SECTION(fv_imageG_buf, "DATABUF");
//uint32_t fv_imageG_buf[FV_HEIGHT*FV_WIDTH/4];

//#pragma DATA_SECTION(cur_value, "DATABUF");
float	cur_value[FV_HEIGHT*FV_WIDTH];		//���ʷָ�����



//ָ��ͼ����
Image_t fp_src_org;
Image_t fp_src;
//Image_t fp_src1;
Image_t fp_src_copy;
Image_t fp_imageG;
Image_t fp_imageO;

FPMinutiaSet_t fp_minutia;

user_t    gobal_user;

//ָ��ͼ������������
uint32_t fp_src_buf[FP_HEIGHT*FP_WIDTH/4];
//uint32_t fp_src1_buf[(117*150)/4];

uint32_t fp_src_copy_buf[FP_HEIGHT*FP_WIDTH/4];	//ָ��ͼ�������ݴ�����
	
//#pragma DATA_SECTION(fp_imageG_buf, "DATABUF");
uint32_t fp_imageG_buf[FP_HEIGHT*FP_WIDTH/4];

//#pragma DATA_SECTION(fp_imageO_buf, "DATABUF");
uint32_t fp_imageO_buf[FP_HEIGHT*FP_WIDTH/4];

Image_t image_display;
static uint32_t image_display_buf[124*216/4];
//Image_t image_display_fp;
//Image_t image_display_fv;
//static uint32_t image_display_fp_buf[124*124/4];
//static uint32_t image_display_fv_buf[96*216/4];


//��ʼ��ȫ��ͼ�����
//ͼ��ṹ���ʼ��:��ȫ��ͼ��ṹ��Ĳ�����ʼ��
//������ͼ�������뾲̬����(Ϊͼ�����ݷ���ռ�)
void image_init(void) 
{
	//ͼ��ṹ���ʼ��:��ȫ��ͼ��ṹ��Ĳ�����ʼ��
	//������ͼ�������뾲̬����(Ϊͼ�����ݷ���ռ�)
	//ImageCreate(&fv_src_org, (void*)0x80000000, 480, 752, 480, ImageGray);

	ImageCreate(&fv_src_org, (void*)0x80100000, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG, ImageGray);

    ImageCreate(&fv_src, fv_src_buf, FV_WIDTH, FV_HEIGHT, FV_PITCH, ImageGray);
	ImageCreate(&fv_src_copy, fv_src_copy_buf, FV_WIDTH, FV_HEIGHT, FV_PITCH, ImageGray);
    //ImageCreate(&fv_imageG, fv_imageG_buf, FV_WIDTH, FV_HEIGHT, FV_PITCH, ImageGray);
	 ImageCreate(&fv_dst, fv_dst_buf, FV_WIDTH, FV_HEIGHT, FV_PITCH, ImageGray);

	ImageFlood(&fv_src_org, 0);
	ImageFlood(&fv_src, 0);
	ImageFlood(&fv_src_copy, 0);
    //ImageFlood(&fv_imageG, 0);
	ImageFlood(&fv_dst, 0);


	ImageCreate(&fp_src_org, (void*)0x80200000, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG, ImageGray);

	//ImageCreate(&fp_src1, fp_src1_buf, 150, 117, 150, ImageGray);


	ImageCreate(&fp_src, fp_src_buf, FP_WIDTH, FP_HEIGHT, FP_PITCH, ImageGray);
	ImageCreate(&fp_src_copy, fp_src_copy_buf, FP_WIDTH, FP_HEIGHT, FP_PITCH, ImageGray);
	ImageCreate(&fp_imageG, fp_imageG_buf, FP_WIDTH, FP_HEIGHT, FP_PITCH, ImageGray);
	ImageCreate(&fp_imageO, fp_imageO_buf, FP_WIDTH, FP_HEIGHT, FP_PITCH, ImageGray);

	ImageFlood(&fp_src_org, 0);
	ImageFlood(&fp_src, 0);
	//ImageFlood(&fp_src1, 0);
	ImageFlood(&fp_src_copy, 0);
    ImageFlood(&fp_imageG, 0);
	ImageFlood(&fp_imageO, 0);

	//ImageCreate(&image_display_fv, image_display_fv_buf, 96, 216, 96, ImageGray);
	//ImageCreate(&image_display_fp, image_display_fp_buf, 124, 124, 124, ImageGray);
	ImageCreate(&image_display, image_display_buf, 124, 216, 124, ImageGray);


}

//ϵͳȫ�ֱ�����ʼ��
void sys_global_init(void)
{
	image_init(); 
	sys_database_init();
	//sys_database_init0();
}













