/*
 * STD_TYPES.h
 *
 * Created: 11/25/2023 3:12:46 PM
 *  Author: ME
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned int u16;
typedef signed int s16;

typedef unsigned long int u32;
typedef signed long int s32;

#define  NULL ((void*)(0))

#define ZERO   0

typedef enum
{
	STD_enuOk		      ,
	STD_enuNullPtr	      ,
	STD_enuInvalidValue   ,
	STD_enuInvalidState   ,
	STD_enuInvalidConfig  ,
	STD_enuOperationFailed
}STD_enuErrorStatus_t;

#endif /* STD_TYPES_H_ */
