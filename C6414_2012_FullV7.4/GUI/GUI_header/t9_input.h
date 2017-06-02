
#ifndef __T9_INPUT_H_
#define __T9_INPUT_H_

/* �������Ͷ��� */
#include "../../bsp/bsp_header/z_mytype.h"

#ifdef __cplusplus
extern "C" {
#endif


/*"ƴ�����뷨�������б�"*/
//������ݽṹ
typedef struct 
{
    char  *t9PY_T9;
    char  *PY     ;
    char  *PY_mb  ;
//	int   word_count;
}t9PY_index;

//���뷨���ݽṹ
typedef struct{   
  short  input_mode      ;  //���뷨ģʽ
  
  t9PY_index*index       ;  //������,����ʼλ��

  t9PY_index*mb_index[6] ;  //ָ�����飬��Ԫ��ָ��ǰ��������6��ƴ�����������λ��

  short  pinyin_buf[6]   ;  //��ǰ�Ѿ������ƴ������
  short  pinyin_count    ;  //ƴ����������� 

  short  pinyin_selected ;  //��ǰѡ�е�ƴ����λ��

  short  show_offset     ;  //��ǰ����ʾ�ĺ������ַ��ں�������е�����ֽ�λ��(�ڼ�����0��ʼ����) ;  
  char  show_buf[14]     ;  //��ʾ����һ����ʾ6������,�������12��ascii��                    ;

   char  buf[32]        ;  //���뻺�����һ������16������,����32��ascii��
  short  count          ;  //��ǰ�Ѿ�����ĺ�����ռ���ֽ��������ǵ���Ӣ�����������  

}t9_input_t;


//t9ƴ�����뷨��ԭʼ�궨�塣
#define macro_t9_key_0                0u         
#define macro_t9_key_1                1u
#define macro_t9_key_2                2u
#define macro_t9_key_3                3u
#define macro_t9_key_4                4u
#define macro_t9_key_5                5u
#define macro_t9_key_6                6u
#define macro_t9_key_7                7u
#define macro_t9_key_8                8u
#define macro_t9_key_9                9u
#define macro_t9_key_space            10u
#define macro_t9_key_backspace        11u
#define macro_t9_key_enter            12u
#define macro_t9_key_exit             13u
#define macro_t9_key_switch           14u
#define macro_t9_key_pinyin0          15u
#define macro_t9_key_pinyin1          16u
#define macro_t9_key_pinyin2          17u
#define macro_t9_key_pinyin3          18u
#define macro_t9_key_pinyin4          19u
#define macro_t9_key_pinyin5          20u
#define macro_t9_key_show_forward     21u
#define macro_t9_key_show_back        22u
#define macro_t9_key_word0            23u
#define macro_t9_key_word1            24u
#define macro_t9_key_word2            25u
#define macro_t9_key_word3            26u
#define macro_t9_key_word4            27u
#define macro_t9_key_word5            28u

//һЩת��ĺ궨��
#define macro_t9_key_abc     macro_t9_key_2
#define macro_t9_key_def     macro_t9_key_3
#define macro_t9_key_ghi     macro_t9_key_4
#define macro_t9_key_jkl     macro_t9_key_5
#define macro_t9_key_mno     macro_t9_key_6
#define macro_t9_key_pqrs    macro_t9_key_7
#define macro_t9_key_tuv     macro_t9_key_8
#define macro_t9_key_wxyz    macro_t9_key_9

//t9����ģʽ,enΪӢ��cnΪ����numΪ����
/*
�������·ֱ���
1.����
2.Сд��ĸ
3.��д��ĸ
4.����
*/

#define macro_t9_mode_cn     0u
#define macro_t9_mode_len    1u
#define macro_t9_mode_uen    2u
#define macro_t9_mode_num    3u


//ѡ�е�ƴ���궨��
#define macro_t9_pyselected0  0
#define macro_t9_pyselected1  1
#define macro_t9_pyselected2  2
#define macro_t9_pyselected3  3
#define macro_t9_pyselected4  4
#define macro_t9_pyselected5  5

//���������ַ�����
#define macro_t9_max_input_count  32


//�ⲿ����������
extern t9PY_index t9_py_index[];

//��������:
bool_t t9_en_keyhandler (t9_input_t*input,short key_id);  //Ӣ����ĸ�����ֵ����봦��
bool_t t9_cn_keyhandler   (t9_input_t*input,short key_id);//��������,����Ҫ������������������
bool_t t9_cn_searchhandler(t9_input_t*input);//��������
void   t9_cn_showhandler  (t9_input_t*input);//��ʾ����
void   t9_cn_input        (t9_input_t*input,short key_id);//���뷨���ܺ���
void   t9_initialize(t9_input_t*input,t9PY_index*index);    //�����ʼ��



#ifdef __cplusplus
}
#endif

#endif

