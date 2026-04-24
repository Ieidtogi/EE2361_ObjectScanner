/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "i2c.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "vl53l5cx_api.h"
#include "platform.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define PIN_SCL PB8
#define PIN_SDA PB9
#define LPN_PIN PA0
#define RST_PIN PA1
#define INT_PIN PA2

#define OUTPUT_DEVICE_ADDR (0x10 << 1)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

VL53L5CX_Configuration 	Dev;
VL53L5CX_ResultsData 	Results;

uint8_t status = 0;
uint8_t resolution, isAlive;

uint8_t p_data_ready;

volatile int IntCount;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void get_data_by_interrupt(VL53L5CX_Configuration *p_dev);
void get_data_by_polling(VL53L5CX_Configuration *p_dev);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  Dev.platform.handle = &hi2c1;
  Dev.platform.address = VL53L5CX_DEFAULT_I2C_ADDRESS;

  HAL_GPIO_WritePin(PWR_EN_C_GPIO_Port, PWR_EN_C_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LPn_C_GPIO_Port, LPn_C_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(PWR_EN_C_GPIO_Port, PWR_EN_C_Pin, GPIO_PIN_SET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(LPn_C_GPIO_Port, LPn_C_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  status = vl53l5cx_is_alive(&Dev, &isAlive);
  if(!isAlive) {
	  printf("Sensor not found! Check PB8/PB9 wiring.\n");
	  while(1);
  }

  printf("Loading firmware... please wait.\n");

  status = vl53l5cx_init(&Dev);

  status |= vl53l5cx_set_resolution(&Dev, VL53L5CX_RESOLUTION_8X8);

  status |= vl53l5cx_set_ranging_frequency_hz(&Dev, 5); // 5Hz

  status |= vl53l5cx_set_ranging_mode(&Dev, VL53L5CX_RANGING_MODE_CONTINUOUS);

  vl53l5cx_start_ranging(&Dev);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  get_data_by_polling(&Dev);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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

/* USER CODE BEGIN 4 */

void get_data_by_interrupt(VL53L5CX_Configuration *p_dev) {
	do
	{
		__WFI();	// Wait for interrupt
		if(IntCount !=0 ){
			IntCount=0;
			status = vl53l5cx_get_resolution(p_dev, &resolution);
			status = vl53l5cx_get_ranging_data(p_dev, &Results);

//			for(int i = 0; i < resolution;i++){
//				/* Print per zone results */
//				printf("Zone : %2d, Nb targets : %2u, Ambient : %4lu Kcps/spads, ",
//						i,
//						Results.nb_target_detected[i],
//						Results.ambient_per_spad[i]);
//
//				/* Print per target results */
//				if(Results.nb_target_detected[i] > 0){
//					printf("Target status : %3u, Distance : %4d mm\n",
//							Results.target_status[VL53L5CX_NB_TARGET_PER_ZONE * i],
//							Results.distance_mm[VL53L5CX_NB_TARGET_PER_ZONE * i]);
//				}else{
//					printf("Target status : 255, Distance : No target\n");
//				}
//			}

//			printf("\n");
		}
	} while(1);
}


void get_data_by_polling(VL53L5CX_Configuration *p_dev) {
	status = vl53l5cx_check_data_ready(&Dev, &p_data_ready);

	if(p_data_ready){
		status = vl53l5cx_get_resolution(p_dev, &resolution);
		status = vl53l5cx_get_ranging_data(p_dev, &Results);

//		if (status == 0)
//		    {
		      /* Transmit the 8x8 grid to the device at 0x10 */
		      /* We cast the distance_mm array (int16_t[64]) to uint8_t* for the HAL function */

		      HAL_StatusTypeDef i2c_status = HAL_I2C_Master_Transmit(&hi2c1, OUTPUT_DEVICE_ADDR,
		                                                            (uint8_t*)Results.distance_mm,
		                                                            128, 100);
//		    }

//			for(int i = 0; i < resolution;i++){
//				/* Print per zone results */
//				printf("Zone : %2d, Nb targets : %2u, Ambient : %4lu Kcps/spads, ",
//						i,
//						Results.nb_target_detected[i],
//						Results.ambient_per_spad[i]);
//
//				/* Print per target results */
//				if(Results.nb_target_detected[i] > 0){
//					printf("Target status : %3u, Distance : %4d mm\n",
//							Results.target_status[VL53L5CX_NB_TARGET_PER_ZONE * i],
//							Results.distance_mm[VL53L5CX_NB_TARGET_PER_ZONE * i]);
//				}else{
//					printf("Target status : 255, Distance : No target\n");
//				}
//			}

//			printf("\n");
	}else{
		HAL_Delay(5);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
