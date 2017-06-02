
#include "bsp_header\z_flash.h"


/****************************************************************************
* ��    �ƣ�flash_select_page(uint8_t page_num)
* ��    �ܣ�flashѡҳ
* ��ڲ�����page_num		ҳ�� 0--3
* ���ڲ�������
* ˵    �������CPLD
* ���÷�����flash_select_page(1) ;
****************************************************************************/
void flash_select_page(uint8_t page_num)
{
    switch(page_num)
    {
       case 0: FLASH_PAGE_0 ; break ;
       case 1: FLASH_PAGE_1 ; break ;
       case 2: FLASH_PAGE_2 ; break ;
       case 3: FLASH_PAGE_3 ; break ;
       default:FLASH_PAGE_1 ; break ;
    }
}
/****************************************************************************
* ��    �ƣ�lash_init(void)
* ��    �ܣ�flash��ʼ�� ѡ�е�һҳ ����0ҳ���ڹ̻�������ֿ⣩
* ��ڲ�������
* ���ڲ�������
* ˵    �������CPLD
* ���÷�����flash_init(void);
****************************************************************************/
void flash_init(void)
{
    //Ĭ��ѡ�е�һҳ���ݡ�
    flash_select_page(1);
}
/****************************************************************************
* ��    �ƣ�int32_t flash_polling_check(uint32_t addr)
* ��    �ܣ�flash��ѯ��æ
* ��ڲ�����addr		��ַ
* ���ڲ�������
* ˵    ����
* ���÷�����if (flash_polling_check(sector_addr));
****************************************************************************/
static int32_t flash_polling_check(uint32_t addr)
{
	uint16_t CurrData;
	uint32_t TimeOut = 0;

	while (TimeOut < FLASH_TIMEOUT)	//MAX_TIMEOUT=0x07FFFFFF
	{
		CurrData = *(volatile uint16_t *)(addr);
		CurrData = CurrData & 0x0080;//read DQ7
		if (CurrData == 0x0080)
		{
			return TRUE;
		}
		TimeOut++;
	}
	return FALSE;
}
/****************************************************************************
* ��    �ƣ�flash_reset_chip(void)
* ��    �ܣ�ID Exit\CFI Exit\Sec ID Exit
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����flash_reset_chip();
****************************************************************************/
void  flash_reset_chip(void)
{
	*sysAddress(0x555) = 0x00AA;  // write data 0x00AA to device addr 0x555
    *sysAddress(0x2AA) = 0x0055;  // write data 0x0055 to device addr 0x2AA
    *sysAddress(0x555) = 0x00F0;  // write data 0x00F0 to device addr 0x555
}
/****************************************************************************
* ��    �ƣ�flash_check_chip(void)
* ��    �ܣ���ȡID���ж��Ƿ�����
* ��ڲ�������
* ���ڲ�����TRUE  or  FALSE
* ˵    ����
* ���÷�����if(flash_check_chip());
****************************************************************************/
int32_t flash_check_chip(void)
{
	uint16_t id1 = 0;  //SST Manufacturer's ID code
	uint16_t id2 = 0;  //SST39VF6401B device code
	
    //Issue the Software Product ID code to 39VF640XB
    *sysAddress(0x555) = 0x00AA;  // write data 0x00AA to device addr 0x555
    *sysAddress(0x2AA) = 0x0055;  // write data 0x0055 to device addr 0x2AA
    *sysAddress(0x555) = 0x0090;  // write data 0x0090 to device addr 0x555
	//Tida Max 150ns for SST39VF6401B
    _delay_us(1);
	id1 = *sysAddress(0x0000);
	id2 = *sysAddress(0x0001);
    //Returning the SST39VF640X to the normal operation.
	flash_reset_chip();

	if ((id1==0x00BF) && (id2==0x236D))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* ��    �ƣ�flash_erase_sector(uint32_t sector_addr)
* ��    �ܣ��β���
* ��ڲ�����sector_addr  �ε�ַ ���ڶ��ڵ��κε�ַ
* ���ڲ�����TRUE  or  FALSE
* ˵    ����sector_addr ��СΪ FLASH_BASE_ADDR	:0x64000000
*           ��ĳ���ε�ַ��Χ��ʱ�����ö�
*			�ڵ��øú���֮ǰһ��Ҫ��ѡ��ҳ��
* ���÷�����flash_erase_sector(0x64000000);
****************************************************************************/
int32_t flash_erase_sector(uint32_t sector_addr)
{
	int32_t  i;
	//get the start address of the sector
	sector_addr &= 0xFFFFF800;
	//Issue the Sector Erase command to 39VF640X
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0080;     // write data 0x0080 to device addr 0x555
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	//write data 0x0050 to device sector addr
	*(volatile uint16_t *)sector_addr = 0x0050;

	if (flash_polling_check(sector_addr))
	{	//check sector erase succeed or not
		for (i = 0; i < FLASH_SECTOR_SIZE; i += 2)
		{
			if (*(volatile uint16_t *)(sector_addr + i) != 0xFFFF)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* ��    �ƣ�flash_erase_block(uint32_t block_addr)
* ��    �ܣ������
* ��ڲ�����block_addr  ���ַ ���ڿ��ڵ��κε�ַ
* ���ڲ�����TRUE  or  FALSE
* ˵    ����sector_addr ��СΪ FLASH_BASE_ADDR	:0x64000000
*           ��ĳ�����ַ��Χ��ʱ�����ö�
* ���÷�����flash_erase_block(0x64000000);
****************************************************************************/
int32_t flash_erase_block(uint32_t block_addr)
{
	int32_t  i;
	//get the start address of the block
	block_addr &= 0xFFFF8000;
	//Issue the Block Erase command to 39VF640X
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0080;     // write data 0x0080 to device addr 0x555
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	//write data 0x0030 to device block addr
	*(volatile uint16_t *)block_addr = 0x0030;

	if (flash_polling_check(block_addr))
	{	//check block erase succeed or not
		for (i = 0; i < FLASH_BLOCK_SIZE; i += 2)
		{
			if (*(volatile uint16_t *)(block_addr + i) != 0xFFFF)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* ��    �ƣ�flash_erase_chip(void)
* ��    �ܣ�Ƭ����
* ��ڲ�������
* ���ڲ�����TRUE  or  FALSE
* ˵    ����
* ���÷�����flash_erase_chip();
****************************************************************************/
int32_t flash_erase_chip(void)
{
	//Issue the Chip Erase command to 39VF640X
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0080;     // write data 0x0080 to device addr 0x555
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0010;     // write data 0x0010 to device addr 0x555

	if (flash_polling_check(0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* ��    �ƣ�flash_write_word(uint32_t addr, uint16_t data)
* ��    �ܣ���flash��ַдһ���֣�16bit
* ��ڲ�����addr		��ַ
*          data		����
* ���ڲ�����TRUE  or  FALSE
* ˵    ����
* ���÷�����flash_write_word(0x64000000, 0x5555);
****************************************************************************/
int32_t flash_write_word(uint32_t addr, uint16_t data)
{
    uint32_t TimeOut = 0;
	addr &= 0xFFFFFFFE;
	
    *sysAddress(0x555) = 0x00AA; // write data 0x00AA to device addr 0x555
    *sysAddress(0x2AA) = 0x0055; // write data 0x0055 to device addr 0x2AA
    *sysAddress(0x555) = 0x00A0; // write data 0x00A0 to device addr 0x555
	// transfer the WORD to destination
	*(volatile uint16_t *)addr = data;

    while (*(volatile uint16_t *)addr != data)
	{
		if (++TimeOut > FLASH_TIMEOUT)
		{
		    return FALSE;
		}
	}
	return TRUE;
}
/****************************************************************************
* ��    �ƣ�flash_write_sector(uint32_t addr ,uint16_t *pSrc)
* ��    �ܣ���flash��ַдһ���Σ�4K Bytes
* ��ڲ�����addr		��ַ
*          *pSrc	�����׵�ַ
* ���ڲ�����TRUE  or  FALSE
* ˵    ����
* ���÷�����flash_write_sector(0x64000000, (uint16_t*)gImage_pic);
****************************************************************************/
int32_t flash_write_sector(uint32_t addr ,uint16_t *pSrc)
{
	uint32_t i;
    uint16_t *pBuf = pSrc;
	addr &= 0xFFFFF800;
	
	for (i = 0; i < FLASH_SECTOR_SIZE; i ++)
	{
		if (flash_write_word(addr + i*2, *pBuf))
		{
		   pBuf++;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;  
}
/****************************************************************************
* ��    �ƣ�flash_write_block(uint32_t addr,uint16_t *pSrc)
* ��    �ܣ���flash��ַдһ���Σ�64K Bytes
* ��ڲ�����addr		��ַ
*          *pSrc	�����׵�ַ
* ���ڲ�����TRUE  or  FALSE
* ˵    ����
* ���÷�����flash_write_block(0x64000000, (uint16_t*)gImage_pic);
****************************************************************************/
int32_t flash_write_block(uint32_t addr,uint16_t *pSrc)
{
	uint32_t i;
    uint16_t *pBuf = pSrc;
	addr &= 0xFFFF8000;
	
	for (i = 0; i < FLASH_BLOCK_SIZE; i++)
	{
		if (flash_write_word(addr + i*2, *pBuf))
		{
		   pBuf++;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE; 
}
/****************************************************************************
* ��    �ƣ�flash_read_byte(uint32_t addr)
* ��    �ܣ���flash��ַ��ȡһ���ֽ�
* ��ڲ�����addr		��ַ
* ���ڲ�����
* ˵    ����
* ���÷�����
****************************************************************************/
uint8_t flash_read_byte(uint32_t addr)
{
	return (*(volatile uint8_t *)addr);
}
/****************************************************************************
* ��    �ƣ�flash_read_word(uint32_t addr)
* ��    �ܣ���flash��ַ��ȡһ����
* ��ڲ�����addr		��ַ
* ���ڲ�����
* ˵    ����
* ���÷�����
****************************************************************************/
uint16_t flash_read_word(uint32_t addr)
{
	addr &= 0xFFFFFFFE;
	return (*(volatile uint16_t *)addr);
}











