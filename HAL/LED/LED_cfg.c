/**
 * @file    LED_config.c
 * @author  Alaa Hisham
 * @brief   Contains LED post-compile configurations
 * @version 0.0
 * @date    14-12-2023
 */ 

/*===========================================================================================================*/
/*						   Includes	    		    			     */
/*===========================================================================================================*/
#include "STD_TYPES.h"

#include "LED.h"
#include "LED_cfg.h"

/*===========================================================================================================*/
/*				     LED Configurations & Initial States 		    		     */
/*===========================================================================================================*/

const LED_stConfig_t LED_stConfigArr[NUMBER_OF_LEDS] =
{
	#if NUMBER_OF_LEDS > LED_ONE
	[LED_ONE] = 
	{
		.port	       = GPIOB		,
		.pin	       = GPIO_enuPin0		,
		.active_state  = LED_enuActiveHigh	,
		.initial_state = LED_enuOff 
	}
	#endif
	
	#if NUMBER_OF_LEDS > LED_TWO
	,[LED_TWO] =
	{
		.port	       = GPIOB		,
		.pin	       = GPIO_enuPin1		,
		.active_state  = LED_enuActiveHigh	,
		.initial_state = LED_enuOff
	}
	#endif
	
	#if NUMBER_OF_LEDS > LED_THREE
	,[LED_THREE] =
	{
		.port	       = GPIOB		,
		.pin	       = GPIO_enuPin2		,
		.active_state  = LED_enuActiveHigh	,
		.initial_state = LED_enuOff
	}
	#endif
	
	#if NUMBER_OF_LEDS > LED_FOUR
	,[LED_FOUR] =
	{
		.port	       = GPIOB		,
		.pin	       = GPIO_enuPin3		,
		.active_state  = LED_enuActiveHigh	,
		.initial_state = LED_enuOff
	}
	#endif
};