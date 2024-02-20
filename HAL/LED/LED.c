/**
 * @file	LED.c
 * @author  Alaa Hisham
 * @brief   Contains LED API implementations
 * @version 0.1
 * @date    14-12-2023
 */ 

/*===========================================================================================================*/
/*						  Includes	    		    			     */
/*===========================================================================================================*/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"

#include "HAL/LED/LED.h"
#include "HAL/LED/LED_cfg.h"

/*===========================================================================================================*/
/*					      Global Variables    		    			     */
/*===========================================================================================================*/
extern const LED_stConfig_t LED_stConfigArr[NUMBER_OF_LEDS];


/*===========================================================================================================*/
/*					    API Implementations	    		    			     */
/*===========================================================================================================*/
/**
 * @brief Initialize all the Configured LEDs in the LED_config.c file
 *
 * @return void
 */
void LED_Init(void)
{
    u8 loc_iterator = ZERO;
    GPIO_strPinConfig_t temp_pinConfig;

	u8 on_value = GPIO_PIN_HIGH;
	u8 off_value = GPIO_PIN_LOW;

    temp_pinConfig.mode = OUTPUT_PIN;
    temp_pinConfig.modeCfg.outputCfg.pull = PULLDOWN;
    temp_pinConfig.modeCfg.outputCfg.speed = OUTPUT_MEDIUM_SPEED;
	temp_pinConfig.modeCfg.outputCfg.type = OUTPUT_PUSH_PULL;
        
    for(loc_iterator=ZERO; loc_iterator<NUMBER_OF_LEDS; loc_iterator++)
    {
        switch ((u32)LED_stConfigArr[loc_iterator].port)
        {
        case (u32)GPIOA: RCC_enuSetPeripheralClk(RCC_AHB1_GPIOA, RCC_ENABLE); break;
        case (u32)GPIOB: RCC_enuSetPeripheralClk(RCC_AHB1_GPIOB, RCC_ENABLE); break;
        case (u32)GPIOC: RCC_enuSetPeripheralClk(RCC_AHB1_GPIOC, RCC_ENABLE); break;
        default: break;
        }

        temp_pinConfig.port = LED_stConfigArr[loc_iterator].port;
        temp_pinConfig.pin = LED_stConfigArr[loc_iterator].pin;

		GPIO_enuInitPin(&temp_pinConfig);

    	if(LED_enuActiveHigh == LED_stConfigArr[loc_iterator].active_state)
    	{
            on_value = GPIO_PIN_HIGH;
			off_value = GPIO_PIN_LOW;
    	}
    	else if(LED_enuActiveLow == LED_stConfigArr[loc_iterator].active_state)
    	{
    	    on_value = GPIO_PIN_LOW;
			off_value = GPIO_PIN_HIGH;
    	}
		else
		{
			/* Do Nothing */
		}

		if(LED_enuOff == LED_stConfigArr[loc_iterator].initial_state)
    	{
    		/* Turn the LED initially Off */
    	    GPIO_enuSetPin(LED_stConfigArr[loc_iterator].port, LED_stConfigArr[loc_iterator].pin, off_value);
    	}
    	else if(LED_enuOn == LED_stConfigArr[loc_iterator].initial_state)
    	{
		    /* Turn the LED initially On */
    		GPIO_enuSetPin(LED_stConfigArr[loc_iterator].port, LED_stConfigArr[loc_iterator].pin, on_value);
    	}
    	else
    	{
    		/* Do Nothing */
    	}
    }
}

/**
 * @brief			: Sets the state (on/off) for the given LED
 * 
 * @param[in] Copy_u8LedIndex	: The index of the LED to set
 * @param[in] Copy_enumState	: The state to set the LED to (LED_enuOutputLow/LED_enuOutputHigh)
 * 								
 * @return STD_enuErrorStatus_t	: 
 *				  
 */
STD_enuErrorStatus_t LED_enuSetState(u8 Copy_u8LedIndex, LED_enuOutputState_t Copy_enumState)
{
	STD_enuErrorStatus_t Local_enumErrorState = STD_enuOk;
	
	if(Copy_u8LedIndex < NUMBER_OF_LEDS)
	{
		/* Set the output state of the LED pin */
		if(LED_stConfigArr[Copy_u8LedIndex].active_state == LED_enuActiveHigh)
		{
			Local_enumErrorState = GPIO_enuSetPin(LED_stConfigArr[Copy_u8LedIndex].port,
									  LED_stConfigArr[Copy_u8LedIndex].pin,
									  Copy_enumState);
		}
		else if(LED_stConfigArr[Copy_u8LedIndex].active_state == LED_enuActiveLow)
		{
			Local_enumErrorState = GPIO_enuSetPin(LED_stConfigArr[Copy_u8LedIndex].port,
									  LED_stConfigArr[Copy_u8LedIndex].pin,
									  (!Copy_enumState));
		}
		else
		{	/* Update the error status */
			Local_enumErrorState = STD_enuInvalidConfig;
		}
	}
	else
	{	/* Update the error status */
		Local_enumErrorState = STD_enuInvalidValue;
	}
	
	return Local_enumErrorState;
}

/**
 * @brief 			: Function to set the value of multiple different LEDs at once (Max. 8 LEDs)
 * 								
 * @param[in] Add_pu8LedArr	: Array of LED indices (LED in lowest index corresponds to LSB in Copy_u8ArrValue)
 * @param[in] Copy_u8ArrSize	: The size of the LED array
 * @param[in] Copy_u8ArrValue	: The value of the array
 * 								
 * @return STD_enuErrorStatus_t :
 */
STD_enuErrorStatus_t LED_enuSetLedArr(u8* Add_pu8LedArr, u8 Copy_u8ArrSize, u8 Copy_u8ArrValue)
{
	STD_enuErrorStatus_t Local_enumErrorState = STD_enuOk;
	u8 Local_u8LedIterator = ZERO;
	
	if(Copy_u8ArrSize <= NUMBER_OF_LEDS)
	{
		for(Local_u8LedIterator=ZERO; Local_u8LedIterator<Copy_u8ArrSize; Local_u8LedIterator++)
		{
			if(GET_BIT(Copy_u8ArrValue,Local_u8LedIterator)) 
            {	/* Turn the LED on */
                LED_enuSetState(Add_pu8LedArr[Local_u8LedIterator], LED_enuOn);
            }
			else 
			{	/* Turn the LED off */
                LED_enuSetState(Add_pu8LedArr[Local_u8LedIterator], LED_enuOff);
			}
		}
	}
	else
	{	/* Update the error status */
		Local_enumErrorState = STD_enuInvalidValue;
	}
	
	return Local_enumErrorState;
}