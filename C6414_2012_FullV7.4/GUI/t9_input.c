
#include <stdio.h>

#include <string.h>
#include "GUI_header/t9_input.h"


//#define my_strlen(ptr) strlen(ptr)
//�����ַ������ȵĺ������û�����ͨ���궨�����ú�����ĺ���
//static unsigned int my_strlen(char*str)
//{
//   unsigned int count=0;
//   while(*str++) {
//     count++;
//   }
//   return count;
//}

/*�����ַ������ȵĺ������û�����ͨ���궨�����ú�����ĺ���*/
int32_t pl_strlen(char*str)
{
   int32_t count=0;
   while(*str++){
     count++;
   }
   return count;
}


//0-396
char PY_mb_space []  = {' '};
char PY_mb_a     []  = {"����"};
char PY_mb_ai    []  = {"��������������������������"};
char PY_mb_an    []  = {"������������������"};
char PY_mb_ang   []  = {"������"};
char PY_mb_ao    []  = {"���������°����ð�"};
char PY_mb_ba    []  = {"�˰ѰͰְհ԰ΰǰɰӰṴ̋ưʰϰȰ�"};
char PY_mb_bai   []  = {"�װٰڰܰݰ۰ذ�"};
char PY_mb_ban   []  = {"�������������߰��"};
char PY_mb_bang  []  = {"�������������������"};
char PY_mb_bao   []  = {"������������������������������������"};
char PY_mb_bei   []  = {"������������������������������"};
char PY_mb_ben   []  = {"����������"};
char PY_mb_beng  []  = {"�����±ñű�"};
char PY_mb_bi    []  = {"�ƱǱȱ˱ʱɱұرϱձӱѱݱбֱԱͱױ̱αڱܱ�"};
char PY_mb_bian  []  = {"�߱�ޱ���������"};
char PY_mb_biao  []  = {"�����"};
char PY_mb_bie   []  = {"�����"};
char PY_mb_bin   []  = {"����������"};
char PY_mb_bing  []  = {"������������������"};
char PY_mb_bo    []  = {"����������������������������������������"};
char PY_mb_bu    []  = {"��������������������"};
char PY_mb_ca    []  = {"��"};
char PY_mb_cai   []  = {"�²ŲĲƲòɲʲǲȲ˲�"};
char PY_mb_can   []  = {"�βͲвϲѲҲ�"};
char PY_mb_cang  []  = {"�ֲײԲղ�"};
char PY_mb_cao   []  = {"�ٲڲܲ۲�"};
char PY_mb_ce    []  = {"���޲��"};
char PY_mb_ceng  []  = {"�����"};
char PY_mb_cha   []  = {"������������ɲ"};
char PY_mb_chai  []  = {"����"};
char PY_mb_chan  []  = {"�������������������"};
char PY_mb_chang []  = {"������������������������"};
char PY_mb_chao  []  = {"��������������������"};
char PY_mb_che   []  = {"������������"};
char PY_mb_chen  []  = {"�������������³��ĳ�"};
char PY_mb_cheng []  = {"�Ƴųɳʳгϳǳ˳ͳ̳γȳѳҳ�"};
char PY_mb_chi   []  = {"�Գճڳس۳ٳֳ߳޳ݳܳ����"};
char PY_mb_chong []  = {"������"};
char PY_mb_chou  []  = {"�������������"};
char PY_mb_chu   []  = {"����������������������������������"};
char PY_mb_chuai []  = {"��"};
char PY_mb_chuan []  = {"��������������"};
char PY_mb_chuang[]  = {"����������"};
char PY_mb_chui  []  = {"����������"};
char PY_mb_chun  []  = {"��������������"};
char PY_mb_chuo  []  = {"��"};
char PY_mb_ci    []  = {"�ôʴĴɴȴǴŴƴ˴δ̴�"};
char PY_mb_cong  []  = {"�ѴӴҴдϴ�"};
char PY_mb_cou   []  = {"��"};
char PY_mb_cu    []  = {"�ִٴ״�"};
char PY_mb_cuan  []  = {"�ڴܴ�"};
char PY_mb_cui   []  = {"�޴ߴݴ�����"};
char PY_mb_cun   []  = {"����"};
char PY_mb_cuo   []  = {"�������"};
char PY_mb_da    []  = {"�������"};
char PY_mb_dai   []  = {"������������������������"};
char PY_mb_dan   []  = {"������������������������������"};
char PY_mb_dang  []  = {"����������"};
char PY_mb_dao   []  = {"������������������������"};
char PY_mb_de    []  = {"�õµ�"};
char PY_mb_deng  []  = {"�Ƶǵŵȵ˵ʵ�"};
char PY_mb_di    []  = {"�͵̵εҵϵеӵѵյ׵ֵصܵ۵ݵڵ޵�"};
char PY_mb_dian  []  = {"���ߵ�������������"};
char PY_mb_diao  []  = {"�����������"};
char PY_mb_die   []  = {"��������������"};
char PY_mb_ding  []  = {"������������������"};
char PY_mb_diu   []  = {"��"};
char PY_mb_dong  []  = {"��������������������"};
char PY_mb_dou   []  = {"����������������"};
char PY_mb_du    []  = {"�����������¶ĶöʶŶǶȶɶ�"};
char PY_mb_duan  []  = {"�˶̶ζ϶ж�"};
char PY_mb_dui   []  = {"�ѶӶԶ�"};
char PY_mb_dun   []  = {"�ֶضն׶ܶ۶ٶ�"};
char PY_mb_duo   []  = {"��߶�޶��������"};
char PY_mb_e     []  = {"����������������"};
char PY_mb_en    []  = {"��"};
char PY_mb_er    []  = {"����������������"};
char PY_mb_fa    []  = {"����������������"};
char PY_mb_fan   []  = {"����������������������������������"};
char PY_mb_fang  []  = {"���������������·÷ķ�"};
char PY_mb_fei   []  = {"�ɷǷȷƷʷ˷̷ͷϷзη�"};
char PY_mb_fen   []  = {"�ַԷ׷ҷշӷطڷٷ۷ݷܷ޷߷�"};
char PY_mb_feng  []  = {"����������������"};
char PY_mb_fo    []  = {"��"};
char PY_mb_fou   []  = {"��"};
char PY_mb_fu    []  = {"������󸥷���������������������������������������������������������������������������"};
char PY_mb_ga    []  = {"�¸�"};
char PY_mb_gai   []  = {"�øĸƸǸȸ�"};
char PY_mb_gan   []  = {"�ɸʸ˸θ̸͸ѸϸҸи�"};
char PY_mb_gang  []  = {"�Ըոڸٸظ׸ָ۸�"};
char PY_mb_gao   []  = {"�޸�߸�ݸ�����"};
char PY_mb_ge    []  = {"����������������������"};
char PY_mb_gei   []  = {"��"};
char PY_mb_gen   []  = {"����"};
char PY_mb_geng  []  = {"��������������"};
char PY_mb_gong  []  = {"������������������������������"};
char PY_mb_gou   []  = {"������������������"};
char PY_mb_gu    []  = {"�����ù¹��������ŹȹɹǹƹĹ̹ʹ˹�"};
char PY_mb_gua   []  = {"�Ϲιйѹҹ�"};
char PY_mb_guai  []  = {"�Թչ�"};
char PY_mb_guan  []  = {"�ع۹ٹڹ׹ݹܹ�߹��"};
char PY_mb_guang []  = {"����"};
char PY_mb_gui   []  = {"������������������"};
char PY_mb_gun   []  = {"������"};
char PY_mb_guo   []  = {"������������"};
char PY_mb_ha    []  = {"���"};
char PY_mb_hai   []  = {"��������������"};
char PY_mb_han   []  = {"��������������������������������������"};
char PY_mb_hang  []  = {"������"};
char PY_mb_hao   []  = {"���������úºźƺ�"};
char PY_mb_he    []  = {"�ǺȺ̺ϺκͺӺҺ˺ɺԺкʺغֺպ�"};
char PY_mb_hei   []  = {"�ں�"};
char PY_mb_hen   []  = {"�ۺܺݺ�"};
char PY_mb_heng  []  = {"��ߺ���"};
char PY_mb_hong  []  = {"����������"};
char PY_mb_hou   []  = {"��������"};
char PY_mb_hu    []  = {"������������������������������������"};
char PY_mb_hua   []  = {"������������������"};
char PY_mb_huai  []  = {"����������"};
char PY_mb_huan  []  = {"�����������û»�������������"};
char PY_mb_huang []  = {"�ĻŻʻ˻ƻ̻ͻȻǻɻлλѻ�"};
char PY_mb_hui   []  = {"�һֻӻԻջػ׻ڻܻ������߻޻�ݻٻ�"};
char PY_mb_hun   []  = {"�������"};
char PY_mb_huo   []  = {"�������������"};
char PY_mb_ji    []  = {"���������������������������������������������������������ƼǼͼ˼ɼ��ʼ����ȼü̼żļ���"};
char PY_mb_jia   []  = {"�ӼмѼϼҼμԼռ׼ּؼۼݼܼټ޼�Ю"};
char PY_mb_jian  []  = {"����߼����������������������������������������������������"};
char PY_mb_jiang []  = {"��������������������������"};
char PY_mb_jiao  []  = {"���������������������ǽƽʽȽýŽ½��˽ɽнνϽ̽ѽ;���"};
char PY_mb_jie   []  = {"�׽Խӽսҽֽڽٽܽ��ݽ޽ؽ߽����������"};
char PY_mb_jin   []  = {"���������������������������������"};
char PY_mb_jing  []  = {"��������������������������������������������������"};
char PY_mb_jiong []  = {"����"};
char PY_mb_jiu   []  = {"�������žþľ��¾ƾɾʾ̾ξǾȾ;�"};
char PY_mb_ju    []  = {"�ӾоѾԾҾϾֽ۾վ׾ھپؾ�޾ܾ߾����ݾ��۾�"};
char PY_mb_juan  []  = {"��������"};
char PY_mb_jue   []  = {"��������������"};
char PY_mb_jun   []  = {"����������������������"};
char PY_mb_ka    []  = {"������"};
char PY_mb_kai   []  = {"����������"};
char PY_mb_kan   []  = {"��������������"};
char PY_mb_kang  []  = {"��������������"};
char PY_mb_kao   []  = {"��������"};
char PY_mb_ke    []  = {"�����¿ƿÿſĿǿȿɿʿ˿̿Ϳ�"};
char PY_mb_ken   []  = {"�Ͽѿҿ�"};
char PY_mb_keng  []  = {"�Կ�"};
char PY_mb_kong  []  = {"�տ׿ֿ�"};
char PY_mb_kou   []  = {"�ٿڿۿ�"};
char PY_mb_ku    []  = {"�ݿ޿߿����"};
char PY_mb_kua   []  = {"������"};
char PY_mb_kuai  []  = {"�����"};
char PY_mb_kuan  []  = {"���"};
char PY_mb_kuang []  = {"�����������"};
char PY_mb_kui   []  = {"����������������������"};
char PY_mb_kun   []  = {"��������"};
char PY_mb_kuo   []  = {"��������"};
char PY_mb_la    []  = {"��������������"};
char PY_mb_lai   []  = {"������"};
char PY_mb_lan   []  = {"������������������������������"};
char PY_mb_lang  []  = {"��������������"};
char PY_mb_lao   []  = {"������������������"};
char PY_mb_le    []  = {"������"};
char PY_mb_lei   []  = {"����������������������"};
char PY_mb_leng  []  = {"������"};
char PY_mb_li    []  = {"��������������������������������������������������������������������"};
char PY_mb_lian  []  = {"����������������������������"};
char PY_mb_liang []  = {"������������������������"};
char PY_mb_liao  []  = {"������������������������"};
char PY_mb_lie   []  = {"����������"};
char PY_mb_lin   []  = {"������������������������"};
char PY_mb_ling  []  = {"����������������������������"};
char PY_mb_liu   []  = {"����������������������"};
char PY_mb_long  []  = {"��������¡��¤¢£"};
char PY_mb_lou   []  = {"¦¥§¨ª©"};
char PY_mb_lu    []  = {"¶¬®«¯­±²°³½¼¸¹»µ·¾º´"};
char PY_mb_luan  []  = {"������������"};
char PY_mb_lue   []  = {"����"};
char PY_mb_lun   []  = {"��������������"};
char PY_mb_luo   []  = {"������������������������"};
char PY_mb_lv    []  = {"��¿������������������������"};
char PY_mb_ma    []  = {"������������������"};
char PY_mb_mai   []  = {"������������"};
char PY_mb_man   []  = {"����������á������"};
char PY_mb_mang  []  = {"æâäãçå"};
char PY_mb_mao   []  = {"èëìéêîíïðóñò"};
char PY_mb_me    []  = {"ô"};
char PY_mb_mei   []  = {"ûöõü÷ýúøùÿ��þ��������"};
char PY_mb_men   []  = {"������"};
char PY_mb_meng  []  = {"����������������"};
char PY_mb_mi    []  = {"����������������������������"};
char PY_mb_mian  []  = {"������������������"};
char PY_mb_miao  []  = {"����������������"};
char PY_mb_mie   []  = {"����"};
char PY_mb_min   []  = {"������������"};
char PY_mb_ming  []  = {"������������"};
char PY_mb_miu   []  = {"��"};
char PY_mb_mo    []  = {"����ġģĤĦĥĢħĨĩĭİĪįĮīĬ"};
char PY_mb_mou   []  = {"Ĳıĳ"};
char PY_mb_mu    []  = {"ĸĶĵķĴľĿ��ļĹĻ��Ľĺ��"};
char PY_mb_na    []  = {"��������������"};
char PY_mb_nai   []  = {"����������"};
char PY_mb_nan   []  = {"�������"};
char PY_mb_nang  []  = {"��"};
char PY_mb_nao   []  = {"����������"};
char PY_mb_ne    []  = {"��"};
char PY_mb_nei   []  = {"����"};
char PY_mb_nen   []  = {"��"};
char PY_mb_neng  []  = {"��"};
char PY_mb_ni    []  = {"����������������������"};
char PY_mb_nian  []  = {"��������������"};
char PY_mb_niang []  = {"����"};
char PY_mb_niao  []  = {"����"};
char PY_mb_nie   []  = {"��������������"};
char PY_mb_nin   []  = {"��"};
char PY_mb_ning  []  = {"��š������Ţ"};
char PY_mb_niu   []  = {"ţŤŦť"};
char PY_mb_nong  []  = {"ũŨŧŪ"};
char PY_mb_nu    []  = {"ūŬŭ"};
char PY_mb_nuan  []  = {"ů"};
char PY_mb_nue   []  = {"űŰ"};
char PY_mb_nuo   []  = {"ŲŵųŴ"};
char PY_mb_nv    []  = {"Ů"};
char PY_mb_o     []  = {"Ŷ"};
char PY_mb_ou    []  = {"ŷŹŸŻżźŽ"};
char PY_mb_pa    []  = {"ſž����������"};
char PY_mb_pai   []  = {"������������"};
char PY_mb_pan   []  = {"����������������"};
char PY_mb_pang  []  = {"����������"};
char PY_mb_pao   []  = {"��������������"};
char PY_mb_pei   []  = {"������������������"};
char PY_mb_pen   []  = {"����"};
char PY_mb_peng  []  = {"����������������������������"};
char PY_mb_pi    []  = {"��������������Ƥ��ƣơ��ƢƥƦƨƧƩ"};
char PY_mb_pian  []  = {"Ƭƫƪƭ"};
char PY_mb_piao  []  = {"ƯƮưƱ"};
char PY_mb_pie   []  = {"ƲƳ"};
char PY_mb_pin   []  = {"ƴƶƵƷƸ"};
char PY_mb_ping  []  = {"ƽ��ƾ��ƿƺƻƼƹ"};
char PY_mb_po    []  = {"����������������"};
char PY_mb_pou   []  = {"��"};
char PY_mb_pu    []  = {"������������������������������"};
char PY_mb_qi    []  = {"������������������������������������������������������������������������"};
char PY_mb_qia   []  = {"��ǡǢ"};
char PY_mb_qian  []  = {"ǧǪǤǨǥǣǦǫǩǰǮǯǬǱǭǳǲǴǷǵǶǸ"};
char PY_mb_qiang []  = {"ǺǼǹǻǿǽǾ��"};
char PY_mb_qiao  []  = {"������������������������������"};
char PY_mb_qie   []  = {"����������"};
char PY_mb_qin   []  = {"����������������������"};
char PY_mb_qing  []  = {"��������������������������"};
char PY_mb_qiong []  = {"����"};
char PY_mb_qiu   []  = {"����������������"};
char PY_mb_qu    []  = {"����������������ȡȢȣȥȤ"};
char PY_mb_quan  []  = {"ȦȫȨȪȭȬȩȧȮȰȯ"};
char PY_mb_que   []  = {"Ȳȱȳȴȸȷȵȶ"};
char PY_mb_qun   []  = {"ȹȺ"};
char PY_mb_ran   []  = {"ȻȼȽȾ"};
char PY_mb_rang  []  = {"ȿ��������"};
char PY_mb_rao   []  = {"������"};
char PY_mb_re    []  = {"����"};
char PY_mb_ren   []  = {"��������������������"};
char PY_mb_reng  []  = {"����"};
char PY_mb_ri    []  = {"��"};
char PY_mb_rong  []  = {"��������������������"};
char PY_mb_rou   []  = {"������"};
char PY_mb_ru    []  = {"��������������������"};
char PY_mb_ruan  []  = {"����"};
char PY_mb_rui   []  = {"������"};
char PY_mb_run   []  = {"����"};
char PY_mb_ruo   []  = {"����"};
char PY_mb_sa    []  = {"������"};
char PY_mb_sai   []  = {"��������"};
char PY_mb_san   []  = {"��ɡɢ��"};
char PY_mb_sang  []  = {"ɣɤɥ"};
char PY_mb_sao   []  = {"ɦɧɨɩ"};
char PY_mb_se    []  = {"ɫɬɪ"};
char PY_mb_sen   []  = {"ɭ"};
char PY_mb_seng  []  = {"ɮ"};
char PY_mb_sha   []  = {"ɱɳɴɰɯɵɶɷ��"};
char PY_mb_shai  []  = {"ɸɹ"};
char PY_mb_shan  []  = {"ɽɾɼ��ɺɿ������ɻ������������դ"};
char PY_mb_shang []  = {"����������������"};
char PY_mb_shao  []  = {"����������������������"};
char PY_mb_she   []  = {"������������������������"};
char PY_mb_shen  []  = {"��������������������������������ʲ"};
char PY_mb_sheng []  = {"��������ʤ����ʡʥʢʣ"};
char PY_mb_shi   []  = {"��ʮʯʱʿʶ��ʳʾʽʹʼ����ʵ����ʷ��ʩ��ʻʪ�Ƴ�ʬʧ����ʦʫʨʰʴʸʺ��������������"};
char PY_mb_shou  []  = {"��������������������"};
char PY_mb_shu   []  = {"������������������������������������������������������ˡ����������"};
char PY_mb_shua  []  = {"ˢˣ"};
char PY_mb_shuai []  = {"˥ˤ˦˧"};
char PY_mb_shuan []  = {"˩˨"};
char PY_mb_shuang[]  = {"˫˪ˬ"};
char PY_mb_shui  []  = {"˭ˮ˰˯"};
char PY_mb_shun  []  = {"˱˳˴˲"};
char PY_mb_shuo  []  = {"˵˸˷˶"};
char PY_mb_si    []  = {"��˿˾˽˼˹��˺��˻����������"};
char PY_mb_song  []  = {"����������������"};
char PY_mb_sou   []  = {"��������"};
char PY_mb_su    []  = {"����������������������"};
char PY_mb_suan  []  = {"������"};
char PY_mb_sui   []  = {"����������������������"};
char PY_mb_sun   []  = {"������"};
char PY_mb_suo   []  = {"����������������"};
char PY_mb_ta    []  = {"����������̡̢̤̣"};
char PY_mb_tai   []  = {"̨̧̥̦̫̭̬̩̪"};
char PY_mb_tan   []  = {"̸̵̷̶̴̮̰̯̲̱̳̹̻̺̼̾̿̽"};
char PY_mb_tang  []  = {"��������������������������"};
char PY_mb_tao   []  = {"����������������������"};
char PY_mb_te    []  = {"��"};
char PY_mb_teng  []  = {"��������"};
char PY_mb_ti    []  = {"������������������������������"};
char PY_mb_tian  []  = {"����������������"};
char PY_mb_tiao  []  = {"������������"};
char PY_mb_tie   []  = {"������"};
char PY_mb_ting  []  = {"ͣ��͡����ͤͥͦͧ͢"};
char PY_mb_tong  []  = {"ͨͬͮͩͭͯͪͫͳͱͰͲʹ"};
char PY_mb_tou   []  = {"͵ͷͶ͸"};
char PY_mb_tu    []  = {"͹ͺͻͼͽͿ;��������"};
char PY_mb_tuan  []  = {"����"};
char PY_mb_tui   []  = {"������������"};
char PY_mb_tun   []  = {"��������"};
char PY_mb_tuo   []  = {"����������������������"};
char PY_mb_wa    []  = {"��������������"};
char PY_mb_wai   []  = {"����"};
char PY_mb_wan   []  = {"����������������������������������"};
char PY_mb_wang  []  = {"��������������������"};
char PY_mb_wei   []  = {"Σ��΢ΡΪΤΧΥΦΨΩάΫΰαβγέίή��δλζηθξνιμεοκ"};
char PY_mb_wen   []  = {"��������������������"};
char PY_mb_weng  []  = {"������"};
char PY_mb_wo    []  = {"������������������"};
char PY_mb_wu    []  = {"����������������������������������������������������������"};
char PY_mb_xi    []  = {"Ϧϫ����ϣ������Ϣ��Ϥϧϩ����ϬϡϪ��Ϩ����ϥϰϯϮϱϭϴϲϷϵϸ϶"};
char PY_mb_xia   []  = {"ϺϹϻ��Ͽ��ϾϽϼ������"};
char PY_mb_xian  []  = {"ϳ����������������������������������������������������"};
char PY_mb_xiang []  = {"����������������������������������������"};
char PY_mb_xiao  []  = {"����������������С��ТФ��ЧУЦХ"};
char PY_mb_xie   []  = {"ЩШЪЫЭавбгЯЬдйкжмелиз"};
char PY_mb_xin   []  = {"����о����п��н����"};
char PY_mb_xing  []  = {"����������������������������"};
char PY_mb_xiong []  = {"��������������"};
char PY_mb_xiu   []  = {"��������������������"};
char PY_mb_xu    []  = {"��������������������������������������"};
char PY_mb_xuan  []  = {"������������ѡѢѤѣ"};
char PY_mb_xue   []  = {"ѧѩѪ��ѥѦѨ"};
char PY_mb_xun   []  = {"ѰѮѸѯѶѫѬѲѱѭѵѴѷѳ"};
char PY_mb_ya    []  = {"ѽѹ������ѾѺѻѼѿ������������"};
char PY_mb_yan   []  = {"������������������������������������������������������������������"};
char PY_mb_yang  []  = {"����������������������������������"};
char PY_mb_yao   []  = {"��������ҢҦҤҥҡң��ҧҨҩҪҫԿ"};
char PY_mb_ye    []  = {"ҬҭүҮҲұҰҵҶҷҳҹҴҺҸ"};
char PY_mb_yi    []  = {"һ����ҽ��ҿ����������������������������������������������������������������������"};
char PY_mb_yin   []  = {"������������������������������ӡ"};
char PY_mb_ying  []  = {"ӦӢӤӧӣӥӭӯӫӨөӪӬӮӱӰӳӲ"};
char PY_mb_yo    []  = {"Ӵ"};
char PY_mb_yong  []  = {"ӶӵӸӹӺӷ��ӽӾ��ӿ��Ӽӻ��"};
char PY_mb_you   []  = {"����������������������������������������"};
char PY_mb_yu    []  = {"����������������������������������������������������Ԧ����������ԡԤ������Ԣ��ԣ������ԥ"};
char PY_mb_yuan  []  = {"ԩԧԨԪԱ԰ԫԭԲԬԮԵԴԳԯԶԷԹԺԸ"};
char PY_mb_yue   []  = {"ԻԼ��������Ծ��Խ"};
char PY_mb_yun   []  = {"������������������������"};
char PY_mb_za    []  = {"������զ"};
char PY_mb_zai   []  = {"����������������"};
char PY_mb_zan   []  = {"��������"};
char PY_mb_zang  []  = {"������"};
char PY_mb_zao   []  = {"����������������������������"};
char PY_mb_ze    []  = {"��������"};
char PY_mb_zei   []  = {"��"};
char PY_mb_zen   []  = {"��"};
char PY_mb_zeng  []  = {"������"};
char PY_mb_zha   []  = {"����������բագէթըե��"};
char PY_mb_zhai  []  = {"իժլ��խծկ"};
char PY_mb_zhan  []  = {"մձճղհնչյոշռսջվ��տպ"};
char PY_mb_zhang []  = {"��������������������������������"};
char PY_mb_zhao  []  = {"��������������������צ"};
char PY_mb_zhe   []  = {"����������������������"};
char PY_mb_zhen  []  = {"��������������������������������֡"};
char PY_mb_zheng []  = {"��������������������֤֣��֢"};
char PY_mb_zhi   []  = {"ְֱֲֳִֵֶַָֹֺֻּֽ֧֥֦֪֭֮֨֯֫֬֩��־����������ֿ������������������"};
char PY_mb_zhong []  = {"����������������������"};
char PY_mb_zhou  []  = {"����������������������������"};
char PY_mb_zhu   []  = {"��סעף������������������������������������פ������"};
char PY_mb_zhua  []  = {"ץ"};
char PY_mb_zhuai []  = {"ק"};
char PY_mb_zhuan []  = {"רשת׫׭"};
char PY_mb_zhuang[]  = {"ױׯ׮װ׳״��ײ"};
char PY_mb_zhui  []  = {"׷׹׵׶׺׸"};
char PY_mb_zhun  []  = {"׼׻"};
char PY_mb_zhuo  []  = {"׿׾׽��������������"};
char PY_mb_zi    []  = {"����������������������������"};
char PY_mb_zong  []  = {"��������������"};
char PY_mb_zou   []  = {"��������"};
char PY_mb_zu    []  = {"����������������"};
char PY_mb_zuan  []  = {"׬����"};
char PY_mb_zui   []  = {"��������"};
char PY_mb_zun   []  = {"����"};
char PY_mb_zuo   []  = {"��������������"};

//0-396
t9PY_index t9_py_index[] ={
{"0"		,	"0"	    ,	PY_mb_space},
{"200000"	,	"a"	    ,	PY_mb_a},
{"220000"	,	"ba"	,	PY_mb_ba},
{"220000"	,	"ca"	,	PY_mb_ca},
{"224000"	,	"bai"	,	PY_mb_bai},
{"224000"	,	"cai"	,	PY_mb_cai},
{"226000"	,	"ban"	,	PY_mb_ban},
{"226000"	,	"bao"	,	PY_mb_bao},
{"226000"	,	"can"	,	PY_mb_can},
{"226000"	,	"cao"	,	PY_mb_cao},
{"226400"	,	"bang"	,	PY_mb_bang},
{"226400"	,	"cang"	,	PY_mb_cang},
{"230000"	,	"ce"	,	PY_mb_ce},
{"234000"	,	"bei"	,	PY_mb_bei},
{"236000"	,	"ben"	,	PY_mb_ben},
{"236400"	,	"beng"	,	PY_mb_beng},
{"236400"	,	"ceng"	,	PY_mb_ceng},
{"240000"	,	"ai"	,	PY_mb_ai},
{"240000"	,	"bi"	,	PY_mb_bi},
{"240000"	,	"ci"	,	PY_mb_ci},
{"242000"	,	"cha"	,	PY_mb_cha},
{"242400"	,	"chai"	,	PY_mb_chai},
{"242600"	,	"bian"	,	PY_mb_bian},
{"242600"	,	"biao"	,	PY_mb_biao},
{"242600"	,	"chan"	,	PY_mb_chan},
{"242600"	,	"chao"	,	PY_mb_chao},
{"242640"	,	"chang"	,	PY_mb_chang},
{"243000"	,	"bie"	,	PY_mb_bie},
{"243000"	,	"che"	,	PY_mb_che},
{"243600"	,	"chen"	,	PY_mb_chen},
{"243640"	,	"cheng"	,	PY_mb_cheng},
{"244000"	,	"chi"	,	PY_mb_chi},
{"246000"	,	"bin"	,	PY_mb_bin},
{"246400"	,	"bing"	,	PY_mb_bing},
{"246640"	,	"chong"	,	PY_mb_chong},
{"246800"	,	"chou"	,	PY_mb_chou},
{"248000"	,	"chu"	,	PY_mb_chu},
{"248260"	,	"chuan"	,	PY_mb_chuan},
{"248264"	,	"chuang",	PY_mb_chuang},
{"248400"	,	"chuai"	,	PY_mb_chuai},
{"248400"	,	"chui"	,	PY_mb_chui},
{"248400"	,	"chun"	,	PY_mb_chun},
{"248600"	,	"chuo"	,	PY_mb_chuo},
{"260000"	,	"an"	,	PY_mb_an},
{"260000"	,	"ao"	,	PY_mb_ao},
{"260000"	,	"bo"	,	PY_mb_bo},
{"264000"	,	"ang"	,	PY_mb_ang},
{"266400"	,	"cong"	,	PY_mb_cong},
{"268000"	,	"cou"	,	PY_mb_cou},
{"280000"	,	"bu"	,	PY_mb_bu},
{"280000"	,	"cu"	,	PY_mb_cu},
{"282600"	,	"cuan"	,	PY_mb_cuan},
{"284000"	,	"cui"	,	PY_mb_cui},
{"286000"	,	"cun"	,	PY_mb_cun},
{"286000"	,	"cuo"	,	PY_mb_cuo},
{"300000"	,	"e"	    ,	PY_mb_e},
{"320000"	,	"da"	,	PY_mb_da},
{"320000"	,	"fa"	,	PY_mb_fa},
{"324000"	,	"dai"	,	PY_mb_dai},
{"326000"	,	"dan"	,	PY_mb_dan},
{"326000"	,	"dao"	,	PY_mb_dao},
{"326000"	,	"fan"	,	PY_mb_fan},
{"326400"	,	"dang"	,	PY_mb_dang},
{"326400"	,	"fang"	,	PY_mb_fang},
{"330000"	,	"de"	,	PY_mb_de},
{"334000"	,	"fei"	,	PY_mb_fei},
{"336000"	,	"fen"	,	PY_mb_fen},
{"336400"	,	"deng"	,	PY_mb_deng},
{"336400"	,	"feng"	,	PY_mb_feng},
{"340000"	,	"di"	,	PY_mb_di},
{"342600"	,	"dian"	,	PY_mb_dian},
{"342600"	,	"diao"	,	PY_mb_diao},
{"343000"	,	"die"	,	PY_mb_die},
{"346400"	,	"ding"	,	PY_mb_ding},
{"348000"	,	"diu"	,	PY_mb_diu},
{"360000"	,	"en"	,	PY_mb_en},
{"360000"	,	"fo"	,	PY_mb_fo},
{"366400"	,	"dong"	,	PY_mb_dong},
{"368000"	,	"dou"	,	PY_mb_dou},
{"368000"	,	"fou"	,	PY_mb_fou},
{"370000"	,	"er"	,	PY_mb_er},
{"380000"	,	"du"	,	PY_mb_du},
{"380000"	,	"fu"	,	PY_mb_fu},
{"382600"	,	"duan"	,	PY_mb_duan},
{"384000"	,	"dui"	,	PY_mb_dui},
{"386000"	,	"dun"	,	PY_mb_dun},
{"386000"	,	"duo"	,	PY_mb_duo},
//{"400000"	,	"i"	,	PY_mb_space},
{"420000"	,	"ha"	,	PY_mb_ha},
{"420000"	,	"ga"	,	PY_mb_ga},
{"423000"	,	"hai"	,	PY_mb_hai},
{"424000"	,	"gai"	,	PY_mb_gai},
{"426000"	,	"gan"	,	PY_mb_gan},
{"426000"	,	"gao"	,	PY_mb_gao},
{"426000"	,	"han"	,	PY_mb_han},
{"426000"	,	"hao"	,	PY_mb_hao},
{"426400"	,	"gang"	,	PY_mb_gang},
{"426400"	,	"hang"	,	PY_mb_hang},
{"430000"	,	"ge"	,	PY_mb_ge},
{"430000"	,	"he"	,	PY_mb_he},
{"434000"	,	"gei"	,	PY_mb_gei},
{"434000"	,	"hei"	,	PY_mb_hei},
{"436000"	,	"gen"	,	PY_mb_gan},
{"436000"	,	"hen"	,	PY_mb_hen},
{"436400"	,	"geng"	,	PY_mb_geng},
{"436400"	,	"heng"	,	PY_mb_heng},
{"466400"	,	"gong"	,	PY_mb_gong},
{"466400"	,	"hong"	,	PY_mb_hong},
{"468000"	,	"gou"	,	PY_mb_gou},
{"468000"	,	"hou"	,	PY_mb_hou},
{"480000"	,	"gu"	,	PY_mb_gu},
{"480000"	,	"hu"	,	PY_mb_hu},
{"482000"	,	"gua"	,	PY_mb_gua},
{"482000"	,	"hua"	,	PY_mb_hua},
{"482300"	,	"huai"	,	PY_mb_huai},
{"482400"	,	"guai"	,	PY_mb_guai},
{"482600"	,	"guan"	,	PY_mb_guan},
{"482600"	,	"huan"	,	PY_mb_huan},
{"482640"	,	"guang"	,	PY_mb_guang},
{"482640"	,	"huang"	,	PY_mb_huang},
{"484000"	,	"gui"	,	PY_mb_gui},
{"484000"	,	"hui"	,	PY_mb_hui},
{"486000"	,	"gun"	,	PY_mb_gun},
{"486000"	,	"guo"	,	PY_mb_guo},
{"486000"	,	"hun"	,	PY_mb_hun},
{"486000"	,	"huo"	,	PY_mb_huo},
{"520000"	,	"ka"	,	PY_mb_ka},
{"520000"	,	"la"	,	PY_mb_la},
{"524000"	,	"kai"	,	PY_mb_kai},
{"524000"	,	"lai"	,	PY_mb_lai},
{"526000"	,	"kan"	,	PY_mb_kan},
{"526000"	,	"kao"	,	PY_mb_kao},
{"526000"	,	"lan"	,	PY_mb_lan},
{"526000"	,	"lao"	,	PY_mb_lao},
{"526400"	,	"kang"	,	PY_mb_kang},
{"526400"	,	"lang"	,	PY_mb_lang},
{"530000"	,	"ke"	,	PY_mb_ke},
{"530000"	,	"le"	,	PY_mb_le},
{"534000"	,	"lei"	,	PY_mb_lei},
{"536000"	,	"ken"	,	PY_mb_ken},
{"536400"	,	"keng"	,	PY_mb_keng},
{"536600"	,	"leng"	,	PY_mb_leng},
{"540000"	,	"ji"	,	PY_mb_ji},
{"540000"	,	"li"	,	PY_mb_li},
{"542000"	,	"jia"	,	PY_mb_jia},
{"542600"	,	"jian"	,	PY_mb_jian},
{"542600"	,	"jiao"	,	PY_mb_jiao},
{"542600"	,	"lian"	,	PY_mb_lian},
{"542600"	,	"liao"	,	PY_mb_liao},
{"542640"	,	"jiang"	,	PY_mb_jiang},
{"542640"	,	"liang"	,	PY_mb_liang},
{"543000"	,	"jie"	,	PY_mb_jie},
{"543000"	,	"lie"	,	PY_mb_lie},
{"546000"	,	"jin"	,	PY_mb_jin},
{"546000"	,	"lin"	,	PY_mb_lin},
{"546400"	,	"jing"	,	PY_mb_jing},
{"546400"	,	"ling"	,	PY_mb_ling},
{"546640"	,	"jiong"	,	PY_mb_jiong},
{"548000"	,	"jiu"	,	PY_mb_jiu},
{"548000"	,	"liu"	,	PY_mb_liu},
{"566400"	,	"kong"	,	PY_mb_kong},
{"566400"	,	"long"	,	PY_mb_long},
{"568000"	,	"kou"	,	PY_mb_kou},
{"568000"	,	"lou"	,	PY_mb_lou},
{"580000"	,	"ju"	,	PY_mb_ju},
{"580000"	,	"ku"	,	PY_mb_ku},
{"580000"	,	"lu"	,	PY_mb_lu},
{"580000"	,	"lv"	,	PY_mb_lv},
{"582000"	,	"kua"	,	PY_mb_kua},
{"582400"	,	"kuai"	,	PY_mb_kuai},
{"582600"	,	"juan"	,	PY_mb_juan},
{"582600"	,	"kuan"	,	PY_mb_kuan},
{"582600"	,	"luan"	,	PY_mb_luan},
{"582640"	,	"kuang"	,	PY_mb_kuang},
{"583000"	,	"jue"	,	PY_mb_jue},
{"583000"	,	"lue"	,	PY_mb_lue},
{"584000"	,	"kui"	,	PY_mb_kui},
{"586000"	,	"jun"	,	PY_mb_jun},
{"586000"	,	"kun"	,	PY_mb_kun},
{"586000"	,	"kuo"	,	PY_mb_kuo},
{"586000"	,	"lun"	,	PY_mb_lun},
{"586000"	,	"luo"	,	PY_mb_luo},
{"600000"	,	"o"	    ,	PY_mb_o},
{"620000"	,	"ma"	,	PY_mb_ma},
{"620000"	,	"na"	,	PY_mb_na},
{"624000"	,	"mai"	,	PY_mb_mai},
{"624000"	,	"nai"	,	PY_mb_nai},
{"626000"	,	"man"	,	PY_mb_man},
{"626000"	,	"mao"	,	PY_mb_mao},
{"626000"	,	"nan"	,	PY_mb_nan},
{"626000"	,	"nao"	,	PY_mb_nao},
{"626400"	,	"mang"	,	PY_mb_mang},
{"626400"	,	"nang"	,	PY_mb_nang},
{"630000"	,	"me"	,	PY_mb_me},
{"630000"	,	"ne"	,	PY_mb_ne},
{"634000"	,	"mei"	,	PY_mb_mei},
{"634000"	,	"nei"	,	PY_mb_nei},
{"636000"	,	"men"	,	PY_mb_men},
{"636000"	,	"nen"	,	PY_mb_nen},
{"636400"	,	"meng"	,	PY_mb_meng},
{"636400"	,	"neng"	,	PY_mb_neng},
{"640000"	,	"mi"	,	PY_mb_mi},
{"640000"	,	"ni"	,	PY_mb_ni},
{"642600"	,	"mian"	,	PY_mb_mian},
{"642600"	,	"miao"	,	PY_mb_miao},
{"642600"	,	"nian"	,	PY_mb_nian},
{"642600"	,	"niao"	,	PY_mb_niao},
{"642640"	,	"niang"	,	PY_mb_niang},
{"643000"	,	"mie"	,	PY_mb_mie},
{"643000"	,	"nie"	,	PY_mb_nie},
{"646000"	,	"min"	,	PY_mb_min},
{"646000"	,	"nin"	,	PY_mb_nin},
{"646400"	,	"ming"	,	PY_mb_ming},
{"646400"	,	"ning"	,	PY_mb_ning},
{"648000"	,	"miu"	,	PY_mb_miu},
{"648000"	,	"niu"	,	PY_mb_niu},
{"660000"	,	"mo"	,	PY_mb_mo},
{"666400"	,	"nong"	,	PY_mb_nong},
{"668000"	,	"mou"	,	PY_mb_mou},
{"680000"	,	"mu"	,	PY_mb_mu},
{"680000"	,	"nu"	,	PY_mb_nu},
{"680000"	,	"nv"	,	PY_mb_nv},
{"680000"	,	"ou"	,	PY_mb_ou},
{"682600"	,	"nuan"	,	PY_mb_nuan},
{"683000"	,	"nue"	,	PY_mb_nue},
{"686000"	,	"nuo"	,	PY_mb_nuo},
{"720000"	,	"pa"	,	PY_mb_pa},
{"720000"	,	"sa"	,	PY_mb_sa},
{"724000"	,	"pai"	,	PY_mb_pai},
{"724000"	,	"sai"	,	PY_mb_sai},
{"726000"	,	"pan"	,	PY_mb_pan},
{"726000"	,	"pao"	,	PY_mb_pao},
{"726000"	,	"ran"	,	PY_mb_ran},
{"726000"	,	"rao"	,	PY_mb_rao},
{"726000"	,	"sao"	,	PY_mb_sao},
{"726000"	,	"san"	,	PY_mb_san},
{"726400"	,	"pang"	,	PY_mb_pang},
{"726400"	,	"rang"	,	PY_mb_rang},
{"726400"	,	"sang"	,	PY_mb_sang},
{"730000"	,	"re"	,	PY_mb_re},
{"730000"	,	"se"	,	PY_mb_se},
{"734000"	,	"pei"	,	PY_mb_pei},
{"736000"	,	"pen"	,	PY_mb_pen},
{"736000"	,	"ren"	,	PY_mb_ren},
{"736000"	,	"sen"	,	PY_mb_sen},
{"736400"	,	"peng"	,	PY_mb_peng},
{"736400"	,	"reng"	,	PY_mb_reng},
{"736400"	,	"seng"	,	PY_mb_seng},
{"740000"	,	"pi"	,	PY_mb_pi},
{"740000"	,	"qi"	,	PY_mb_qi},
{"740000"	,	"ri"	,	PY_mb_ri},
{"740000"	,	"si"	,	PY_mb_si},
{"742000"	,	"qia"	,	PY_mb_qia},
{"742000"	,	"sha"	,	PY_mb_sha},
{"742400"	,	"shai"	,	PY_mb_shai},
{"742600"	,	"pian"	,	PY_mb_pian},
{"742600"	,	"piao"	,	PY_mb_piao},
{"742600"	,	"qian"	,	PY_mb_qian},
{"742600"	,	"qiao"	,	PY_mb_qiao},
{"742600"	,	"shan"	,	PY_mb_shan},
{"742600"	,	"shao"	,	PY_mb_shao},
{"742640"	,	"qiang"	,	PY_mb_qiang},
{"742640"	,	"shang ",	PY_mb_shang},
{"743000"	,	"pie"	,	PY_mb_pie},
{"743000"	,	"qie"	,	PY_mb_qie},
{"743000"	,	"she"	,	PY_mb_she},
{"743600"	,	"shen"	,	PY_mb_shen},
{"743640"	,	"sheng"	,	PY_mb_sheng},
{"744000"	,	"shi"	,	PY_mb_shi},
{"746000"	,	"pin"	,	PY_mb_pin},
{"746000"	,	"qin"	,	PY_mb_qin},
{"746400"	,	"ping"	,	PY_mb_ping},
{"746400"	,	"qing"	,	PY_mb_qing},
{"746640"	,	"qiong"	,	PY_mb_qiong},
{"746800"	,	"shou"	,	PY_mb_shou},
{"748000"	,	"qiu"	,	PY_mb_qiu},
{"748000"	,	"shu"	,	PY_mb_shu},
{"748200"	,	"shua"	,	PY_mb_shua},
{"748240"	,	"shuai"	,	PY_mb_shuai},
{"748260"	,	"shuan"	,	PY_mb_shuan},
{"748264"	,	"shuang",	PY_mb_shuang},
{"748400"	,	"shui"	,	PY_mb_shui},
{"748600"	,	"shun"	,	PY_mb_shun},
{"748600"	,	"shuo"	,	PY_mb_shuo},
{"760000"	,	"po"	,	PY_mb_po},
{"766400"	,	"rong"	,	PY_mb_rong},
{"766400"	,	"song"	,	PY_mb_song},
{"768000"	,	"pou"	,	PY_mb_pou},
{"768000"	,	"rou"	,	PY_mb_rou},
{"768000"	,	"sou"	,	PY_mb_sou},
{"780000"	,	"pu"	,	PY_mb_pu},
{"780000"	,	"qu"	,	PY_mb_qu},
{"780000"	,	"ru"	,	PY_mb_ru},
{"780000"	,	"su"	,	PY_mb_su},
{"782600"	,	"quan"	,	PY_mb_quan},
{"782600"	,	"ruan"	,	PY_mb_ruan},
{"782600"	,	"suan"	,	PY_mb_suan},
{"783000"	,	"que"	,	PY_mb_que},
{"784000"	,	"rui"	,	PY_mb_rui},
{"784000"	,	"sui"	,	PY_mb_sui},
{"786000"	,	"qun"	,	PY_mb_qun},
{"786000"	,	"run"	,	PY_mb_run},
{"786000"	,	"ruo"	,	PY_mb_ruo},
{"786000"	,	"sun"	,	PY_mb_sun},
{"786000"	,	"suo"	,	PY_mb_suo},
//{"800000"	,	"u"	,	PY_mb_space},
//{"800000"	,	"v"	,	PY_mb_space},
{"820000"	,	"ta"	,	PY_mb_ta},
{"824000"	,	"tai"	,	PY_mb_tai},
{"826000"	,	"tan"	,	PY_mb_tan},
{"826000"	,	"tao"	,	PY_mb_tao},
{"826400"	,	"tang"	,	PY_mb_tang},
{"830000"	,	"te"	,	PY_mb_te},
{"836400"	,	"teng"	,	PY_mb_teng},
{"840000"	,	"ti"	,	PY_mb_ti},
{"842600"	,	"tian"	,	PY_mb_tian},
{"842600"	,	"tiao"	,	PY_mb_tiao},
{"843000"	,	"tie"	,	PY_mb_tie},
{"846400"	,	"ting"	,	PY_mb_ting},
{"866400"	,	"tong"	,	PY_mb_tong},
{"868000"	,	"tou"	,	PY_mb_tou},
{"880000"	,	"tu"	,	PY_mb_tu},
{"882600"	,	"tuan"	,	PY_mb_tuan},
{"884000"	,	"tui"	,	PY_mb_tui},
{"886000"	,	"tun"	,	PY_mb_tun},
{"886000"	,	"tuo"	,	PY_mb_tuo},
{"920000"	,	"wa"	,	PY_mb_wa},
{"920000"	,	"ya"	,	PY_mb_ya},
{"920000"	,	"za"	,	PY_mb_za},
{"924000"	,	"wai"	,	PY_mb_wai},
{"924000"	,	"zai"	,	PY_mb_zai},
{"926000"	,	"wan"	,	PY_mb_wan},
{"926000"	,	"yan"	,	PY_mb_yan},
{"926000"	,	"yao"	,	PY_mb_yao},
{"926000"	,	"zan"	,	PY_mb_zan},
{"926000"	,	"zao"	,	PY_mb_zao},
{"926400"	,	"wang"	,	PY_mb_wang},
{"926400"	,	"yang"	,	PY_mb_yang},
{"926400"	,	"zang"	,	PY_mb_zang},
{"930000"	,	"ye"	,	PY_mb_ye},
{"930000"	,	"ze"	,	PY_mb_ze},
{"934000"	,	"wei"	,	PY_mb_wei},
{"934000"	,	"zei"	,	PY_mb_zei},
{"936000"	,	"wen"	,	PY_mb_wen},
{"936000"	,	"zen"	,	PY_mb_zen},
{"936400"	,	"weng"	,	PY_mb_weng},
{"936400"	,	"zeng"	,	PY_mb_zeng},
{"940000"	,	"xi"	,	PY_mb_xi},
{"940000"	,	"yi"	,	PY_mb_yi},
{"940000"	,	"zi"	,	PY_mb_zi},
{"942000"	,	"xia"	,	PY_mb_xia},
{"942000"	,	"zha"	,	PY_mb_zha},
{"942400"	,	"zhai"	,	PY_mb_zhai},
{"942600"	,	"xian"	,	PY_mb_xiao},
{"942600"	,	"xiao"	,	PY_mb_xiao},
{"942600"	,	"zhan"	,	PY_mb_zhan},
{"942600"	,	"zhao"	,	PY_mb_zhao},
{"942640"	,	"xiang"	,	PY_mb_xiang},
{"942640"	,	"zhang"	,	PY_mb_zhang},
{"943000"	,	"xie"	,	PY_mb_xie},
{"943000"	,	"zhe"	,	PY_mb_zhe},
{"943600"	,	"zhen"	,	PY_mb_zhen},
{"943640"	,	"zheng"	,	PY_mb_zheng},
{"944000"	,	"zhi"	,	PY_mb_zhi},
{"946000"	,	"xin"	,	PY_mb_xin},
{"946000"	,	"yin"	,	PY_mb_yin},
{"946400"	,	"xing"	,	PY_mb_xing},
{"946400"	,	"ying"	,	PY_mb_ying},
{"946640"	,	"xiong"	,	PY_mb_xiong},
{"946640"	,	"zhong"	,	PY_mb_zhong},
{"946800"	,	"zhou"	,	PY_mb_zhou},
{"948000"	,	"xiu"	,	PY_mb_xiu},
{"948000"	,	"zhu"	,	PY_mb_zhu},
{"948200"	,	"zhua"	,	PY_mb_zhua},
{"948240"	,	"zhuai"	,	PY_mb_zhuai},
{"948260"	,	"zhuan"	,	PY_mb_zhuan},
{"948264"	,	"zhuang",	PY_mb_zhuang},
{"948400"	,	"zhui"	,	PY_mb_zhui},
{"948600"	,	"zhun"	,	PY_mb_zhun},
{"948600"	,	"zhuo"	,	PY_mb_zhuo},
{"960000"	,	"wo"	,	PY_mb_wo},
{"960000"	,	"yo"	,	PY_mb_yo},
{"966400"	,	"yong"	,	PY_mb_yong},
{"966400"	,	"zong"	,	PY_mb_zong},
{"968000"	,	"you"	,	PY_mb_you},
{"968000"	,	"zou"	,	PY_mb_zou},
{"980000"	,	"wu"	,	PY_mb_wu},
{"980000"	,	"xu"	,	PY_mb_xu},
{"980000"	,	"yu"	,	PY_mb_yu},
{"980000"	,	"zu"	,	PY_mb_zu},
{"982600"	,	"xuan"	,	PY_mb_xuan},
{"982600"	,	"yuan"	,	PY_mb_yuan},
{"982600"	,	"zuan"	,	PY_mb_zuan},
{"983000"	,	"xue"	,	PY_mb_xue},
{"983000"	,	"yue"	,	PY_mb_yue},
{"984000"	,	"zui"	,	PY_mb_zui},
{"986000"	,	"xun"	,	PY_mb_xun},
{"986000"	,	"yun"	,	PY_mb_yun},
{"986000"	,	"zun"	,	PY_mb_zun},
{"986000"	,	"zuo"	,	PY_mb_zuo},
};

//һ��������
short t9_local_index1[8]={1,	55,	87,	125,	181,	225,	304,	323};

//����������

short t9_local_index2[8][8]={
{2,		12,		17,		0,	43,		0,	49,		0,},
{56,	64,		69,		0,	75,		80,	81,		0,},
{87,	97,		0,		0,	105,	0,	109,	0,},
{125,	135,	141,	0,	159,	0,	163,	0,},
{182,	192,	200,	0,	215,	0,	218,	0,},
{225,	238,	247,	0,	283,	0,	289,	0,},
{304,	309,	311,	0,	316,	0,	318,	0,},
{323,	336,	344,	0,	377,	0,	383,	0,},
};

char ascii_tab[8][4]={
	{'a','b','c', 0 },
	{'d','e','f', 0 },
	{'g','h','i', 0 },
	{'j','k','l', 0 },
	{'m','n','o', 0 },
	{'p','q','r','s'},
	{'t','u','v', 0 },
	{'w','x','y','z'},
};

                      
//���뷨ת��
static void do_switch(t9_input_t*input)
{
	int i;
	for(i=0;i<6;i++)
	{
	  input->mb_index[i]=(t9PY_index*)0;
	  input->pinyin_buf[i]=-1;
	}
	input->pinyin_count=0;
	input->pinyin_selected=0;
	for(i=0;i<14;i++)
	{
	   input->show_buf[i]=0;
	}
	input->show_offset=0;

	switch(input->input_mode)
	{
	case macro_t9_mode_cn :
		input->input_mode=macro_t9_mode_len;break;
	case macro_t9_mode_len:
		input->input_mode=macro_t9_mode_uen;break;
	case macro_t9_mode_uen:
		input->input_mode=macro_t9_mode_num;break;
	case macro_t9_mode_num:
		input->input_mode=macro_t9_mode_cn;break;
	default:
		input->input_mode=macro_t9_mode_cn;break;
	}
}

static void update_struct(t9_input_t*input,short index_begin)
{
	short i;
	char*ptr;
	short count;
	for(i=0;i<6&&(i+index_begin)<397;i++)
	{
		input->mb_index[i]=&input->index[index_begin+i];
	}
	//i--;
	//�����Դ����Ϣ
	if(input->mb_index[input->pinyin_selected]!=(t9PY_index*)0)
	{
		ptr=input->mb_index[input->pinyin_selected]->PY_mb;
		count=pl_strlen(ptr);
		ptr+=input->show_offset; //ƫ����
		count=count-input->show_offset>12?12:count-input->show_offset;
        for(i=0;i<count;i++)
		{
			input->show_buf[i]=*ptr++;
		}
		for(;i<14;i++)
		{
			input->show_buf[i]=0;
		}
	}
}

/*static void update_showbuf(t9_input_t*input)
{
	short i;
	char*ptr;
	short count;
	if(input->mb_index[input->pinyin_selected]!=(t9PY_index*)0)
	{
		ptr=input->mb_index[input->pinyin_selected]->PY_mb;
		count=pl_strlen(ptr);
		ptr+=input->show_offset; //ƫ����
		count=count-input->show_offset>12?12:count-input->show_offset;
        for(i=0;i<count;i++)
		{
			input->show_buf[i]=*ptr++;
		}
		for(;i<14;i++)
		{
			input->show_buf[i]=0;
		}
	}
}*/

bool_t   t9_cn_searchhandler(t9_input_t*input)
{
	char  buf[7]={0,0,0,0,0,0,0};
	int   index_begin;
	int   i,j;
	int   count=0;

	for(i=0;i<6;i++)
	{
		if(input->pinyin_buf[i]>=0){
			buf[i]='2'+input->pinyin_buf[i];
			++count;
		}
		else{
			break;
		}
	}
	if(count>2) //�����������2ʱ��Ҫͨ���Ƚ��ַ����Ƿ������
	{
		index_begin=t9_local_index2[input->pinyin_buf[0]][input->pinyin_buf[1]]; //��ȡ��������ʼ��ַ
		for(i=2;i<count;i++)
		{
			for(j=index_begin;j<397;j++)
			{
				if(input->index[j].t9PY_T9[i]==buf[i]){
					index_begin=j;
					break;
					}
			}
			if(j>=397){
				for(j=i;j<6;j++)
				{
					input->pinyin_buf[j]=-1;//������Ķ����Ϊ�㡣
				}
				break;  //ĳ������ʧ��,����������Ѿ��������⣬�ʽ�����ĺ���
			}
		}//end for i=2;
		update_struct(input,index_begin);
		return _true;
	}//end if(count>2)
	else if(count==2)
	{
		if(t9_local_index2[input->pinyin_buf[0]][input->pinyin_buf[1]]!=0)
		{
			index_begin=t9_local_index2[input->pinyin_buf[0]][input->pinyin_buf[1]];

			update_struct(input,index_begin);

			return _true;
		}
		else
		{
			 input->pinyin_buf[1]=-1; //�������Ч����ȥ��
			 index_begin=t9_local_index1[input->pinyin_buf[0]];

			 update_struct(input,index_begin);
		     return _true;
		}
	}//end else if
	else if(count==1)
	{
        index_begin=t9_local_index1[input->pinyin_buf[0]];

		update_struct(input,index_begin);
		return _true;
	}
	//���������else if(count==0)���ô���
	return _false;//δ֪���룻
}

bool_t t9_cn_keyhandler (t9_input_t*input,short key_id)
{
   short temp;
   short i;
	switch(key_id)
	{
	  case macro_t9_key_0           :
		   return _false;
	  case macro_t9_key_1           :
		   return _false;

	  case macro_t9_key_2           :
	  case macro_t9_key_3           :
	  case macro_t9_key_4           :
	  case macro_t9_key_5           :
	  case macro_t9_key_6           :
	  case macro_t9_key_7           :
	  case macro_t9_key_8           :
	  case macro_t9_key_9           :
		   if(input->pinyin_count<6)//����û��
		   {
			  input->pinyin_buf[input->pinyin_count]=key_id-2;//key_id=2ʱ��������0��1��0λ��
			  input->pinyin_count++;
		   }
		   break;

	 case macro_t9_key_space       :
	      return _false;
	 case macro_t9_key_backspace   :
		 if(input->pinyin_count>0)
		 {
			input->pinyin_count--;
			input->pinyin_buf[input->pinyin_count]=-1;//ɾ��һ��ƴ��
			if(input->pinyin_count==0)//Ҫ��ɾ�������һ��ƴ��
			{
			   for(i=0;i<6;i++)
		      {
	             input->pinyin_buf[i]=-1;   //����Ϊ-1ʱ����Чֵ����Ϊ������Ϊ����ֵ(0-7)
		         input->mb_index[i]=(t9PY_index *)0;
		      }
		      for(i=0;i<12;i++)
		      {
			     input->show_buf[i]=0;
		      }
		      input->show_offset=0;
		      input->pinyin_count =0;  
		      input->pinyin_selected=0; //���½ṹ��Ϣ��׼���´ε�����
			}//end if(input->pinyin_count==0)
			
		 }
		 else
		 {    //ɾ��ʱҪ����Ҫɾ��ascii�뻹�Ǻ��֣���Ҫ�������Ƿ��Ѿ���
			 if(input->count>0){ //����ǿ�
				input->count--;
				if((unsigned char)input->buf[input->count]>0x7e){  //�ж��Ǻ��ֻ���ascii��,
                     input->buf[input->count]=0;    //����ɾ�������ֽ�
			         input->count--;
			         input->buf[input->count]=0; 
				}else{
					input->buf[input->count]=0;  //ascii��ɾ��һ���ֽ�
				}//end else 1
			 }//end if(input->count>0)
		 }//end else
		 //update_showbuf(input);//��������
		break;

	//case macro_t9_key_enter       :
	//	break;//�Ȳ���
	case macro_t9_key_exit        :
		break;//�Ȳ���
	case macro_t9_key_switch      : 
		do_switch(input);
		break;
	case macro_t9_key_pinyin0     :
	case macro_t9_key_pinyin1     :
	case macro_t9_key_pinyin2     :
	case macro_t9_key_pinyin3     :
	case macro_t9_key_pinyin4     :
	case macro_t9_key_pinyin5     :
		if(input->mb_index[key_id-15]!=(void*)0){  //��ѡ����һ���յ�ƴ��ʱ������
         input->pinyin_selected=key_id-15;
		 input->show_offset=0;//ƫ�����±�Ϊ0
		}
		 break;
	case macro_t9_key_show_forward:  //ǰ����ҳ��ѡ�е�ƴ���ĺ��ַ�����ʾ
	    input->show_offset+=12;
		if(input->mb_index[input->pinyin_selected]!=(void*)0){   //��ǰ��ѡ��ƴ��Ϊ��Чֵ
			 if((short)pl_strlen(input->mb_index[input->pinyin_selected]->PY_mb)<=input->show_offset){
				 input->show_offset-=12;                         //��ǰƫ�����Ƿ���������Чֵ��Χ��
			 }
		 }
		 break;
	case macro_t9_key_show_back   : //���˷�ҳ
         if(input->show_offset>0)  //input->show_offset==0ʱ�ڵ�һҳ
		 input->show_offset-=12;
		 break;
	case macro_t9_key_word0       :
	case macro_t9_key_word1       :
	case macro_t9_key_word2       :
	case macro_t9_key_word3       :
	case macro_t9_key_word4       :
	case macro_t9_key_word5       :  
		temp=key_id-23;//temp���ʱ��Ϊ��ǰ��ʾ��6����ѡ�����еĺ���
		temp<<=1;//temp��ƫ�Ʊ�Ϊ�ֽ�ƫ��
		if(input->show_buf[temp]!=0&&input->count<macro_t9_max_input_count)//���ѡ����Ч
		{
		  input->buf[input->count]=input->show_buf[temp];
		  input->count++;
          input->buf[input->count]=input->show_buf[temp+1];
		  input->count++;//count���ֽ�������temp����ƫ��
		  
		  for(i=0;i<6;i++)
		  {
	        input->pinyin_buf[i]=-1;   //����Ϊ-1ʱ����Чֵ����Ϊ������Ϊ����ֵ(0-7)
		    input->mb_index[i]=(t9PY_index *)0;
		  }
		  for(i=0;i<12;i++)
		  {
			  input->show_buf[i]=0;
		  }
		  input->show_offset=0;
		  input->pinyin_count =0;  
		  input->pinyin_selected=0; //���½ṹ��Ϣ��׼���´ε�����
		}

		break;
	default:return _false;
	}

	return _true;
}

bool_t t9_en_keyhandler (t9_input_t*input,short key_id)
{
   short i;
	switch(key_id)
	{
	  case macro_t9_key_0           :
	  case macro_t9_key_1           :
        if(input->input_mode==macro_t9_mode_num){
            if(input->count<macro_t9_max_input_count){
			   input->buf[input->count]=key_id+48;//ת����ascii��
			   input->count++;
			}
		}
		break;
	  case macro_t9_key_abc         : /*macro_t9_key_2*/
	  case macro_t9_key_def         : /*macro_t9_key_3*/
	  case macro_t9_key_ghi         : /*macro_t9_key_4*/ 
	  case macro_t9_key_jkl         : /*macro_t9_key_5*/ 
	  case macro_t9_key_mno         : /*macro_t9_key_6*/
	  case macro_t9_key_pqrs        : /*macro_t9_key_7*/
	  case macro_t9_key_tuv         : /*macro_t9_key_8*/
	  case macro_t9_key_wxyz        : /*macro_t9_key_9*/
		if(input->input_mode==macro_t9_mode_len){
			for(i=0;i<4;i++)
			{
				input->show_buf[i]=ascii_tab[key_id-2][i];//Сд��ĸ
			}

		}else if(input->input_mode==macro_t9_mode_uen){
			for(i=0;i<3;i++)
			{
				input->show_buf[i]=ascii_tab[key_id-2][i]-32;//��д��ĸ
			}
			if(ascii_tab[key_id-2][3]!=0){
				input->show_buf[3]=ascii_tab[key_id-2][3]-32;
			}else{
				input->show_buf[3]=0;
			}

		}else if(input->input_mode==macro_t9_mode_num)
		{
			if(input->count<macro_t9_max_input_count){
				input->buf[input->count]=key_id+48;//ת����ascii��
				input->count++;
			}
		}
		break;
	 case macro_t9_key_space       :
	      return _false;
	 case macro_t9_key_backspace   :
			 if(input->count>0)
			 { //����ǿ�
				input->count--;
				if((unsigned char)input->buf[input->count]>0x7e){  //�ж��Ǻ��ֻ���ascii��,
                     input->buf[input->count]=0;    //����ɾ�������ֽ�
			         input->count--;
			         input->buf[input->count]=0; 
				}else{
					input->buf[input->count]=0;  //ascii��ɾ��һ���ֽ�
				}//end else 1
			 }//end if(input->count>0)
		break;

	case macro_t9_key_enter       :
		break;//�Ȳ���
	case macro_t9_key_exit        :
		break;//�Ȳ���
	case macro_t9_key_switch      :
		do_switch(input);
		break;//�Ȳ���
	case macro_t9_key_pinyin0     :
	case macro_t9_key_pinyin1     :
	case macro_t9_key_pinyin2     :
	case macro_t9_key_pinyin3     :
		if(input->input_mode==macro_t9_mode_len||
		   input->input_mode==macro_t9_mode_uen)
		{
		   if(input->show_buf[key_id-15]>0&&\
		      input->count<macro_t9_max_input_count){
		      input->buf[input->count]=input->show_buf[key_id-15]; 
		      input->count++;
		   }
		}
		break;  
	default:return _false;
	}
	return _true;
}




void t9_initialize(t9_input_t*input,t9PY_index*index)
{
	int i;
	for(i=0;i<macro_t9_max_input_count;i++)
	{
		input->buf[i]=0;
	}
	input->count=0;
	input->index=index;
	input->input_mode=macro_t9_mode_cn;
	for(i=0;i<6;i++)
	{
	  input->mb_index[i]=(t9PY_index*)0;
	  input->pinyin_buf[i]=-1;
	}
	input->pinyin_count=0;
	input->pinyin_selected=0;
	for(i=0;i<14;i++)
	{
	   input->show_buf[i]=0;
	}
	input->show_offset=0;
}







