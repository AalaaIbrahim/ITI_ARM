/**
 * @file    :   BTN_config.c
 * @author  :   Alaa Hisham
 * @brief   :   BTN Module post-build configurations
 * @version :   0.0
 * @date    :   19-02-2024
 */

#include "../../../include/LIB/STD_TYPES.h"

#include "../../../include/MCAL/GPIO/GPIO.h"

#include "../../../include/HAL/BTN/BTN.h"
#include "../../../include/HAL/BTN/BTN_cfg.h"

const BTN_stConfig_t BTN_stConfigArr[NUMBER_OF_BTNS] =
{
	#if NUMBER_OF_BTNS > BTN_ONE
		[BTN_ONE] =
		{
			.port			= GPIOB			  ,
			.pin			= GPIO_enuPin5		  ,
			.pull_type		= BTN_enuInternalPullUp  				  
		}
	#endif
	
	#if NUMBER_OF_BTNS > BTN_TWO
		,[BTN_TWO] =
		{
			.port			= GPIOB			  ,
			.pin			= GPIO_enuPin1			  ,
			.pull_type		= BTN_enuInternalPullUp  				  
		}
	#endif
		
	#if NUMBER_OF_BTNS > BTN_THREE
		,[BTN_THREE] =
		{
			.port			= GPIOB			  ,
			.pin			= GPIO_enuPin2			  ,
			.pull_type		= BTN_enuInternalPullUp  				  
		}
	#endif
};