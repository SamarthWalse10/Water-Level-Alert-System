# Water-Level-Alert-System
A Water Level Alert System using a TTGO SIM7600e-H and a 40A solid state relay to send SMS alerts and automatically control an AC water pump for flood management.

This project is a Water Level Alert System designed to manage flood situations in an apartment. It utilizes a TTGO SIM7600e-H development board and a 40A solid state relay to control an AC water pump. The system operates by monitoring water levels using a transistor-based sensor with two thresholds: minimum and maximum. When the water reaches the minimum threshold, an SMS alert is sent and the SIM7600 module wakes from sleep mode. If the water continues to rise and reaches the maximum threshold, the pump is activated and another SMS alert is sent. The pump will drain the water until the level drops below the minimum threshold, at which point the pump turns off and a final SMS alert is sent, after which the SIM7600 module returns to sleep mode to conserve power.
## Features
- SMS Alerts: Sends SMS notifications when water reaches specified thresholds.
- Automatic Pump Control: Automatically turns the water pump on and off based on the water level.
- Energy Efficient: Utilizes sleep mode in the SIM7600 module to conserve power when the system is idle.
- High Current Handling: Controls an AC water pump with up to 40A current using a solid state relay.
- Transistor-Based Sensor: Monitors water levels accurately using a simple and reliable transistor circuit.
## Components Required
1. TTGO SIM7600e-H Development Board: Used for GSM communication and SMS alerts.
2. 40A Solid State Relay: Controls the AC water pump based on signals from the development board.
3. Transistor-Based Water Level Sensor: Monitors water levels with two thresholds (minimum and maximum).
4. AC Water Pump: Drains water from the apartment during flood situations.
5. SIM Card: Provides SMS capability for the SIM7600 module.
6. Jumper Wires and Connectors: For connecting components on breadboard or PCB.
7. 5V Power Supply: Supplies power to the development board.
## Getting Started
- Clone the repository:
   ```bash
   git clone https://github.com/SamarthWalse10/Water-Level-Alert-System.git
- Upload the provided code to the TTGO SIM7600e-H development board using your preferred IDE.
- Install the SoftwareSerial library for communicating with the SIM7600 module.
- Modify the code as needed to configure SMS recipient numbers, threshold values, and other parameters specific to your setup.
- Insert the SIM Card into the TTGO development board.
- Power on the system and monitor the serial output (e.g., Arduino Serial Monitor) for debugging and status messages.
- Observe the system's behavior as the water level reaches the defined thresholds:
- SMS alerts will be sent when the water level reaches the minimum and maximum thresholds.
- The water pump will automatically turn on and off based on the water level.
## Screenshots
![WhatsApp Image 2024-07-08 at 14 40 06_17eaceef (1)](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/746ff6c3-9b9a-40a3-964b-862417bb46a0)
![WhatsApp Image 2024-07-08 at 15 06 18_44cc2e2a](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/647c0145-fcda-419a-b849-5644e54f1b69)
![WhatsApp Image 2024-07-08 at 15 06 19_18614e45](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/0635f996-a26d-48ef-beb0-9e001ffebea0)
![WhatsApp Image 2024-07-08 at 15 06 19_cde7112d](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/83314c8c-aabd-4918-9433-dbcbde30a1cd)
![WhatsApp Image 2024-07-08 at 15 06 20_b560f216](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/0a24270d-9f3d-40ae-a6b6-2d4685f09e97)
![WhatsApp Image 2024-07-08 at 15 06 20_3ef4d25f](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/d099013f-f822-4737-a055-75e9de2cfd43)
![WhatsApp Image 2024-07-08 at 15 06 20_85866c97](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/da721d7e-526c-4d01-bdb5-9da326bf2453)
![WhatsApp Image 2024-07-08 at 15 06 21_c215d706](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/44a00325-4e6f-4e81-a046-c73b3a31c3c1)
![WhatsApp Image 2024-07-08 at 15 14 10_1f616329](https://github.com/SamarthWalse10/Water-Level-Alert-System/assets/125689593/7f5d8705-95d1-4807-bb2a-3e2d68ae9f3d)
