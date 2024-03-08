/*
 * @file  : SYSTICK.h
 * @brief : user interface for SYSTICK timer
 * @author: Alaa Hisham
 * @date  : 07-03-2024
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "STD_TYPES.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/


/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef enum 
{
    CLK_AHB_DIV_BY_8 ,
    CLK_AHB
} SYSTICK_enuClkSrc_t;

typedef enum 
{
    OneTime ,
    Periodic
} SYSTICK_enuMode_t;

/*===========================================================================================================*/
/*											 Function Prototypes											 */
/*===========================================================================================================*/

/**
 * @brief Starts the timer with the given mode
 *
 * @param[in] Copy_enuTimerMode	: the timer mode (onetime/ periodic)
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid timer mode
 */
STD_enuErrorStatus_t SYSTICK_start(SYSTICK_enuMode_t Copy_enuTimerMode);

/**
 * @brief Stops the SYSTICK timer
 *
 * @return 
 */
void SYSTICK_stop(void);

/**
 * @brief Sets the clock source for the SYSTICK timer
 *
 * @param[in] Copy_f32ClkSpeed   : The AHB Clock Speed (in MHz)
 * @param[in] Copy_enuTimerClk	: The AHB division factor
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid clock speed
 */
STD_enuErrorStatus_t SYSTICK_SetClkSpeed(f32 Copy_f32ClkSpeed); 

/**
 * @brief Sets the prescaler for SysTick input clock
 *
 * @param[in] Copy_enuTimerClk	: The AHB prescaler
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid prescaler
 */
STD_enuErrorStatus_t SYSTICK_SetClkPrescaler(SYSTICK_enuClkSrc_t Copy_enuPrescaler);

/**
 * @brief Sets the reload value of the SysTick timer
 *
 * @param[in] Copy_u32Time   	: time to set the systick timer to
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t SYSTICK_setTimeMs(u32 Copy_u32Time);

/**
 * @brief Enables the SYSTICK timer interrupt
 *
 * @return 
 */
void SYSTICK_EnableInterrupt(void);

/**
 * @brief Disables the SYSTICK timer interrupt
 *
 * @return 
 */
void SYSTICK_DisableInterrupt(void);

/**
 * @brief Set a function to call when systick timer interrupt is fired
 *
 * @param[in] Add_Callback   	: address of the callback function
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 	 : Successful Operation
 * 								  STD_enuNullPtr : Add_Callback is a NULL pointer
 */
STD_enuErrorStatus_t SYSTICK_SetCBF(void (*Add_Callback)(void));

#endif /* NVIC_H_ */

