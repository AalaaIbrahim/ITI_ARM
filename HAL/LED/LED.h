/**
 * @file    LED.h
 * @author  Alaa Hisham
 * @brief   Provides user interface with LED Module
 * @version 0.1
 * @date    14-12-2023
 */ 


#ifndef LED_H_
#define LED_H_

/*===========================================================================================================*/
/*						  Includes	    		    			     */
/*===========================================================================================================*/
#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO.h"

/*===========================================================================================================*/
/*						   Macros	    		    			     */
/*===========================================================================================================*/
/* The index of each LED in the system */
#define LED_ONE		0
#define LED_TWO		1
#define LED_THREE	2
#define LED_FOUR	3

/*===========================================================================================================*/
/*					       LED Data Types	    		    			     */
/*===========================================================================================================*/
typedef enum
{
    LED_enuActiveHigh ,
    LED_enuActiveLow
}LED_enuActiveState_t;

typedef enum
{
    LED_enuOff     ,
    LED_enuOn
}LED_enuOutputState_t;

/*===========================================================================================================*/
/*						  LED APIs	    		    			     */
/*===========================================================================================================*/
/**
 * @brief Initialize all the Configured LEDs in the LED_config.c file
 *
 * @return void
 */
void LED_Init(void);

/**
 * @brief			: Sets the state (on/off) for the given LED
 * 
 * @param[in] Copy_u8LedIndex	: The index of the LED to set
 * @param[in] Copy_enumState	: The state to set the LED to (LED_enumOutputLow/LED_enumOutputHigh)
 * 								
 * @return STD_enuErrorStatus_t	: 
 *				  
 */
STD_enuErrorStatus_t LED_enuSetState(u8 Copy_u8LedIndex, LED_enuOutputState_t Copy_enumState);

/**
 * @brief 			: Function to set the value of multiple different LEDs at once (Max. 8 LEDs)
 * 								
 * @param[in] Add_pu8LedArr	: Array of LED indices (LED in lowest index corresponds to LSB in Copy_u8ArrValue)
 * @param[in] Copy_u8ArrSize	: The size of the LED array
 * @param[in] Copy_u8ArrValue	: The value of the array
 * 								
 * @return STD_enuErrorStatus_t :
 */
STD_enuErrorStatus_t LED_enuSetLedArr(u8* Add_pu8LedArr, u8 Copy_u8ArrSize, u8 Copy_u8ArrValue);

#endif /* LED_H_ */