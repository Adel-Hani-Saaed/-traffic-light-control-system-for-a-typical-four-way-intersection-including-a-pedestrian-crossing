/*******************************************************/
/*******************************************************/
/*************** Author: Adel Hani      ****************/
/*************** Layer: APP             ****************/
/*************** SWC: APP               ****************/
/*************** Date: 4/1/2025         ****************/
/*************** Version: 1.00          ****************/
/*******************************************************/
/*******************************************************/

/* APP Layer Includes */
#include "APP/APP_interface.h"  // تضمين واجهة التطبيق التي تحتوي على تعريفات الدوال

/**
 * @brief Main function: Entry point for the traffic light application.
 *        It initializes the application and starts the traffic light system.
 */
void main(void)
{
    /* Initialize the application components (e.g., LEDs, Timers, Interrupts) */
    APP_voidInit();

    /* Start the traffic light control system */
    APP_voidStartTrifficLight();
}
