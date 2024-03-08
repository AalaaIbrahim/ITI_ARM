/*
 * @file  : HSYSTICK.c
 * @brief : API Implementations for the SysTick timer Handler
 * @author: Alaa Hisham
 * @date  : 08-03-2024
 */
/*===========================================================================================================*/
/*												    Includes		 										 */
/*===========================================================================================================*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC.h"
#include "NVIC.h"
#include "SYSTICK.h"
#include "HSYSTICK.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/


/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/

/*===========================================================================================================*/
/*										  	   Global Variables											     */
/*===========================================================================================================*/
SYSTICK_enuMode_t HSTK_gl_mode = OneTime;

/*===========================================================================================================*/
/*										  	   Private Functions											 */
/*===========================================================================================================*/
/**
 * @brief updates the SYSTICK timer's clock value for correct time calculations
 *        Should be called back whenever the system clock (AHB clock) is changed
 */
void update_systick_clock(void);

/*===========================================================================================================*/
/*										  	  API Implementations											 */
/*===========================================================================================================*/
/**
 * @brief Initializes the SysTick timer
 *
 * @return 
 */
STD_enuErrorStatus_t SYSTICK_Init(void)
{
    return RCC_enuSetCBF(SYSTICK_INDEX, update_systick_clock);
}

/**
 * @brief Sets the clock source for the SYSTICK timer
 *
 * @param[in] Copy_enuTimerClk	: The AHB division factor
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid timer mode
 */
STD_enuErrorStatus_t HSYSTICK_SetClkSrc(HSYSTICK_enuClkSrc_t Copy_enuTimerClk)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if ((CLK_AHB_DIV_BY_8 == (SYSTICK_enuClkSrc_t)Copy_enuTimerClk) 
     || (CLK_AHB == (SYSTICK_enuClkSrc_t)Copy_enuTimerClk))
    {
        loc_enuErrorStatus = SYSTICK_SetClkPrescaler(Copy_enuTimerClk);
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Sets the SysTick timer to trigger an interrupt (once or periodically) 
 *        after given time
 *
 * @param[in] Copy_u32Time   	: time to set the systick timer to
 * @param[in] Copy_enuMode      : OneTime / Periodic
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t HSYSTICK_DelayMs(u32 Copy_u32Time, HSYSTICK_enuMode_t Copy_enuMode)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    loc_enuErrorStatus = SYSTICK_setTimeMs(Copy_u32Time);

    if(STD_enuOk == loc_enuErrorStatus)
    {
        NVIC_EnableIRQ(SysTick_IRQn);
        SYSTICK_EnableInterrupt();
        loc_enuErrorStatus = SYSTICK_start(Copy_enuMode);
    }
    else
    {
        /* Do Nothing */
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Set a function to call when systick timer interrupt is fired
 *
 * @param[in] Add_Callback   	: address of the callback function
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 	 : Successful Operation
 * 								  STD_enuNullPtr : Add_Callback is a NULL pointer
 */
STD_enuErrorStatus_t HSYSTICK_SetCBF(void (*Add_Callback)(void))
{
    return SYSTICK_SetCBF(Add_Callback);
}

/**
 * @brief updates the SYSTICK timer's clock value for correct time calculations
 *        Should be called back whenever the system clock (AHB clock) is changed
 */
void update_systick_clock(void)
{
    f32 AHB_ClkSpeed = RCC_f32GetSysClkSpeed();    
    SYSTICK_SetClkSpeed(AHB_ClkSpeed);
}