/**
 * @file    :   BTN.h
 * @author  :   Alaa Hisham
 * @brief   :   Interface for the BTN Module
 * @version :   0.1
 * @date    :   15-12-2023
 */

#ifndef BTN_H_
#define BTN_H_

/*===========================================================================================================*/
/*						  Includes	    		    			     */
/*===========================================================================================================*/

#include "../../LIB/STD_TYPES.h"

/*===========================================================================================================*/
/*						   Macros	    		    			     */
/*===========================================================================================================*/
/* Button indices */
#define BTN_ONE		0
#define BTN_TWO		1
#define BTN_THREE	2
#define BTN_FOUR	3

/*===========================================================================================================*/
/*					     Button data types	    		    			     */
/*===========================================================================================================*/
typedef enum
{
	BTN_enumNotPressed	,
	BTN_enumPressed
}BTN_enumState_t;

/*===========================================================================================================*/
/*					        Button APIs	    		    			     */
/*===========================================================================================================*/
/**
 * @brief Function to initialize all configured Buttons in the BTN_config.c file 
 * 
 * @return void
 */
void BTN_Init(void);

/**
 * @brief 			    : Reads the current button state 
 * 								
 * @param[in]  Copy_u8BtnIndex	    : The button index (as configured in the BTN_config.c file)
 * @param[out] Add_penumButtonState : Address to return the current button state into
 * 								
 * @return STD_enuErrorStatus_t	    : STD_enuOk	       : Operation successful
 *				                      STD_enuNullPtr	       : input pointer is a null pointer
 *				                      STD_enumInvalidValue      : button's port/pin is invalid
 *				                      BTN_enumInvalidConfig    : unsupported button connection
 *				                      BTN_enumIndexOutOfBounds : invalid button index
 */
STD_enuErrorStatus_t BTN_enuRead(u8 Copy_u8BtnIndex, BTN_enumState_t* Add_penumButtonState);


#endif /* BTN_H_ */