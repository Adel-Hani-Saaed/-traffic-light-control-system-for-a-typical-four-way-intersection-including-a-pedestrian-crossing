/*******************************************************/
/*******************************************************/
/*************** Author: Adel Hani      ****************/
/*************** Layer: APP             ****************/
/*************** SWC: APP                ***************/
/*************** Date: 4/1/2025         ****************/
/*************** Version: 1.00           ***************/
/*******************************************************/
/*******************************************************/

/*Lib Layer*/
#include "../LIB/BIT_Math.h"                          // Include bit manipulation macros
#include "../LIB/STD_TYPES.h"                         // Include standard types definitions
#include "../LIB/Mapping_interface.h"                 // Include mapping interface (e.g., pin mappings)

/*Macl  Layer*/
#include "../MCAL/DIO/DIO_interface.h"                // Include Digital IO interface
#include "../MCAL/GIE/GIE_interface.h"                // Include Global Interrupt Enable interface
#include "../MCAL/EXTI/EXTI_interface.h"              // Include External Interrupt interface
#include "../MCAL/TIMER_0/Timer0_interface.h"         // Include Timer0 interface for delays

/*Hal  Layer*/
#include "../HAL/LED/Led_interface.h"                 // Include LED interface for controlling LEDs
#include "../HAL/SW/SW_interface.h"                   // Include Switch interface (for external switches)

/*APP  Layer*/
#include "APP_config.h"
#include "APP_interface.h"

u8 Local_u8MoodState = NORMAL_MOOD;  // Variable to store the current mood (normal or pedestrian)
u8 ActiveStreet = NO_OD_ACTIVE_STREET_1;                 // Variable to store the active street (1 or 2)

LED_T LED_CAR_GREEN_S1        = {LED_PORTA , LED_PIN0 ,LED_SOURCE}; // Green LED for car (Street 1)
LED_T LED_CAR_YELLOW_S1       = {LED_PORTA , LED_PIN1 ,LED_SOURCE}; // Yellow LED for car (Street 1)
LED_T LED_CAR_RED_S1          = {LED_PORTA , LED_PIN2 ,LED_SOURCE}; // Red LED for car (Street 1)
LED_T LED_PEDESTRIAN_GREEN_S1 = {LED_PORTA , LED_PIN3 ,LED_SOURCE}; // Green LED for pedestrian (Street 1)
LED_T LED_PEDESTRIAN_RED_S1   = {LED_PORTA , LED_PIN4 ,LED_SOURCE}; // Red LED for pedestrian (Street 1)

LED_T LED_CAR_GREEN_S2        = {LED_PORTA , LED_PIN5 ,LED_SOURCE}; // Green LED for car (Street 2)
LED_T LED_CAR_YELLOW_S2       = {LED_PORTA , LED_PIN6 ,LED_SOURCE}; // Yellow LED for car (Street 2)
LED_T LED_CAR_RED_S2          = {LED_PORTA , LED_PIN7 ,LED_SOURCE}; // Red LED for car (Street 2)
LED_T LED_PEDESTRIAN_GREEN_S2 = {LED_PORTB , LED_PIN0 ,LED_SOURCE}; // Green LED for pedestrian (Street 2)
LED_T LED_PEDESTRIAN_RED_S2   = {LED_PORTB , LED_PIN1 ,LED_SOURCE}; // Red LED for pedestrian (Street 2)

void APP_voidInit(void)
{
	/* Initialize LEDs for both Street 1 and Street 2 */
	LED_voidPinInit(&LED_CAR_RED_S1);  // Initialize red car LED for Street 1
	LED_voidPinInit(&LED_CAR_YELLOW_S1);  // Initialize yellow car LED for Street 1
	LED_voidPinInit(&LED_CAR_GREEN_S1);  // Initialize green car LED for Street 1
	LED_voidPinInit(&LED_PEDESTRIAN_RED_S1);  // Initialize red pedestrian LED for Street 1
	LED_voidPinInit(&LED_PEDESTRIAN_GREEN_S1);  // Initialize green pedestrian LED for Street 1

	LED_voidPinInit(&LED_CAR_RED_S2);  // Initialize red car LED for Street 2
	LED_voidPinInit(&LED_CAR_YELLOW_S2);  // Initialize yellow car LED for Street 2
	LED_voidPinInit(&LED_CAR_GREEN_S2);  // Initialize green car LED for Street 2
	LED_voidPinInit(&LED_PEDESTRIAN_RED_S2);  // Initialize red pedestrian LED for Street 2
	LED_voidPinInit(&LED_PEDESTRIAN_GREEN_S2);  // Initialize green pedestrian LED for Street 2

	/* Set Pin2 and Pin3 in PortD to High for interrupt configuration */
	DIO_enumSetPinValue(DIO_PORTD, DIO_PIN2, DIO_HIGH);  // Set pin for interrupt 1 to high

	/* Initialize External Interrupt (INT0) and set the callback function for button press */
	EXTI_voidINT0Init();  // Initialize interrupt for button
	EXTI_u8ExtISetCallBackINT0(&ButtonEXTI_voidTrafficLightState_Street);  // Set callback function for interrupt

	/* Initialize Timer0 for delay functionality between LED switching */
	TIMER0_voidInit();  // Initialize Timer0

	/* Enable global interrupts */
	GIE_voidEnable();  // Enable global interrupts for external interrupt handling



}

void APP_voidStartTrifficLight(void)
{
	while(1)
	{
		if (Local_u8MoodState == NORMAL_MOOD)  // Check if the system is in normal traffic mode
		{
			if (ActiveStreet == NO_OD_ACTIVE_STREET_1)  // If Street 1 is active
			{
				u8 exitFlag = CLEAR_EXIT_FLAG;  // Flag to exit loop if pedestrian mode is activated

				/* Street 1: Car moves (green), Pedestrian stops (red) */
				Car_voidGREENLED_S1();  // Turn on green car LED for Street 1
				PEDESTRIAN_voidREDLED_S1();  // Turn off pedestrian green LED for Street 1
				Car_voidRedLED_S2();  // Turn off car green LED for Street 2
				PEDESTRIAN_voidGREENLED_S2();  // Turn on pedestrian green LED for Street 2

				/* Wait for 5 seconds before switching to the other street */
				for(u8 i = SAERT_COUNTER_LOOP_NORMAL_MOOD; i < NO_OF_LOOPS_TIMER0_NORMAL_MOOD; i++)  // Loop to create a delay of 15 seconds
				{
					TIMER0_voidDelay_ms_(DELAY_MS_LOOP_NORMAL_MOOD);  // Delay for 100ms
					if(Local_u8MoodState == PEDESTRIAN_MOOD)  // Check if the button is pressed
					{
						exitFlag = SET_EXIT_FLAG;  // Set exit flag if pedestrian mode is activated
						break;  // Exit the loop
					}
				}
				ActiveStreet = NO_OD_ACTIVE_STREET_2;  // Switch to Street 2

				if (exitFlag == SET_EXIT_FLAG) continue;  // If pedestrian mode is active, skip the remaining code

				/* Street 1: Car stops (yellow), Pedestrian moves (green) */
				Car_voidYallowLED();  // Turn on yellow car LEDs for both streets
				Car_voidRedLED_S1();  // Turn off car green LED for Street 1
				PEDESTRIAN_voidGREENLED_S1();  // Turn on pedestrian green LED for Street 1
				Car_voidGREENLED_S2();  // Turn on green car LED for Street 2
				PEDESTRIAN_voidREDLED_S2();  // Turn off pedestrian green LED for Street 2

				/* Wait for another 5 seconds */
				for(u8 i = SAERT_COUNTER_LOOP_NORMAL_MOOD; i < NO_OF_LOOPS_TIMER0_NORMAL_MOOD; i++)  // Loop to create a delay of 15 seconds
				{
					TIMER0_voidDelay_ms_(DELAY_MS_LOOP_NORMAL_MOOD);  // Delay for 100ms
					if(Local_u8MoodState == PEDESTRIAN_MOOD)  // Check if pedestrian mode is activated
					{
						exitFlag = SET_EXIT_FLAG;  // Set exit flag if pedestrian mode is activated
						break;  // Exit the loop
					}
				}

				if (exitFlag == SET_EXIT_FLAG) continue;  // If pedestrian mode is active, skip the remaining code

				Car_voidYallowLED();  // Turn off yellow car LEDs
			}
			else if (ActiveStreet == NO_OD_ACTIVE_STREET_2)  // If Street 2 is active
			{
				u8 exitFlag = CLEAR_EXIT_FLAG;  // Flag to exit loop if pedestrian mode is activated

				/* Street 2: Car moves (green), Pedestrian stops (red) */
				Car_voidGREENLED_S2();  // Turn on green car LED for Street 2
				PEDESTRIAN_voidREDLED_S2();  // Turn off pedestrian green LED for Street 2
				Car_voidRedLED_S1();  // Turn off car green LED for Street 1
				PEDESTRIAN_voidGREENLED_S1();  // Turn on pedestrian green LED for Street 1

				/* Wait for 5 seconds before switching to the other street */
				for(u8 i = SAERT_COUNTER_LOOP_NORMAL_MOOD; i < NO_OF_LOOPS_TIMER0_NORMAL_MOOD; i++)  // Loop to create a delay of 15 seconds
				{
					TIMER0_voidDelay_ms_(DELAY_MS_LOOP_NORMAL_MOOD);  // Delay for 100ms
					if(Local_u8MoodState == PEDESTRIAN_MOOD)  // Check if pedestrian mode is activated
					{
						exitFlag = SET_EXIT_FLAG;  // Set exit flag if pedestrian mode is activated
						break;  // Exit the loop
					}
				}
				ActiveStreet = NO_OD_ACTIVE_STREET_1;  // Switch to Street 1

				if (exitFlag == SET_EXIT_FLAG ) continue;  // If pedestrian mode is active, skip the remaining code

				/* Street 2: Car stops (yellow), Pedestrian moves (green) */
				Car_voidYallowLED();  // Turn on yellow car LEDs for both streets
				Car_voidRedLED_S2();  // Turn off car green LED for Street 2
				PEDESTRIAN_voidGREENLED_S2();  // Turn on pedestrian green LED for Street 2
				Car_voidGREENLED_S1();  // Turn on green car LED for Street 1
				PEDESTRIAN_voidREDLED_S1();  // Turn off pedestrian green LED for Street 1

				/* Wait for another 5 seconds */
				for(u8 i = SAERT_COUNTER_LOOP_NORMAL_MOOD; i < NO_OF_LOOPS_TIMER0_NORMAL_MOOD ; i++)  // Loop to create a delay of 5 seconds
				{
					TIMER0_voidDelay_ms_(DELAY_MS_LOOP_NORMAL_MOOD);  // Delay for 100ms
					if(Local_u8MoodState == PEDESTRIAN_MOOD)  // Check if pedestrian mode is activated
					{
						exitFlag = SET_EXIT_FLAG;  // Set exit flag if pedestrian mode is activated
						break;  // Exit the loop
					}
				}

				if (exitFlag == SET_EXIT_FLAG) continue;  // If pedestrian mode is active, skip the remaining code

				Car_voidYallowLED();  // Turn off yellow car LEDs
			}
		}
		else if (Local_u8MoodState == PEDESTRIAN_MOOD)  // If the system is in pedestrian mode
		{
			/* Pedestrian Mode: Cars stop, Pedestrians move */
			Car_voidYallowLED();  // Turn on yellow car LEDs for both streets
			Car_voidRedLED_S1();  // Turn off car green LED for Street 1
			Car_voidRedLED_S2();  // Turn off car green LED for Street 2
			PEDESTRIAN_voidGREENLED_S1();  // Turn on pedestrian green LED for Street 1
			PEDESTRIAN_voidGREENLED_S2();  // Turn on pedestrian green LED for Street 2

			/* Wait for 5 seconds to allow pedestrians to cross */
			TIMER0_voidDelay_ms_(DELAY_MS_TIMER0_PEDESTRIAN_MOOD);  // Delay for 5 seconds
			Car_voidYallowLED();  // Turn off yellow car LEDs for both streets

			/* Switch back to normal mode after pedestrian crossing */
			Local_u8MoodState = NORMAL_MOOD;
		}
	}
}


/* Interrupt callback function to handle pedestrian button press */
void ButtonEXTI_voidTrafficLightState_Street(void)
{
	TIMER0_voidStopTimer();  // Stop timer for immediate response
	if (Local_u8MoodState == NORMAL_MOOD)  // If system is in normal mode
	{
		Local_u8MoodState = PEDESTRIAN_MOOD;  // Switch to pedestrian mode
	}
}

/* Function to turn on the green LED for Street 1 (Car) */
void Car_voidGREENLED_S1(void)
{
	LED_voidPinTurnOn(&LED_CAR_GREEN_S1);  // Turn on green car LED for Street 1
	LED_voidPinTurnOff(&LED_CAR_YELLOW_S1);  // Turn off yellow car LED for Street 1
	LED_voidPinTurnOff(&LED_CAR_RED_S1);  // Turn off red car LED for Street 1
}

/* Function to toggle the yellow LEDs for both streets */
void Car_voidYallowLED(void)
{
	for (u8 i = SAERT_COUNTER_LOOP_YLED; i < NO_OF_LOOPS_YLED; i++)  // Loop to toggle yellow LED multiple times
	{
		LED_voidPinToggle(&LED_CAR_YELLOW_S1);  // Toggle yellow car LED for Street 1
		LED_voidPinToggle(&LED_CAR_YELLOW_S2);  // Toggle yellow car LED for Street 2
		TIMER0_voidDelay_ms_(DELAY_MS_LOOP_YLED);  // Delay between toggles
	}
}

/* Function to turn on the red LED for Street 1 (Car) */
void Car_voidRedLED_S1(void)
{
	LED_voidPinTurnOn(&LED_CAR_RED_S1);  // Turn on red car LED for Street 1
	LED_voidPinTurnOff(&LED_CAR_YELLOW_S1);  // Turn off yellow car LED for Street 1
	LED_voidPinTurnOff(&LED_CAR_GREEN_S1);  // Turn off green car LED for Street 1
}

/* Function to turn on the green LED for Street 1 (Pedestrian) */
void PEDESTRIAN_voidGREENLED_S1(void)
{
	LED_voidPinTurnOn(&LED_PEDESTRIAN_GREEN_S1);  // Turn on green pedestrian LED for Street 1
	LED_voidPinTurnOff(&LED_PEDESTRIAN_RED_S1);  // Turn off red pedestrian LED for Street 1
}

/* Function to turn on the red LED for Street 1 (Pedestrian) */
void PEDESTRIAN_voidREDLED_S1(void)
{
	LED_voidPinTurnOn(&LED_PEDESTRIAN_RED_S1);  // Turn on red pedestrian LED for Street 1
	LED_voidPinTurnOff(&LED_PEDESTRIAN_GREEN_S1);  // Turn off green pedestrian LED for Street 1
}

/* Function to turn on the green LED for Street 2 (Car) */
void Car_voidGREENLED_S2(void)
{
	LED_voidPinTurnOn(&LED_CAR_GREEN_S2);  // Turn on green car LED for Street 2
	LED_voidPinTurnOff(&LED_CAR_YELLOW_S2);  // Turn off yellow car LED for Street 2
	LED_voidPinTurnOff(&LED_CAR_RED_S2);  // Turn off red car LED for Street 2
}

/* Function to turn on the red LED for Street 2 (Car) */
void Car_voidRedLED_S2(void)
{
	LED_voidPinTurnOn(&LED_CAR_RED_S2);  // Turn on red car LED for Street 2
	LED_voidPinTurnOff(&LED_CAR_YELLOW_S2);  // Turn off yellow car LED for Street 2
	LED_voidPinTurnOff(&LED_CAR_GREEN_S2);  // Turn off green car LED for Street 2
}

/* Function to turn on the green LED for Street 2 (Pedestrian) */
void PEDESTRIAN_voidGREENLED_S2(void)
{
	LED_voidPinTurnOn(&LED_PEDESTRIAN_GREEN_S2);  // Turn on green pedestrian LED for Street 2
	LED_voidPinTurnOff(&LED_PEDESTRIAN_RED_S2);  // Turn off red pedestrian LED for Street 2
}

/* Function to turn on the red LED for Street 2 (Pedestrian) */
void PEDESTRIAN_voidREDLED_S2(void)
{
	LED_voidPinTurnOn(&LED_PEDESTRIAN_RED_S2);  // Turn on red pedestrian LED for Street 2
	LED_voidPinTurnOff(&LED_PEDESTRIAN_GREEN_S2);  // Turn off green pedestrian LED for Street 2
}
