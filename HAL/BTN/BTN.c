/**
 * @file    :   BTN.c
 * @author  :   Alaa Hisham
 * @brief   :   Contains Button API Definitions
 * @version :   0.1
 * @date    :   15-12-2023
 */

/*===========================================================================================================*/
/*						   Includes	    		    			     */
/*===========================================================================================================*/
//#include "LIB/STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"
//#include "UTIL/DELAY/DELAY.h"

#include "BTN.h"
#include "BTN_cfg.h"

/*===========================================================================================================*/
/*						Global Variables    		    			     */
/*===========================================================================================================*/
extern const BTN_stConfig_t BTN_stConfigArr[NUMBER_OF_BTNS];

/*===========================================================================================================*/
/*					       API Implementations    		    			     */
/*===========================================================================================================*/

/**
 * @brief Function to initialize all configured Buttons in the BTN_config.c file 
 * 
 * @return void
 */
void BTN_Init(void)
{
	u8 loc_iterator = ZERO;
    GPIO_strPinConfig_t temp_pinConfig;

    temp_pinConfig.mode = INPUT_PIN;
    
	for(loc_iterator=ZERO; loc_iterator<NUMBER_OF_BTNS; loc_iterator++)
	{
        switch ((u32)BTN_stConfigArr[loc_iterator].port)
        {
        case (u32)GPIOA: RCC_enuSetPeripheralClk(RCC_AHB1_GPIOA, RCC_ENABLE); break;
        case (u32)GPIOB: RCC_enuSetPeripheralClk(RCC_AHB1_GPIOB, RCC_ENABLE); break;
        case (u32)GPIOC: RCC_enuSetPeripheralClk(RCC_AHB1_GPIOC, RCC_ENABLE); break;
        default: break;
        }

        temp_pinConfig.port = BTN_stConfigArr[loc_iterator].port;
        temp_pinConfig.pin = BTN_stConfigArr[loc_iterator].pin;

		switch (BTN_stConfigArr[loc_iterator].pull_type)
		{
		case BTN_enuExternalPullDown:
		case BTN_enuExternalPullUp: temp_pinConfig.modeCfg.inputCfg.pull = FLOATING; break;
		case BTN_enuInternalPullUp:
		case BTN_enuInternalPullDown:
			temp_pinConfig.modeCfg.inputCfg.pull = BTN_stConfigArr[loc_iterator].pull_type-1;
			break;		
		default: /* Invalid */ break;
		}

		GPIO_enuInitPin(&temp_pinConfig);
	}
}

/**
 * @brief 			    			: Reads the current button state 
 * 								
 * @param[in]  Copy_u8BtnIndex	    : The button index (as configured in the BTN_config.c file)
 * @param[out] Add_penumButtonState : Address to return the current button state into
 * 								
 * @return STD_enuErrorStatus_t	    : STD_enuOk	       : Operation successful
 *				      BTN_enumNullPtr	       : input pointer is a null pointer
 *				      BTN_enumInvalidPort      : button's port is invalid
 *				      BTN_enumInvalidPin       : button's pin is invalid
 *				      STD_enuInvalidConfig    : unsupported button connection
 *				      BTN_enumIndexOutOfBounds : invalid button index
 */
STD_enuErrorStatus_t BTN_enuRead(u8 Copy_u8BtnIndex, BTN_enumState_t* Add_penumButtonState)
{
	STD_enuErrorStatus_t Local_enumErrorState = STD_enuOk;
	u8 Local_enumBtnPinValue;
	
	if(Copy_u8BtnIndex < NUMBER_OF_BTNS)
	{
		/* Get the button's pin value */
		Local_enumErrorState = GPIO_enuGetPin(BTN_stConfigArr[Copy_u8BtnIndex].port,
											  BTN_stConfigArr[Copy_u8BtnIndex].pin, &Local_enumBtnPinValue);
														
		if(STD_enuOk == Local_enumErrorState)
		{
			switch(BTN_stConfigArr[Copy_u8BtnIndex].pull_type )
			{
				case BTN_enuInternalPullDown:
				case BTN_enuExternalPullDown: break;
				case BTN_enuInternalPullUp  :
				case BTN_enuExternalPullUp  : Local_enumBtnPinValue = !Local_enumBtnPinValue; break;
				default: Local_enumErrorState = STD_enuInvalidConfig;
			}
			
			if(BTN_enumPressed == (BTN_enumState_t)Local_enumBtnPinValue)
			{
				/* Todo: Apply the delay for debouncing */
				for(unsigned int i=0; i<4000000; i++);

				/* Update the button state */
				*Add_penumButtonState = BTN_enumPressed;
			}
			else
			{	/* Update the button state */
				*Add_penumButtonState = BTN_enumNotPressed;
			}
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{	/* Update the error status */
		Local_enumErrorState = STD_enuInvalidValue;
	}
	
	return Local_enumErrorState;
}