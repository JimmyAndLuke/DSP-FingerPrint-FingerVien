
#include "bsp_header\z_sys_time.h"
//#include "sys_time.h"
//#include "myctype.h"

/***********************************************************************
ԭ����ʱ����Ҫ��ʱС��1msʱ����_delay_us����Ҫ��ʱ����1msʱ����_delay_ms
��ʱ����û����ֲ�ԣ���CPU����720MHzҪ�޸ģ���������������ʾ�������Թ�����
׼ȷ��Ҫ����ȷ����ʱҪ�Լ����ơ�
***********************************************************************/
void _delay_ms(int32_t t)
{
   int32_t tt;
   for(;t>0;t--)
   {
     for(tt=90000;tt>0;tt--)
     {
     }
   }
}

void _delay_us(int32_t t)
{
   int32_t tt;
   for(;t>0;t--)
   {
     for(tt=85;tt>0;tt--)
     {
     }
   }
}

uint32_t get_systicks(void)
{
  return 0;
}

uint32_t get_systime_ms(void)
{
  return 0;
}

bool_t get_local_time(sys_time*time)
{
  return _true;
}

bool_t get_local_time_ascii(sys_time*time)
{
  return _true;
}





