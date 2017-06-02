/******************************************************************************
 * �ļ�����image_acquisition.c
 * ���ܣ�  ͼ���뵼������
******************************************************************************/

#include "dip_header/image_acquisition.h"

/******************************************************************************
  * ���ܣ����ļ��м���ͼ��
  * ������image       ͼ��
  *       flag ��ʶ�ɼ�����ʲôͼ��
  *			FINGER_PRINT ָ��ͼ��
  *			FINGER_VEIN  ָ����ͼ��
  * ���أ�������
******************************************************************************/
void ImageImport(Image_t *image, uint32_t flag)
{
	volatile uint32_t *ptr;
	volatile uint32_t *ptrd;
	int32_t i, j;
	int32_t tempJ;
	if (flag == FINGER_VEIN) {
		ptr = ptrd = (uint32_t*)(IMAGE_IN_ADDR);
		for (i = 0; i <  FV_WH_ORG_SIZE32; i++) {			
			*ptrd++ = *ptr;
			ptr += 2;
		}

		ptr = ((uint32_t *)(IMAGE_IN_ADDR)) ;
		ptrd= ((uint32_t *)(IMAGE_FV_IN_ADDR)) ;
		//asm ( " NOP " ) ;

		for (j = FV_HEIGHT_ORG-1; j >= 0; j--) {
			tempJ = (j*FV_WIDTH_ORG)>>2;
			for (i = 0; i < (FV_WIDTH_ORG>>2); i++) {
				*(ptrd+tempJ+i) = *ptr++;
			}
		}
		//for (i = 0; i < FV_WH_ORG_SIZE32; i++) {
		//	*ptrd = *ptr;

		//}

	} else if (flag == FINGER_PRINT) {
		ptr = ptrd = (uint32_t*)(IMAGE_IN_ADDR);
		for (i = 0; i <  FP_WH_ORG_SIZE32; i++) {			
			*ptrd++ = *ptr;
			ptr += 2;
		}

		ptr = ((uint32_t *)(IMAGE_IN_ADDR)) ;
		ptrd= ((uint32_t *)(IMAGE_FP_IN_ADDR)) ;
		//asm ( " NOP " ) ;
		for (j = FP_HEIGHT_ORG-1; j >= 0; j--) {
			tempJ = (FP_WIDTH_ORG * j)>>2;
			for (i = 0; i < (FP_WIDTH_ORG>>2); i++) {
				*(ptrd+tempJ+i) = *ptr++;
			}
		}
		//for (i = 0; i < FP_WH_ORG_SIZE; i++) {
		//	*ptrd = *ptr ;

		//}

	}

}


/******************************************************************************
  * ���ܣ����ļ��м���ͼ��
  * ������image       ͼ��
  *       flag ��ʶ�ɼ�����ʲôͼ��
  *			FINGER_PRINT ָ��ͼ��
  *			FINGER_VEIN  ָ����ͼ��
  * ���أ�������
******************************************************************************/
void ImageExport(Image_t *image, uint32_t flag)
{
	volatile uint32_t *ptr;
	volatile uint32_t *ptrd;
	int32_t i;
	
	if (flag == FINGER_VEIN) {
		ptr = ((uint32_t *)(image->pimg));
		ptrd= ((unsigned int*)(IMAGE_FV_OUT_ADDR)) ;
		for (i = 0; i < FV_WH_SIZE32; i++) {
			*ptrd = *ptr ;
			ptr++;
			ptrd++;
		}


	} else if (flag == FINGER_PRINT) {
		ptr = ((uint32_t *)(image->pimg));
		ptrd= ((unsigned int*)(IMAGE_FP_OUT_ADDR)) ;

		for (i = 0; i < FP_WH_SIZE32; i++) {
			*ptrd = *ptr ;
			ptr++;
			ptrd++;
		}
	} else if (flag == FINGER_TEST) {
		ptr = ((uint32_t *)(image->pimg));
		ptrd= ((unsigned int*)(IMAGE_TEST_ADDR)) ;

		for (i = 0; i < FP_WH_ORG_SIZE32; i++) {
			*ptrd = *ptr ;
			ptr++;
			ptrd++;
		}
	}
}



/******************************************************************************
  * ���ܣ����ļ��м���ͼ��
  * ������image       ͼ��
  *       flag ��ʶ�ɼ�����ʲôͼ��
  *			FINGER_PRINT ָ��ͼ��
  *			FINGER_VEIN  ָ����ͼ��
  * ���أ�������
******************************************************************************/
//void FeatureExport(pFPMinutiaSet_t minutia1, pFVMinutiaSet_t minutia2, uint32_t id)
//{
//	volatile uint32_t *ptr;
//	volatile uint32_t *ptrd;
//	int32_t i;
//	
//
//	if (flag == FINGER_VEIN) {
//		ptr = ((uint32_t *)(minutia1));
//		ptrd= ((unsigned int*)(FEATURE_OUT_ADDR) + id * 4096) ;
//		*ptrd = id;
//		ptrd++;
//		*ptrd = minutia1->nbminutia;
//		*
//		for (i = 0; i < FV_WH_SIZE32; i++) {
//			*ptrd = *ptr ;
//			ptr++;
//			ptrd++;
//		}
//
//
//	} else if (flag == FINGER_PRINT) {
//		ptr = ((uint32_t *)(image->pimg));
//		ptrd= ((unsigned int*)(IMAGE_FP_OUT_ADDR)) ;
//
//		for (i = 0; i < FP_WH_SIZE32; i++) {
//			*ptrd = *ptr ;
//			ptr++;
//			ptrd++;
//		}
//	} 
//}

