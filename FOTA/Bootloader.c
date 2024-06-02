#include "Bootloader.h"


/******************Help Functions**************************************/
static uint32_t CRC_Verify(uint8_t* pdata, uint32_t DataLength, uint32_t HostCRC);
static void Send_ACK(uint8_t dataLen);
static void Send_notACK();
static uint8_t Perform_Flash_Erase(uint32_t PageAdress, uint32_t PageNumber);
static uint8_t Address_Verification(uint32_t Address);
static uint8_t Flash_Payload_Write(uint16_t* pdata, uint32_t startAddress, uint8_t lengthOfPayload);
/**********************************************************************/

/*****************APIs************************************************/
static void Get_Version(uint8_t *Received_Buffer);
static void Get_Help(uint8_t *Received_Buffer);
static void Get_Chip_ID(uint8_t *Received_Buffer);
static void Erase_Flash(uint8_t *Received_Buffer);
static void Write_Data(uint8_t *Received_Buffer);
/********************************************************************/
static uint8_t Received_Buffer[Buffer_Length];

BL_Status_t BL_FetchCommand()
{
	BL_Status_t status = BL_notACK;
	HAL_StatusTypeDef HalStatus = HAL_ERROR;
	uint8_t DataLength = 0;
	HalStatus = HAL_UART_Receive(&huart2, Received_Buffer,1, HAL_MAX_DELAY);

	if(HalStatus != HAL_OK){
		status = BL_notACK;
	}else{
		DataLength = Received_Buffer[0];
		HalStatus = HAL_UART_Receive(&huart2, Received_Buffer, DataLength, HAL_MAX_DELAY);
	}
	if(HalStatus != HAL_OK){
			status = BL_notACK;
	}else{
		switch(Received_Buffer[1]){
		case CBL_GET_VER:     Get_Version(Received_Buffer); break;
		case CBL_GET_HELP:    Get_Help(Received_Buffer); break;
		case CBL_GET_CID:     Get_Chip_ID(Received_Buffer);   break;
		case CBL_GOTO_ADDR:   BL_SendMessage("Read the desired add. of bootloader"); break;
		case CBL_FLASH_ERASE: Erase_Flash(Received_Buffer); break;
		case CBL_MEM_WRITE:   Write_Data(Received_Buffer); break;

		default : status = BL_notACK;

		}

	}
	return status;

}

void BL_SendMessage(char *format,...)
{
	char message[100] = {0};
	va_list args;
	va_start(args,format);
	vsprintf(message,format,args);
	HAL_UART_Transmit(&huart2, (uint8_t*)message, sizeof(message), HAL_MAX_DELAY);
}

static uint32_t CRC_Verify(uint8_t* pdata, uint32_t DataLength, uint32_t HostCRC)
{
	  uint32_t CRC_Status = CRC_FAILED;
	  uint32_t MCU_CRC = 0;
	  uint32_t DataBuffer = 0;
	  for(uint8_t count = 0; count<DataLength; count++){
		  DataBuffer = (uint32_t)pdata[count];
		  MCU_CRC = HAL_CRC_Accumulate(&hcrc, &DataBuffer, 1);
	  }
	  _HAL_CRC_DR_RESET(&hcrc);
	  if(HostCRC == MCU_CRC){
		  CRC_Status = CRC_VERIFIED;
	  }else{
		  CRC_Status = CRC_FAILED;
	  }
	  return CRC_Status;
}

static void Send_ACK(uint8_t dataLen)
{
	uint8_t ACK_Value[2] = {0};
	ACK_Value[0] = Send_ACK;
	ACK_Value[1] =dataLen;
	HAL_UART_Transmit(&huart2, (uint8_t*)ACK_Value, 2, HAL_MAX_DELAY);

}
static void Send_notACK()
{
	uint8_t ACK_Value = Send_notACK;
	HAL_UART_Transmit(&huart2, &ACK_Value, sizeof(ACK_Value), HAL_MAX_DELAY);
}

static void Get_Version(uint8_t *Received_Buffer)
{
	uint8_t Version[4] = {BL_VENDOR_ID,BL_MAJOR_VERSION,BL_MINOR_VERSION,BL_PATCH_VERSION};
	uint16_t ReceivedPacketLength = 0;
	uint32_t CRC_Value = 0;
	ReceivedPacketLength = Received_Buffer[0] + 1;
	CRC_Value = *(uint32_t*)(Received_Buffer + ReceivedPacketLength -4);
	if(CRC_VERIFIED == CRC_Verify(((uint8_t*)&Received_Buffer[0]), ReceivedPacketLength-4, CRC_Value)){
		Send_ACK(4);
		HAL_UART_Transmit(&huart2, (uint8_t*)Version, 4, HAL_MAX_DELAY);

	}else{
		Send_notACK();
	}

}

static void Get_Help(uint8_t *Received_Buffer)
{
	uint8_t Supported_cmds[6] = {
			CBL_GET_VER,
			CBL_GET_HELP,
            CBL_GET_CID,
            CBL_GOTO_ADDR,
            CBL_FLASH_ERASE,
            CBL_MEM_WRITE
	};
    uint16_t ReceivedPacketLength = 0;
	uint32_t CRC_Value = 0;
	ReceivedPacketLength = Received_Buffer[0] + 1;
	CRC_Value = *(uint32_t*)(Received_Buffer + ReceivedPacketLength -4);
	if(CRC_VERIFIED == CRC_Verify(((uint8_t*)&Received_Buffer[0]), ReceivedPacketLength-4, CRC_Value)){
		Send_ACK(6);
		HAL_UART_Transmit(&huart2, (uint8_t*)Supported_cmds, 6, HAL_MAX_DELAY);

	}else{
		Send_notACK();
	}
}

static void Get_Chip_ID(uint8_t *Received_Buffer)
{
	uint16_t Chip_ID = 0;
	uint16_t ReceivedPacketLength = 0;
	uint32_t CRC_Value = 0;
	ReceivedPacketLength = Received_Buffer[0] + 1;
	CRC_Value = *(uint32_t*)(Received_Buffer + ReceivedPacketLength -4);
	if(CRC_VERIFIED == CRC_Verify(((uint8_t*)&Received_Buffer[0]), ReceivedPacketLength-4, CRC_Value)){
		Chip_ID = (uint16_t)(DBGMCU->IDCODE & 0x00000FFF);       //To read bits from 0-11
		Send_ACK(2);
		HAL_UART_Transmit(&huart2, (uint8_t*)&Chip_ID, 2, HAL_MAX_DELAY);

	}else{
		Send_notACK();
	}
}

static void Erase_Flash(uint8_t *Received_Buffer)
{
	uint8_t Erase_Status = UNSUCCESSFUL_ERASE;
	uint16_t ReceivedPacketLength = 0;
	uint32_t CRC_Value = 0;
	ReceivedPacketLength = Received_Buffer[0] + 1;
	CRC_Value = *(uint32_t*)(Received_Buffer + ReceivedPacketLength -4);
	if(CRC_VERIFIED == CRC_Verify(((uint8_t*)&Received_Buffer[0]), ReceivedPacketLength-4, CRC_Value)){

		Erase_Status = Perform_Flash_Erase((*(uint32_t*)&Received_Buffer[7]), Received_Buffer[6]);
		Send_ACK(1);
		HAL_UART_Transmit(&huart2, (uint8_t*)&Erase_Status, 1, HAL_MAX_DELAY);

	}else{
		Send_notACK();
	}
}

static uint8_t Perform_Flash_Erase(uint32_t PageAddress, uint32_t PageNumber)
{
	FLASH_EraseInitTypeDef pEraseInit;
	uint32_t PageError = 0;
	HAL_StatusTypeDef HAL_STATUS = HAL_ERROR;
	uint8_t PageStatus = INVALID_PAGE_NUMBER;
	if(PageNumber > MAX_FLASH_PAGE_NUMBER){
		PageStatus = INVALID_PAGE_NUMBER;
	}else{
		PageStatus = VALID_PAGE_NUMBER;
		if(PageNumber <= MAX_FLASH_PAGE_NUMBER || PageAddress == FLASH_MASS_ERASE){
			if(PageAddress == FLASH_MASS_ERASE){
				pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
				pEraseInit.Banks = FLASH_BANK_1;
				pEraseInit.PageAddress = 0x8008000;
				pEraseInit.NbPages = 12;
			}else{
				pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
				pEraseInit.Banks = FLASH_BANK_1;
				pEraseInit.PageAddress = PageAddress;
				pEraseInit.NbPages = PageNumber;

			}
			HAL_FLASH_Unlock();
			HAL_STATUS = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
			HAL_FLASH_Lock();
			if(HAL_STATUS == HAL_SUCCESSFUL_ERASE){
				PageStatus = SUCCESSFUL_ERASE;
			}else{
				PageStatus = UNSUCCESSFUL_ERASE;
			}
		}else{
			PageStatus = INVALID_PAGE_NUMBER;
		}
	}
	return PageStatus;
}

static void Write_Data(uint8_t *Received_Buffer)
{
	uint8_t verifyAddress;
	uint32_t receivedAddress = 0;
	uint8_t  dataLen;
	uint8_t writingStatus = Flash_Payload_Write_Failed;
	uint16_t ReceivedPacketLength = 0;
	uint32_t CRC_Value = 0;
	ReceivedPacketLength = Received_Buffer[0] + 1;
	CRC_Value = *(uint32_t*)(Received_Buffer + ReceivedPacketLength -4);
	if(CRC_VERIFIED == CRC_Verify(((uint8_t*)&Received_Buffer[0]), ReceivedPacketLength-4, CRC_Value)){
		Send_ACK(1);
		receivedAddress = *((uint32_t*)&Received_Buffer[2]);
		dataLen = Received_Buffer[6];
		verifyAddress = Address_Verification(receivedAddress);
		if(verifyAddress == VALID_ADDRESS){
			//Writing Payload to Flash
			writingStatus = Flash_Payload_Write((uint16_t*)&Received_Buffer[7], receivedAddress, dataLen);
			HAL_UART_Transmit(&huart2, (uint8_t*)&writingStatus, 1, HAL_MAX_DELAY);
		}else{
			HAL_UART_Transmit(&huart2, (uint8_t*)&verifyAddress, 1, HAL_MAX_DELAY);
		}
		Send_ACK(1);


	}else{
		Send_notACK();
	}
}

static uint8_t Address_Verification(uint32_t Address)
{
	uint8_t Address_Validation = INVALID_ADDRESS;
	if(Address >= FLASH_BASE && Address <= STM32_FLASH_END){
		Address_Validation = VALID_ADDRESS;
	}else if(Address >= SRAM_BASE && Address <= STM32_SRAM_END){
		Address_Validation = VALID_ADDRESS;
	}else{
		Address_Validation = INVALID_ADDRESS;
	}
	return Address_Validation;
}

static uint8_t Flash_Payload_Write(uint16_t* pdata, uint32_t startAddress, uint8_t lengthOfPayload)
{
	uint32_t Address = 0;
	uint8_t updateAddress;
	HAL_StatusTypeDef HAL_Status = HAL_ERROR;
	uint8_t payloadStatus = Flash_Payload_Write_Failed;
	HAL_FLASH_Unlock();
	for(uint8_t payloadCount = 0, updateAddress = 0; payloadCount<(lengthOfPayload/2); payloadCount++, updateAddress+=2){
		Address = startAddress + updateAddress;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, pdata[payloadCount]);
	}
	if(HAL_Status != HAL_OK){
		payloadStatus = Flash_Payload_Write_Failed;
	}else{
		payloadStatus = Flash_Payload_Write_Done;
	}

	return payloadStatus;
}
