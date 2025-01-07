/*******************************************************/
/*******************************************************/
/*************** Author: Adel Hani      ****************/
/*************** Layer: APP             ****************/
/*************** SWC: APP                ***************/
/*************** Date: 4/1/2025         ****************/
/*************** Version: 1.00           ***************/
/*******************************************************/
/*******************************************************/

#ifndef APP_APP_INTERFACE_H_
#define APP_APP_INTERFACE_H_

#define NORMAL_MOOD         0  // Define normal mode for traffic light
#define PEDESTRIAN_MOOD     1  // Define pedestrian mode for traffic light


void APP_voidInit(void);
void APP_voidStartTrifficLight(void);


// Declare function prototypes for different functionalities
void ButtonEXTI_voidTrafficLightState_Street(void);   // Interrupt callback for pedestrian button

void Car_voidGREENLED_S1(void);                        // Function to turn green LED on for Street 1 (car)
void Car_voidYallowLED(void);                          // Function to toggle yellow LEDs for both streets
void Car_voidRedLED_S1(void);                          // Function to turn red LED on for Street 1 (car)
void PEDESTRIAN_voidGREENLED_S1(void);                 // Function to turn green LED on for Street 1 (pedestrian)
void PEDESTRIAN_voidREDLED_S1(void);                   // Function to turn red LED on for Street 1 (pedestrian)

void Car_voidGREENLED_S2(void);                        // Function to turn green LED on for Street 2 (car)
void Car_voidRedLED_S2(void);                          // Function to turn red LED on for Street 2 (car)
void PEDESTRIAN_voidGREENLED_S2(void);                 // Function to turn green LED on for Street 2 (pedestrian)
void PEDESTRIAN_voidREDLED_S2(void);                   // Function to turn red LED on for Street 2 (pedestrian)

#endif /* APP_APP_INTERFACE_H_ */
