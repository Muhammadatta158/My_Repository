void CAN_TX(uint32_t ID, uint8_t dataLength, uint8_t* payLoad)
{
	uint8_t freeMailBoxes = 0;
	CAN_TxHeaderTypeDef pHeader;
	uint32_t pTxMailbox = 0;

	pHeader.DLC = dataLength;
	pHeader.IDE = CAN_ID_STD;
	pHeader.RTR = CAN_RTR_DATA;
	pHeader.StdId = ID;

	freeMailBoxes = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);

	if(freeMailBoxes)
	{
		if(HAL_CAN_AddTxMessage(&hcan, &pHeader, payLoad, &pTxMailbox) != HAL_OK)   //This API is to add a new transmission request
		{
			Error_Handler();
		}

		//Check if the message is pending or sent
		while(HAL_CAN_IsTxMessagePending(&hcan, pTxMailbox));

	}

}

void CAN_RX_Filter(uint16_t STD_Filter_ID, uint16_t STD_Mask_ID)
{
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterIdHigh = STD_Filter_ID << 5;             //First 5 bits arn't allowed(TRM)
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = STD_Mask_ID << 5;        //First 5 bits arn't allowed(TRM)
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

	if(HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

void CAN_RX(uint32_t* ID, uint8_t* dataLength, uint8_t* payLoad)
{
	CAN_RxHeaderTypeDef pHeader;

	while(HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_FILTER_FIFO0) == 0);

	if(HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &pHeader, payLoad) != HAL_OK)
	{
		Error_Handler();
	}
	*ID = pHeader.StdId;
	*dataLength = pHeader.DLC;

}