/*
 * RCC.c
 *
 *  Created on: 6 Feb 2024
 *      Author: workstation
 */
/*===========================================================================================================*/
/*												    Includes		 										 */
/*===========================================================================================================*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_private.h"
#include "RCC.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/

/*===========================================================================================================*/
/*										  	   Global Variables											     */
/*===========================================================================================================*/
void (*Add_TimClkUpdate[NUMBER_OF_SYSTEM_TIMERS])(void) = {NULL};

/*===========================================================================================================*/
/*										  	  API Implementations											 */
/*===========================================================================================================*/
/**
 * @brief Function to select a clock for the system
 *
 * @param[in] Copy_enuBusClk	: Index of the bus
 * 			  Options			: RCC_HSI_CLK
 * 			  					  RCC_HSE_CLK
 * 			  					  RCC_PLL_CLK
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid Clock index
 * 								  STD_enuOperationFailed : Selected clock is not running
 */
STD_enuErrorStatus_t RCC_enuSelectSysClk(RCC_enuClkIndex_t Copy_enuClock)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;
	u8 Loc_u8ClockState = CLK_DISABLED;

	switch(Copy_enuClock)
	{
	case RCC_HSI_CLK:
		/* Get HSI Clock State */
		Loc_u8ClockState = GET_BIT(RCC->CR, CR_HSI_RDY); break;

	case RCC_HSE_CLK:
		/* Get HSE Clock State */
		Loc_u8ClockState = GET_BIT(RCC->CR, CR_HSE_RDY); break;

	case RCC_PLL_CLK:
		/* Get PLL Clock State */
		Loc_u8ClockState = GET_BIT(RCC->CR, CR_PLL_RDY); break;

	default:
		Local_enuErrorStatus = STD_enuInvalidValue;
	}

	if(STD_enuOk == Local_enuErrorStatus)
	{
		if(CLK_DISABLED == Loc_u8ClockState)
		{
			Local_enuErrorStatus = STD_enuOperationFailed;
		}
		else
		{
			/* Select clock if not already selected */
			if(Copy_enuClock != (RCC->CR & CR_SWS_READ_MASK)>>CR_SWS_READ_OFFSET)
			{
				RCC->CFGR &= (SYS_CLK_SELECT_MASK<<SYS_CLK_REG_OFFSET);
				RCC->CFGR |= Copy_enuClock;

				/* Update Clock Value in Relevant Modules */
				for(int i=ZERO; i<NUMBER_OF_SYSTEM_TIMERS; i++)
				{
					if(NULL != Add_TimClkUpdate[i])
					{
						Add_TimClkUpdate[i]();
					}
					else
					{
						/* Do Nothing */
					}
				}
			}
			else
			{
				/* Do Nothing */
			}
		}
	}
	else
	{
		/* Do Nothing */
	}

	return Local_enuErrorStatus;
}

/**
 * @brief Function to configure the division factor for bus clock
 *
 * @param[in] Copy_enuBusClk	: Index of the bus
 * 			  Options			: RCC_AHB_CLK
 * 			  					  RCC_APB1_CLK
 * 			  					  RCC_APB2_CLK
 *
 * @param[in] Copy_enuClkState	: the division factor for the bus clock
 * 			  Options			: For AHB  -> AHB prescaler options
 * 								  For APBx -> APB prescaler options
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidConfig	 : Invalid Prescaler
 * 								  STD_enuInvalidValue	 : Invalid Clock index
 */
STD_enuErrorStatus_t RCC_enuConfigBusClk(RCC_enuBusIndex_t Copy_enuBusClk, u8 Copy_u8Prescaler)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if((Copy_u8Prescaler == ZERO)
	||((Copy_u8Prescaler >= APB_PRSCLR_MIN)
	 &&(Copy_u8Prescaler <= AHB_PRSCLR_MAX)))
	{
		switch(Copy_enuBusClk)
		{
		case RCC_AHB_CLK:
			if(Copy_u8Prescaler >= AHB_PRSCLR_MIN)
			{
				RCC->CFGR &= CFGR_AHB_PRSCLR_MASK;
				RCC->CFGR |= (Copy_u8Prescaler << CFGR_AHB_PRSCLR_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}
			break;
		case RCC_APB1_CLK:
			if(Copy_u8Prescaler <= APB_PRSCLR_MAX)
			{
				RCC->CFGR &= CFGR_APB1_PRSCLR_MASK;
				RCC->CFGR |= (Copy_u8Prescaler << CFGR_APB1_PRSCLR_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}
			break;
		case RCC_APB2_CLK:
			if(Copy_u8Prescaler <= APB_PRSCLR_MAX)
			{
				RCC->CFGR &= CFGR_APB2_PRSCLR_MASK;
				RCC->CFGR |= (Copy_u8Prescaler << CFGR_APB2_PRSCLR_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}
			break;
		default : Local_enuErrorStatus = STD_enuInvalidValue;
		}

	}
	else
	{
		Local_enuErrorStatus = STD_enuInvalidConfig;
	}

	return Local_enuErrorStatus;
}

/**
 * @brief Function to Enable/Disable a certain clock
 *
 * @param[in] Copy_enuClk		: Index of the clock
 * @param[in] Copy_enuClkState	: the state of the clock
 * 								  Options: RCC_ENABLE
 * 								  		   RCC_DISABLE
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidState	 : Invalid Clock State
 * 								  STD_enuInvalidValue	 : Invalid Clock index
 */

STD_enuErrorStatus_t RCC_enuSetClkState(RCC_enuClkIndex_t Copy_enuClk, u8 Copy_enuClkState)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if(RCC_ENABLE == Copy_enuClkState)
	{
		switch(Copy_enuClk)
		{
		case RCC_HSI_CLK:
			/* Enable HSI Clock */
			SET_BIT(RCC->CR, CR_HSI_ON);

			/* Wait until Clock is ready */
			while(!GET_BIT(RCC->CR, CR_HSI_RDY));
			break;

		case RCC_HSE_CLK:
			/* Enable HSE Clock */
			SET_BIT(RCC->CR, CR_HSE_ON);
			//RCC->CR = 0x12345678;
			/* Wait until Clock is ready */
			while(!GET_BIT(RCC->CR, CR_HSE_RDY));
			break;

		case RCC_PLL_CLK:
			/* Enable PLL Clock */
			SET_BIT(RCC->CR, CR_PLL_ON);

			/* Wait until Clock is ready */
			while(!GET_BIT(RCC->CR, CR_PLL_RDY));
			break;

		default:
			Local_enuErrorStatus = STD_enuInvalidValue;
		}
	}
	else if(RCC_DISABLE == Copy_enuClkState)
	{
		switch(Copy_enuClk)
		{
		case RCC_HSI_CLK:
			/* Disable HSI Clock */
			CLR_BIT(RCC->CR, CR_HSI_ON);

			/* Wait until Clock is disabled */
			while(GET_BIT(RCC->CR, CR_HSI_RDY));

			break;
		case RCC_HSE_CLK:
			/* Disable HSE Clock */
			CLR_BIT(RCC->CR, CR_HSE_ON);

			/* Wait until Clock is disabled */
			while(GET_BIT(RCC->CR, CR_HSE_RDY));

			break;
		case RCC_PLL_CLK:
			/* Disable PLL Clock */
			CLR_BIT(RCC->CR, CR_PLL_ON);

			/* Wait until Clock is disabled */
			while(GET_BIT(RCC->CR, CR_PLL_RDY));

			break;
		default:
			Local_enuErrorStatus = STD_enuInvalidValue;
		}
	}
	else
	{
		Local_enuErrorStatus = STD_enuInvalidState;
	}


	return Local_enuErrorStatus;
}

/**
 * @brief Function to Enable/Disable clock for the given peripheral
 *
 * @param[in] Copy_enuPeripheral: Index of the peripheral
 * @param[in] Copy_enuClkState	: the state of the peripheral clock
 * 								  Options: RCC_ENABLE
 * 								  		   RCC_DISABLE
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidState	 : Invalid Clock State
 * 								  STD_enuInvalidValue : Invalid peripheral index
 */
STD_enuErrorStatus_t RCC_enuSetPeripheralClk(RCC_enuPeripheralIndex_t Copy_enuPeripheral, u8 Copy_enuClkState)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if(RCC_ENABLE == Copy_enuClkState)
	{
		if(Copy_enuPeripheral < AHB2_OFFSET)
		{
			SET_BIT(RCC->AHB1ENR, Copy_enuPeripheral);
		}
		else if(RCC_AHB2_OTGFS == Copy_enuPeripheral)
		{
			SET_BIT(RCC->AHB1ENR, (Copy_enuPeripheral-AHB2_OFFSET));
		}
		else if(Copy_enuPeripheral < APB2_OFFSET)
		{
			SET_BIT(RCC->AHB1ENR, (Copy_enuPeripheral-APB1_OFFSET));
		}
		else if(Copy_enuPeripheral < MAX_PERIPHERAL_INDEX)
		{
			SET_BIT(RCC->AHB1ENR, (Copy_enuPeripheral-APB2_OFFSET));
		}
		else
		{
			Local_enuErrorStatus = STD_enuInvalidValue;
		}
	}
	else if(RCC_DISABLE == Copy_enuClkState)
	{
		if(Copy_enuPeripheral < AHB2_OFFSET)
		{
			CLR_BIT(RCC->AHB1ENR, Copy_enuPeripheral);
		}
		else if(RCC_AHB2_OTGFS == Copy_enuPeripheral)
		{
			CLR_BIT(RCC->AHB1ENR, (Copy_enuPeripheral-AHB2_OFFSET));
		}
		else if(Copy_enuPeripheral < APB2_OFFSET)
		{
			CLR_BIT(RCC->AHB1ENR, (Copy_enuPeripheral-APB1_OFFSET));
		}
		else if(Copy_enuPeripheral < MAX_PERIPHERAL_INDEX)
		{
			CLR_BIT(RCC->AHB1ENR, (Copy_enuPeripheral-APB2_OFFSET));
		}
		else
		{
			Local_enuErrorStatus = STD_enuInvalidValue;
		}
	}
	else
	{
		Local_enuErrorStatus = STD_enuInvalidState;
	}


	return Local_enuErrorStatus;
}

/**
 * @brief Function to configure the PLL clock
 *
 * Caution!
 * 		The PLL clock can only be configured while it's stopped otherwise
 * 		configuration will not take effect
 *
 * @param[in] Add_strPLLConfig : pointer to the PLL configuration structure
 *
 * @return STD_enuErrorStatus_t: STD_enuOk 			   : Successful Operation
 * 								 STD_enuNullPtr		   : Add_strPLLConfig is a null pointer
 * 								 STD_enuInvalidConfig  : Invalid PLL configuration
 * 								 STD_enuOperationFailed: configuration failed (PLL already running)
 */
STD_enuErrorStatus_t RCC_enuConfigurePLL(RCC_strPLLConfig_t* Add_strPLLConfig)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if(NULL != Add_strPLLConfig)
	{
		if(!GET_BIT(RCC->CR, CR_PLL_RDY))
		{
			if((Add_strPLLConfig->Q >= PLL_Q_MIN_VALUE) && (Add_strPLLConfig->Q <= PLL_Q_MAX_VALUE))
			{
				RCC->PLLCFGR &= PLL_Q_MASK;
				RCC->PLLCFGR |= (Add_strPLLConfig->Q << PLL_Q_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}

			if((Add_strPLLConfig->P >= PLL_P_MIN_VALUE) && (Add_strPLLConfig->P <= PLL_P_MAX_VALUE))
			{
				RCC->PLLCFGR &= PLL_P_MASK;
				RCC->PLLCFGR |= (Add_strPLLConfig->P << PLL_P_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}

			if((Add_strPLLConfig->N >= PLL_N_MIN_VALUE)
					&& (Add_strPLLConfig->N <= PLL_N_MAX_VALUE)
					&& (Add_strPLLConfig->N != PLL_N_WRONG_VALUE))
			{
				RCC->PLLCFGR &= PLL_N_MASK;
				RCC->PLLCFGR |= (Add_strPLLConfig->N << PLL_N_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}

			if((Add_strPLLConfig->M >= PLL_M_MIN_VALUE) && (Add_strPLLConfig->M <= PLL_M_MAX_VALUE))
			{
				RCC->PLLCFGR &= PLL_M_MASK;
				RCC->PLLCFGR |= (Add_strPLLConfig->M << PLL_M_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}

			if((Add_strPLLConfig->PLL_CLK_SRC == RCC_HSI_CLK) || (Add_strPLLConfig->PLL_CLK_SRC == RCC_HSE_CLK))
			{
				RCC->PLLCFGR &= PLL_CLK_MASK;
				RCC->PLLCFGR |= (Add_strPLLConfig->PLL_CLK_SRC << PLL_CLK_OFFSET);
			}
			else
			{
				Local_enuErrorStatus = STD_enuInvalidConfig;
			}
		}
		else
		{
			Local_enuErrorStatus = STD_enuOperationFailed;
		}
	}
	else
	{
		Local_enuErrorStatus = STD_enuNullPtr;
	}

	return Local_enuErrorStatus;
}

f32 RCC_f32GetSysClkSpeed(void) 
{
	f32 loc_f32SysClk = ZERO;
	u8 loc_SpeedSrcPLL = ZERO;
    u32 loc_u32plln = ZERO;
	u32 loc_u32pllp = ZERO;
	u32 loc_u32SrcPLL=ZERO;
	u32 loc_u32pllm = ZERO;
    
    if ((RCC->CFGR & ~(SYS_CLK_SELECT_MASK)) == RCC_PLL_CLK) 
	{
		loc_u32SrcPLL = (RCC->PLLCFGR & PLL_CLK_MASK)>>PLL_CLK_OFFSET;
    	loc_u32pllm = (RCC->PLLCFGR & PLL_M_MASK)>>PLL_M_OFFSET;
    	loc_u32plln = (RCC->PLLCFGR & PLL_N_MASK)>>PLL_N_OFFSET;
    	loc_u32pllp = (RCC->PLLCFGR & PLL_P_MASK)>>PLL_P_OFFSET;
        
		loc_SpeedSrcPLL = (loc_u32SrcPLL == RCC_HSI_CLK)? HSI_CLK_SPEED_MHZ : HSI_CLK_SPEED_MHZ;

        loc_f32SysClk =  (loc_SpeedSrcPLL*loc_u32plln) / (loc_u32pllm * loc_u32pllp);
    } 
	else 
	{
        loc_f32SysClk = ((RCC->CFGR & SYS_CLK_SELECT_MASK) == RCC_HSI_CLK) ? HSI_CLK_SPEED_MHZ : HSE_CLK_SPEED_MHZ;
    }
    
    return loc_f32SysClk;
}

/**
 * @brief Set a function to call whenever the system clock is changed
 * 
 * This function is used to update the peripheral/module of the given index, if needed, with 
 * the new value of the system clock.
 * Should be used with modules that depend on system clock value in their operation.
 * It should be called by the give module's handler 
 * 		  
 * @param[in] Copy_u8Peripheral : Index of the peripheral
 * @param[in] Add_Callback   	: address of the callback function
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 	 : Successful Operation
 * 								  STD_enuNullPtr : Add_Callback is a NULL pointer
 */
STD_enuErrorStatus_t RCC_enuSetCBF(u8 Copy_u8Peripheral, void (*Add_Callback)(void))
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if(Copy_u8Peripheral >= NUMBER_OF_SYSTEM_TIMERS)
	{
		Local_enuErrorStatus = STD_enuInvalidValue;
	}
	else if(NULL != Add_Callback)
	{
		Add_TimClkUpdate[Copy_u8Peripheral] = Add_Callback;
	}
	else
	{
		Local_enuErrorStatus = STD_enuNullPtr;
	}

	return Local_enuErrorStatus;	
}