/*
 * API_GPIO.C
 *
 *  Created on: Oct 3, 2024
 *      Author: Nahue
 */
/* Includes ******************************************************************************/
#include "main.h"
#include "API_GPIO.h"
#include <stdbool.h>
/*Defines ********************************************************************************/

/*Declaration of variables ***************************************************************/
//valores esperados para LDx: LD1_Pin|LD3_Pin|LD2_Pin
     led_t LDx;
     delay_t miDelay;               // Estructura para el delay no bloqueante

/*** function of variables ***************************************************************/


/***function definition********************************************************************/
       /**
         * @brief GPIO Initialization Function
         * @param None
         * @retval None
         */
        void MX_GPIO_Init(void)
       {
         GPIO_InitTypeDef GPIO_InitStruct = {0};
       /* USER CODE BEGIN MX_GPIO_Init_1 */
       /* USER CODE END MX_GPIO_Init_1 */

         /* GPIO Ports Clock Enable */
         __HAL_RCC_GPIOC_CLK_ENABLE();

         __HAL_RCC_GPIOH_CLK_ENABLE();
         __HAL_RCC_GPIOA_CLK_ENABLE();
         __HAL_RCC_GPIOB_CLK_ENABLE();
         __HAL_RCC_GPIOD_CLK_ENABLE();
         __HAL_RCC_GPIOG_CLK_ENABLE();

         /*Configure GPIO pin Output Level */
         HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

         /*Configure GPIO pin Output Level */
         HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

         /*Configure GPIO pin : PC13 */
         GPIO_InitStruct.Pin = GPIO_PIN_13;
         GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
         GPIO_InitStruct.Pull = GPIO_NOPULL;
         HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

         /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
         GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
         GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
         GPIO_InitStruct.Pull = GPIO_NOPULL;
         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
         HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

         /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
         GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
         GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
         GPIO_InitStruct.Pull = GPIO_NOPULL;
         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
         HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

         /*Configure GPIO pin : USB_OverCurrent_Pin */
         GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
         GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
         GPIO_InitStruct.Pull = GPIO_NOPULL;
         HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

       /* USER CODE BEGIN MX_GPIO_Init_2 */
       /* USER CODE END MX_GPIO_Init_2 */
       }


/**
 * @brief GPIO Led on Function
 * @param led_t LDx
 * @retval none
 */
 void writeLedOn_GPIO(led_t LDx)
 {
	 HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_SET);
 }
 /*
  * @brief GPIO led off Function
  * @param led_t LDx
  * @retval none
  */
  void writeLedOff_GPIO(led_t LDx)
  {
	  HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_RESET);
  }
  /*
   * @brief GPIO toggle Led function
   * @param led_t LDx
   * retval none
   */
  void toggleLed_GPIO(led_t LDx)
  {
	  HAL_GPIO_TogglePin(GPIOB , LDx);
  }
  /*
   * @breaf GPIO readButton Status
   *  @param none
   *  @retval HAL_GPIO_ReadPin
   */
   buttonStatus_t readButton_GPIO (void)
  {
	  return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
  }
//   void DelayGPIOInit(delay_gpio_t *delay_t, delay_gpio_t espera)
//  {
//	delay_t->estartTime = HAL_GetTick();
//    delay_t->espera = espera;
//    delay_t->andando = false;
//    uint32_t tickstart = HAL_GetTick();
//    uint32_t wait = Delay;
//
//    /* Add a freq to guarantee minimum wait */
//    if (wait < HAL_MAX_DELAY)
//    {
//      wait += (uint32_t)(uwTickFreq);
//    }
//    while((HAL_GetTick() - tickstart) < wait)
//    {
//    }
//   }

   // Inicializa el delay no bloqueante
   void DelayGPIO_Iniciar(delay_t *delay_t, uint32_t espera_ms) {
       delay_t->startTime = HAL_GetTick();   // Obtiene el tiempo actual en milisegundos
       delay_t->espera = espera_ms;          // Establece el tiempo de espera
       delay_t->corriendo = true;            // Activa la bandera de que está corriendo
   }

   // Verifica si el delay ha terminado (sin bloquear el flujo)
   bool DelayGPIO_NoBloqueante(delay_t *delay_t) {
       if (delay_t->corriendo) {
           // Verifica si el tiempo transcurrido es mayor o igual al tiempo de espera
           if ((HAL_GetTick() - delay_t->startTime) >= delay_t->espera) {
               delay_t->corriendo = false;  // Desactiva la bandera
               return true;  // El delay ha terminado
           }
       }
       return false;  // El delay sigue en curso
   }

