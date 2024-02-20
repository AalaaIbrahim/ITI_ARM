/*
 * RCC_private.h
 *
 *  Created on: 6 Feb 2024
 *      Author: workstation
 */

#ifndef RCC_RCC_PRIVATE_H_
#define RCC_RCC_PRIVATE_H_


typedef struct
{
	volatile u32 CR           ;
	volatile u32 PLLCFGR      ;
	volatile u32 CFGR         ;
	volatile u32 CIR          ;
	volatile u32 AHB1RSTR     ;
	volatile u32 AHB2RSTR     ;
	u32			 Reserved00	  ;
	u32			 Reserved01	  ;
	volatile u32 APB1RSTR     ;
	volatile u32 APB2RSTR     ;
	u32			 Reserved02	  ;
	u32			 Reserved03	  ;
	volatile u32 AHB1ENR      ;
	volatile u32 AHB2ENR      ;
	u32			 Reserved04	  ;
	u32			 Reserved05	  ;
	volatile u32 APB1ENR      ;
	volatile u32 APB2ENR      ;
	u32			 Reserved06	  ;
	u32			 Reserved07	  ;
	volatile u32 AHB1RLPENR   ;
	volatile u32 AHB2RLPENR   ;
	u32			 Reserved08	  ;
	u32			 Reserved09	  ;
	volatile u32 APB1RLPENR   ;
	volatile u32 APB2RLPENR   ;
	u32			 Reserved10	  ;
	u32			 Reserved11	  ;
	volatile u32 BDCR         ;
	volatile u32 CSR          ;
	u32			 Reserved12	  ;
	u32			 Reserved13	  ;
	volatile u32 SSCGR        ;
	volatile u32 PLLI2SCFGR   ;
	u32			 Reserved14	  ;
	volatile u32 DCKCFGR	  ;
}RCC_strReg_t;

#define RCC		((volatile RCC_strReg_t*) 0x40023800)

/**
 * RCC Control Register bits
 */
#define CR_HSI_ON			   0
#define CR_HSE_ON			   16
#define CR_PLL_ON			   24

#define CR_HSI_RDY			 1
#define CR_HSE_RDY		   17
#define CR_PLL_RDY			 25

#define CR_SWS_READ_MASK	   0x000C
#define CR_SWS_READ_OFFSET	   0x2

#define CFGR_AHB_PRSCLR_MASK	   0XFFFFFF0F
#define CFGR_AHB_PRSCLR_OFFSET   4
#define AHB_PRSCLR_MAX	   	   15
#define AHB_PRSCLR_MIN		   8

#define CFGR_APB1_PRSCLR_MASK	   0XFFFFE3FF
#define CFGR_APB1_PRSCLR_OFFSET  10

#define CFGR_APB2_PRSCLR_MASK	   0XFFFF1FFF
#define CFGR_APB2_PRSCLR_OFFSET  13

#define APB_PRSCLR_MAX	   	   7
#define APB_PRSCLR_MIN		   4


/**
 * System Clock Selection
 */
#define SYS_CLK_SELECT_MASK	   0xFFFC
#define SYS_CLK_REG_OFFSET	   0


/**
 * Clock States
 */
#define CLK_DISABLED 		   0
#define CLK_ENABLED 		   1

/*
 * System bus offsets
 */
#define AHB1_OFFSET			   0
#define AHB2_OFFSET			   29
#define APB1_OFFSET			   30
#define APB2_OFFSET			   60
#define MAX_PERIPHERAL_INDEX   79

/*----------------- PLL Configurations ------------------*/
#define PLL_Q_MIN_VALUE		   2
#define PLL_Q_MAX_VALUE		   15
#define PLL_Q_OFFSET		   24
#define PLL_Q_MASK 			   0xF0FFFFFF

#define PLL_P_MIN_VALUE		   0
#define PLL_P_MAX_VALUE		   3
#define PLL_P_OFFSET		   16
#define PLL_P_MASK 			   0xFFFCFFFF

#define PLL_N_MIN_VALUE		   2
#define PLL_N_MAX_VALUE		   510
#define PLL_N_WRONG_VALUE	   433
#define PLL_N_OFFSET		   6
#define PLL_N_MASK 			   0xFFFF803F

#define PLL_M_MIN_VALUE		   2
#define PLL_M_MAX_VALUE		   63
#define PLL_M_OFFSET		   0
#define PLL_M_MASK 			   0xFFFFFFC0

#define PLL_CLK_OFFSET		   22
#define PLL_CLK_MASK 		   0xFFDFFFFF

#endif /* RCC_RCC_PRIVATE_H_ */
