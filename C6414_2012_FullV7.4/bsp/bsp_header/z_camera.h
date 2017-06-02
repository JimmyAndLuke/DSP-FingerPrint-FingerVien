/******************************************************************************
 * �ļ�����z_camera.h
 * ���ܣ�  ����ָ�ƺ�ָ������ͷ�ɼ�ͼ��	
******************************************************************************/
#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "z_mytype.h"

#include "..\..\C6414_2012_Fullcfg.h"
#include <csl.h>
#include <csl_irq.h>  
#include <csl_edma.h>


#ifdef __cplusplus
extern "C" {
#endif


//����Ҫ�ɼ���ͼ����ָ�ơ�ָ�����ĺꡣ
#define FINGER_VEIN     (0x00000001U)
#define FINGER_PRINT    (0x00000002U)
#define FINGER_TEST		(0x00000003U)

//void camera_reset(void);			 //����ͷ��λ
void camera_capture(uint32_t flag); //����ͷ����һ����Ƭ
void camera_init(void);			 //����ͷ��ʼ��


#ifdef __cplusplus
}
#endif /* extern "C" */



#endif




