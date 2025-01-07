# Traffic Light Control System with Pedestrian Crossing

## Overview
This project implements a traffic light control system for a typical four-way intersection, with a pedestrian crossing feature. The system is designed using an FSM (Finite State Machine) for structured state transitions. This project is part of the ReNile Embedded Systems evaluation process.

---

## Features
1. Traffic light control for two main streets (Red, Yellow, Green LEDs).
2. Pedestrian crossing system with request buttons and Walk/Don't Walk signals.
3. Emergency pedestrian override mode to prioritize safety.
4. System implemented using FSM for state-based control.
5. Timed light cycles with smooth transitions.

---

## Hardware Requirements
1. Microcontroller: Atmega32.
2. LEDs:
   - **Traffic Lights**: 6 LEDs (Red, Yellow, Green for each street).
   - **Pedestrian Signals**: 2 LEDs (Walk, Don’t Walk for each street).
3. Push Buttons:
   - For pedestrian crossing requests.
4. Resistors and breadboard for connections.
5. Power supply (e.g., USB or battery pack).

---

## Testing Scenarios
1. Normal traffic light cycle without pedestrian request:
**Street 1 and Street 2 alternate in Red/Yellow/Green states.**
2. Pedestrian crossing request:
**Pedestrian button press triggers pedestrian crossing signal and stops traffic.**
3. Transition back to normal mode after pedestrian crossing.



## Circuit Diagram
<div align="center">
  <img src="Image/Hardware image.png" alt=" Project Features " width="650">
</div>

---

## Software Description
1. **Architecture**:  
   - The system uses a **Finite State Machine (FSM)** with states such as:
     - Normal Traffic Mode
     - Pedestrian Request Mode
     - Emergency Mode (override).
   - Each state has defined transitions triggered by timers or button presses.

2. **State Diagram**:  
![State Diagram (Finite State Machine Design](Image/State Diagram (Finite State Machine Design).png)

3. **Code Highlights**:
   - Organized into modular functions for readability.
   - Includes proper comments for every line/block.
   - Utilizes `delay` for timing and debouncing techniques for button handling.

---

## How to Set Up
### Hardware Setup:
1. Connect LEDs and buttons to the microcontroller as shown in the circuit diagram.
2. Ensure resistors are connected to protect LEDs.

### Software Setup:
1. Clone the repository:
   ```bash
   git clone https://github.com/Adel-Hani-Saaed/-traffic-light-control-system-for-a-typical-four-way-intersection-including-a-pedestrian-crossing.git
