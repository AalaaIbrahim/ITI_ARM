/*
 * RCC.h
 *
 *  Created on: 6 Feb 2024
 *      Author: workstation
 */

#ifndef RCC_RCC_H_
#define RCC_RCC_H_

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "STD_TYPES.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
#define NUMBER_OF_SYSTEM_TIMERS			5

/* Indices of timers in the system */
#define SYSTICK_INDEX					0


#define RCC_DISABLE 		1
#define RCC_ENABLE 			2

/**
 * AHB prescaler options
 */
#define SYS_CLK_DIV_BY_1       0X0
#define SYS_CLK_DIV_BY_2       0X8
#define SYS_CLK_DIV_BY_4       0X9
#define SYS_CLK_DIV_BY_8       0XA
#define SYS_CLK_DIV_BY_16      0XB
#define SYS_CLK_DIV_BY_64      0XC
#define SYS_CLK_DIV_BY_128     0XD
#define SYS_CLK_DIV_BY_256     0XE
#define SYS_CLK_DIV_BY_512     0XF

/**
 * APB prescaler options
 */
#define AHB_CLK_DIV_BY_1       0X0
#define AHB_CLK_DIV_BY_2       0X4
#define AHB_CLK_DIV_BY_4       0X5
#define AHB_CLK_DIV_BY_8       0X6
#define AHB_CLK_DIV_BY_16      0X7

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef enum
{
	RCC_HSI_CLK,
	RCC_HSE_CLK,
	RCC_PLL_CLK
}RCC_enuClkIndex_t;

typedef enum
{
	RCC_AHB_CLK ,
	RCC_APB1_CLK,
	RCC_APB2_CLK
}RCC_enuBusIndex_t;

typedef enum
{
	PLL_P_2,
	PLL_P_4,
	PLL_P_6,
	PLL_P_8
}RCC_enuPLL_P_t;

typedef enum
{
	RCC_AHB1_GPIOA = 0	,
	RCC_AHB1_GPIOB		,
	RCC_AHB1_GPIOC		,
	RCC_AHB1_GPIOD		,
	RCC_AHB1_GPIOE		,
	RCC_AHB1_GPIOH = 7	,
	RCC_AHB1_CRC   = 12	,
	RCC_AHB1_DMA1  = 21	,
	RCC_AHB1_DMA2		,
	RCC_AHB2_OTGFS = 29	,
	RCC_APB1_TIM2  = 30	,
	RCC_APB1_TIM3		,
	RCC_APB1_TIM4		,
	RCC_APB1_TIM5		,
	RCC_APB1_WWDG  = 41	,
	RCC_APB1_SPI2  = 44	,
	RCC_APB1_SPI3   	,
	RCC_APB1_USART2= 47	,
	RCC_APB1_I2C1  = 51 ,
	RCC_APB1_I2C2  		,
	RCC_APB1_I2C3		,
	RCC_APB1_PWR   = 58	,
	RCC_APB2_TIM1  = 60	,
	RCC_APB2_USART1= 64	,
	RCC_APB2_USART6  	,
	RCC_APB2_ADC1  = 68	,
	RCC_APB2_SDIO  = 71	,
	RCC_APB2_SPI1		,
	RCC_APB2_SPI4   	,
	RCC_APB2_SYSCFG		,
	RCC_APB2_TIM2  = 76	,
	RCC_APB2_TIM3		,
	RCC_APB2_TIM4
}RCC_enuPeripheralIndex_t;

typedef struct
{
	/**
	 * Division factor for the main PLL and audio PLL (PLLI2S) input clock
	 * Range: [2 - 63]
	 */
	u8 M;

	/**
	 * Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
	 * Range: [2 - 510] excluding 433
	 */
	u16 N;

	/**
	 * Main PLL division factor for main system clock
	 * Options: 2, 4, 6, 8
	 */
	RCC_enuPLL_P_t P;

	/**
	 * Main PLL division factor for USB OTG FS, SDIO and random number generator clocks
	 * Range: [2 - 15]
	 */
	u8 Q;

	/**
	 * Main PLL and audio PLL (PLLI2S) entry clock source
	 * Options: RCC_HSI_CLK, RCC_HSE_CLK
	 */
	RCC_enuClkIndex_t PLL_CLK_SRC;
}RCC_strPLLConfig_t;

/*===========================================================================================================*/
/*											 Function Prototypes											 */
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
STD_enuErrorStatus_t RCC_enuSelectSysClk(RCC_enuClkIndex_t Copy_enuClock);

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
 * @return STD_enuErrorStatus_t : RCC_enuOk 			 : Successful Operation
 * 								  RCC_enuInvalidState	 : Invalid Clock State
 * 								  RCC_enuInvalidClock	 : Invalid Clock index
 */
STD_enuErrorStatus_t RCC_enuConfigBusClk(RCC_enuBusIndex_t Copy_enuBusClk, u8 Copy_u8Prescaler);

/**
 * @brief Function to Enable/Disable a certain clock
 *
 * @param[in] Copy_enuClk		: Index of the clock
 * @param[in] Copy_enuClkState	: the state of the clock
 * 								  Options: RCC_ENABLE
 * 								  		   RCC_DISABLE
 * @return STD_enuErrorStatus_t : RCC_enuOk 			 : Successful Operation
 * 								  RCC_enuInvalidState	 : Invalid Clock State
 * 								  RCC_enuInvalidClock	 : Invalid Clock index
 */
STD_enuErrorStatus_t RCC_enuSetClkState(RCC_enuClkIndex_t Copy_enuClk, u8 Copy_enuClkState);

/**
 * @brief Function to Enable/Disable clock for the given peripheral
 *
 * @param[in] Copy_enuPeripheral: Index of the peripheral
 * @param[in] Copy_enuClkState	: the state of the peripheral clock
 * 								  Options: RCC_ENABLE
 * 								  		   RCC_DISABLE
 * @return STD_enuErrorStatus_t : RCC_enuOk 			 : Successful Operation
 * 								  RCC_enuInvalidState	 : Invalid Clock State
 * 								  RCC_enuInvalidPeriphal : Invalid peripheral index
 */
STD_enuErrorStatus_t RCC_enuSetPeripheralClk(RCC_enuPeripheralIndex_t Copy_enuPeripheral, u8 Copy_enuClkState);

/**
 * @brief Function to configure the PLL clock
 *
 * Caution!
 * 		The PLL clock can only be configured while it's stopped otherwise
 * 		configuration will not take effect
 *
 * @param[in] Add_strPLLConfig : pointer to the PLL configuration structure
 *
 * @return STD_enuErrorStatus_t: RCC_enuOk 			 : Successful Operation
 * 								 RCC_enuInvalidConfig: Invalid PLL configuration
 * 								 RCC_enuNullPtr		 : The passed pointer is a null pointer
 * 								 RCC_enuConfigFailed : if the PLL is already running
 */
STD_enuErrorStatus_t RCC_enuConfigurePLL(RCC_strPLLConfig_t* Add_strPLLConfig);

f32 RCC_f32GetSysClkSpeed(void); 

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
STD_enuErrorStatus_t RCC_enuSetCBF(u8 Copy_u8Peripheral, void (*Add_Callback)(void));

#endif /* RCC_RCC_H_ */
