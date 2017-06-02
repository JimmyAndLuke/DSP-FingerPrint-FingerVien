#ifndef SYS_TIME_H_H______
#define SYS_TIME_H_H______
#include "z_mytype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	union{
		uint32_t year;
		char     a_year[4];
	}yy;
	union{
		uint32_t mon ;
		char     a_mon[4];
	}mo;
	union{
		uint32_t day;
		char     a_day[4];
	}dd;
	union{
		uint32_t hour;
		char     a_hour[4];
	}hh;
	union{
		uint32_t week;
		char     a_week;
	}ww;
	union{
		uint32_t min ;
		char     a_min[4];
	}mm;
	union{
		uint32_t sec ;
		char     a_sec;
	}ss;
	union{
		uint32_t msec;
		char     a_msec[4];
	}ms;
}sys_time;


//����ĺ�����720MHz���ǱȽϾ�ȷ����ʱ������
extern void _delay_ms(int32_t t);
extern void _delay_us(int32_t t);

//������ǻ�ȡϵͳʱ��ĺ���

/*****************************************
*��ȡϵͳ�����˶��ٸ�ʱ�ӽ��ġ�
*****************************************/
uint32_t get_systicks(void);

/*****************************************
*��msΪ��λ����ϵͳ�����˶��ٸ�����
******************************************/
uint32_t get_systime_ms(void);

/******************************************************
*�������ƣ�bool_t get_local_time(sys_time*time)
*���������sys_time*time ָ��һ��ϵͳʱ������ݽṹ
*���ز�����bool_t ������Ϊ _falseʱ����ϵͳû��ʵʱʱ��
*          ������Ϊ_trueʱ������ϵͳ��ʵʱʱ��

*˵����    ��ȡϵͳ��ǰ�ı���ʱ�䣬��ϵͳ��ʵʱʱ���ṩ
*          ��ϵͳ������ϵͳʱ��ʱ����ϵͳ�������ṩһ��
*          ���ʱ�䡣
*******************************************************/
bool_t get_local_time(sys_time*time);

/******************************************************
*���ڻ�ȡ��ǰϵͳʱ�䣬���Ǹ�ʱ����ascii����ʽ�ġ�
*******************************************************/
bool_t get_local_time_ascii(sys_time*time);

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif

