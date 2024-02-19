/**
 * @file	LED_config.h
 * @author  Alaa Hisham
 * @brief   Contains pre-compile configurations for the LED Module
 * @version 0.0
 * @date    19-02-2023
 */ 


#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#include "LIB/STD_TYPES.h"
/*===========================================================================================================*/
/*						    Macros	    		    			     */
/*===========================================================================================================*/
/**
 * @brief The number of LEDs in the system
 */ 
#define NUMBER_OF_LEDS	1

/*===========================================================================================================*/
/*					      Defined data types    		    			     */
/*===========================================================================================================*/
typedef struct
{
	void* port  ;		     /* The port of the LED (GPIOA, GPIOB, GPIOC) */
	u8 	  pin   ;		     /* The pin number of the LED (GPIO_enuPin0 ... GPIO_enuPin15) */
	u8    active_state  ;	 /* The LED's HW connection (LED_enumActiveHigh/ LED_enumActiveLow) */
	u8    initial_state ;	 /* The initial state of the LED (on/ off) */
}LED_stConfig_t;

#endif /* LED_CONFIG_H_ */