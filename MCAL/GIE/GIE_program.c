/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: EXTI			  *******************/
/*************** Date: 27/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/


#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_TYPES.h"

#include "GIE_interface.h"
#include "GIE_register.h"

/*Enable GIE (Global interrupt Enable)*/
void GIE_voidEnable (void)
{
SET_BIT(SREG_REG,SREG_I);
}

/*Disable GIE (Global interrupt Enable)*/
void GIE_voidDisable (void)
{
CLR_BIT(SREG_REG,SREG_I);
}

