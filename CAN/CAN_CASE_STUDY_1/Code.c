#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;
unsigned char TxData[8] = {'C','A','N',' ','N','O',':',' '};
 uint8_t frameNo = 0;
 unsigned char RxData[8];
 uint16_t RxID, RxDLC;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();

  //Filter bank IDs
  CAN_RX_Filter(0x3FF,0x7FF);


  //Take CAN controller into start mode
  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
	  Error_Handler();
  }

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  TxData[7] = frameNo++;
	  CAN_TX(0x3FF, 8, TxData);
	  CAN_RX(&RxID, &RxDLC, RxData);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 1;
  hcan.Init.Mode = CAN_MODE_LOOPBACK;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}