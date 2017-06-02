/******************************************************************************
 * �ļ�����image_processing.h
 * ��  �ܣ�ͼ������
******************************************************************************/

#if !defined __IMAGE_PROCESSING_H
#define __IMAGE_PROCESSING_H

//#include "image.h"
//#include "image_base.h"
//#include "image_binary.h"
//#include "image_segment.h"
//#include "image_enhance_filter.h"
//#include "image_morphology.h"
//#include "image_miscellaneous.h"
//#include "image_thining.h"
//#include "image_feature.h"
//#include "image_math.h"

#include "../../bsp/bsp_header/z_mytype.h"
#include "../../sys/sys_header/sys_global.h"
#include "image.h"
#include "image_feature.h"
#include "image_base.h"
#include "image_acquisition.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
  * ���ܣ��Ծ���ͼ����д���
  * ������image			   ����ͼ��
  *		  smooth_w		   ��ֵƽ��ģ��ߴ�
  *		  cur_t			   ���ʷָ�����
  *		  cur_w			   ����΢�ּ���ߴ�
  *		  tmplt_w		   ��ʴ,���ͽṹԪ�سߴ�
  *		  tmpltA		   ��ʴ,���ͽṹԪ��
  *		  tmplt_s		   ��ʴ,���ͽṹԪ��֮��
  *		  minutia		   ϸ�ڵ㼯
  *		  region_ath	   ��ͨ����ֵ
  * ���أ�������
******************************************************************************/
FunError_t FVImageProcessing
(
 Image_t *image_org,
 Image_t *image,
 Image_t *imageG,
 const int32_t smooth_w,
 const int32_t cur_t,
 const int32_t cur_w,
 const int32_t fore_area_thr,
 const int32_t back_area_thr,
 //const int32_t tmplt_w,
 //int32_t *tmpltA,
 //const int32_t tmplt_s,
 pFVMinutiaSet_t minutia,
 const int32_t burr_thr
);


/******************************************************************************
  * ���ܣ���ָ��ͼ����д���
  * ������image			   ָ��ͼ��
  *		  imageGrads	   ָ��ͼ����ݶ�ͼ��
  *		  imageOri		   ָ��ͼ��ķ���ͼ��
  *		  grads_ori_size   �����ݶȺͷ���ߴ�
  *		  seg_size		   �ַָ�ߴ�
  *		  seg_step		   �ַָ��
  *		  seg_thr		   �ַָ���ֵ
  *		  gauss_sigma	   ��˹��׼��
  *		  soft_size		   ��(ƽ��)�ߴ�
  *		  thin_thr		   ϸ��ë����ֵ
  *		  minutia		   ϸ�ڵ㼯
  * ���أ�������
******************************************************************************/
FunError_t FPImageProcessing
(
 Image_t *image_org,
 Image_t *image,
 Image_t *imageGrads,
 Image_t *imageOri,
 const int32_t grads_ori_size,
 const int32_t seg_size,
 const int32_t seg_step,
 const int32_t seg_thr,
 const double gauss_sigma,
 const int32_t soft_size,
 const int32_t thin_thr,
 pFPMinutiaSet_t minutia
);




bool_t check_finger_ok
(	
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
);


void pixel_decompression_ex
(
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t dst_width,
 const int32_t dst_height,
 const int32_t dst_pitch
);


//ѹ������
void pixel_compression_ex
(
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
);

void get_fixed_roi
(
 uint8_t *pDst,
 const int32_t dst_width,
 const int32_t dst_height,
 const int32_t dst_pitch,
 uint8_t *pSrc,
 const int32_t upleft_x,
 const int32_t upleft_y,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 );

void change_edge_color
(
 //uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t up_x,
 const int32_t up_y,
 const int32_t dn_x, 
 const int32_t dn_y,
 const int32_t color,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 );

void pixel_add
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 );


#ifdef __cplusplus
}
#endif	/* extern "C" */

#endif /* __IMAGE_PROCESSING_H */

