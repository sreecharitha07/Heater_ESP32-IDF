# ***HEATER_ESP32-IDF***

## 1. OVER VIEW OF THE PROJECT

A temperature-based state tracker is a straightforward but powerful embedded system that continuously senses temperature and adjusts its operation based on how hot or cold it becomes. The temperature range should be divided into various levels, such as Target Reached, Heating, Stabilizing, Idle, and Overheat. The system should react in a certain way at each of these levels, also known as states. This type of configuration is helpful in fields where temperature directly influences how the system should operate, such as HVAC monitoring, industrial safety systems, and smart home control.

In this implementation, the system is developed using the ESP-IDF framework on an ESP32 microcontroller, utilizing FreeRTOS to manage periodic operations. Since physical temperature sensors like DS18B20 are not supported in the simulation environment in wokwi for ESP-IDF templates hence, the temperature values are simulated using the esp_random () function. The system transitions through five defined states—Idle, Heating, Stabilizing, Target Reached and Overheat—based on these simulated temperatures. Each state is indicated using dedicated LEDs, while a buzzer and heater output are controlled accordingly to reflect system behaviour. The buzzer is activated in the Overheat state, and the heater is turned off when overheating occurs, demonstrating a complete feedback loop for safe temperature control.

## 2. SOFTWARE TOOL USED

WOKWI 

Wokwi is an online simulator for embedded systems development, especially useful for prototyping microcontroller-based projects like those using the ESP32,STM32,ARDUINO. It allows users to write, compile, and test their code in a virtual environment without needing physical hardware. 

In our project, we used Wokwi to simulate the ESP32 along with LEDs, a heater indicator, and a buzzer in a ESP-IDF framework , making it easy to visualize and test our temperature-based state tracking system. Since Wokwi doesn’t support all sensors (like DS18B20) or actual BLE broadcasting, we used simulated values and serial output to verify functionality.

## 3. FEATURES

1. Simlulated Temperature Input - esp randomly simulates the temperature in between 25°C–45°C using the required libraries.
   
2. Based on the temperature we have classified into 5 states:
   
     • Idle
   
     • Heating
   
     • Stabilizing
   
     • Target Reached
   
     • Overheat
   
4. Heater control logic (ON/OFF) using an LED.

5. LED indicators for each state.

6. Serial monitor logging to display the following:

     • Cureent Temperature in celsius.

     • Current State
   
     • Heater Status(ON/OFF)
   
     • Buzzer Status

7. Buzzer alert when system is overheated

8. Implemented using FreeRTOS for task scheduling


## 4. HARDWARE COMPONENTS USED IN WOKWI

1. ESP32 - Development board

2. 5 LEDs - To indicate the system state as follows:

     •	IDLE -> Blue led
   
     •	HEATING -> Orange led
   
     •	STABLIZING -> Pink led
   
     •	TARGET REACHED -> Yellow led
   
     •	OVER HEATED -> Green led

3. 1 LED - To Indicate the HEATER status(ON/OFF)

     • TURN ON -> Red led

4. Resistors for each Led preferably 220Ω

   **Why Resistors are used?**

   Resistors limit the current flowing through the LED to prevent it from burning out.

   LEDs are sensitive to high current:

     • LEDs typically operate safely at ~20mA (0.02A).

     • If connected directly to a 3.3V (ESP32) or 5V (Arduino) pin without a resistor, too much current would flow → damaging the LED and possibly the microcontroller.

   **Resistor Calculation**
   
     • Resistance(R) = [ V(supply) - V(led) ] / I
   
     • V(supply) = 3.3V (ESP32) [For Ardunio its 5V]
   
     • V(led) = 2V (approx. for red LED; varies slightly with color)
   
     • I=0.02A ( desired current )

        R = [3.3V - 2V]/0.02A = 65Ω

   So, a resistor of 65Ω would be the absolute minimum for 20mA.

   But we add extra margin for protection, and 220Ω is a commonly available, safe value.

6. Breadboard	- For wiring and connections


## 5. HOW TO RUN IN WOKWI

1. Open Wokwi simulator.

2. Select ESP32 IDF Project template.

3. Write the main.c code according to the specifications.

4. Connect:

     • LEDs to GPIOs 14, 27, 26, 25, 33 (one per state)

     • Heater LED to GPIO 2

     • Buzzer to GPIO 4

     • Each resistor to should be connected each LEDs anode.

   Place the LEDS and resistors in the Bread boeard and make the connection with proper voltage and ground supply

5. Run the simulation and observe output via Serial Monitor.


## 6. STATE TRANSITION LOGIC



| Temperature Range     | State          | Heater |
|-----------------------|----------------|--------|
| < 0.1°C               | Idle           | OFF    |
| 0.1°C to < 30°C       | Heating        | ON     |
| 30°C to < 35°C        | Stabilizing    | ON     |
| 35°C to < 40°C        | TargetReached  | ON     |
| ≥ 40°C                | Overheat       | OFF    |


## 7. A FEW SNAP SHOTS OF THE PROJECT

1. Temperature > 40°C , State - Overheat , Heater should be OFF , Buzzer should be ON , GREEN LED GLOWS displayed in serial monitor.

<img width="940" height="576" alt="image" src="https://github.com/user-attachments/assets/2a2f5c58-1d36-4351-89ee-f9a70756b4b7" />

2. Temperature is in range 35°C to < 40°C , State - Target Reached  , Heater should be ON , RED LED for Heater and YELLOW LED For state GLOWS.

<img width="940" height="577" alt="image" src="https://github.com/user-attachments/assets/6f839b1e-9b69-4057-8961-7178bf9a4f94" />

3. Temperature is in range 0.1°C to < 30°C , State - Heating  , Heater should be ON , RED LED for Heater and ORANGE LED For state GLOWS.

<img width="940" height="572" alt="image" src="https://github.com/user-attachments/assets/4c3aa947-8db7-4527-843a-835773c3a428" />


## 8. CONCLUSION

This project successfully implements a temperature-based heater control system using the ESP32 development board and the ESP-IDF framework. The system continuously simulates temperature readings, detects the current temperature range, and transitions between various states — Idle, Heating, Stabilizing, Target Reached, and Overheat. Based on these states, the heater is automatically turned ON or OFF, and LEDs provide clear visual feedback for each condition.

Serial logging ensures that all temperature values, state transitions, and heater status are monitored in real-time, making the system transparent and easy to debug. The use of FreeRTOS enables smooth periodic operation with clear task management.

Although BLE functionality could not be fully demonstrated in the Wokwi simulation due to platform limitations, the structural BLE advertising logic was designed to broadcast the heater state in a real-world deployment.

## 9. FUTURE ENHANCEMENTS

While many of the features listed below are standard in commercial heater control systems, they represent valuable improvements that can be incorporated into this prototype to enhance its real-world functionality, reliability, and usability:

1. Touchscreen or OLED Display

   Provide real-time feedback directly on the device using a small screen for displaying temperature and state info.

2. Data Logging & Analytics
   
   Store temperature trends locally (SD card) or remotely (cloud) to analyze heating behavior over time.

3. Wireless Communication & IoT Integration:

   Add Bluetooth (BLE) or Wi-Fi to send data to smartphones or IoT platforms like Blynk, ThingsBoard, or Home Assistant.

   Implement remote control features via mobile apps or cloud dashboards.


## 10. AUTHOR

Vasuvandla Sree Charitha

July 2025




       



     
     
