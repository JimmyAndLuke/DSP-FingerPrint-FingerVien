/******************************************************************************
 * �ļ�����sys_global.c
 * ���ܣ�  һЩϵͳ��ȫ�ֱ����Ͳ���
******************************************************************************/


#include "sys_header/sys_user.h"

//��ȡ���ݿ��ָ��
//static database_t*sys_get_database(void);
static void sys_db_clear_unit(uint32_t id   );  //����һ�����ݵ�Ԫ
//static sys_db_write_unit(uint32_t id,void*buf);//дһ�����ݵ�Ԫ
static void sys_lock_db  (void);
static void sys_unlock_db(void);
static void sys_set_id_map(uint32_t id);
static void sys_clear_id_map(uint32_t id);
static database_t dynamic_db;

inline static void sys_lock_db(void)
{
	extern far LCK_Obj flash_lock;
	
	LCK_pend(&flash_lock,SYS_FOREVER);
}

inline static void sys_unlock_db(void)
{
	extern far LCK_Obj flash_lock;
	
	LCK_post(&flash_lock);
}

 database_t*sys_get_database(void)
{
	return &dynamic_db;
}


void sys_db_clear_unit(uint32_t id)
{
	uint32_t page_addr;
	
//	sys_lock_db();

	flash_select_page(2);

    //�û�ID��ת��Ϊflash�е�ҳƫ�Ƶ�ַ
	//page_addr=id*4096+0x64000000;
	page_addr=id*8192+0x64000000;

	flash_erase_sector(page_addr);

	_delay_ms(18);

	//sys_unlock_db();
}


 void sys_db_write_unit(uint32_t id,void*buf)
{
	uint32_t page_addr;
	uint16_t *pBuf1 = (uint16_t *)(buf);
	uint16_t *pBuf2 = pBuf1 + 2048;

	flash_select_page(2);

	//�û�ID��ת��Ϊflash�е�ҳƫ�Ƶ�ַ
	//page_addr=id*4096+0x64000000;
	page_addr=id*8192+0x64000000;

    flash_erase_sector(page_addr);
	flash_erase_sector(page_addr+4096);
    _delay_ms(20);
	flash_write_sector(page_addr, buf);
	flash_write_sector(page_addr+4096, pBuf2);
}

static void sys_set_id_map(uint32_t id)
{
	uint32_t rows;
	uint32_t cols;

	database_t*db;
	db=sys_get_database();

	//16*32 = 512 = 1MWord/2KWord
	rows=id>>5;//id����32
	cols=id&0x0000001f;//��32ȡ����
	
	db->id_map[rows]|=(1<<cols);
}

static void sys_clear_id_map(uint32_t id)
{
	uint32_t rows;
	uint32_t cols;
    uint32_t tmp;

	database_t*db;
	db=sys_get_database();

	rows=id>>5;//id����32
	cols=id&0x0000001f;//��32ȡ����
	
	tmp=~(1<<cols);
	db->id_map[rows]&=tmp;
}


void sys_database_init(void)
{
	uint32_t    i;
	database_t *db;
	user_t     *user;
	uint32_t   *ptrs;
	uint32_t   *ptrd;

	db=sys_get_database();

	db->start_addr    =0x64000000;
	//db->unit_size     =4096;
	db->unit_size     =8192;
	db->all_cnt       =0;
	db->admin_cnt     =0;
	db->user_cnt       =0;
	db->dynamic_start_addr=0x80A00000; //����ҳ
	db->list_head     =(user_t*)0;
	db->list_current  =(user_t*)0;
    db->list_tail     =(user_t*)0;
    //for(i=0;i<16;i++){
	for(i=0;i<8;i++){
		db->id_map[i]=0;
	}

	//ɾ��ID������
	//sys_db_clear_unit(2);

	flash_select_page(2);

	ptrs=(uint32_t*)db->start_addr;
	ptrd=(uint32_t*)db->dynamic_start_addr;

	//1ҳ��Ϊ1M word  = 2M byte,ÿ�θ���32bit,��/4
	for(i=0;i<(0x00200000/4);i++)
	{
		*ptrd++=*ptrs++;
	}

	//for(i=0;i<512;i++){
	for(i=0;i<256;i++){
		//user=(user_t*)(db->dynamic_start_addr+i*4096);
		user=(user_t*)(db->dynamic_start_addr+i*8192);

		/*�Ƿ�ID���Թ�*/
		//if(user->id>=512){
		if(user->id>=256){
			continue;
		}

		//��һ���û�
		if(db->list_head==(user_t*)0){
			
			sys_set_id_map(user->id);

			db->list_current=user;
			db->list_head   =user;
			db->list_tail   =user;
			user->pre       =(user_t*)0;
			user->next      =(user_t*)0;
			db->all_cnt++;
			if(user->attribute==macro_db_administrator){
			    db->admin_cnt++;
			}else{
				db->user_cnt++;
			}
			continue;
		}

		//�ڶ������ϵ��û�
		sys_set_id_map(user->id);
		user->pre=db->list_current;
		db->list_current->next=user;
		user->next=(user_t*)0;
		db->list_current=user;
		db->list_tail=user;
        db->all_cnt++;
		if(user->attribute==macro_db_administrator){
			db->admin_cnt++;
		}else{
			db->user_cnt++;
		}
		
	}//end for ( i=0...
}

void sys_database_init0(void)
{
	uint32_t    i;
	database_t *db;
	//user_t     *user;
	//uint32_t   *ptrs;
	//uint32_t   *ptrd;

	db=sys_get_database();

	db->start_addr    =0x64000000;
	//db->unit_size     =4096;
	db->unit_size     =8192;
	db->all_cnt       =0;
	db->admin_cnt     =0;
	db->user_cnt       =0;
	db->dynamic_start_addr=0x80A00000; //����ҳ
	db->list_head     =(user_t*)0;
	db->list_current  =(user_t*)0;
    db->list_tail     =(user_t*)0;
    //for(i=0;i<16;i++){
	 for(i=0;i<8;i++){
		db->id_map[i]=0;
	}

	//flash_select_page(2);

	//ptrs=(uint32_t*)db->start_addr;
	//ptrd=(uint32_t*)db->dynamic_start_addr;

	////1ҳ��Ϊ1M word  = 2M byte,ÿ�θ���32bit,��/4
	//for(i=0;i<(0x00200000/4);i++)
	//{
	//	*ptrd++=*ptrs++;
	//}

	//for(i=0;i<512;i++){
	//	user=(user_t*)(db->dynamic_start_addr+i*4096);

	//	/*�Ƿ�ID���Թ�*/
	//	if(user->id>=512){
	//		continue;
	//	}

	//	//��һ���û�
	//	if(db->list_head==(user_t*)0){
	//		
	//		sys_set_id_map(user->id);

	//		db->list_current=user;
	//		db->list_head   =user;
	//		db->list_tail   =user;
	//		user->pre       =(user_t*)0;
	//		user->next      =(user_t*)0;
	//		db->all_cnt++;
	//		if(user->attribute==macro_db_administrator){
	//		    db->admin_cnt++;
	//		}else{
	//			db->user_cnt++;
	//		}
	//		continue;
	//	}

	//	//�ڶ������ϵ��û�
	//	sys_set_id_map(user->id);
	//	user->pre=db->list_current;
	//	db->list_current->next=user;
	//	user->next=(user_t*)0;
	//	db->list_current=user;
	//	db->list_tail=user;
 //       db->all_cnt++;
	//	if(user->attribute==macro_db_administrator){
	//		db->admin_cnt++;
	//	}else{
	//		db->user_cnt++;
	//	}
	//	
	//}//end for ( i=0...
}


//�������ֻ�Ǽ򵥵ؽ�����û����ӵ��û����б����棬Ȼ����µ�flash��
bool_t  sys_database_add (user_t*user)
{
	database_t*db;
	
	sys_lock_db();

	db=sys_get_database();

	user->pre=db->list_tail;
	
	user->next=(user_t*)0;
	
	db->list_tail->next=user;

	db->list_tail=user;

	//���µ�flash��
	sys_db_write_unit(user->id,user);

    if(user->attribute==macro_db_administrator){
       db->admin_cnt++;
    }else{
       db->user_cnt++;
    }
    
    db->all_cnt++;

	sys_unlock_db();

	return _true;
}

/*�������ֻ�Ǽ򵥵ؽ�һ���û���SDRAM��ɾ����Ȼ���ɾ��FLASH�еĴ洢*/
bool_t  sys_database_delete  (user_t*user)
{
	database_t *db;

	sys_lock_db();

	db=sys_get_database();

	//ϵͳ���뱣������һ���û�
	/*if( (db->all_cnt<=1 ) || ( db->list_head==user ) ){
		return _false;
	}*/
	
	if( db->all_cnt<=1 ){
	    return _false;
	}
	
	///*���������1.�ڶ���β����2.�ڶ����м䡣3.����ͷ��*/
	if( db->list_head==user){
	
      db->list_head=db->list_head->next;
      db->list_head->pre=(user_t*)0;
      
    }else if(db->list_tail==user){
        //1Ҫɾ�����û���β��ʱ
		db->list_tail=db->list_tail->pre;
		db->list_tail->next=(user_t*)0;
	}else{
		user->pre->next = user->next; 		
		user->next->pre = user->pre;
	}

//�����û�����
   	if(user->attribute==macro_db_administrator){
       db->admin_cnt--;
    }else{
       db->user_cnt--;
    }
    
    db->all_cnt--;
    
	sys_db_clear_unit(user->id);

	//�����û���Ϊ����
	user->id=0xffffffff;
	
	sys_unlock_db();

	return _true;
}



user_t* sys_database_get_next(void       )
{
	database_t *db;

	db=sys_get_database();

	if(db->all_cnt<=1){

		return (user_t*)0;

	}else if(db->list_current==db->list_tail){

		db->list_current=db->list_head;
		return (user_t*)0;

	}else{

		db->list_current=db->list_current->next;
		return db->list_current;

	}//end else {
}


user_t* sys_database_get_pre (void       )
{
	database_t*db;

	db=sys_get_database();

	if(db->all_cnt<=1){
		return (user_t*)0;

	}else if( db->list_current==db->list_head ){

		db->list_current=db->list_tail;
		return (user_t*)0;

	}else{
		db->list_current=db->list_current->pre;
		return db->list_current;
	}//end else {
}


user_t* sys_database_get_head(void       )
{
	database_t*db;

	db=sys_get_database();

	return db->list_head;
}

user_t* sys_database_get_tail(void       )
{
	database_t*db;

	db=sys_get_database();

	return db->list_tail;
}


void    sys_database_go_to_head(void)
{
	database_t*db;

	db=sys_get_database();

	db->list_current=db->list_head;
}

void    sys_database_go_to_tail(void)
{
	database_t*db;

	db=sys_get_database();

	db->list_current=db->list_tail;
}

uint32_t sys_database_malloc_id  (void       )
{
	uint32_t i,j;
	database_t*db;
	uint32_t id;

	id=0xffffffff;

	db=sys_get_database();

	//for(i=0;i<16;i++)
	for (i = 0; i < 8; i++)
	{
		if(db->id_map[i]!=0xffffffff){
            for(j=0;j<32;j++){
				if(( db->id_map[i] & (1<<j) )==0){
					db->id_map[i]|=(1<<j);
					id=i*32+j;
					return id;
				}//end if ( (db->id_map...
			}//end for ( j=0...
		}//end if ( db->id...
	}//end for ( i=0...
	return id;
}

void  sys_database_free_id (uint32_t id)
{
	sys_clear_id_map(id);
}

user_t*  sys_database_malloc_user(uint32_t id)
{
	database_t*db;

	user_t*user;

	db=sys_get_database();

	//user=(user_t*)(db->dynamic_start_addr+id*4096);
	user=(user_t*)(db->dynamic_start_addr+id*8096);

	return user;	
}



/*userָ������ݽṹ����SDRAM�û���Ϣ�Ķ����У������ȿ�����������*/
bool_t sys_user_register(user_t*user)
{
	uint32_t*ptrs;
	uint32_t*ptrd;
    uint32_t id;
    uint32_t i;

	//��Ϊ���û�����һ��id��
	id=sys_database_malloc_id();
	//id = 0x0;
	if(id==0xffffffff){
		return _false;
	}

	//��ȡ��id�ŵ��ڴ�ָ��
	ptrd=(uint32_t*)sys_database_malloc_user(id);
	ptrs=(uint32_t*)user;
   
   user->id=id;
   //������user�����ݱ���Ҫȫ����ʼ����
   //��������
	//for(i=0;i<1024;i++){
   for(i=0;i<2048;i++){
		*ptrd++=*ptrs++;
	}
    //�������ݵ����ݿ�
    //ptrd-=1024;
	ptrd-=2048;
	return sys_database_add((user_t*)ptrd);
}


/*ע��һ���û�����Ϣ*/
bool_t sys_user_unregister(user_t*user)
{
    sys_database_free_id(user->id);
	return sys_database_delete(user);
}

/*����Ƿ�����ͨ�û�*/
bool_t sys_is_normal_user(user_t*user)
{
	if(user->attribute==macro_db_normal_user){
		return _true;
	}else{
		return _false;
	}
}
/*���һ���û��Ƿ��ǹ���Ա*/
bool_t sys_is_administrator(user_t*user)
{
	if(user->attribute==macro_db_administrator){
		return _true;
	}
	else{
		return _false;
	}
}


