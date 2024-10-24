/*
 * API_GPIO.h
 *
 *  Created on               : Oct 3, 2024
 *      Author               : Nahue
 *  Funtion of driver        : Driver que contiene funciones para manejo de puertos GPIO que utiliza funciones de la HAL
 *                             de STM32 nucleo f4xx
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_
/*includes*************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/*Exported types*******************************************************************************/
 typedef uint16_t led_t; /* importante que el tipo se uint16_t, si no, no funciona LD3_Pin */
 typedef bool buttonStatus_t , bool_t;// Tipos para botones y valores booleanos
 typedef uint32_t delay_gpio_t; // Tipo para almacenar el tiempo en ticks
 // Estructura para manejar el delay no bloqueante
 typedef struct {
     delay_gpio_t startTime;          // Tiempo de inicio en milisegundos
     delay_gpio_t espera;             // Tiempo de espera en milisegundos
     bool_t corriendo;                // Bandera que indica si el delay está corriendo
 } delay_t;


 /*Exported functions prototypes **************************************************************/
 void MX_GPIO_Init(void);
 void writeLedOn_GPIO(led_t LDx);       //enciende led
 void writeLedOff_GPIO(led_t LDx); //apaga led
 void toggleLed_GPIO(led_t LDx);  //cambia el estado mientras este activa esta funcion
 void DelayGPIO_Iniciar(delay_t *delay_t, uint32_t espera_ms);  // Inicia el delay
 bool DelayGPIO_NoBloqueante(delay_t *delay_t);                 // Verifica si el delay ha terminado

 buttonStatus_t readButton_GPIO (void);
#endif /* API_INC_API_GPIO_H_ */
