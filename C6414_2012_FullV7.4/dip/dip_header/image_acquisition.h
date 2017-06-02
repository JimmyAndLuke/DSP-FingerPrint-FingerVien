/******************************************************************************
 * �ļ�����image_acquisition.h
 * ���ܣ�  ����ͼ��
******************************************************************************/

#if !defined __IMAGE_ACQUISITION_H
#define __IMAGE_ACQUISITION_H

#ifdef __cplusplus
extern "C" {
#endif

/* �������Ͷ��� */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../bsp/bsp_header/z_camera.h"

#include "image.h"
#include "../../sys/sys_header/sys_global.h"

#define IMAGE_IN_ADDR			0x80000000
#define IMAGE_FV_IN_ADDR		0x80100000
#define IMAGE_FP_IN_ADDR		0x80200000

#define IMAGE_FV_OUT_ADDR		0x80300000
#define IMAGE_FP_OUT_ADDR		0x80400000
#define IMAGE_TEST_ADDR			0x80500000

/******************************************************************************
  * ���ܣ����ļ��м���ͼ��
  * ������image       ͼ��
  *       flag ��ʶ�ɼ�����ʲôͼ��
  *			FINGER_PRINT ָ��ͼ��
  *			FINGER_VEIN  ָ����ͼ��
  * ���أ�������
******************************************************************************/
void ImageImport(Image_t *image, uint32_t flag);


/******************************************************************************
  * ���ܣ����ļ��м���ͼ��
  * ������image       ͼ��
  *       flag ��ʶ�ɼ�����ʲôͼ��
  *			FINGER_PRINT ָ��ͼ��
  *			FINGER_VEIN  ָ����ͼ��
  * ���أ�������
******************************************************************************/
void ImageExport(Image_t *image, uint32_t flag);





#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_ACQUISITION_H */



