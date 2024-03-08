/*
 * @file  : SYSTICK.c
 * @brief : API Implementations for SysTick peripheral
 * @author: Alaa Hisham
 * @date  : 07-03-2024
 */
/*===========================================================================================================*/
/*												    Includes		 										 */
/*===========================================================================================================*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
#define STK_CTRL            (*((volatile u32*)0xE000E010))   // SysTick Control and Status Register
#define STK_LOAD            (*((volatile u32*)0xE000E014))   // SysTick Reload Value Register
#define STK_CVR             (*((volatile u32*)0xE000E018))   // SysTick Current Value Register
#define STK_CALIB           (*((volatile u32*)0xE000E01C))   // SysTick Calibration Value Register

#define CTRL_ENABLE_MASK    0X00000001
#define CTRL_INTERRUPT_MASK 0X00000002

#define LOAD_MAX_VAL        0X00FFFFFF

#define MS_TO_US(MS_TIME)   ((MS_TIME)*1000)
#define US_TO_MS(US_TIME)   ((US_TIME)/1000)

#define MAX_AHB_CLK_MHZ     84
/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/


/*===========================================================================================================*/
/*										  	   Global Variables											     */
/*===========================================================================================================*/
SYSTICK_enuMode_t STK_gl_mode = OneTime;
f32 AHB_ClkSpeed_MHz = 16; /* Default (HSI) Clock Value */
SYSTICK_enuClkSrc_t STK_gl_DivFactor = 8; 
void (*SYSTICK_IntHandler)(void) = NULL;

/*===========================================================================================================*/
/*										  	  API Implementations											 */
/*===========================================================================================================*/
/**
 * @brief Starts the timer with the given mode
 *
 * @param[in] Copy_enuTimerMode	: the timer mode (onetime/ periodic)
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid timer mode
 */
STD_enuErrorStatus_t SYSTICK_start(SYSTICK_enuMode_t Copy_enuTimerMode)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if (OneTime == Copy_enuTimerMode || Periodic == Copy_enuTimerMode)
    {
        STK_gl_mode = Copy_enuTimerMode;
        STK_CTRL |= CTRL_ENABLE_MASK;
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Stops the SYSTICK timer
 *
 * @return 
 */
void SYSTICK_stop(void)
{
    /* Clear Counter Enable bit */
    STK_CTRL &= ~CTRL_ENABLE_MASK;
}

/**
 * @brief Sets the prescaler for SysTick input clock
 *
 * @param[in] Copy_enuTimerClk	: The AHB prescaler
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid prescaler
 */
STD_enuErrorStatus_t SYSTICK_SetClkPrescaler(SYSTICK_enuClkSrc_t Copy_enuPrescaler)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if ((CLK_AHB_DIV_BY_8 == Copy_enuPrescaler) 
     || (CLK_AHB == Copy_enuPrescaler))
    {
        AHB_ClkSpeed_MHz = Copy_enuPrescaler;

        STK_CTRL |= CTRL_ENABLE_MASK;
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Sets the clock source for the SYSTICK timer
 *
 * @param[in] Copy_f32ClkSpeed   : The AHB Clock Speed (in MHz)
 * @param[in] Copy_enuTimerClk	: The AHB division factor
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid clock speed
 */
STD_enuErrorStatus_t SYSTICK_SetClkSpeed(f32 Copy_f32ClkSpeed)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if (Copy_f32ClkSpeed > MAX_AHB_CLK_MHZ)
    {
        AHB_ClkSpeed_MHz = Copy_f32ClkSpeed;
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Sets the systick timer
 *
 * @param[in] Copy_u32Time   	: time to set the systick timer to
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t SYSTICK_setTimeMs(u32 Copy_u32Time)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;
    
    float loc_f32TickTime_us = (float)STK_gl_DivFactor/AHB_ClkSpeed_MHz;
    u16 loc_u16MaxTime_ms = US_TO_MS(loc_f32TickTime_us*LOAD_MAX_VAL);

    if(Copy_u32Time > loc_u16MaxTime_ms)
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }
    else
    {
        STK_LOAD = MS_TO_US(Copy_u32Time)/loc_f32TickTime_us;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Enables the SYSTICK timer interrupt
 *
 * @return 
 */
void SYSTICK_EnableInterrupt(void)
{
    STK_CTRL |= CTRL_INTERRUPT_MASK;
}

/**
 * @brief Disables the SYSTICK timer interrupt
 *
 * @return 
 */
void SYSTICK_DisableInterrupt(void)
{
    STK_CTRL &= ~CTRL_INTERRUPT_MASK;
}

/**
 * @brief Set a function to call when systick timer interrupt is fired
 *
 * @param[in] Add_Callback   	: address of the callback function
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 	 : Successful Operation
 * 								  STD_enuNullPtr : Add_Callback is a NULL pointer
 */
STD_enuErrorStatus_t SYSTICK_SetCBF(void (*Add_Callback)(void))
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(NULL != Add_Callback)
    {
        SYSTICK_IntHandler = Add_Callback;
    }
    else
    {
        loc_enuErrorStatus = STD_enuNullPtr;
    }

    return loc_enuErrorStatus;
}

void SysTick_Handler(void) 
{
    if(NULL != SYSTICK_IntHandler)
    {
        SYSTICK_IntHandler();

        if(OneTime == STK_gl_mode)
        {
            SYSTICK_stop();
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }
}