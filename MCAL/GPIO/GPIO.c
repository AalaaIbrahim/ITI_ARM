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

#include "GPIO.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
#define MODER_PIN_BITS		2
#define MODER_PIN_MASK		0X00000003

#define OSPEEDR_PIN_BITS	2
#define OSPEEDR_PIN_MASK	0X00000003

#define PUPDR_PIN_BITS		2
#define PUPDR_PIN_MASK		0X00000003

#define AFR_PIN_BITS		4
#define AFR_PIN_MASK		0X0000000F

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef struct {
    volatile u32 MODER;    /* Mode register */
    volatile u32 OTYPER;   /* Output type register */
    volatile u32 OSPEEDR;  /* Output speed register */
    volatile u32 PUPDR;    /* Pull-up/pull-down register */
    volatile u32 IDR;      /* Input data register */
    volatile u32 ODR;      /* Output data register */
    volatile u32 BSRR;     /* Bit set/reset register */
    volatile u32 LCKR;     /* Configuration lock register */
    volatile u32 AFRL;     /* Alternate function low register */
    volatile u32 AFRH;     /* Alternate function high register */
} GPIO_t;

/*===========================================================================================================*/
/*										  	   Private Functions											 */
/*===========================================================================================================*/
static STD_enuErrorStatus_t set_output_speed(void* port, u8 pin, u8 speed);
static STD_enuErrorStatus_t set_pin_pull(void* port, u8 pin, u8 pull_type);
static STD_enuErrorStatus_t set_af(void* port, u8 pin, u8 af_index);

/*===========================================================================================================*/
/*										  	  API Implementations											 */
/*===========================================================================================================*/
STD_enuErrorStatus_t GPIO_enuInitPin(GPIO_strPinConfig_t* Add_pstConfig)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;
	u32 loc_u32tempMode = ZERO;

	if(Add_pstConfig == NULL)
	{
		Local_enuErrorStatus = STD_enuNullPtr;
	}
	else 
	{
		if(Add_pstConfig->port == NULL)
		{
			Local_enuErrorStatus = STD_enuNullPtr;
		}
		else if (Add_pstConfig->pin < GPIO_TOTAL_PINS)
		{
			switch ((u32)(Add_pstConfig->port))
			{
				case (u32)GPIOC :if (Add_pstConfig->pin < GPIO_enuPin13) {Local_enuErrorStatus = STD_enuInvalidValue; break;} else {/* */}
				case (u32)GPIOB :
				case (u32)GPIOA :
				{
					switch (Add_pstConfig->mode)
					{
					case INPUT_PIN:
						/* Cofigure input pull type */
						set_pin_pull(
							Add_pstConfig->port, 
							Add_pstConfig->pin,
							Add_pstConfig->modeCfg.inputCfg.pull
							);

						break;

					case OUTPUT_PIN:
						/* Cofigure output type */
						if(OUTPUT_PUSH_PULL == Add_pstConfig->modeCfg.outputCfg.type)
							((GPIO_t*)(Add_pstConfig->port))->OTYPER &= ~(1 << (Add_pstConfig->pin));
						
						else if(OUTPUT_OPEN_DRAIN == Add_pstConfig->modeCfg.outputCfg.type)
							((GPIO_t*)(Add_pstConfig->port))->OTYPER |= (1 << (Add_pstConfig->pin));

						else Local_enuErrorStatus = STD_enuInvalidConfig;

						/* Cofigure output speed */
						set_output_speed(
							Add_pstConfig->port, 
							Add_pstConfig->pin,
							Add_pstConfig->modeCfg.outputCfg.speed
							);

						/* Cofigure output pull type */
						set_pin_pull(
							Add_pstConfig->port, 
							Add_pstConfig->pin,
							Add_pstConfig->modeCfg.outputCfg.pull
							);

						break;

					case AF_PIN:
						/* Cofigure alternate function index */
						set_af(
							Add_pstConfig->port, 
							Add_pstConfig->pin,
							Add_pstConfig->modeCfg.afCfg.index
							);
						break;

					case ANALOG_PIN:
						/* code */
						break;
					
					default: Local_enuErrorStatus = STD_enuInvalidConfig;
					}

					if(STD_enuOk == Local_enuErrorStatus)
					{
						/* Set the pin mode */
						loc_u32tempMode = ((GPIO_t*)(Add_pstConfig->port))->MODER;
						loc_u32tempMode &= ~(MODER_PIN_MASK << (MODER_PIN_BITS*(Add_pstConfig->pin)));
						loc_u32tempMode |= (Add_pstConfig->mode << (MODER_PIN_BITS*(Add_pstConfig->pin)));
						((GPIO_t*)(Add_pstConfig->port))->MODER = loc_u32tempMode;
					}
					else {/* Do Nothing */}

				}
				break;
				default: Local_enuErrorStatus = STD_enuInvalidValue;
			}
		}
		else 
		{
			Local_enuErrorStatus = STD_enuInvalidValue;
		}
	}

	return Local_enuErrorStatus;
}

STD_enuErrorStatus_t GPIO_enuSetPin(void* port, u8 pin, u8 value)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if(port == NULL)
	{
		Local_enuErrorStatus = STD_enuNullPtr;
	}
	else if (pin < GPIO_TOTAL_PINS)
	{
		switch ((u32)port)
		{
			case (u32)GPIOC :if (pin < GPIO_enuPin13) {Local_enuErrorStatus = STD_enuInvalidValue; break;} else {/* */}
			case (u32)GPIOB :
			case (u32)GPIOA :value?((((GPIO_t*)port)->ODR) |= (1 << pin))
								  :((((GPIO_t*)port)->ODR) &= ~(1 << pin)); break;
			default: Local_enuErrorStatus = STD_enuInvalidValue; break;
		}
	}
	else 
	{
		Local_enuErrorStatus = STD_enuInvalidValue;
	}
	
	return Local_enuErrorStatus ;
}

STD_enuErrorStatus_t GPIO_enuGetPin(void* port , u8 pin , u8* value)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if(port == NULL || value == NULL)
	{
		Local_enuErrorStatus = STD_enuNullPtr;
	}
	else if(pin < GPIO_TOTAL_PINS)	
	{
		switch ((u32)port)
		{
			case (u32)GPIOC :if (pin < GPIO_enuPin13) {Local_enuErrorStatus = STD_enuInvalidValue; break;} else {/* */}
			case (u32)GPIOB :
			case (u32)GPIOA :*value = (((((GPIO_t*)port)->IDR)>>pin) & 1);break;
			default: Local_enuErrorStatus = STD_enuInvalidValue; break;
		}
	}
	else 
	{
		Local_enuErrorStatus = STD_enuInvalidValue;
	}
	
	return Local_enuErrorStatus ; 
}

STD_enuErrorStatus_t set_output_speed(void* port, u8 pin, u8 speed)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;
	u32 loc_u32tempSpeed = ZERO;
	
	if(speed <= OUTPUT_VHIGH_SPEED)
	{
		loc_u32tempSpeed = ((GPIO_t*)port)->OSPEEDR;
		loc_u32tempSpeed	&= ~(OSPEEDR_PIN_MASK << (OSPEEDR_PIN_BITS*pin));
		loc_u32tempSpeed	|= speed << (OSPEEDR_PIN_BITS*pin);
		((GPIO_t*)port)->OSPEEDR = loc_u32tempSpeed;
	}
	else Local_enuErrorStatus = STD_enuInvalidConfig;

	return Local_enuErrorStatus;
}

STD_enuErrorStatus_t set_pin_pull(void* port, u8 pin, u8 pull_type)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;
	u32 loc_u32tempPull = ZERO;
	
	if(pull_type <= PULLDOWN)
	{
		loc_u32tempPull = ((GPIO_t*)port)->PUPDR;
		loc_u32tempPull	&= ~(PUPDR_PIN_MASK << (PUPDR_PIN_BITS*pin));
		loc_u32tempPull	|= pull_type << (PUPDR_PIN_BITS*pin);
		((GPIO_t*)port)->PUPDR = loc_u32tempPull;
	}
	else Local_enuErrorStatus = STD_enuInvalidConfig;

	return Local_enuErrorStatus;
}

STD_enuErrorStatus_t set_af(void* port, u8 pin, u8 af_index)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;
	u32 loc_u32tempAf = ZERO;
	
	if(af_index <= AF7)
	{
		loc_u32tempAf = ((GPIO_t*)port)->AFRL;
		loc_u32tempAf &= ~(AFR_PIN_MASK << (AFR_PIN_BITS*pin));
		loc_u32tempAf |= af_index << (AFR_PIN_BITS*pin);
		((GPIO_t*)port)->AFRL = loc_u32tempAf;
	}
	else if(af_index <= AF15)
	{
		loc_u32tempAf = ((GPIO_t*)port)->AFRH;
		loc_u32tempAf &= ~(AFR_PIN_MASK << (AFR_PIN_BITS*pin));
		loc_u32tempAf |= af_index << (AFR_PIN_BITS*pin);
		((GPIO_t*)port)->AFRH = loc_u32tempAf;
	}
	else Local_enuErrorStatus = STD_enuInvalidConfig;

	return Local_enuErrorStatus;
}