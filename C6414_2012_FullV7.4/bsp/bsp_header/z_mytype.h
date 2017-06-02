

#ifndef __MYCTYPE_H__
#define __MYCTYPE_H__


#ifdef __cplusplus
extern "C" {
#endif


typedef  char               int8_t   ;
typedef  short int          int16_t  ;
typedef  int                int32_t  ;

typedef  unsigned char      uint8_t  ;
typedef  unsigned short int uint16_t ;
typedef  unsigned int       uint32_t ;

//typedef  unsigned int       size_t   ;

typedef  int                bool_t   ;

typedef  uint8_t            byte_t   ;
typedef  uint16_t           word_t   ;
typedef  uint32_t           dword_t  ;

typedef  uint16_t           color_t  ;




#ifndef TRUE
#define FALSE               ((int32_t)0)
#define TRUE                ((int32_t)1)
#endif

#define  _true              ((int32_t)1)
#define  _false             ((int32_t)0)

#ifndef NULL
#define NULL                ((void*)0)
#endif

#define  PL_NULL            ((void*)0)



/* ָ������ */
typedef void*			Pointer_t;
/* ������ͣ�����������͸����ָ�� */
typedef void*			Handle_t;
/* �ַ������� */
typedef char*			String_t;


typedef struct Point_t {
	int32_t x;
	int32_t y;
} Point_t;

/* �������� */
typedef enum Bool_t
{
	/* false��� */
	bFalse = 0,
    /* true��� */
	bTrue  = 1
} Bool_t;

/* ����PIֵ */
#ifndef M_PI
//#define M_PI			3.1415926535897932384626433832795
//#define M_PI				3.1415926
//#define M_EPI				57.29578		//180/M_PI
#define M_PI				3.1415926
#define M_PI_X2				6.2831852
#define M_EPI				57.29578		//180/M_PI
#define M_EPI_2				28.64789
#endif

/* ����������� */
typedef enum FunError_t
{
	/* δ������� */
	FunFailure			= -1,
	/* û�д��� */
	FunOK				= 0,
	/* �ڴ治�� */
	FunMemory,
	/* ������Ч */
	FunBadParameter,
	/* �ļ���ʽ���� */
	FunBadFormat,
	/* ����������� */
	FunIoError,
	FunError
} FunError_t;


#ifdef __cplusplus
}
#endif /* extern "C" */



#endif /* __MYCTYPE_H__ */









