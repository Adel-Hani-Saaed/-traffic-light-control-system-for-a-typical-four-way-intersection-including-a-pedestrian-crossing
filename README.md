# Traffic Light Control System 🚦

This project implements a **smart traffic light control system** using embedded systems principles. The system efficiently manages traffic flow for two streets, incorporating both normal operation and pedestrian crossing functionality. Designed with modularity in mind, it separates application logic, hardware abstraction, and microcontroller-level control.

---

## Features

### 1. **Normal Mode**
   - Controls vehicle and pedestrian lights based on preset timings.
   - Ensures smooth traffic flow without manual intervention.

### 2. **Pedestrian Mode**
   - Activated via a button press.
   - Stops vehicle flow to allow safe pedestrian crossing.

### 3. **Real-Time Responsiveness**
   - External interrupts allow dynamic switching between modes without restarting the system.

### 4. **Extensibility**
   - Designed to accommodate additional streets or advanced features like sensors for adaptive traffic management.

---

## System Architecture

The project follows a layered architecture for clear separation of concerns:

### 1. **APP Layer**
   - Handles overall system coordination.
   - Contains the main program and high-level logic.

### 2. **HAL (Hardware Abstraction Layer)**
   - Manages hardware components such as LEDs and buttons.
   - Provides an interface for controlling hardware without exposing low-level details.

### 3. **MCAL (Microcontroller Abstraction Layer)**
   - Controls microcontroller peripherals like timers and external interrupts.
   - Ensures precise timing and event-driven responsiveness.

---

## Components Used

### Hardware
- **LEDs**: Represent traffic lights for vehicles and pedestrians.
- **Push Button**: Allows pedestrians to request crossing.
- **Microcontroller**: (e.g., ATmega32) Simulates traffic system behavior.
- **Timers & Interrupts**: Ensure precise operation and responsiveness.

### Software
- **C Programming**: Core logic implementation.
- **Modular Design**: Separation of logic for scalability and readability.

---

## Workflow

1. **Initialization Phase**:
   - Configures LEDs as outputs.
   - Sets up timers and external interrupts.
   - Initializes the traffic system to `NORMAL_MODE`.

2. **Normal Mode Operation**:
   - Alternates vehicle traffic lights between green, yellow, and red.
   - Keeps pedestrian lights red unless `PEDESTRIAN_MODE` is activated.

3. **Pedestrian Mode Operation**:
   - Activated via a button press (using an external interrupt).
   - Stops vehicle traffic by switching all vehicle lights to red.
   - Activates pedestrian green lights for safe crossing.

4. **Return to Normal Mode**:
   - Resets pedestrian lights to red.
   - Resumes normal traffic light operation.

---

## Code Structure

- **`APP.c`**: High-level logic and coordination.
- **`APP_interface.h`**: Declaration of application-level functions.
- **`LED.c` / `LED_interface.h`**: HAL layer for LED control.
- **`Button.c` / `Button_interface.h`**: HAL layer for button handling.
- **`Timer.c` / `Timer_interface.h`**: MCAL layer for timer operations.
- **`EXTI.c` / `EXTI_interface.h`**: MCAL layer for external interrupts.

---

## Sample Code

```c
void main(void) {
    APP_voidInit();            // Initialize system components.
    APP_voidStartTrifficLight();  // Start traffic light management.
}
```

---

## Key Concepts Demonstrated

1. **Real-Time Systems**:
   - Precise timing using hardware timers.
   - Event-driven behavior with external interrupts.

2. **Embedded Systems Design**:
   - Layered architecture for modularity and scalability.
   - Low-level hardware control with abstraction.

3. **Safety and Reliability**:
   - Ensures pedestrian safety with dedicated crossing mode.
   - Resilient to mode switching in real-time.

---

## Future Enhancements

- **Adaptive Traffic Management**: Use sensors to adjust timing based on traffic density.
- **Remote Control**: Add IoT capabilities for remote monitoring and control.
- **Energy Efficiency**: Integrate power-saving techniques for LED operation.

---

## Author
**Adel Hani**  
Embedded Systems Developer

---

## Contact
- **Email**: adelhani832@gmail.com
- **LinkedIn**: [Your LinkedIn Profile](#)

