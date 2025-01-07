/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: Timer0		  *******************/
/*************** Date: 27/3/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


/* Description : this Function is to set the Timer0
 * \input  : nothing
 * Return  : nothing
 */
void TIMER0_voidInit();


/* Description : this Function is registration Function the Call back for CTC Mode
 * \input :  void (*Copy_pvCallBackFunc)(void)    		 ,  Pointer to function
 *  Return  : State of Function  OK or NOK
 */
u8 TIMER0_u8SetCallBackCTCMode		(void (*Copy_pvCallBackFunc)(void));


/* Description : this Function is registration Function the Call back for Normal Mode
 * \input :  void (*Copy_pvCallBackFunc)(void)    		 ,  Pointer to function
 *  Return  : State of Function  OK or NOK
 */
u8 TIMER0_u8SetCallBackOverFlowMode (void (*Copy_pvCallBackFunc)(void));



/* Description : this Function is to set the value of pre_load in register TCNT0_REG
 * \input  : Copy_u8PreloadValue       Range : 0 ~ 255
 * Return  : nothing
 */
void TIMER0_voidSetPreloadValue (u8 Copy_u8PreloadValue) ;



/* Description : this Function is to set the value of CTC Value in register OCR0
 * \input  : Copy_u8PreloadValue       Range : 0 ~ 255
 * Return  : nothing
 */
void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value);



/* Description : this Function is to return the value of pre_load in register TCNT0_REG
 * \input  :  nothing
 * Return  :  Range : 0 ~ 255
 */
u8 TIMER0_u8GetTimerCounterValue (void);



/* Description : this Function is Stop timer TCNT0_REG == 0 ;
 * \input  :  nothing
 * Return  :  nothing
 */
void TIMER0_voidStopTimer(void);


/* Description : this Function is to set Delay by ms
 * \input  : Copy_u8PreloadValue       Range : Time needed
 * Return  : nothing
 */
void TIMER0_voidDelay_ms_(u32 Copy_u16TimeNeed);


#endif /* TIMER0_INTERFACE_H_ */
