/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "cmd.h"
#include "protocol.h" 
#include "stm32f1xx_it.h"
#include "rs485.h"
#include "rs232.h"
#include "weight.h"
#include "crc.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osTimerId DoorTimer01Handle;
osTimerId DoorTimer02Handle;
osTimerId DoorTimer03Handle;
osTimerId DoorTimer04Handle;
osTimerId DoorTimer05Handle;
osTimerId DoorTimer06Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void DoorCallback01(void const * argument);
void DoorCallback02(void const * argument);
void DoorCallback03(void const * argument);
void DoorCallback04(void const * argument);
void DoorCallback05(void const * argument);
void DoorCallback06(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of DoorTimer01 */
  osTimerDef(DoorTimer01, DoorCallback01);
  DoorTimer01Handle = osTimerCreate(osTimer(DoorTimer01), osTimerOnce, NULL);

  /* definition and creation of DoorTimer02 */
  osTimerDef(DoorTimer02, DoorCallback02);
  DoorTimer02Handle = osTimerCreate(osTimer(DoorTimer02), osTimerOnce, NULL);

  /* definition and creation of DoorTimer03 */
  osTimerDef(DoorTimer03, DoorCallback03);
  DoorTimer03Handle = osTimerCreate(osTimer(DoorTimer03), osTimerOnce, NULL);

  /* definition and creation of DoorTimer04 */
  osTimerDef(DoorTimer04, DoorCallback04);
  DoorTimer04Handle = osTimerCreate(osTimer(DoorTimer04), osTimerOnce, NULL);

  /* definition and creation of DoorTimer05 */
  osTimerDef(DoorTimer05, DoorCallback05);
  DoorTimer05Handle = osTimerCreate(osTimer(DoorTimer05), osTimerOnce, NULL);

  /* definition and creation of DoorTimer06 */
  osTimerDef(DoorTimer06, DoorCallback06);
  DoorTimer06Handle = osTimerCreate(osTimer(DoorTimer06), osTimerOnce, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  uint8_t a[8]={0x01,0x06,0x00,0x40,0xFC,0x1B,0x89,0x15};
  for(;;)
  {
    //Rs485_Send(a,8);
    cmd_select();
    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* DoorCallback01 function */
void DoorCallback01(void const * argument)
{
  /* USER CODE BEGIN DoorCallback01 */
  
  closeFlag1=0x01;
  door1_state=DOOR_STATE_CLOSE;
  /* USER CODE END DoorCallback01 */
}

/* DoorCallback02 function */
void DoorCallback02(void const * argument)
{
  /* USER CODE BEGIN DoorCallback02 */
  
  closeFlag2=0x01;
  door2_state=DOOR_STATE_CLOSE;
  /* USER CODE END DoorCallback02 */
}

/* DoorCallback03 function */
void DoorCallback03(void const * argument)
{
  /* USER CODE BEGIN DoorCallback03 */
  
  closeFlag3=0x01;
  door3_state=DOOR_STATE_CLOSE;
  /* USER CODE END DoorCallback03 */
}

/* DoorCallback04 function */
void DoorCallback04(void const * argument)
{
  /* USER CODE BEGIN DoorCallback04 */
  
  closeFlag4=0x01;
  door4_state=DOOR_STATE_CLOSE;
  /* USER CODE END DoorCallback04 */
}

/* DoorCallback05 function */
void DoorCallback05(void const * argument)
{
  /* USER CODE BEGIN DoorCallback05 */
  
  closeFlag5=0x01;
  door5_state=DOOR_STATE_CLOSE;
  /* USER CODE END DoorCallback05 */
}

/* DoorCallback06 function */
void DoorCallback06(void const * argument)
{
  /* USER CODE BEGIN DoorCallback06 */
  closeFlag6=0x01;
  door6_state=DOOR_STATE_CLOSE;
  /* USER CODE END DoorCallback06 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

