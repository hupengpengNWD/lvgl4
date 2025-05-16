/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// #include "ux_device_cdc_acm.h"
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
/* USER CODE BEGIN PV */
typedef enum {
  APPLICATION_IDLE = 0,
  APPLICATION_INIT,
  APPLICATION_RUNNING,
  APPLICATION_SD_UNPLUGGED,
  APPLICATION_SD_PLUGGED,
  APPLICATION_SD_ERROR,
}FS_FileOperationsTypeDef;

FATFS SDFatFs;    /* File system object for SD logical drive */
char SDPath[4];   /* SD logical drive path */
FS_FileOperationsTypeDef appli_sd_state = APPLICATION_IDLE;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void MX_FATFS_Init(void)
{
  /* USER CODE BEGIN Init */
  if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
  {
	  appli_sd_state = APPLICATION_INIT;
  }


  // SDPath: "0:/"
  if(appli_sd_state == APPLICATION_INIT)
  {
	  if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
		  appli_sd_state = APPLICATION_SD_ERROR;
  }
  /* USER CODE END Init */
}

/* USER CODE BEGIN Application */
int32_t FS_FileTest(void)
{
	FRESULT res; /* FatFs function common result code */
	FIL SDFile;

	uint32_t byteswritten, bytesread; /* File write/read counts */
	uint8_t rtext[100]; /* File read buffer */
	const uint8_t wtext[] = "hello world hello world hello world hello world"; /* File write buffer */

	if(appli_sd_state == APPLICATION_SD_ERROR)	return -1;

	/* Create and Open a new text file object with write access */
	if(f_open(&SDFile,  "hello.txt", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
	{

	  /* Write data to the text file */
	  res = f_write(&SDFile, (const void *)wtext, sizeof(wtext), (void *)&byteswritten);

	  if((byteswritten > 0) && (res == FR_OK))
	  {
		/* Close the open text file */
		f_close(&SDFile);

		/* Open the text file object with read access */
		if(f_open(&SDFile, "DshanMCUH7R.TXT", FA_READ) == FR_OK)
		{
		  /* Read data from the text file */
		  res = f_read(&SDFile, ( void *)rtext, sizeof(rtext), (void *)&bytesread);

		  if((bytesread > 0) && (res == FR_OK))
		  {
			/* Close the open text file */
			f_close(&SDFile);

			/* Compare read data with the expected data */
			if(bytesread == byteswritten)
			{
			  // ux_device_cdc_acm_printf("%s", rtext);
			  /* Success of the demo: no error occurrence */
			  return 0;
			}
		  }
		}
	  }
	}

	return -1;
}
/* USER CODE END Application */
