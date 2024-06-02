#ifndef SRC_BOOTLOADER_H_
#define SRC_BOOTLOADER_H_

#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "crc.h"
#include "stm32f103xb.h"

#define Buffer_Length    200

//User Options
#define CBL_GET_VER            0x10
#define CBL_GET_HELP           0x11
#define CBL_GET_CID            0x12
#define CBL_GOTO_ADDR          0x14
#define CBL_FLASH_ERASE        0x15
#define CBL_MEM_WRITE          0x16


//CRC Status
#define CRC_VERIFIED           0x01
#define CRC_FAILED             0x00


//Acknowledge Status
#define SEND_ACK               0xAB
#define SEND_notACK            0xCD

//Bootloader Version
#define BL_VENDOR_ID           100
#define BL_MAJOR_VERSION       1
#define BL_MINOR_VERSION       1
#define BL_PATCH_VERSION       0

//Erase Status
#define INVALID_PAGE_NUMBER    0x00
#define VALID_PAGE_NUMBER      0x01
#define UNSUCCESSFUL_ERASE     0x02
#define SUCCESSFUL_ERASE       0x03
#define HAL_SUCCESSFUL_ERASE   0xFFFFFFFU

//Flash Macros
#define MAX_FLASH_PAGE_NUMBER  16
#define FLASH_MASS_ERASE       0xFF

//Address Verification
#define STM32_SRAM_SIZE        (20 * 1024)
#define STM32_FLASH_SIZE       (64 * 1024)
#define STM32_SRAM_END         (SRAM_BASE + STM32_SRAM_SIZE)
#define STM32_FLASH_END        (FLASH_BASE + STM32_FLASH_SIZE)

#define INVALID_ADDRESS          0x00
#define VALID_ADDRESS            0x01

//Payload Write
#define Flash_Payload_Write_Failed     0x00
#define Flash_Payload_Write_Done       0x01

typedef enum{
	BL_notACK = 0,
	BL_ACK
}BL_Status_t;

BL_Status_t BL_FetchCommand();
void BL_SendMessage(char *format,...);



#endif /* SRC_BOOTLOADER_H_ */
