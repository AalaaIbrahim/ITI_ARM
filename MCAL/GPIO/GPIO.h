/*
 * RCC.h
 *
 *  Created on: 6 Feb 2024
 *      Author: workstation
 */

#ifndef RCC_GPIO_H_
#define RCC_GPIO_H_

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "STD_TYPES.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
/* GPIO ports */
#define GPIOA ((void*)0x40020000)
#define GPIOB ((void*)0x40020400)
#define GPIOC ((void*)0x40020800)
#define GPIOD ((void*)0x40020C00)
#define GPIOE ((void*)0x40021000)
#define GPIOH ((void*)0x40021C00)

/**
 * GPIO pin mode options
 */
#define INPUT_PIN			  0X0
#define OUTPUT_PIN			  0X1
#define AF_PIN				  0X2
#define ANALOG_PIN			  0X3

/* GPIO output pin value options */
#define GPIO_PIN_LOW		  0
#define GPIO_PIN_HIGH		  1

/* GPIO output speed options */
#define OUTPUT_LOW_SPEED      0X0
#define OUTPUT_MEDIUM_SPEED   0X1
#define OUTPUT_HIGH_SPEED     0X2
#define OUTPUT_VHIGH_SPEED    0X3

/* GPIO output pin type options */
#define OUTPUT_PUSH_PULL  	  0X0
#define OUTPUT_OPEN_DRAIN	  0X1

/* GPIO pin pull type options */
#define FLOATING		  	  0X0
#define PULLUP				  0X1
#define PULLDOWN		 	  0X2

/* GPIO pin Alternate Function Options */
#define AF0  				  0X0      
#define AF1  				  0X1      
#define AF2  				  0X2      
#define AF3  				  0X3      
#define AF4  				  0X4      
#define AF5  				  0X5      
#define AF6  				  0X6      
#define AF7  				  0X7 
#define AF8  				  0X8 
#define AF9  				  0X9 
#define AF10 				  0XA
#define AF11 				  0XB
#define AF12 				  0XC
#define AF13 				  0XD
#define AF14 				  0XE
#define AF15 				  0XF

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef enum
{
    GPIO_enuPin0  ,       
    GPIO_enuPin1  ,       
    GPIO_enuPin2  ,       
    GPIO_enuPin3  ,       
    GPIO_enuPin4  ,       
    GPIO_enuPin5  ,       
    GPIO_enuPin6  ,       
    GPIO_enuPin7  ,
    GPIO_enuPin8  ,
    GPIO_enuPin9  ,
    GPIO_enuPin10 ,
    GPIO_enuPin11 ,
    GPIO_enuPin12 ,
    GPIO_enuPin13 ,
    GPIO_enuPin14 ,
    GPIO_enuPin15 ,

	GPIO_TOTAL_PINS
}GPIO_enuPin_t;

typedef struct
{
	/**
	 * The GPIO port where the pin is located
	 * Range: GPIOA ... GPIOH
	 */
	void* port;

	/**
	 * The pin number on the GPIO port
	 * Range: GPIO_enuPin0 ... GPIO_enuPin15
	 */
	u8 pin;

	/**
	 * Options: INPUT_PIN	,	OUTPUT_PIN
	 * 			AF_PIN 		,	ANALOG_PIN
	 */
	u8 mode;

	union 
	{
        struct 
		{
			/**
	 		 * The output type of the GPIO pin
	 		 * Options: OUTPUT_PUSH_PULL, OUTPUT_OPEN_DRAIN
	 		 */
            u8 type;

			/**
	 		 * The GPIO pin output speed
	 		 * {prefix: OUTPUT_}{LOW/MEDIUM/HIGH/VHIGH}{suffix:_SPEED}
	 		 */
            u8 speed;

			/**
	 		 * The GPIO pin pull type
	 		 * Options: FLOATING, PULLUP, PULLDOWN
	 		 */
            u8 pull;
        } outputCfg;

		struct 
		{
			/**
	 		 * The GPIO pin pull type
	 		 * Options: FLOATING, PULLUP, PULLDOWN
	 		 */
            u8 pull;
        } inputCfg;

        struct 
		{
            u8 index;
        } afCfg;

		struct 
		{
            
        } analogCfg;
    } modeCfg;

}GPIO_strPinConfig_t;

/*===========================================================================================================*/
/*											 Function Prototypes											 */
/*===========================================================================================================*/

/**
 * @brief Function to initialize a single GPIO pin
 *
 * @param[in] Add_pstConfig 	: pointer to the pin configuration structure
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuNullPtr		 : Add_pstConfig or a struct element is a null ptr
 * 								  STD_enuInvalidValue	 : A struct element is of invalid value
 * 								  STD_enuInvalidConfig	 : A struct element provides an invalid configuration
 */
STD_enuErrorStatus_t GPIO_enuInitPin(GPIO_strPinConfig_t* Add_pstConfig);

/**
 * @brief Function to set the value of an output pin
 *
 * @param[in] port				: The GPIO port where the pin is located
 * 			  Options			: GPIOA
 * 			  					  GPIOB
 * 			  					  GPIOC
 *
 * @param[in] pin				: the pin index on the given port
 * 			  Options			: GPIO_enuPin0 ... GPIO_enuPin15
 * 								  (For GPIOC: pin options: GPIO_enuPin13 ... GPIO_enuPin15)
 * 
 * @param[in] value				: the value to set the output pin to
 * 			  Options			: GPIO_PIN_LOW, GPIO_PIN_HIGH
 * 
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuNullPtr		 : port is a null ptr
 * 								  STD_enuInvalidValue	 : Invalid port/pin value
 */
STD_enuErrorStatus_t GPIO_enuSetPin(void* port, u8 pin, u8 value);

/**
 * @brief Function to read the value of a GPIO pin
 *
 * @param[in] port				: The GPIO port where the pin is located
 * 			  Options			: GPIOA
 * 			  					  GPIOB
 * 			  					  GPIOC
 *
 * @param[in] pin				: the pin index on the given port
 * 			  Options			: GPIO_enuPin0 ... GPIO_enuPin15
 * 								  (For GPIOC: pin options: GPIO_enuPin13 ... GPIO_enuPin15)
 * 
 * @param[out] value			: address to store the pin value
 * 
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuNullPtr		 : port/value is a null ptr
 * 								  STD_enuInvalidValue	 : Invalid port/pin value
 */
STD_enuErrorStatus_t GPIO_enuGetPin(void* port , u8 pin , u8* value);

#endif /* RCC_RCC_H_ */
