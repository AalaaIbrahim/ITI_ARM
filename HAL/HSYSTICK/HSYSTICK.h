/*
 * @file  : SYSTICK.h
 * @brief : user interface for SYSTICK timer
 * @author: Alaa Hisham
 * @date  : 07-03-2024
 */

#ifndef HSYSTICK_H_
#define HSYSTICK_H_

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "STD_TYPES.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
/**
 * IRQ pending status options
 */
#define IRQ_NOT_PENDING		    0X0
#define IRQ_PENDING			    0X1

/**
 * Options for group (preemption) priority number of bits
 */
#define FOUR_GROUP_PRI_BITS     0x00000000
#define THREE_GROUP_PRI_BITS    0x00000400
#define TWO_GROUP_PRI_BITS      0x00000500
#define ONE_GROUP_PRI_BITS      0x00000600
#define ZERO_GROUP_PRI_BITS     0x00000700

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef enum 
{
    H_CLK_AHB_DIV_BY_8 ,
    H_CLK_AHB
} HSYSTICK_enuClkSrc_t;

typedef enum 
{
    H_OneTime ,
    H_Periodic
} HSYSTICK_enuMode_t;

/*===========================================================================================================*/
/*											 Function Prototypes											 */
/*===========================================================================================================*/

/**
 * @brief Initializes the SysTick timer
 *
 * @return 
 */
STD_enuErrorStatus_t SYSTICK_Init(void);

/**
 * @brief Sets the clock source for the SYSTICK timer
 *
 * @param[in] Copy_enuTimerClk	: The AHB division factor
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid timer mode
 */
STD_enuErrorStatus_t HSYSTICK_SetClkSrc(HSYSTICK_enuClkSrc_t Copy_enuTimerClk);

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
STD_enuErrorStatus_t HSYSTICK_DelayMs(u32 Copy_u32Time, HSYSTICK_enuMode_t Copy_enuMode);

/**
 * @brief Set a function to call when systick timer interrupt is fired
 *
 * @param[in] Add_Callback   	: address of the callback function
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 	 : Successful Operation
 * 								  STD_enuNullPtr : Add_Callback is a NULL pointer
 */
STD_enuErrorStatus_t HSYSTICK_SetCBF(void (*Add_Callback)(void));

#endif 

