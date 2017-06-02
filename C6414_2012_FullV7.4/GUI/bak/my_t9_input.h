
#ifndef __T9_INPUT_H_
#define __T9_INPUT_H_

/* �������Ͷ��� */


#ifdef __cplusplus
extern "C" {
#endif

//#define EN_PC_TEST	//PC�ϲ���

typedef struct tag_t9PY_index
{
	char *t9PY_T9;	//����
	char *PY;		//ƴ��
	char *PY_mb;	//���
}t9PY_index;

typedef struct tag_t9_input_t
{
	//�ӿռ俼��,����˳��
	unsigned char input_mode;		//���뷨ģʽ:��,��Сд,����
	unsigned char switch_mode;		//ѡ��ƴ��or����
	unsigned char py_count;			//����ƴ����Ŀ,<=6(0-5)
	unsigned char py_index;			//��ѡƴ������
	unsigned char mb_match_num;		//�������ַ�������ƥ���������,<=8(0-7);
	unsigned char hz_index;			//��ѡ��������
	unsigned char count;			//����������������

	unsigned char py_buf[6];		//����ƴ���ִ�������
	unsigned char hz_select[4];				//ѡ�еĺ��ֻ�����
	unsigned char show_buf[20];		//����ʾ���ֻ�����,0-17(9������)
	unsigned char buf[34];			//������������

	unsigned char *py_select;
	t9PY_index *py_mb[8];			//ƥ��ƴ��������е�λ��
	t9PY_index *mb_select;			//��ѡ�е�ƴ����Ӧ�����

}t9_input_t;

/*
typedef struct tagt9_input_t
{	//�ӷ��࿼��
	unsigned char input_mode;		//���뷨ģʽ:��,��Сд,����
	unsigned char switch_mode;		//ѡ��ƴ��or����

	unsigned char py_buf[6];		//����ƴ���ִ�������
	unsigned char py_count;			//����ƴ����Ŀ,<=6(0-5)
	unsigned char py_index;			//��ѡƴ������
	//unsigned char py_hz;
	unsigned char *py_select;

	t9PY_index *py_mb[8];			//ƥ��ƴ��������е�λ��
	t9PY_index *mb_select;			//��ѡ�е�ƴ����Ӧ�����
	unsigned char mb_match_num;		//�������ַ�������ƥ���������,<=8(0-7);

	unsigned char show_buf[20];		//����ʾ���ֻ�����,0-17(9������)
	unsigned char hz_index;			//��ѡ��������
	unsigned char hz_select[4];				//ѡ�еĺ��ֻ�����

	unsigned char buf[34];			//������������
	unsigned char count;			//����������������
}t9_input_t;
*/


//	
//һ��������			   2   3   4    5    6    7    8    9  (�������������ִ�����2���ϵ�������)
short t9_search_index1[8]={1, 55, 87, 125, 181, 225, 304, 323};

//����������(�������������ִ�����2���ϵ�������)
short t9_search_index2[8][8]={
{2,		12,		17,		0,	43,		0,	49,		0,},//22,23,24,25,26,27,28,29
{56,	64,		69,		0,	75,		80,	81,		0,},//32,33,34,35,36,37,38,39
{87,	97,		0,		0,	105,	0,	109,	0,},//42,43,44,45,46,47,48,49
{125,	135,	141,	0,	159,	0,	163,	0,},//52,53,54,55,56,57,58,59
{182,	192,	200,	0,	215,	0,	218,	0,},//62,63,64,65,66,67,68,69
{225,	238,	247,	0,	283,	0,	289,	0,},//72,73,74,75,76,77,78,79
{304,	309,	311,	0,	316,	0,	318,	0,},//82,83,84,85,86,87,88,89
{323,	336,	344,	0,	377,	0,	383,	0,},//92,93,94,95,96,97,98,99
};


//#define CNTLQ      0x11
//#define CNTLS      0x13
//#define DEL        0x7F
#define BACKSPACE		0x08
#define CR				0x0D
#define LF				0x0A

#define OVER			124u // '|'

#define T9_PY_PREV		47u	// '/'
#define T9_PY_NEXT		42u	// '*'
#define T9_HZ_PREV		45u	// '-'
#define T9_HZ_NEXT		43u	// '+'

#define T9_PY_HZ		20u	// '.'



#define T9_PY_INPUT		35u // '#'

#define T9_CHN_MODE     0u
#define T9_UEN_MODE     1u
#define T9_LEN_MODE		2u
#define T9_NUM_MODE		3u

#define MAX_BUF_LEN		32

#define T9_NUM_0	48u         
#define T9_NUM_1	49u
#define T9_NUM_2	50u
#define T9_NUM_3	51u
#define T9_NUM_4	52u
#define T9_NUM_5	53u
#define T9_NUM_6	54u
#define T9_NUM_7	55u
#define T9_NUM_8	56u		
#define T9_NUM_9	57u

//��ĸ�����ֵĶ�Ӧ
#define T9_ALPHABET_abc     T9_NUM_2
#define T9_ALPHABET_def     T9_NUM_3
#define T9_ALPHABET_ghi     T9_NUM_4
#define T9_ALPHABET_jkl     T9_NUM_5
#define T9_ALPHABET_mno     T9_NUM_6
#define T9_ALPHABET_pqrs    T9_NUM_7
#define T9_ALPHABET_tuv     T9_NUM_8
#define T9_ALPHABET_wxyz    T9_NUM_9


//�ַ�ת����
char ascii_tab[8][4]={
	{'a','b','c',  },//2
	{'d','e','f',  },//3
	{'g','h','i',  },//4
	{'j','k','l',  },//5
	{'m','n','o',  },//6
	{'p','q','r','s'},//7
	{'t','u','v',  },//8
	{'w','x','y','z'},//9
};


static unsigned int my_strlen(char*str);
//static unsigned char char_to_num(char key);
static void input_switch(t9_input_t *p_t9_input);
static unsigned char t9_get_match_py_mb(t9_input_t *p_t9_input);

void t9_cn_show_handle(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_cn_show(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_cn_key_handle(t9_input_t *p_t9_input, unsigned char temp_char);

void t9_en_show(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_en_key_handle(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_input_init(t9_input_t *p_t9_input);
	

//0-396
//ƴ�����뷨�������б�
char PY_mb_space []={"0"};
char PY_mb_a     []={"@����"};
char PY_mb_ai    []={"@��������������������������"};
char PY_mb_an    []={"@������������������"};
char PY_mb_ang   []={"@������"};
char PY_mb_ao    []={"@���������°����ð�"};
char PY_mb_ba    []={"@�˰ѰͰְհ԰ΰǰɰӰṴ̋ưʰϰȰ�"};
char PY_mb_bai   []={"@�װٰڰܰݰ۰ذ�"};
char PY_mb_ban   []={"@�������������߰��"};
char PY_mb_bang  []={"@�������������������"};
char PY_mb_bao   []={"@������������������������������������"};
char PY_mb_bei   []={"@������������������������������"};
char PY_mb_ben   []={"@����������"};
char PY_mb_beng  []={"@�����±ñű�"};
char PY_mb_bi    []={"@�ƱǱȱ˱ʱɱұرϱձӱѱݱбֱԱͱױ̱αڱܱ�"};
char PY_mb_bian  []={"@�߱�ޱ���������"};
char PY_mb_biao  []={"@�����"};
char PY_mb_bie   []={"@�����"};
char PY_mb_bin   []={"@����������"};
char PY_mb_bing  []={"@������������������"};
char PY_mb_bo    []={"@����������������������������������������"};
char PY_mb_bu    []={"@��������������������"};
char PY_mb_ca    []={"@��"};
char PY_mb_cai   []={"@�²ŲĲƲòɲʲǲȲ˲�"};
char PY_mb_can   []={"@�βͲвϲѲҲ�"};
char PY_mb_cang  []={"@�ֲײԲղ�"};
char PY_mb_cao   []={"@�ٲڲܲ۲�"};
char PY_mb_ce    []={"@���޲��"};
char PY_mb_ceng  []={"@�����"};
char PY_mb_cha   []={"@������������ɲ"};
char PY_mb_chai  []={"@����"};
char PY_mb_chan  []={"@�������������������"};
char PY_mb_chang []={"@������������������������"};
char PY_mb_chao  []={"@��������������������"};
char PY_mb_che   []={"@������������"};
char PY_mb_chen  []={"@�������������³��ĳ�"};
char PY_mb_cheng []={"@�Ƴųɳʳгϳǳ˳ͳ̳γȳѳҳ�"};
char PY_mb_chi   []={"@�Գճڳس۳ٳֳ߳޳ݳܳ����"};
char PY_mb_chong []={"@������"};
char PY_mb_chou  []={"@�������������"};
char PY_mb_chu   []={"@����������������������������������"};
char PY_mb_chuai []={"@��"};
char PY_mb_chuan []={"@��������������"};
char PY_mb_chuang[]={"@����������"};
char PY_mb_chui  []={"@����������"};
char PY_mb_chun  []={"@��������������"};
char PY_mb_chuo  []={"@��"};
char PY_mb_ci    []={"@�ôʴĴɴȴǴŴƴ˴δ̴�"};
char PY_mb_cong  []={"@�ѴӴҴдϴ�"};
char PY_mb_cou   []={"@��"};
char PY_mb_cu    []={"@�ִٴ״�"};
char PY_mb_cuan  []={"@�ڴܴ�"};
char PY_mb_cui   []={"@�޴ߴݴ�����"};
char PY_mb_cun   []={"@����"};
char PY_mb_cuo   []={"@�������"};
char PY_mb_da    []={"@�������"};
char PY_mb_dai   []={"@������������������������"};
char PY_mb_dan   []={"@������������������������������"};
char PY_mb_dang  []={"@����������"};
char PY_mb_dao   []={"@������������������������"};
char PY_mb_de    []={"@�õµ�"};
char PY_mb_deng  []={"@�Ƶǵŵȵ˵ʵ�"};
char PY_mb_di    []={"@�͵̵εҵϵеӵѵյ׵ֵصܵ۵ݵڵ޵�"};
char PY_mb_dian  []={"@���ߵ�������������"};
char PY_mb_diao  []={"@�����������"};
char PY_mb_die   []={"@��������������"};
char PY_mb_ding  []={"@������������������"};
char PY_mb_diu   []={"@��"};
char PY_mb_dong  []={"@��������������������"};
char PY_mb_dou   []={"@����������������"};
char PY_mb_du    []={"@�����������¶ĶöʶŶǶȶɶ�"};
char PY_mb_duan  []={"@�˶̶ζ϶ж�"};
char PY_mb_dui   []={"@�ѶӶԶ�"};
char PY_mb_dun   []={"@�ֶضն׶ܶ۶ٶ�"};
char PY_mb_duo   []={"@��߶�޶��������"};
char PY_mb_e     []={"@����������������"};
char PY_mb_en    []={"@��"};
char PY_mb_er    []={"@����������������"};
char PY_mb_fa    []={"@����������������"};
char PY_mb_fan   []={"@����������������������������������"};
char PY_mb_fang  []={"@���������������·÷ķ�"};
char PY_mb_fei   []={"@�ɷǷȷƷʷ˷̷ͷϷзη�"};
char PY_mb_fen   []={"@�ַԷ׷ҷշӷطڷٷ۷ݷܷ޷߷�"};
char PY_mb_feng  []={"@����������������"};
char PY_mb_fo    []={"@��"};
char PY_mb_fou   []={"@��"};
char PY_mb_fu    []={"@������󸥷�����������������������������������������������������������������������������"};
char PY_mb_ga    []={"@�¸�"};
char PY_mb_gai   []={"@�øĸƸǸȸ�"};
char PY_mb_gan   []={"@�ɸʸ˸θ̸͸ѸϸҸи�"};
char PY_mb_gang  []={"@�Ըոڸٸظ׸ָ۸�"};
char PY_mb_gao   []={"@�޸�߸�ݸ�����"};
char PY_mb_ge    []={"@����������������������"};
char PY_mb_gei   []={"@��"};
char PY_mb_gen   []={"@����"};
char PY_mb_geng  []={"@��������������"};
char PY_mb_gong  []={"@������������������������������"};
char PY_mb_gou   []={"@������������������"};
char PY_mb_gu    []={"@�����ù¹��������ŹȹɹǹƹĹ̹ʹ˹�"};
char PY_mb_gua   []={"@�Ϲιйѹҹ�"};
char PY_mb_guai  []={"@�Թչ�"};
char PY_mb_guan  []={"@�ع۹ٹڹ׹ݹܹ�߹��"};
char PY_mb_guang []={"@����"};
char PY_mb_gui   []={"@������������������"};
char PY_mb_gun   []={"@������"};
char PY_mb_guo   []={"@������������"};
char PY_mb_ha    []={"@���"};
char PY_mb_hai   []={"@��������������"};
char PY_mb_han   []={"@��������������������������������������"};
char PY_mb_hang  []={"@������"};
char PY_mb_hao   []={"@���������úºźƺ�"};
char PY_mb_he    []={"@�ǺȺ̺ϺκͺӺҺ˺ɺԺкʺغֺպ�"};
char PY_mb_hei   []={"@�ں�"};
char PY_mb_hen   []={"@�ۺܺݺ�"};
char PY_mb_heng  []={"@��ߺ���"};
char PY_mb_hong  []={"@����������"};
char PY_mb_hou   []={"@��������"};
char PY_mb_hu    []={"@������������������������������������"};
char PY_mb_hua   []={"@������������������"};
char PY_mb_huai  []={"@����������"};
char PY_mb_huan  []={"@�����������û»�������������"};
char PY_mb_huang []={"@�ĻŻʻ˻ƻ̻ͻȻǻɻлλѻ�"};
char PY_mb_hui   []={"@�һֻӻԻջػ׻ڻܻ������߻޻�ݻٻ�"};
char PY_mb_hun   []={"@�������"};
char PY_mb_huo   []={"@�������������"};
char PY_mb_ji    []={"@���������������������������������������������������������������������ƼǼ��ͼ˼ɼ��ʼ����ȼü̼żļ¼�������"};
char PY_mb_jia   []={"@�ӼмѼϼҼμԼռ׼ּؼۼݼܼټ޼�Ю"};
char PY_mb_jian  []={"@����߼����������������������������������������������������"};
char PY_mb_jiang []={"@��������������������������"};
char PY_mb_jiao  []={"@���������������������ǽƽʽȽýŽ½��˽ɽнνϽ̽ѽ;���"};
char PY_mb_jie   []={"@�׽Խӽսҽֽڽٽܽ��ݽ޽ؽ߽����������"};
char PY_mb_jin   []={"@���������������������������������"};
char PY_mb_jing  []={"@��������������������������������������������������"};
char PY_mb_jiong []={"@����"};
char PY_mb_jiu   []={"@�������žþľ��¾ƾɾʾ̾ξǾȾ;�"};
char PY_mb_ju    []={"@�ӾоѾԾҾϾֽ۾վ׾ھپؾ�޾ܾ߾����ݾ��۾�"};
char PY_mb_juan  []={"@��������"};
char PY_mb_jue   []={"@��������������"};
char PY_mb_jun   []={"@����������������������"};
char PY_mb_ka    []={"@������"};
char PY_mb_kai   []={"@����������"};
char PY_mb_kan   []={"@��������������"};
char PY_mb_kang  []={"@��������������"};
char PY_mb_kao   []={"@��������"};
char PY_mb_ke    []={"@�����¿ƿÿſĿǿȿɿʿ˿̿Ϳ�"};
char PY_mb_ken   []={"@�Ͽѿҿ�"};
char PY_mb_keng  []={"@�Կ�"};
char PY_mb_kong  []={"@�տ׿ֿ�"};
char PY_mb_kou   []={"@�ٿڿۿ�"};
char PY_mb_ku    []={"@�ݿ޿߿����"};
char PY_mb_kua   []={"@������"};
char PY_mb_kuai  []={"@�����"};
char PY_mb_kuan  []={"@���"};
char PY_mb_kuang []={"@�����������"};
char PY_mb_kui   []={"@����������������������"};
char PY_mb_kun   []={"@��������"};
char PY_mb_kuo   []={"@��������"};
char PY_mb_la    []={"@��������������"};
char PY_mb_lai   []={"@������"};
char PY_mb_lan   []={"@������������������������������"};
char PY_mb_lang  []={"@��������������"};
char PY_mb_lao   []={"@������������������"};
char PY_mb_le    []={"@������"};
char PY_mb_lei   []={"@����������������������"};
char PY_mb_leng  []={"@������"};
char PY_mb_li    []={"@��������������������������������������������������������������������"};
char PY_mb_lian  []={"@����������������������������"};
char PY_mb_liang []={"@������������������������"};
char PY_mb_liao  []={"@������������������������"};
char PY_mb_lie   []={"@����������"};
char PY_mb_lin   []={"@������������������������"};
char PY_mb_ling  []={"@����������������������������"};
char PY_mb_liu   []={"@����������������������"};
char PY_mb_long  []={"@��������¡��¤¢£"};
char PY_mb_lou   []={"@¦¥§¨ª©"};
char PY_mb_lu    []={"@¶¬®«¯­±²°³½¼¸¹»µ·¾º´"};
char PY_mb_luan  []={"@������������"};
char PY_mb_lue   []={"@����"};
char PY_mb_lun   []={"@��������������"};
char PY_mb_luo   []={"@������������������������"};
char PY_mb_lv    []={"@��¿������������������������"};
char PY_mb_ma    []={"@������������������"};
char PY_mb_mai   []={"@������������"};
char PY_mb_man   []={"@����������á������"};
char PY_mb_mang  []={"@æâäãçå"};
char PY_mb_mao   []={"@èëìéêîíïðóñò"};
char PY_mb_me    []={"@ô"};
char PY_mb_mei   []={"@ûöõü÷ýúøùÿ��þ��������"};
char PY_mb_men   []={"@������"};
char PY_mb_meng  []={"@����������������"};
char PY_mb_mi    []={"@����������������������������"};
char PY_mb_mian  []={"@������������������"};
char PY_mb_miao  []={"@����������������"};
char PY_mb_mie   []={"@����"};
char PY_mb_min   []={"@������������"};
char PY_mb_ming  []={"@������������"};
char PY_mb_miu   []={"@��"};
char PY_mb_mo    []={"@����ġģĤĦĥĢħĨĩĭİĪįĮīĬ"};
char PY_mb_mou   []={"@Ĳıĳ"};
char PY_mb_mu    []={"@ĸĶĵķĴľĿ��ļĹĻ��Ľĺ��"};
char PY_mb_na    []={"@��������������"};
char PY_mb_nai   []={"@����������"};
char PY_mb_nan   []={"@�������"};
char PY_mb_nang  []={"@��"};
char PY_mb_nao   []={"@����������"};
char PY_mb_ne    []={"@��"};
char PY_mb_nei   []={"@����"};
char PY_mb_nen   []={"@��"};
char PY_mb_neng  []={"@��"};
char PY_mb_ni    []={"@����������������������"};
char PY_mb_nian  []={"@��������������"};
char PY_mb_niang []={"@����"};
char PY_mb_niao  []={"@����"};
char PY_mb_nie   []={"@��������������"};
char PY_mb_nin   []={"@��"};
char PY_mb_ning  []={"@��š������Ţ"};
char PY_mb_niu   []={"@ţŤŦť"};
char PY_mb_nong  []={"@ũŨŧŪ"};
char PY_mb_nu    []={"@ūŬŭ"};
char PY_mb_nuan  []={"@ů"};
char PY_mb_nue   []={"@űŰ"};
char PY_mb_nuo   []={"@ŲŵųŴ"};
char PY_mb_nv    []={"@Ů"};
char PY_mb_o     []={"@Ŷ"};
char PY_mb_ou    []={"@ŷŹŸŻżźŽ"};
char PY_mb_pa    []={"@ſž����������"};
char PY_mb_pai   []={"@������������"};
char PY_mb_pan   []={"@����������������"};
char PY_mb_pang  []={"@����������"};
char PY_mb_pao   []={"@��������������"};
char PY_mb_pei   []={"@������������������"};
char PY_mb_pen   []={"@����"};
char PY_mb_peng  []={"@����������������������������"};
char PY_mb_pi    []={"@��������������Ƥ��ƣơ��ƢƥƦƨƧƩ"};
char PY_mb_pian  []={"@Ƭƫƪƭ"};
char PY_mb_piao  []={"@ƯƮưƱ"};
char PY_mb_pie   []={"@ƲƳ"};
char PY_mb_pin   []={"@ƴƶƵƷƸ"};
char PY_mb_ping  []={"@ƽ��ƾ��ƿƺƻƼƹ"};
char PY_mb_po    []={"@����������������"};
char PY_mb_pou   []={"@��"};
char PY_mb_pu    []={"@������������������������������"};
char PY_mb_qi    []={"@������������������������������������������������������������������������"};
char PY_mb_qia   []={"@��ǡǢ"};
char PY_mb_qian  []={"@ǧǪǤǨǥǣǦǫǩǰǮǯǬǱǭǳǲǴǷǵǶǸ"};
char PY_mb_qiang []={"@ǺǼǹǻǿǽǾ��"};
char PY_mb_qiao  []={"@������������������������������"};
char PY_mb_qie   []={"@����������"};
char PY_mb_qin   []={"@����������������������"};
char PY_mb_qing  []={"@��������������������������"};
char PY_mb_qiong []={"@����"};
char PY_mb_qiu   []={"@����������������"};
char PY_mb_qu    []={"@����������������ȡȢȣȥȤ"};
char PY_mb_quan  []={"@ȦȫȨȪȭȬȩȧȮȰȯ"};
char PY_mb_que   []={"@Ȳȱȳȴȸȷȵȶ"};
char PY_mb_qun   []={"@ȹȺ"};
char PY_mb_ran   []={"@ȻȼȽȾ"};
char PY_mb_rang  []={"@ȿ��������"};
char PY_mb_rao   []={"@������"};
char PY_mb_re    []={"@����"};
char PY_mb_ren   []={"@��������������������"};
char PY_mb_reng  []={"@����"};
char PY_mb_ri    []={"@��"};
char PY_mb_rong  []={"@��������������������"};
char PY_mb_rou   []={"@������"};
char PY_mb_ru    []={"@��������������������"};
char PY_mb_ruan  []={"@����"};
char PY_mb_rui   []={"@������"};
char PY_mb_run   []={"@����"};
char PY_mb_ruo   []={"@����"};
char PY_mb_sa    []={"@������"};
char PY_mb_sai   []={"@��������"};
char PY_mb_san   []={"@��ɡɢ��"};
char PY_mb_sang  []={"@ɣɤɥ"};
char PY_mb_sao   []={"@ɦɧɨɩ"};
char PY_mb_se    []={"@ɫɬɪ"};
char PY_mb_sen   []={"@ɭ"};
char PY_mb_seng  []={"@ɮ"};
char PY_mb_sha   []={"@ɱɳɴɰɯɵɶɷ��"};
char PY_mb_shai  []={"@ɸɹ"};
char PY_mb_shan  []={"@ɽɾɼ��ɺɿ������ɻ������������դ"};
char PY_mb_shang []={"@����������������"};
char PY_mb_shao  []={"@����������������������"};
char PY_mb_she   []={"@������������������������"};
char PY_mb_shen  []={"@��������������������������������ʲ"};
char PY_mb_sheng []={"@��������ʤ����ʡʥʢʣ"};
char PY_mb_shi   []={"@��ʮʯʱʿʶ��ʳʾʽʹʼ����ʵ����ʷ��ʩ��ʻʪ�Ƴ�ʬʧ����ʦʭʫʨʰʴʸʺ����������������������"};
char PY_mb_shou  []={"@��������������������"};
char PY_mb_shu   []={"@������������������������������������������������������ˡ����������"};
char PY_mb_shua  []={"@ˢˣ"};
char PY_mb_shuai []={"@˥ˤ˦˧"};
char PY_mb_shuan []={"@˩˨"};
char PY_mb_shuang[]={"@˫˪ˬ"};
char PY_mb_shui  []={"@˭ˮ˰˯"};
char PY_mb_shun  []={"@˱˳˴˲"};
char PY_mb_shuo  []={"@˵˸˷˶"};
char PY_mb_si    []={"@��˿˾˽˼˹��˺��˻����������"};
char PY_mb_song  []={"@����������������"};
char PY_mb_sou   []={"@��������"};
char PY_mb_su    []={"@����������������������"};
char PY_mb_suan  []={"@������"};
char PY_mb_sui   []={"@����������������������"};
char PY_mb_sun   []={"@������"};
char PY_mb_suo   []={"@����������������"};
char PY_mb_ta    []={"@����������̡̢̤̣"};
char PY_mb_tai   []={"@̨̧̥̦̫̭̬̩̪"};
char PY_mb_tan   []={"@̸̵̷̶̴̮̰̯̲̱̳̹̻̺̼̾̿̽"};
char PY_mb_tang  []={"@��������������������������"};
char PY_mb_tao   []={"@����������������������"};
char PY_mb_te    []={"@��"};
char PY_mb_teng  []={"@��������"};
char PY_mb_ti    []={"@������������������������������"};
char PY_mb_tian  []={"@����������������"};
char PY_mb_tiao  []={"@������������"};
char PY_mb_tie   []={"@������"};
char PY_mb_ting  []={"@ͣ��͡����ͤͥͦͧ͢"};
char PY_mb_tong  []={"@ͨͬͮͩͭͯͪͫͳͱͰͲʹ"};
char PY_mb_tou   []={"@͵ͷͶ͸"};
char PY_mb_tu    []={"@͹ͺͻͼͽͿ;��������"};
char PY_mb_tuan  []={"@����"};
char PY_mb_tui   []={"@������������"};
char PY_mb_tun   []={"@��������"};
char PY_mb_tuo   []={"@����������������������"};
char PY_mb_wa    []={"@��������������"};
char PY_mb_wai   []={"@����"};
char PY_mb_wan   []={"@����������������������������������"};
char PY_mb_wang  []={"@��������������������"};
char PY_mb_wei   []={"@Σ��΢ΡΪΤΧΥΦΨΩάΫΰαβγέίή��δλζηθξνιμεοκ"};
char PY_mb_wen   []={"@��������������������"};
char PY_mb_weng  []={"@������"};
char PY_mb_wo    []={"@������������������"};
char PY_mb_wu    []={"@����������������������������������������������������������"};
char PY_mb_xi    []={"@Ϧϫ����ϣ������Ϣ��Ϥϧϩ����ϬϡϪ��Ϩ����ϥϰϯϮϱϭϴϲϷϵϸ϶"};
char PY_mb_xia   []={"@ϺϹϻ��Ͽ��ϾϽϼ������"};
char PY_mb_xian  []={"@ϳ����������������������������������������������������"};
char PY_mb_xiang []={"@����������������������������������������"};
char PY_mb_xiao  []={"@����������������С��ТФ��ЧУЦХ"};
char PY_mb_xie   []={"@ЩШЪЫЭавбгЯЬдйкжмелиз"};
char PY_mb_xin   []={"@����о����п��н����"};
char PY_mb_xing  []={"@����������������������������"};
char PY_mb_xiong []={"@��������������"};
char PY_mb_xiu   []={"@��������������������"};
char PY_mb_xu    []={"@��������������������������������������"};
char PY_mb_xuan  []={"@������������ѡѢѤѣ"};
char PY_mb_xue   []={"@ѧѩѪ��ѥѦѨ"};
char PY_mb_xun   []={"@ѰѮѸѯѶѫѬѲѱѭѵѴѷѳ"};
char PY_mb_ya    []={"@ѽѹ������ѾѺѻѼѿ������������"};
char PY_mb_yan   []={"@������������������������������������������������������������������"};
char PY_mb_yang  []={"@����������������������������������"};
char PY_mb_yao   []={"@��������ҢҦҤҥҡң��ҧҨҩҪҫԿ"};
char PY_mb_ye    []={"@ҬҭүҮҲұҰҵҶҷҳҹҴҺҸ"};
char PY_mb_yi    []={"@һ����ҽ��ҿҼҾ������������������������������������������������������������������������������������������"};
char PY_mb_yin   []={"@������������������������������ӡ"};
char PY_mb_ying  []={"@ӦӢӤӧӣӥӭӯӫӨөӪӬӮӱӰӳӲ"};
char PY_mb_yo    []={"@Ӵ"};
char PY_mb_yong  []={"@ӶӵӸӹӺӷ��ӽӾ��ӿ��Ӽӻ��"};
char PY_mb_you   []={"@����������������������������������������"};
char PY_mb_yu    []={"@����������������������������������������������������Ԧ����������ԡԤ������Ԣ��ԣ������ԥ"};
char PY_mb_yuan  []={"@ԩԧԨԪԱ԰ԫԭԲԬԮԵԴԳԯԶԷԹԺԸ"};
char PY_mb_yue   []={"@ԻԼ��������Ծ��Խ"};
char PY_mb_yun   []={"@������������������������"};
char PY_mb_za    []={"@������զ"};
char PY_mb_zai   []={"@����������������"};
char PY_mb_zan   []={"@��������"};
char PY_mb_zang  []={"@������"};
char PY_mb_zao   []={"@����������������������������"};
char PY_mb_ze    []={"@��������"};
char PY_mb_zei   []={"@��"};
char PY_mb_zen   []={"@��"};
char PY_mb_zeng  []={"@������"};
char PY_mb_zha   []={"@����������բագէթըե��"};
char PY_mb_zhai  []={"@իժլ��խծկ"};
char PY_mb_zhan  []={"@մձճղհնչյոշռսջվ��տպ"};
char PY_mb_zhang []={"@��������������������������������"};
char PY_mb_zhao  []={"@��������������������צ"};
char PY_mb_zhe   []={"@����������������������"};
char PY_mb_zhen  []={"@��������������������������������֡"};
char PY_mb_zheng []={"@��������������������֤֣��֢"};
char PY_mb_zhi   []={"@ְֱֲֳִֵֶַָֹֺֻּֽ֧֥֦֪֭֮֨֯֫֬֩��־������������ֿ������������������"};
char PY_mb_zhong []={"@����������������������"};
char PY_mb_zhou  []={"@����������������������������"};
char PY_mb_zhu   []={"@��סעף������������������������������������פ������"};
char PY_mb_zhua  []={"@ץ"};
char PY_mb_zhuai []={"@ק"};
char PY_mb_zhuan []={"@רשת׫׭"};
char PY_mb_zhuang[]={"@ױׯ׮װ׳״��ײ"};
char PY_mb_zhui  []={"@׷׹׵׶׺׸"};
char PY_mb_zhun  []={"@׼׻"};
char PY_mb_zhuo  []={"@׿׾׽��������������"};
char PY_mb_zi    []={"@����������������������������"};
char PY_mb_zong  []={"@��������������"};
char PY_mb_zou   []={"@��������"};
char PY_mb_zu    []={"@����������������"};
char PY_mb_zuan  []={"@׬����"};
char PY_mb_zui   []={"@��������"};
char PY_mb_zun   []={"@����"};
char PY_mb_zuo   []={"@��������������"};

//0-396,397
//ƴ�����뷨��ѯ���,T9������ĸ������(index),
//��������
t9PY_index t9PY_index2[] ={
{""		,	"0"	    ,	PY_mb_space},
{"2"		,	"a"	    ,	PY_mb_a},
{"22"	,	"ba"	,	PY_mb_ba},
{"22"	,	"ca"	,	PY_mb_ca},
{"224"	,	"bai"	,	PY_mb_bai},
{"224"	,	"cai"	,	PY_mb_cai},
{"226"	,	"ban"	,	PY_mb_ban},
{"226"	,	"bao"	,	PY_mb_bao},
{"226"	,	"can"	,	PY_mb_can},
{"226"	,	"cao"	,	PY_mb_cao},
{"2264"	,	"bang"	,	PY_mb_bang},
{"2264"	,	"cang"	,	PY_mb_cang},
{"23"	,	"ce"	,	PY_mb_ce},
{"234"	,	"bei"	,	PY_mb_bei},
{"236"	,	"ben"	,	PY_mb_ben},
{"2364"	,	"beng"	,	PY_mb_beng},
{"2364"	,	"ceng"	,	PY_mb_ceng},
{"24"	,	"ai"	,	PY_mb_ai},
{"24"	,	"bi"	,	PY_mb_bi},
{"24"	,	"ci"	,	PY_mb_ci},
{"242"	,	"cha"	,	PY_mb_cha},
{"2424"	,	"chai"	,	PY_mb_chai},
{"2426"	,	"bian"	,	PY_mb_bian},
{"2426"	,	"biao"	,	PY_mb_biao},
{"2426"	,	"chan"	,	PY_mb_chan},
{"2426"	,	"chao"	,	PY_mb_chao},
{"24264"	,	"chang"	,	PY_mb_chang},
{"243"	,	"bie"	,	PY_mb_bie},
{"243"	,	"che"	,	PY_mb_che},
{"2436"	,	"chen"	,	PY_mb_chen},
{"24364"	,	"cheng"	,	PY_mb_cheng},
{"244"	,	"chi"	,	PY_mb_chi},
{"246"	,	"bin"	,	PY_mb_bin},
{"2464"	,	"bing"	,	PY_mb_bing},
{"24664"	,	"chong"	,	PY_mb_chong},
{"2468"	,	"chou"	,	PY_mb_chou},
{"248"	,	"chu"	,	PY_mb_chu},
{"24826"	,	"chuan"	,	PY_mb_chuan},
{"248264"	,	"chuang",	PY_mb_chuang},
{"2484"	,	"chuai"	,	PY_mb_chuai},
{"2484"	,	"chui"	,	PY_mb_chui},
{"2484"	,	"chun"	,	PY_mb_chun},
{"2486"	,	"chuo"	,	PY_mb_chuo},
{"26"	,	"an"	,	PY_mb_an},
{"26"	,	"ao"	,	PY_mb_ao},
{"26"	,	"bo"	,	PY_mb_bo},
{"264"	,	"ang"	,	PY_mb_ang},
{"2664"	,	"cong"	,	PY_mb_cong},
{"268"	,	"cou"	,	PY_mb_cou},
{"28"	,	"bu"	,	PY_mb_bu},
{"28"	,	"cu"	,	PY_mb_cu},
{"2826"	,	"cuan"	,	PY_mb_cuan},
{"284"	,	"cui"	,	PY_mb_cui},
{"286"	,	"cun"	,	PY_mb_cun},
{"286"	,	"cuo"	,	PY_mb_cuo},
{"3"	,	"e"	    ,	PY_mb_e},
{"32"	,	"da"	,	PY_mb_da},
{"32"	,	"fa"	,	PY_mb_fa},
{"324"	,	"dai"	,	PY_mb_dai},
{"326"	,	"dan"	,	PY_mb_dan},
{"326"	,	"dao"	,	PY_mb_dao},
{"326"	,	"fan"	,	PY_mb_fan},
{"3264"	,	"dang"	,	PY_mb_dang},
{"3264"	,	"fang"	,	PY_mb_fang},
{"33"	,	"de"	,	PY_mb_de},
{"334"	,	"fei"	,	PY_mb_fei},
{"336"	,	"fen"	,	PY_mb_fen},
{"3364"	,	"deng"	,	PY_mb_deng},
{"3364"	,	"feng"	,	PY_mb_feng},
{"34"	,	"di"	,	PY_mb_di},
{"3426"	,	"dian"	,	PY_mb_dian},
{"3426"	,	"diao"	,	PY_mb_diao},
{"343"	,	"die"	,	PY_mb_die},
{"3464"	,	"ding"	,	PY_mb_ding},
{"348"	,	"diu"	,	PY_mb_diu},
{"36"	,	"en"	,	PY_mb_en},
{"36"	,	"fo"	,	PY_mb_fo},
{"3664"	,	"dong"	,	PY_mb_dong},
{"368"	,	"dou"	,	PY_mb_dou},
{"368"	,	"fou"	,	PY_mb_fou},
{"37"	,	"er"	,	PY_mb_er},
{"38"	,	"du"	,	PY_mb_du},
{"38"	,	"fu"	,	PY_mb_fu},
{"3826"	,	"duan"	,	PY_mb_duan},
{"384"	,	"dui"	,	PY_mb_dui},
{"386"	,	"dun"	,	PY_mb_dun},
{"386"	,	"duo"	,	PY_mb_duo},
//{"4"	,	"i"	,	PY_mb_space},
{"42"	,	"ha"	,	PY_mb_ha},
{"42"	,	"ga"	,	PY_mb_ga},
{"423"	,	"hai"	,	PY_mb_hai},
{"424"	,	"gai"	,	PY_mb_gai},
{"426"	,	"gan"	,	PY_mb_gan},
{"426"	,	"gao"	,	PY_mb_gao},
{"426"	,	"han"	,	PY_mb_han},
{"426"	,	"hao"	,	PY_mb_hao},
{"4264"	,	"gang"	,	PY_mb_gang},
{"4264"	,	"hang"	,	PY_mb_hang},
{"43"	,	"ge"	,	PY_mb_ge},
{"43"	,	"he"	,	PY_mb_he},
{"434"	,	"gei"	,	PY_mb_gei},
{"434"	,	"hei"	,	PY_mb_hei},
{"436"	,	"gen"	,	PY_mb_gan},
{"436"	,	"hen"	,	PY_mb_hen},
{"4364"	,	"geng"	,	PY_mb_geng},
{"4364"	,	"heng"	,	PY_mb_heng},
{"4664"	,	"gong"	,	PY_mb_gong},
{"4664"	,	"hong"	,	PY_mb_hong},
{"468"	,	"gou"	,	PY_mb_gou},
{"468"	,	"hou"	,	PY_mb_hou},
{"48"	,	"gu"	,	PY_mb_gu},
{"48"	,	"hu"	,	PY_mb_hu},
{"482"	,	"gua"	,	PY_mb_gua},
{"482"	,	"hua"	,	PY_mb_hua},
{"4823"	,	"huai"	,	PY_mb_huai},
{"4824"	,	"guai"	,	PY_mb_guai},
{"4826"	,	"guan"	,	PY_mb_guan},
{"4826"	,	"huan"	,	PY_mb_huan},
{"48264"	,	"guang"	,	PY_mb_guang},
{"48264"	,	"huang"	,	PY_mb_huang},
{"484"	,	"gui"	,	PY_mb_gui},
{"484"	,	"hui"	,	PY_mb_hui},
{"486"	,	"gun"	,	PY_mb_gun},
{"486"	,	"guo"	,	PY_mb_guo},
{"486"	,	"hun"	,	PY_mb_hun},
{"486"	,	"huo"	,	PY_mb_huo},
{"52"	,	"ka"	,	PY_mb_ka},
{"52"	,	"la"	,	PY_mb_la},
{"524"	,	"kai"	,	PY_mb_kai},
{"524"	,	"lai"	,	PY_mb_lai},
{"526"	,	"kan"	,	PY_mb_kan},
{"526"	,	"kao"	,	PY_mb_kao},
{"526"	,	"lan"	,	PY_mb_lan},
{"526"	,	"lao"	,	PY_mb_lao},
{"5264"	,	"kang"	,	PY_mb_kang},
{"5264"	,	"lang"	,	PY_mb_lang},
{"53"	,	"ke"	,	PY_mb_ke},
{"53"	,	"le"	,	PY_mb_le},
{"534"	,	"lei"	,	PY_mb_lei},
{"536"	,	"ken"	,	PY_mb_ken},
{"5364"	,	"keng"	,	PY_mb_keng},
{"5366"	,	"leng"	,	PY_mb_leng},
{"54"	,	"ji"	,	PY_mb_ji},
{"54"	,	"li"	,	PY_mb_li},
{"542"	,	"jia"	,	PY_mb_jia},
{"5426"	,	"jian"	,	PY_mb_jian},
{"5426"	,	"jiao"	,	PY_mb_jiao},
{"5426"	,	"lian"	,	PY_mb_lian},
{"5426"	,	"liao"	,	PY_mb_liao},
{"54264"	,	"jiang"	,	PY_mb_jiang},
{"54264"	,	"liang"	,	PY_mb_liang},
{"543"	,	"jie"	,	PY_mb_jie},
{"543"	,	"lie"	,	PY_mb_lie},
{"546"	,	"jin"	,	PY_mb_jin},
{"546"	,	"lin"	,	PY_mb_lin},
{"5464"	,	"jing"	,	PY_mb_jing},
{"5464"	,	"ling"	,	PY_mb_ling},
{"54664"	,	"jiong"	,	PY_mb_jiong},
{"548"	,	"jiu"	,	PY_mb_jiu},
{"548"	,	"liu"	,	PY_mb_liu},
{"5664"	,	"kong"	,	PY_mb_kong},
{"5664"	,	"long"	,	PY_mb_long},
{"568"	,	"kou"	,	PY_mb_kou},
{"568"	,	"lou"	,	PY_mb_lou},
{"58"	,	"ju"	,	PY_mb_ju},
{"58"	,	"ku"	,	PY_mb_ku},
{"58"	,	"lu"	,	PY_mb_lu},
{"58"	,	"lv"	,	PY_mb_lv},
{"582"	,	"kua"	,	PY_mb_kua},
{"5824"	,	"kuai"	,	PY_mb_kuai},
{"5826"	,	"juan"	,	PY_mb_juan},
{"5826"	,	"kuan"	,	PY_mb_kuan},
{"5826"	,	"luan"	,	PY_mb_luan},
{"58264"	,	"kuang"	,	PY_mb_kuang},
{"583"	,	"jue"	,	PY_mb_jue},
{"583"	,	"lue"	,	PY_mb_lue},
{"584"	,	"kui"	,	PY_mb_kui},
{"586"	,	"jun"	,	PY_mb_jun},
{"586"	,	"kun"	,	PY_mb_kun},
{"586"	,	"kuo"	,	PY_mb_kuo},
{"586"	,	"lun"	,	PY_mb_lun},
{"586"	,	"luo"	,	PY_mb_luo},
{"6"	,	"o"	    ,	PY_mb_o},
{"62"	,	"ma"	,	PY_mb_ma},
{"62"	,	"na"	,	PY_mb_na},
{"624"	,	"mai"	,	PY_mb_mai},
{"624"	,	"nai"	,	PY_mb_nai},
{"626"	,	"man"	,	PY_mb_man},
{"626"	,	"mao"	,	PY_mb_mao},
{"626"	,	"nan"	,	PY_mb_nan},
{"626"	,	"nao"	,	PY_mb_nao},
{"6264"	,	"mang"	,	PY_mb_mang},
{"6264"	,	"nang"	,	PY_mb_nang},
{"63"	,	"me"	,	PY_mb_me},
{"63"	,	"ne"	,	PY_mb_ne},
{"634"	,	"mei"	,	PY_mb_mei},
{"634"	,	"nei"	,	PY_mb_nei},
{"636"	,	"men"	,	PY_mb_men},
{"636"	,	"nen"	,	PY_mb_nen},
{"6364"	,	"meng"	,	PY_mb_meng},
{"6364"	,	"neng"	,	PY_mb_neng},
{"64"	,	"mi"	,	PY_mb_mi},
{"64"	,	"ni"	,	PY_mb_ni},
{"6426"	,	"mian"	,	PY_mb_mian},
{"6426"	,	"miao"	,	PY_mb_miao},
{"6426"	,	"nian"	,	PY_mb_nian},
{"6426"	,	"niao"	,	PY_mb_niao},
{"64264"	,	"niang"	,	PY_mb_niang},
{"643"	,	"mie"	,	PY_mb_mie},
{"643"	,	"nie"	,	PY_mb_nie},
{"646"	,	"min"	,	PY_mb_min},
{"646"	,	"nin"	,	PY_mb_nin},
{"6464"	,	"ming"	,	PY_mb_ming},
{"6464"	,	"ning"	,	PY_mb_ning},
{"648"	,	"miu"	,	PY_mb_miu},
{"648"	,	"niu"	,	PY_mb_niu},
{"66"	,	"mo"	,	PY_mb_mo},
{"6664"	,	"nong"	,	PY_mb_nong},
{"668"	,	"mou"	,	PY_mb_mou},
{"68"	,	"mu"	,	PY_mb_mu},
{"68"	,	"nu"	,	PY_mb_nu},
{"68"	,	"nv"	,	PY_mb_nv},
{"68"	,	"ou"	,	PY_mb_ou},
{"6826"	,	"nuan"	,	PY_mb_nuan},
{"683"	,	"nue"	,	PY_mb_nue},
{"686"	,	"nuo"	,	PY_mb_nuo},
{"72"	,	"pa"	,	PY_mb_pa},
{"72"	,	"sa"	,	PY_mb_sa},
{"724"	,	"pai"	,	PY_mb_pai},
{"724"	,	"sai"	,	PY_mb_sai},
{"726"	,	"pan"	,	PY_mb_pan},
{"726"	,	"pao"	,	PY_mb_pao},
{"726"	,	"ran"	,	PY_mb_ran},
{"726"	,	"rao"	,	PY_mb_rao},
{"726"	,	"sao"	,	PY_mb_sao},
{"726"	,	"san"	,	PY_mb_san},
{"7264"	,	"pang"	,	PY_mb_pang},
{"7264"	,	"rang"	,	PY_mb_rang},
{"7264"	,	"sang"	,	PY_mb_sang},
{"73"	,	"re"	,	PY_mb_re},
{"73"	,	"se"	,	PY_mb_se},
{"734"	,	"pei"	,	PY_mb_pei},
{"736"	,	"pen"	,	PY_mb_pen},
{"736"	,	"ren"	,	PY_mb_ren},
{"736"	,	"sen"	,	PY_mb_sen},
{"7364"	,	"peng"	,	PY_mb_peng},
{"7364"	,	"reng"	,	PY_mb_reng},
{"7364"	,	"seng"	,	PY_mb_seng},
{"74"	,	"pi"	,	PY_mb_pi},
{"74"	,	"qi"	,	PY_mb_qi},
{"74"	,	"ri"	,	PY_mb_ri},
{"74"	,	"si"	,	PY_mb_si},
{"742"	,	"qia"	,	PY_mb_qia},
{"742"	,	"sha"	,	PY_mb_sha},
{"7424"	,	"shai"	,	PY_mb_shai},
{"7426"	,	"pian"	,	PY_mb_pian},
{"7426"	,	"piao"	,	PY_mb_piao},
{"7426"	,	"qian"	,	PY_mb_qian},
{"7426"	,	"qiao"	,	PY_mb_qiao},
{"7426"	,	"shan"	,	PY_mb_shan},
{"7426"	,	"shao"	,	PY_mb_shao},
{"74264"	,	"qiang"	,	PY_mb_qiang},
{"74264"	,	"shang ",	PY_mb_shang},
{"743"	,	"pie"	,	PY_mb_pie},
{"743"	,	"qie"	,	PY_mb_qie},
{"743"	,	"she"	,	PY_mb_she},
{"7436"	,	"shen"	,	PY_mb_shen},
{"74364"	,	"sheng"	,	PY_mb_sheng},
{"744"	,	"shi"	,	PY_mb_shi},
{"746"	,	"pin"	,	PY_mb_pin},
{"746"	,	"qin"	,	PY_mb_qin},
{"7464"	,	"ping"	,	PY_mb_ping},
{"7464"	,	"qing"	,	PY_mb_qing},
{"74664"	,	"qiong"	,	PY_mb_qiong},
{"7468"	,	"shou"	,	PY_mb_shou},
{"748"	,	"qiu"	,	PY_mb_qiu},
{"748"	,	"shu"	,	PY_mb_shu},
{"7482"	,	"shua"	,	PY_mb_shua},
{"74824"	,	"shuai"	,	PY_mb_shuai},
{"74826"	,	"shuan"	,	PY_mb_shuan},
{"748264"	,	"shuang",	PY_mb_shuang},
{"7484"	,	"shui"	,	PY_mb_shui},
{"7486"	,	"shun"	,	PY_mb_shun},
{"7486"	,	"shuo"	,	PY_mb_shuo},
{"76"	,	"po"	,	PY_mb_po},
{"7664"	,	"rong"	,	PY_mb_rong},
{"7664"	,	"song"	,	PY_mb_song},
{"768"	,	"pou"	,	PY_mb_pou},
{"768"	,	"rou"	,	PY_mb_rou},
{"768"	,	"sou"	,	PY_mb_sou},
{"78"	,	"pu"	,	PY_mb_pu},
{"78"	,	"qu"	,	PY_mb_qu},
{"78"	,	"ru"	,	PY_mb_ru},
{"78"	,	"su"	,	PY_mb_su},
{"7826"	,	"quan"	,	PY_mb_quan},
{"7826"	,	"ruan"	,	PY_mb_ruan},
{"7826"	,	"suan"	,	PY_mb_suan},
{"783"	,	"que"	,	PY_mb_que},
{"784"	,	"rui"	,	PY_mb_rui},
{"784"	,	"sui"	,	PY_mb_sui},
{"786"	,	"qun"	,	PY_mb_qun},
{"786"	,	"run"	,	PY_mb_run},
{"786"	,	"ruo"	,	PY_mb_ruo},
{"786"	,	"sun"	,	PY_mb_sun},
{"786"	,	"suo"	,	PY_mb_suo},
//{"8"	,	"u"	,	PY_mb_space},
//{"8"	,	"v"	,	PY_mb_space},
{"82"	,	"ta"	,	PY_mb_ta},
{"824"	,	"tai"	,	PY_mb_tai},
{"826"	,	"tan"	,	PY_mb_tan},
{"826"	,	"tao"	,	PY_mb_tao},
{"8264"	,	"tang"	,	PY_mb_tang},
{"83"	,	"te"	,	PY_mb_te},
{"8364"	,	"teng"	,	PY_mb_teng},
{"84"	,	"ti"	,	PY_mb_ti},
{"8426"	,	"tian"	,	PY_mb_tian},
{"8426"	,	"tiao"	,	PY_mb_tiao},
{"843"	,	"tie"	,	PY_mb_tie},
{"8464"	,	"ting"	,	PY_mb_ting},
{"8664"	,	"tong"	,	PY_mb_tong},
{"868"	,	"tou"	,	PY_mb_tou},
{"88"	,	"tu"	,	PY_mb_tu},
{"8826"	,	"tuan"	,	PY_mb_tuan},
{"884"	,	"tui"	,	PY_mb_tui},
{"886"	,	"tun"	,	PY_mb_tun},
{"886"	,	"tuo"	,	PY_mb_tuo},
{"92"	,	"wa"	,	PY_mb_wa},
{"92"	,	"ya"	,	PY_mb_ya},
{"92"	,	"za"	,	PY_mb_za},
{"924"	,	"wai"	,	PY_mb_wai},
{"924"	,	"zai"	,	PY_mb_zai},
{"926"	,	"wan"	,	PY_mb_wan},
{"926"	,	"yan"	,	PY_mb_yan},
{"926"	,	"yao"	,	PY_mb_yao},
{"926"	,	"zan"	,	PY_mb_zan},
{"926"	,	"zao"	,	PY_mb_zao},
{"9264"	,	"wang"	,	PY_mb_wang},
{"9264"	,	"yang"	,	PY_mb_yang},
{"9264"	,	"zang"	,	PY_mb_zang},
{"93"	,	"ye"	,	PY_mb_ye},
{"93"	,	"ze"	,	PY_mb_ze},
{"934"	,	"wei"	,	PY_mb_wei},
{"934"	,	"zei"	,	PY_mb_zei},
{"936"	,	"wen"	,	PY_mb_wen},
{"936"	,	"zen"	,	PY_mb_zen},
{"9364"	,	"weng"	,	PY_mb_weng},
{"9364"	,	"zeng"	,	PY_mb_zeng},
{"94"	,	"xi"	,	PY_mb_xi},
{"94"	,	"yi"	,	PY_mb_yi},
{"94"	,	"zi"	,	PY_mb_zi},
{"942"	,	"xia"	,	PY_mb_xia},
{"942"	,	"zha"	,	PY_mb_zha},
{"9424"	,	"zhai"	,	PY_mb_zhai},
{"9426"	,	"xian"	,	PY_mb_xiao},
{"9426"	,	"xiao"	,	PY_mb_xiao},
{"9426"	,	"zhan"	,	PY_mb_zhan},
{"9426"	,	"zhao"	,	PY_mb_zhao},
{"94264"	,	"xiang"	,	PY_mb_xiang},
{"94264"	,	"zhang"	,	PY_mb_zhang},
{"943"	,	"xie"	,	PY_mb_xie},
{"943"	,	"zhe"	,	PY_mb_zhe},
{"9436"	,	"zhen"	,	PY_mb_zhen},
{"94364"	,	"zheng"	,	PY_mb_zheng},
{"944"	,	"zhi"	,	PY_mb_zhi},
{"946"	,	"xin"	,	PY_mb_xin},
{"946"	,	"yin"	,	PY_mb_yin},
{"9464"	,	"xing"	,	PY_mb_xing},
{"9464"	,	"ying"	,	PY_mb_ying},
{"94664"	,	"xiong"	,	PY_mb_xiong},
{"94664"	,	"zhong"	,	PY_mb_zhong},
{"9468"	,	"zhou"	,	PY_mb_zhou},
{"948"	,	"xiu"	,	PY_mb_xiu},
{"948"	,	"zhu"	,	PY_mb_zhu},
{"9482"	,	"zhua"	,	PY_mb_zhua},
{"94824"	,	"zhuai"	,	PY_mb_zhuai},
{"94826"	,	"zhuan"	,	PY_mb_zhuan},
{"948264"	,	"zhuang",	PY_mb_zhuang},
{"9484"	,	"zhui"	,	PY_mb_zhui},
{"9486"	,	"zhun"	,	PY_mb_zhun},
{"9486"	,	"zhuo"	,	PY_mb_zhuo},
{"96"	,	"wo"	,	PY_mb_wo},
{"96"	,	"yo"	,	PY_mb_yo},
{"9664"	,	"yong"	,	PY_mb_yong},
{"9664"	,	"zong"	,	PY_mb_zong},
{"968"	,	"you"	,	PY_mb_you},
{"968"	,	"zou"	,	PY_mb_zou},
{"98"	,	"wu"	,	PY_mb_wu},
{"98"	,	"xu"	,	PY_mb_xu},
{"98"	,	"yu"	,	PY_mb_yu},
{"98"	,	"zu"	,	PY_mb_zu},
{"9826"	,	"xuan"	,	PY_mb_xuan},
{"9826"	,	"yuan"	,	PY_mb_yuan},
{"9826"	,	"zuan"	,	PY_mb_zuan},
{"983"	,	"xue"	,	PY_mb_xue},
{"983"	,	"yue"	,	PY_mb_yue},
{"984"	,	"zui"	,	PY_mb_zui},
{"986"	,	"xun"	,	PY_mb_xun},
{"986"	,	"yun"	,	PY_mb_yun},
{"986"	,	"zun"	,	PY_mb_zun},
{"986"	,	"zuo"	,	PY_mb_zuo},
{""		,	""	    ,	PY_mb_space},
};


#ifdef __cplusplus
}
#endif

#endif

