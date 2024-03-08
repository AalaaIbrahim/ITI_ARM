/*
 * @file  : NVIC.h
 * @brief : user interface for NVIC peripheral
 * @author: Alaa Hisham
 * @date  : 05-03-2024
 */

#ifndef NVIC_H_
#define NVIC_H_

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
    NonMaskableInt_IRQn         = -14,  /* Non Maskable Interrupt */
    MemoryManagement_IRQn       = -12,  /* Memory Management Interrupt */
    BusFault_IRQn               = -11,  /* Bus Fault Interrupt */
    UsageFault_IRQn             = -10,  /* Usage Fault Interrupt */
    SVCall_IRQn                 = -5,   /* SV Call Interrupt */
    DebugMonitor_IRQn           = -4,   /* Debug Monitor Interrupt */
    PendSV_IRQn                 = -2,   /* Pend SV Interrupt */
    SysTick_IRQn                = -1,   /* System Tick Interrupt */

    /* STM32F401 specific interrupts */
    WWDG_IRQn                   = 0,    /* Window Watchdog Interrupt */
    PVD_IRQn                    = 1,    /* PVD through EXTI Line detection Interrupt */
    TAMPER_STAMP_IRQn           = 2,    /* Tamper and TimeStamp interrupts through the EXTI line */
    RTC_WKUP_IRQn               = 3,    /* RTC Wakeup interrupt through the EXTI line */
    FLASH_IRQn                  = 4,    /* Flash global interrupt */
    RCC_IRQn                    = 5,    /* RCC global interrupt */
    EXTI0_IRQn                  = 6,    /* EXTI Line 0 interrupt */
    EXTI1_IRQn                  = 7,    /* EXTI Line 1 interrupt */
    EXTI2_IRQn                  = 8,    /* EXTI Line 2 interrupt */
    EXTI3_IRQn                  = 9,    /* EXTI Line 3 interrupt */
    EXTI4_IRQn                  = 10,   /* EXTI Line 4 interrupt */
    DMA1_Stream0_IRQn           = 11,   /* DMA1 Stream 0 global interrupt */
    DMA1_Stream1_IRQn           = 12,   /* DMA1 Stream 1 global interrupt */
    DMA1_Stream2_IRQn           = 13,   /* DMA1 Stream 2 global interrupt */
    DMA1_Stream3_IRQn           = 14,   /* DMA1 Stream 3 global interrupt */
    DMA1_Stream4_IRQn           = 15,   /* DMA1 Stream 4 global interrupt */
    DMA1_Stream5_IRQn           = 16,   /* DMA1 Stream 5 global interrupt */
    DMA1_Stream6_IRQn           = 17,   /* DMA1 Stream 6 global interrupt */
    ADC_IRQn                    = 18,   /* ADC1, ADC2 and ADC3 global interrupt */
    EXTI9_5_IRQn                = 23,   /* EXTI Line[9:5] interrupts */
    TIM1_BRK_TIM9_IRQn          = 24,   /* TIM1 Break interrupt and TIM9 global interrupt */
    TIM1_UP_TIM10_IRQn          = 25,   /* TIM1 Update interrupt and TIM10 global interrupt */
    TIM1_TRG_COM_TIM11_IRQn     = 26,   /* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
    TIM1_CC_IRQn                = 27,   /* TIM1 Capture Compare interrupt */
    TIM2_IRQn                   = 28,   /* TIM2 global interrupt */
    TIM3_IRQn                   = 29,   /* TIM3 global interrupt */
    TIM4_IRQn                   = 30,   /* TIM4 global interrupt */
    I2C1_EV_IRQn                = 31,   /* I2C1 Event Interrupt */
    I2C1_ER_IRQn                = 32,   /* I2C1 Error Interrupt */
    I2C2_EV_IRQn                = 33,   /* I2C2 Event Interrupt */
    I2C2_ER_IRQn                = 34,   /* I2C2 Error Interrupt */
    SPI1_IRQn                   = 35,   /* SPI1 global interrupt */
    SPI2_IRQn                   = 36,   /* SPI2 global interrupt */
    USART1_IRQn                 = 37,   /* USART1 global interrupt */
    USART2_IRQn                 = 38,   /* USART2 global interrupt */
    EXTI15_10_IRQn              = 40,   /* EXTI Line[15:10] interrupts */
    RTC_Alarm_IRQn              = 41,   /* RTC Alarm (A and B) through EXTI Line interrupt */
    OTG_FS_WKUP_IRQn            = 42,   /* USB OTG FS Wakeup through EXTI line interrupt */
    DMA1_Stream7_IRQn           = 47,   /* DMA1 Stream7 Interrupt */
    SDIO_IRQn                   = 49,   /* SDIO global Interrupt */
    TIM5_IRQn                   = 50,   /* TIM5 global Interrupt */
    SPI3_IRQn                   = 51,   /* SPI3 global Interrupt */
    DMA2_Stream0_IRQn           = 56,   /* DMA2 Stream 0 global Interrupt */
    DMA2_Stream1_IRQn           = 57,   /* DMA2 Stream 1 global Interrupt */
    DMA2_Stream2_IRQn           = 58,   /* DMA2 Stream 2 global Interrupt */
    DMA2_Stream3_IRQn           = 59,   /* DMA2 Stream 3 global Interrupt */
    DMA2_Stream4_IRQn           = 60,   /* DMA2 Stream 4 global Interrupt */
    OTG_FS_IRQn                 = 67,   /* USB OTG FS global Interrupt */
    DMA2_Stream5_IRQn           = 68,   /* DMA2 Stream 5 global interrupt */
    DMA2_Stream6_IRQn           = 69,   /* DMA2 Stream 6 global interrupt */
    DMA2_Stream7_IRQn           = 70,   /* DMA2 Stream 7 global interrupt */
    USART6_IRQn                 = 71,   /* USART6 global interrupt */
    I2C3_EV_IRQn                = 72,   /* I2C3 event interrupt */
    I2C3_ER_IRQn                = 73,   /* I2C3 error interrupt */
    FPU_IRQn                    = 81,   /* CRYP crypto global interrupt */
    SPI4_IRQn                   = 84,   /* Hash and Rng global interrupt */

    TOTAL_IRQs
} NVIC_IRQn_t;


/*===========================================================================================================*/
/*											 Function Prototypes											 */
/*===========================================================================================================*/

/**
 * @brief Function to enable the given Interrupt Request
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_EnableIRQ(NVIC_IRQn_t Copy_enuIRQn);

/**
 * @brief Function to disable the given Interrupt Request
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_DisableIRQ(NVIC_IRQn_t Copy_enuIRQn);

/**
 * @brief Sets the pending status of given interrupt or exception to 1.
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_SetPendingIRQ(NVIC_IRQn_t Copy_enuIRQn);

/**
 * @brief Clears the pending status of given interrupt or exception to 0.
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_ClearPendingIRQ(NVIC_IRQn_t Copy_enuIRQn);

/**
 * @brief Reads the pending status of interrupt or exception
 *
 * @param[in]  Copy_enuIRQn   	: the Interrupt Request's index
 * @param[out] Add_pu8Status  	: address to variable to store the IRQ's pending status
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 		  : Successful Operation
 *                                STD_enuNullPtr      : Add_pu8Status is a null pointer
 * 								  STD_enuInvalidValue : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_GetPendingIRQ(NVIC_IRQn_t Copy_enuIRQn, u8* Add_pu8Status);

/**
 * @brief Configure the number of group (and subsequently subgroup) priority bits
 *        for all interrupts/events. (subgroup bits = 4 - group bits)
 *
 * @param[in]  Copy_u32GroupBits: the Interrupt Request's index
 *             Options          : FOUR_GROUP_PRI_BITS 
 *                                THREE_GROUP_PRI_BITS
 *                                TWO_GROUP_PRI_BITS  
 *                                ONE_GROUP_PRI_BITS  
 *                                ZERO_GROUP_PRI_BITS 
 * 
 * @return STD_enuErrorStatus_t : STD_enuOk 		  : Successful Operation
 * 								  STD_enuInvalidValue : Invalid option for group bits
 */
STD_enuErrorStatus_t NVIC_ConfigPriorityBits(u32 Copy_u32GroupBits);

/**
 * @brief Sets the priority of an interrupt or exception with configurable priority level
 *
 * @param[in]  Copy_enuIRQn   	: the Interrupt Request's index
 * @param[in] Copy_u8Priority 	: the desired priority level
 *                                (this input represents the group priority and subgroup priority bits)
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 		  : Successful Operation
 *                                STD_enuNullPtr      : Add_pu8Status is a null pointer
 * 								  STD_enuInvalidValue : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_SetPriority(NVIC_IRQn_t Copy_enuIRQn, u8 Copy_u8Priority);

/**
 * @brief Reads the pending status of interrupt or exception
 *
 * @param[in]  Copy_enuIRQn   	: the Interrupt Request's index
 * @param[out] Add_pu8Priority 	: address to variable to store the IRQ's congigured priority
 * 
 * @return STD_enuErrorStatus_t : STD_enuOk 		  : Successful Operation
 *                                STD_enuNullPtr      : Add_pu8Priority is a null pointer
 * 								  STD_enuInvalidValue : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_GetPriority(NVIC_IRQn_t Copy_enuIRQn, u8* Add_pu8Priority);

#endif /* NVIC_H_ */
