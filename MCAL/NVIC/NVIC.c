/*
 * @file  : NVIC.c
 * @brief : API Implementations for NVIC peripheral
 * @author: Alaa Hisham
 * @date  : 05-03-2024
 */
/*===========================================================================================================*/
/*												    Includes		 										 */
/*===========================================================================================================*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
#define SCB_AIRCR           *((volatile u32*)0xE000ED0C)
#define NVIC                ((void*)0xE000E100)

#define VECT_KEY            0x05FA0000

/*
 * Mask for binary point selection bits 
 * (The split of group priority from subpriority)
 */
#define SCB_AIRCR_KEY_BP_MASK   0xFFFF0800

#define REG_SIZE    		32
#define PRIORITY_MASK		0X000000F0
#define PRIORITY_BITS       4
#define IRQ_PER_PRI_REG     4
#define MIN_PRI_VAL         15

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef struct 
{
    volatile u32 ISER[8];      /* Interrupt Set Enable Register */
    u32 RESERVED0[24];         /* Reserved space */
    volatile u32 ICER[8];      /* Interrupt Clear Enable Register */
    u32 RESERVED1[24];         /* Reserved space */
    volatile u32 ISPR[8];      /* Interrupt Set Pending Register */
    u32 RESERVED2[24];         /* Reserved space */
    volatile u32 ICPR[8];      /* Interrupt Clear Pending Register */
    u32 RESERVED3[24];         /* Reserved space */
    volatile u32 IABR[8];      /* Interrupt Active Bit Register */
    u32 RESERVED4[56];         /* Reserved space */
    volatile u32 IPR[60];       /* Interrupt Priority Register */
    u32 RESERVED5[644];        /* Reserved space */
    volatile u32 STIR;         /* Software Trigger Interrupt Register */
} NVIC_t;

/*===========================================================================================================*/
/*										  	  API Implementations											 */
/*===========================================================================================================*/
/**
 * @brief Function to enable the given Interrupt Request
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_EnableIRQ(NVIC_IRQn_t Copy_enuIRQn)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(Copy_enuIRQn < TOTAL_IRQs)
    {
        ((NVIC_t*)NVIC)->ISER[Copy_enuIRQn/REG_SIZE] = (1 << (Copy_enuIRQn%REG_SIZE));
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Function to disable the given Interrupt Request
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_DisableIRQ(NVIC_IRQn_t Copy_enuIRQn)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(Copy_enuIRQn < TOTAL_IRQs)
    {
        ((NVIC_t*)NVIC)->ICER[Copy_enuIRQn/REG_SIZE] = (1 << (Copy_enuIRQn%REG_SIZE));
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Sets the pending status of given interrupt or exception to 1.
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_SetPendingIRQ(NVIC_IRQn_t Copy_enuIRQn)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(Copy_enuIRQn < TOTAL_IRQs)
    {
        ((NVIC_t*)NVIC)->ISPR[Copy_enuIRQn/REG_SIZE] = (1 << (Copy_enuIRQn%REG_SIZE));
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Clears the pending status of given interrupt or exception to 0.
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_ClearPendingIRQ(NVIC_IRQn_t Copy_enuIRQn)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(Copy_enuIRQn < TOTAL_IRQs)
    {
        ((NVIC_t*)NVIC)->ICPR[Copy_enuIRQn/REG_SIZE] = (1 << (Copy_enuIRQn%REG_SIZE));
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

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
STD_enuErrorStatus_t NVIC_GetPendingIRQ(NVIC_IRQn_t Copy_enuIRQn, u8* Add_pu8Status)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(NULL == Add_pu8Status)
    {
        loc_enuErrorStatus = STD_enuNullPtr;
    }
    else if(Copy_enuIRQn < TOTAL_IRQs)
    {
        *Add_pu8Status = (((NVIC_t*)NVIC)->ISPR[Copy_enuIRQn/REG_SIZE] >> (Copy_enuIRQn%REG_SIZE)) & 1;
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

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
STD_enuErrorStatus_t NVIC_ConfigPriorityBits(u32 Copy_u32GroupBits)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;
    u32 loc_u32Temp = SCB_AIRCR;

    if((FOUR_GROUP_PRI_BITS == Copy_u32GroupBits)
    || ((Copy_u32GroupBits >= THREE_GROUP_PRI_BITS) && (Copy_u32GroupBits <= ZERO_GROUP_PRI_BITS)))
    {
        loc_u32Temp &= ~SCB_AIRCR_KEY_BP_MASK;
        loc_u32Temp |= (VECT_KEY | Copy_u32GroupBits);
        SCB_AIRCR = loc_u32Temp;
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

/**
 * @brief Sets the priority of an interrupt or exception with configurable priority level
 *
 * @param[in]  Copy_enuIRQn   	: the Interrupt Request's index
 * @param[in] Copy_u8Priority 	: the desired priority level
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 		  : Successful Operation
 * 								  STD_enuInvalidValue : Invalid IRQ index
 */
STD_enuErrorStatus_t NVIC_SetPriority(NVIC_IRQn_t Copy_enuIRQn, u8 Copy_u8Priority)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;
    u8 loc_u8PriRegIndex = Copy_enuIRQn/IRQ_PER_PRI_REG;
    u8 loc_u8PriByteOffset = Copy_enuIRQn%IRQ_PER_PRI_REG;

    if(Copy_enuIRQn < TOTAL_IRQs && Copy_u8Priority <= MIN_PRI_VAL)
    {
        ((NVIC_t*)NVIC)->IPR[loc_u8PriRegIndex] &= (PRIORITY_MASK << (loc_u8PriByteOffset*8));
        ((NVIC_t*)NVIC)->IPR[loc_u8PriRegIndex] |= (Copy_u8Priority << (loc_u8PriByteOffset*8 + PRIORITY_BITS));
    }
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}

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
STD_enuErrorStatus_t NVIC_GetPriority(NVIC_IRQn_t Copy_enuIRQn, u8* Add_pu8Priority)
{
    STD_enuErrorStatus_t loc_enuErrorStatus = STD_enuOk;

    if(NULL == Add_pu8Priority)
    {
        loc_enuErrorStatus = STD_enuNullPtr;
    }
    else if(Copy_enuIRQn < TOTAL_IRQs)
    {
        *Add_pu8Priority = (((NVIC_t*)NVIC)->IPR[Copy_enuIRQn/IRQ_PER_PRI_REG] 
                         >> (Copy_enuIRQn%IRQ_PER_PRI_REG)) 
                         & (PRIORITY_MASK >> PRIORITY_BITS);
    } 
    else
    {
        loc_enuErrorStatus = STD_enuInvalidValue;
    }

    return loc_enuErrorStatus;
}