
#include <stdio.h>

#include <string.h>
#include "GUI_header/t9_input.h"


//#define my_strlen(ptr) strlen(ptr)
//�����ַ������ȵĺ������û�����ͨ���궨�����ú�����ĺ���
static unsigned int my_strlen(char*str)
{
   unsigned int count=0;
   while(*str++) {
     count++;
   }
   return count;
}

#define my_getchar()   getchar()

#ifdef EN_PC_TEST
//PC����ת��ΪT9���ְ���
static unsigned char char_to_num(char key)	
{
	switch (key) {

	case 'A':
	case 'a':return T9_ALPHABET_abc;
	case 'B':
	case 'b':return T9_ALPHABET_abc;
	case 'C':
	case 'c':return T9_ALPHABET_abc;
	case 'D':
	case 'd':return T9_ALPHABET_def;
	case 'E':
	case 'e':return T9_ALPHABET_def;
	case 'F':
	case 'f':return T9_ALPHABET_def;
	case 'G':
	case 'g':return T9_ALPHABET_ghi;
	case 'H':
	case 'h':return T9_ALPHABET_ghi;
	case 'I':
	case 'i':return T9_ALPHABET_ghi;
	case 'J':
	case 'j':return T9_ALPHABET_jkl;
	case 'K':
	case 'k':return T9_ALPHABET_jkl;
	case 'L':
	case 'l':return T9_ALPHABET_jkl;
	case 'M':
	case 'm':return T9_ALPHABET_mno;
	case 'N':
	case 'n':return T9_ALPHABET_mno;
	case 'O':
	case 'o':return T9_ALPHABET_mno;
	case 'P':
	case 'p':return T9_ALPHABET_pqrs;
	case 'Q':
	case 'q':return T9_ALPHABET_pqrs;
	case 'R':
	case 'r':return T9_ALPHABET_pqrs;
	case 'S':
	case 's':return T9_ALPHABET_pqrs;
	case 'T':
	case 't':return T9_ALPHABET_tuv;
	case 'U':
	case 'u':return T9_ALPHABET_tuv;
	case 'V':
	case 'v':return T9_ALPHABET_tuv;
	case 'W':
	case 'w':return T9_ALPHABET_wxyz;
    case 'X':
	case 'x':return T9_ALPHABET_wxyz;
	case 'Y':
	case 'y':return T9_ALPHABET_wxyz;
	case 'Z':
	case 'z':return T9_ALPHABET_wxyz;

    case '0':return T9_NUM_0;
	case '1':return T9_NUM_1;
	case '2':return T9_NUM_2;
	case '3':return T9_NUM_3;
	case '4':return T9_NUM_4;
	case '5':return T9_NUM_5;
	case '6':return T9_NUM_6;
	case '7':return T9_NUM_7;
	case '8':return T9_NUM_8;
	case '9':return T9_NUM_9;

	case '/':return T9_PY_PREV;
	case '*':return T9_PY_NEXT;

//	case ' ':
	case '.':return T9_PY_HZ;
	
	case '\n':return CR;
	case '#':return T9_PY_INPUT;

	case '=':
	case '+':return T9_HZ_NEXT;

	case '-':return T9_HZ_PREV;
	case '|':return OVER;
	case '<':return BACKSPACE;

	default:return  0;
	}
}
#endif

//���뷨�л�
static void input_switch(t9_input_t *p_t9_input)
{
	unsigned char i = 0;
	p_t9_input->switch_mode = 0;

	p_t9_input->py_count = 0;
	p_t9_input->py_index = 0;

	p_t9_input->mb_match_num = 0;

	p_t9_input->hz_index = 0;

	for (i = 0; i < 6; i++) 
		p_t9_input->py_buf[i] = 0;
	
	for (i = 0; i < 20; i++)
		p_t9_input->show_buf[i] = 0;

	switch (p_t9_input->input_mode) {
	case T9_CHN_MODE:
		p_t9_input->input_mode = T9_UEN_MODE;
		printf("\n��д����:\n");
		break;
	case T9_UEN_MODE:
		p_t9_input->input_mode = T9_LEN_MODE;
		printf("\nСд����:\n");
		break;
	case T9_LEN_MODE:
		p_t9_input->input_mode = T9_NUM_MODE;
		p_t9_input->switch_mode = 1;	//��������ʱ,ֱ�Ӿ�������������,û��ѡ�����
		printf("\n��������:\n");
		break;
	case T9_NUM_MODE:
		p_t9_input->input_mode = T9_CHN_MODE;
		printf("\n��������:\n");
		break;
	default:
		p_t9_input->input_mode = T9_CHN_MODE;
		printf("\n��������:\n");
		break;
	}
	
}

//��ȡ����ƴ���ִ���Ӧ�ĺ��ֵ����
//p_input:����İ������У���'0'~'9'��ɵ��ַ���
//match_mb:�洢"��ȡ����ƴ��������ַ"������
//����ֵ:����������ƥ��(ȫƥ������ƥ��)��ƴ��,���8��
static unsigned char t9_get_match_py_mb(t9_input_t *p_t9_input)//(char *p_input, t9PY_index **match_mb)
{
	unsigned char i = 0, j = 0;
	unsigned char input_len = 0;

	unsigned char match_num = 0;//p_t9_input->mb_match_num;
	char *p_input = p_t9_input->py_buf;
	t9PY_index **match_mb = p_t9_input->py_mb;

	t9PY_index *p_current_index,*p_last_index;	//ָ��"ƴ�����뷨��ѯ���"�����ĳ���±�Ԫ�صĵ�ַ
//	t9PY_index *p_temp_index;

	unsigned int index_begin = 0, index_end = 0;
	unsigned char py_1 = 0, py_2 = 0;			//һά���ά��������±�
	if (*p_input == '\0')
		return 0;

	input_len = my_strlen(p_input);

	//����һ���:������������ʼ��ַ,����һά,��ά��������ܳ��ֵĸ������
	if (input_len >= 2) {	//�������ִ�>=2,ʹ�ö�ά����
		py_1 = (*p_input) - 0x32;	// ����ĵ�һ���ַ� - '2'
		//p_input++;
		py_2 = (*(p_input+1)) - 0x32; // ����ĵڶ����ַ� - '2'
		
		index_begin = t9_search_index2[py_1][py_2];
		if (index_begin == 0) {						//û�������ִ����(25,27,29,99��),index_beginΪ0����һά����
			index_begin = t9_search_index1[py_1];	//��ʼ��ַ�޸�Ϊһά������Ӧ�ĵ�ַ
			if (py_2 < 7)							//��һά���������һ��Ԫ��,������������ַΪ��һԪ�ض�Ӧ�ĵ�ַ
				index_end = t9_search_index1[py_1+1];
			else									//��Ӧ'99'
				index_end = 397;
		} else										//������ʼ��ַ��Ϊ0
			index_end = t9_search_index2[py_1][py_2+1];

		while (index_end == 0) {	//��һԪ��Ϊ0,��index_endΪ0,�����index_endΪ���Ȳ�Ϊ0��λ��
			py_2++;			       //���index_end�Ѿ�����[py_1][8]��,��
			if(py_2 > 7) {			//��ֲ��һ��[py_1 + 1][0]
				if (py_1 < 7) {
					py_1++;
					py_2 = 0;
				} else {
					index_end = 397;
					break;
				}
			}//end if (py_2 > 7)
			index_end = t9_search_index2[py_1][py_2];
		}//end while (index_end == 0)
	} else {	//�������ִ�==1,һά����
		py_1 = (*p_input) - 0x32;
		index_begin = t9_search_index1[py_1];
		if (py_1 >= 7)
			index_end = 397;
		else
			index_end = t9_search_index1[py_1+1];
	}
	//����һ���:������������ʼ��ַ,����һά,��ά��������ܳ��ֵĸ������

	p_current_index = &(t9PY_index2[index_begin]);	//������ʼ��ַ
	p_last_index = &(t9PY_index2[index_end]);		//�����������ַ

	while (p_current_index < p_last_index) {	//����������
		for (i = 0; i < input_len; i++) {
			if ((*(p_input + i)) != *(p_current_index->t9PY_T9 + i)) {	//��ȫ�����ƥ��
				//((*(p_input + i)) != *((*p_current_index).t9PY_T9 + i)) {	//��ȫ�����ƥ��
/*				if (i + 1 > j) {	//�ҳ����в�ƥ��������Ǹ���ƥ�����ִ�(���ȱ�����j��,��������p_temp_index��)
					j = i + 1;
					p_temp_index = p_current_index; 
				}*/
				break; //
			} 
		}

		if ((i == input_len) && (match_num < 8)) {	//ƥ��ı��浽���ڲ���match_mb
			//ƥ��,���8��.ƥ�䲢����ָ��Ƚϵ��ַ�����һ����������ȫƥ��
			match_mb[match_num] = p_current_index;
			match_num++;
		}

		p_current_index++;
	}//end while (p_current_index < p_last_index)

//	if (j != input_len)	//��ƥ�䵫���ƥ���ַ���1��
//		match_mb[7] = p_temp_index;	
	p_t9_input->mb_match_num = match_num;
	return match_num;
}

//����p_t9_input�ĳ�Ա:show_buf,hz_select��
//temp_char:������ֵ
void t9_cn_show_handle(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char count = 0,i = 0,j = 0;
	unsigned char pos = 2 * (temp_char - 0x31);		  //����ѡ��ĺ��ֵ�λ��,1�����ֶ�Ӧ2���ֽ�
	unsigned char offset = (p_t9_input->hz_index/2)*2;//����2���ֳ���2��������Ϊ�˻��ż��(��Ϊƴ��������ַ���'@'�����Ǻ���)
	
	t9PY_index *temp_py_mb = p_t9_input->py_mb[p_t9_input->py_index];
	p_t9_input->mb_select = p_t9_input->py_mb[p_t9_input->py_index];
	
	if ((temp_char >= T9_NUM_1) && (temp_char <= T9_NUM_9)) {	//ѡ����
		if (p_t9_input->show_buf[pos] != 0) {	//���ֶ�Ӧ�ĺ��ַǿ�,
																		
			p_t9_input->hz_select[0] = p_t9_input->show_buf[pos];	//����ѡ�к��ֻ�����
			p_t9_input->hz_select[1] = p_t9_input->show_buf[pos + 1];

			if (p_t9_input->count < MAX_BUF_LEN) {//���뻺����δ��
				p_t9_input->buf[p_t9_input->count] = p_t9_input->show_buf[pos];	//�������뻺����
				p_t9_input->count++;
				p_t9_input->buf[p_t9_input->count] = p_t9_input->show_buf[pos + 1];
				p_t9_input->count++;
			}

			p_t9_input->py_index = 0;	//���½ṹ��Ϣ��׼���´ε�����
			p_t9_input->py_count = 0;
			for (i = 0; i < 6; i++) 
				p_t9_input->py_buf[i] = 0;

			p_t9_input->hz_index = 0;
			//for (i = 0; i < 20; i++)
				//p_t9_input->show_buf[i] = 0;
		}
	} else {	//��1-9,����ʵ�ʹ��ܰ�����������
		p_t9_input->py_select = temp_py_mb->PY;
		count = strlen(temp_py_mb->PY_mb) - 1;
		count = count - offset > 18 ? 18 : count - offset;//����ж��ٸ���Ч����,����9��,��ʾ9,������ѡ��ʵ�ʵĸ���
		for (j = 0; j < count; j++) {	//������ʾ����
			p_t9_input->show_buf[j] = *(temp_py_mb->PY_mb + offset + 1 + j);
		}
		for (; j < 18; j++) {
			p_t9_input->show_buf[j] = 0;
		}
	}
}


unsigned char flag = 0;//���ڱ���Ƿ���ʾpritf("\n���� /:...\n");
//���ݲ�ͬ�������ֵ,��ʾ��Ӧ�Ľ���
//temp_char:����ļ�ֵ
void t9_cn_show(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char temp;
	t9PY_index * temp_py_mb;
	if ((temp_char >= T9_NUM_1) && (temp_char <= T9_NUM_9)) {		//��ʾ��ѡ���ּ����뻺����
			if (p_t9_input->show_buf[2 * (temp_char - 0x31)] != 0) {	//�����������Ч,����Ӧλ���к���
				printf("                   \n");
				printf("ѡ��ĺ���Ϊ:   ");
				printf(p_t9_input->hz_select);
				printf("\n");
				printf(p_t9_input->buf);
				printf("\n");
				p_t9_input->switch_mode = 0;	//����Ϊƴд״̬
				flag = 1;
			} 
		} else if (temp_char != CR){	//��ʾѡ�����
			printf("\n\n��ѡ���ƴ��:    ");
			printf((p_t9_input->mb_select)->PY);

			printf("\n�������ֻ�+,-ѡ�� \n");
			printf(p_t9_input->show_buf);
			//printf((p_t9_input->mb_select)->PY_mb + (hz_index/2)*2 + 1);
			printf("\n1 2 3 4 5 6 7 8 9\n");

			printf ("ƴд���:");
            for (temp = p_t9_input->py_index; temp < p_t9_input->mb_match_num; temp++) {
                temp_py_mb = p_t9_input->py_mb[temp];

                printf (" ");
                printf (temp_py_mb->PY);//printf ((*(temp_py_mb)).PY);
            }
               printf ("\n");
		}

}

//��������Ĳ�ͬ��ֵ,����p_t9_input(swich_mode,py_index,hz_index��)
//����ȡ��Ӧƴ�������
//temp_char:����ļ�ֵ
void t9_cn_key_handle(t9_input_t *p_t9_input, unsigned char temp_char)
{

	unsigned char match_num = 0;

	switch (temp_char) {
	case T9_NUM_2:
	case T9_NUM_3:
	case T9_NUM_4:
	case T9_NUM_5:
	case T9_NUM_6:
	case T9_NUM_7:
	case T9_NUM_8:
	case T9_NUM_9:
		if (p_t9_input->switch_mode == 0) {	//2-9������Ӧ��ƴ�����
			if(p_t9_input->py_count < 6)	//һ���������6��ƴ��
			{
				p_t9_input->py_buf[p_t9_input->py_count] = temp_char;	//����������ִ�д���Ӧ��
				p_t9_input->py_count++;									//ƴ����������
				p_t9_input->hz_index = 0;   
				match_num = t9_get_match_py_mb(p_t9_input);				//�������
			}
		}
		break;
	case T9_PY_PREV:		//��ǰѡ��ƴ��
			if (p_t9_input->py_index > 0)
				p_t9_input->py_index--;	
			else
				p_t9_input->py_index = p_t9_input->mb_match_num - 1;
			p_t9_input->hz_index = 0;
			break;
	case T9_PY_NEXT:		//���ѡ��
			p_t9_input->py_index++;
			if (p_t9_input->py_index >= p_t9_input->mb_match_num)
				p_t9_input->py_index = 0;
			p_t9_input->hz_index = 0;
			break;
//	case '.':
//	case ' ':
	case T9_PY_INPUT:		//���뷨�л�
		input_switch(p_t9_input);
		break;
	case T9_PY_HZ:			//�ִ�(ƴ��)����orȷ������
		p_t9_input->switch_mode ^= 1;
		break;
	//case '=':
	case T9_HZ_NEXT:		//��һҳ����
		if (p_t9_input->hz_index < strlen((p_t9_input->mb_select)->PY_mb) - 19) //��ͷ�и�'@'
			p_t9_input->hz_index += 18;
		break;
	case T9_HZ_PREV:		//��һҳ����
		if (p_t9_input->hz_index >=18)
			p_t9_input->hz_index -=18;
		break;
	case BACKSPACE:								//ɾ������ƴ��(���ִ�)�����뻺�����ĺ��ֻ���ĸ
		if (p_t9_input->switch_mode == 0) {
			if (p_t9_input->py_count > 0) {			//ɾ��ƴ��(���ִ�)
				//i--;
				p_t9_input->py_count--;
			}
			p_t9_input->py_buf[p_t9_input->py_count] = 0x00; 
			p_t9_input->hz_index = 0; 
			match_num = t9_get_match_py_mb(p_t9_input);
		} else {									//ɾ�����뻺����
			if (p_t9_input->count > 0) {		
				p_t9_input->count--;
			}
			if (p_t9_input->buf[p_t9_input->count] > 0x7E) {//�ж��Ǻ��ֻ����ַ�
				p_t9_input->buf[p_t9_input->count] = 0x00;	//����ɾ�������ֽ�
				p_t9_input->count--;
				p_t9_input->buf[p_t9_input->count] = 0x00;
			//	p_t9_input->count--;
			} else {
				p_t9_input->buf[p_t9_input->count] = 0x00;	//�ַ�ɾ��һ���ֽ�
			//	p_t9_input->count--;				
			}
		}
		break;
//		case OVER:
//			py_ok = 1;
//			break;
	default:
		break;
	}
	
	if (p_t9_input->switch_mode) {			//����ģʽ��,������ʾ�������ʾ
		t9_cn_show_handle(p_t9_input, temp_char);
		t9_cn_show(p_t9_input, temp_char);
	} 
}

//���ݲ�ͬ�������ֵ,��ʾ��Ӧ�Ľ���
//temp_char:����ļ�ֵ
void t9_en_show(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char i = 0;
	unsigned char pos = temp_char - 0x31;
	if (p_t9_input->input_mode == T9_NUM_MODE) {	//��������ģʽ,ֱ����ʾ���������
			printf("                   \n");
			printf("���������Ϊ:   ");		
			printf("%c",p_t9_input->show_buf[0]);
			printf("\n");
			printf(p_t9_input->buf);
			printf("\n");
			flag = 1;
	} else {										//��Сд����ģʽ
		if (temp_char >= T9_NUM_1 && temp_char <= T9_NUM_9)  {	//��ʾѡ�����ĸ
			if (p_t9_input->show_buf[pos] != 0) {	//�����������Ч,����Ӧλ�����ַ�
				printf("                   \n");
				printf("ѡ�����ĸΪ:   ");
				printf("%c",p_t9_input->show_buf[pos]);	

				if (p_t9_input->count < MAX_BUF_LEN) {//���뻺����δ��
					p_t9_input->buf[p_t9_input->count] = p_t9_input->show_buf[pos];	//�������뻺����
					p_t9_input->count++;
				}

				printf("\n");
				printf(p_t9_input->buf);
				printf("\n");
				p_t9_input->switch_mode = 0;	//����Ϊƴд����״̬
				flag = 1;
			} 
		} else if (temp_char != CR ){	//��ʾѡ�����
			//printf("\n\n��ѡ�����ĸ:    ");
			//printf((p_t9_input->mb_select)->PY);

			printf("\n��������ѡ�� \n");
			for (i = 0; i < 4; i++) {
				printf("%c",p_t9_input->show_buf[i]);
				printf(" ");
			}
			//printf((p_t9_input->mb_select)->PY_mb + (hz_index/2)*2 + 1);
			printf("\n1 2 3 4\n");
		}
	}	
	//}
}

//��������Ĳ�ͬ��ֵ,����p_t9_input�ĳ�Ա
//temp_char:����ļ�ֵ
void t9_en_key_handle(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char i = 0;
	switch (temp_char) {
	case T9_NUM_0:
	case T9_NUM_1:
		if (p_t9_input->input_mode == T9_NUM_MODE) {	//�������뷨
			if (p_t9_input->count < MAX_BUF_LEN) {
				p_t9_input->show_buf[0] = temp_char;
				p_t9_input->buf[p_t9_input->count] = temp_char;
				p_t9_input->count++;
				p_t9_input->switch_mode = 1;			//��������ʱ,ֱ�Ӿ�������������,û��ѡ�����
			}
		}
		break;
	case T9_NUM_2:
	case T9_NUM_3:
	case T9_NUM_4:
	case T9_NUM_5:
	case T9_NUM_6:
	case T9_NUM_7:
	case T9_NUM_8:
	case T9_NUM_9:
		if (p_t9_input->switch_mode == 0) {
			if(p_t9_input->py_count < 1) {		//ÿ������ֻ����һ��
				p_t9_input->py_buf[p_t9_input->py_count] = temp_char;
				p_t9_input->py_count++;
				for (i = p_t9_input->py_count; i < 6; i++)
					p_t9_input->py_buf[i] = 0x00;
			}
			if (p_t9_input->input_mode == T9_LEN_MODE) {	//Сдabc
				for (i = 0; i < 4; i++) {
					p_t9_input->show_buf[i] = ascii_tab[temp_char - 0x32][i];//Сд��ĸ
				}
			} else if (p_t9_input->input_mode == T9_UEN_MODE) {	//��дABC
				for (i = 0; i < 3; i++) {
					p_t9_input->show_buf[i] = ascii_tab[temp_char - 0x32][i] - 32;//��д��ĸ
				}
				if (ascii_tab[temp_char - 0x32][3] != 0)
					p_t9_input->show_buf[3] = ascii_tab[temp_char - 0x32][3] - 32;
				else
					p_t9_input->show_buf[3] = 0;
			} 
		}else if (p_t9_input->input_mode == T9_NUM_MODE) {	//��������ʱ,ֱ�Ӿ�������������,û��ѡ�����
				if (p_t9_input->count < MAX_BUF_LEN) {
					p_t9_input->show_buf[0] = temp_char;
					p_t9_input->buf[p_t9_input->count] = temp_char;
					p_t9_input->count++;
					p_t9_input->switch_mode = 1;
				}
			}
		break;
	case T9_PY_HZ:
		if (p_t9_input->input_mode != T9_NUM_MODE)
			p_t9_input->switch_mode ^= 1;				//��ĸ�����ȷ����ĸ
		break;
	case T9_PY_INPUT:
		input_switch(p_t9_input);
		break;
	case BACKSPACE:									//ɾ��������ĸ(���ִ�)�����뻺�����ĺ��ֻ���ĸ
		if (p_t9_input->switch_mode == 0) {
			if (p_t9_input->py_count > 0) {						//ɾ���������ִ�
				//i--;
				p_t9_input->py_count--;
			}
			p_t9_input->py_buf[p_t9_input->py_count] = 0x00; 
		} else {												//ɾ�����뻺����
			if (p_t9_input->count > 0) {
				p_t9_input->count--;
			}
			if (p_t9_input->buf[p_t9_input->count] > 0x7E) {	//�ж��Ǻ���or�ַ�
				p_t9_input->buf[p_t9_input->count] = 0x00;			//����ɾ�������ֽ�
				p_t9_input->count--;
				p_t9_input->buf[p_t9_input->count] = 0x00;
			//	p_t9_input->count--;
			} else {												//�ַ�ɾ��һ���ֽ�
				p_t9_input->buf[p_t9_input->count] = 0x00;
			//	p_t9_input->count--;				
			}
		}
		break;
	}
	if (p_t9_input->switch_mode) {
//		t9_cn_show_handle(p_t9_input, temp_char);
		t9_en_show(p_t9_input, temp_char);
	} 
}

//p_t9_input������Ա�ĳ�ʼ��
void t9_input_init(t9_input_t *p_t9_input) 
{
	unsigned char i = 0;

	p_t9_input->input_mode = 0;
	p_t9_input->switch_mode = 0;

	p_t9_input->py_count = 0;
	p_t9_input->py_index = 0;

	p_t9_input->mb_match_num = 0;

	p_t9_input->hz_index = 0;

	p_t9_input->count = 0;

	
	for (i = 0; i < 6; i++) 
		p_t9_input->py_buf[i] = 0;
	
	for (i = 0; i < 20; i++)
		p_t9_input->show_buf[i] = 0;

	for (i = 0; i < 4; i++)
		p_t9_input->hz_select[i] = 0;

	for (i = 0; i < 34; i++)
		p_t9_input->buf[i] = 0;	

	p_t9_input->py_select = (unsigned char *)0;

	for (i = 0; i < 8; i++)
		p_t9_input->py_mb[i] = (t9PY_index *)0;
	p_t9_input->mb_select = (t9PY_index *)0;

}

//void main(void)
//{
//	t9_input_t input;
//	unsigned char temp_char;
////	printf("Hello world! \n");
//	//putchar(*(PY_mb_a+1));
//	//putchar(*(PY_mb_a+2));
////	printf(temp_word);
////	printf("\n");
//	t9_input_init(&input);
//	printf ("\n���� /:��һƴ�� *:��һƴ�� .�Ϳո񼰻س���:����״̬��ѡ��״̬�л�\n");         //
//	printf ("�밴����2-abc 3-def 4-ghi 5-jkl 6-mno 7-pqrs 8-tuv 9-wxyz \n");  
//	while (temp_char!= '|') {	//����'|'�˳�����
//		if(flag == 1) {
//			if (input.input_mode == T9_CHN_MODE) {	//����������ʾ����
//				printf ("\n���� /:��һƴ�� *:��һƴ�� .�Ϳո񼰻س���:����״̬��ѡ��״̬�л�\n");         //
//				printf ("ƴ��2-abc 3-def 4-ghi 5-jkl 6-mno 7-pqrs 8-tuv 9-wxyz \n");   
//			} else if (input.input_mode == T9_UEN_MODE) {	//��дABC������ʾ����
//				printf ("\nABC��2-ABC 3-DEF 4-GHI 5-JKL 6-MON 7-PQRS 8-TUV 9-WXYZ \n");  			
//			} else if (input.input_mode == T9_LEN_MODE) {	//Сдabc������ʾ����
//				printf ("\nabc��2-abc 3-def 4-ghi 5-jkl 6-mno 7-pqrs 8-tuv 9-wxyz \n"); 
//			} else if (input.input_mode == T9_NUM_MODE) {	//����������ʾ����
//				printf ("\n123:\n"); 
//			}
//			flag = 0;
//		}
//		temp_char = char_to_num(my_getchar());			//��ֵ��ȡ
//		if (input.input_mode == T9_CHN_MODE)			//��������
//			t9_cn_key_handle(&input, temp_char);		//�������ļ�ֵ����
//		else											
//			t9_en_key_handle(&input, temp_char);		//����Ӣ�ļ�ֵ����
//	}
//}







