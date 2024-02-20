/**
 * @file    :   BTN_config.h
 * @author  :   Alaa Hisham
 * @brief   :   Button Module pre-compile configurations
 * @version :   0.0
 * @date    :   19-2-2024
 */


#ifndef BTN_CONFIG_H_
#define BTN_CONFIG_H_

/* The Number of Push Buttons in the system */
#define NUMBER_OF_BTNS		3

typedef enum
{
    BTN_enuExternalPullDown		,
	BTN_enuExternalPullUp		,
	BTN_enuInternalPullUp		,
	BTN_enuInternalPullDown
}BTN_enuPull_t;

typedef struct
{
	void*	        port	  ;
	u8  	        pin		  ;
	BTN_enuPull_t	pull_type ;
}BTN_stConfig_t;


#endif /* BTN_CONFIG_H_ */
