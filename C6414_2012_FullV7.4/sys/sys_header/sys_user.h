/******************************************************************************
 * �ļ�����sys_gobal.h
 * ���ܣ�  һЩϵͳ��ȫ�ֱ����Ͳ���
******************************************************************************/

#if !defined __SYS_USER_H
#define __SYS_USER_H


/* �������Ͷ��� */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../dip/dip_header/dip_header.h"
#include "../../dip/dip_header/image_feature.h"




#ifdef __cplusplus
extern "C" {
#endif



/*
���ݿ����˵����
*���еĶ���������SDRAM����ɣ��ϵ�ʱϵͳ�����һ�����ݵ�SDRAM����������֯��ѭ������
*����д��������ѭ����SDRAM���޸ģ�Ȼ���ٸ��µ�FLASH��ԭ��
*д�����ݿ��һ�����̣�
*1.׼����һ����Ԫ�����ݴ�С4KB
*2.��SDRAM�����һ����Ԫ��
*3.����FLASH�ϵ�һ����Ԫ��
*4.�������Ԫ������д��FLASH�С�
*/

//����
#define macro_db_administrator 0
#define macro_db_normal_user   1


//Ȩ�޺궨���Ȩ�ޣ�дȨ�ޣ�����Ȩ�ޡ�˽��Ȩ��
#define macro_db_limits_all    0
//root�û�
#define macro_db_limits_read   1
#define macro_db_limits_write  2
//����Ա
#define macro_db_limits_self   4
//�û���ֻ�ܿ����Լ�����Ϣ

//�Ա����Ժ궨��
#define macro_db_men            0
#define macro_db_women          1


typedef struct t_user_t{

struct t_user_t *next ; //ָ�����һ���û���ָ��
struct t_user_t *pre  ; //ָ��ǰ��һ���û���ָ��
uint32_t  id          ; //�ڲ�ID,��idΪ0xffffffffʱ����Ϊ��Ч�û�
uint32_t  attribute   ; //����,����Ա��ͨ�û��ȵ�
uint32_t  limits      ; //Ȩ��,���û�ӵ�е�Ȩ��
//time_t    reg_time    ; //ע��ʱ��
char      name[16]    ; //����
uint32_t  sexuality   ; //�Ա�
//feature_t feature   ; //ʶ���õ�����  //jjdeng
FPMinutiaSet_t fp_minutia;
uint8_t   imgbuf[4500];  //����ͼ��     //pl
//uint8_t   rsvd[1]     ; //��������������4kB���������
}user_t;



typedef struct{

uint32_t user_cnt;           //��ͨ�û�����
uint32_t admin_cnt;          //����Ա������
uint32_t all_cnt;            //���û���
user_t*  list_head;          //ָ���û��б�Ŀ�ͷ�����ݽṹ,�������ֻ��ָ��̬������
user_t*  list_current;      //�б�ǰ���û�
user_t*  list_tail;          //�û��б�β��

/*�����Ǻ����ݽṹ������صĳ�Ա*/
uint32_t start_addr;      //���ݿ����ʼ��ַ
uint32_t size      ;      //���ݿ�Ĵ�С,�ֽ�Ϊ��λ
uint32_t unit_size ;      //���ݿ��ÿ��Ԫ��Ԫ��С���ֽ�Ϊ��λ
uint32_t dynamic_start_addr; //��̬���ݿ����ʼ��ַ
uint32_t id_map[8];      //ID�ŵ�λͼ
//uint32_t id_map[16];      //ID�ŵ�λͼ

}database_t;



bool_t sys_user_register   (user_t*user);
bool_t sys_user_unregister (user_t*user);
//bool_t sys_user_login      (user_t*user);
//bool_t sys_user_find       (user_t*user);
//bool_t sys_user_add        (user_t*user);
//bool_t sys_user_delete     (user_t*user);
bool_t sys_is_normal_user  (user_t*user);
bool_t sys_is_administrator(user_t*user);
//bool_t sys_user_change_mod (user_t*user);
//char*  sys_user_get_name   (user_t*user);
//uint32_t sys_user_get_id   (user_t*user);


/*���ݿ�ײ㺯������api���ã��û�����Ӵ�����һ�㡣*/
void    sys_db_write_unit(uint32_t id,void*buf);
database_t*sys_get_database      (void       );
void     sys_database_init       (void       );
bool_t   sys_database_add        (user_t*user);
bool_t   sys_database_delete     (user_t*user);
user_t*  sys_database_get_next   (void       );
user_t*  sys_database_get_pre    (void       );
user_t*  sys_database_get_head   (void       );
user_t*  sys_database_get_tail   (void       );
void     sys_database_go_to_head (void       );
void     sys_database_go_to_tail (void       );
uint32_t sys_database_malloc_id  (void       );//����һ��id��
void     sys_database_free_id    (uint32_t id);
user_t*  sys_database_malloc_user(uint32_t id);//��ȡ��ŵ��û����ݽṹ���ڴ�
//bool_t  sys_database_change_mod(user*_t  );



void sys_database_init0(void);



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __SYS_GLOBAL_H */
















