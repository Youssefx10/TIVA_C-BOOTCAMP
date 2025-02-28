# TIVA_C-BOOTCAMP
#Tiva_C_Motor_and_UART_Control_System
Project Overview
This project implements motor control and UART communication on a Tiva C Series (TM4C123G) microcontroller. The system uses PWM signals to control a DC motor and UART communication to receive user inputs and control an LED based on received commands.

Features
✅ Motor Control via PWM:

Generates a PWM signal to control motor speed and direction.
Uses GPIO and PWM modules for efficient motor operation.
✅ UART Communication:

Receives data from the serial terminal.
Controls on-board LEDs (PF1, PF2, PF3) based on user input.
Echoes received characters for verification.
✅ Embedded System Design:

Utilizes Tiva C clock settings (80 MHz) for optimal performance.
Configures GPIO, PWM, and UART modules correctly.
Hardware Requirements
🔹 Tiva C Series TM4C123G LaunchPad
🔹 DC Motor + Motor Driver (L298N or similar)
🔹 USB-to-UART Converter (Optional, if using PC for serial input)
🔹 LEDs (On-board PF1, PF2, PF3 used for status indication)

Software Requirements
💻 Code Composer Studio (CCS) / Keil uVision
💻 TivaWare Peripheral Library
💻 PuTTY / Tera Term (for UART communication)

How It Works
1. Motor Control (M1_control.c)
Configures PWM0 to generate a variable duty cycle.
Controls motor direction using IN1, IN2 signals.
2. UART Communication (UART_comm.c)
Initializes UART0 to receive user inputs.
Listens for commands:
'a' → Turns Red LED ON
's' → Turns Blue LED ON
'd' → Turns Green LED ON
Other inputs → Sends "Fick, dich!\r\n" (Change this if needed 😅).
3. Main Program (main.c)
Initializes system clock (80 MHz).
Calls M1_control() and UART_COMM().
Enters an infinite loop to keep the system running.
Installation & Usage
1. Clone the Repository
bash
Kopieren
Bearbeiten
git clone https://github.com/Youssefx10/TivaC_Motor_UART.git
cd TivaC_Motor_UART
2. Flash the Code to Tiva C
Open Code Composer Studio / Keil.
Import the project and compile.
Flash to your TM4C123G LaunchPad.
3. Connect to UART Terminal
Open PuTTY / Tera Term.
Set Baud Rate: 9600, Data: 8 bits, Parity: None, Stop: 1 bit.
Send 'a', 's', 'd' to control LEDs.
Future Improvements
🚀 Add PWM Speed Control via UART
🚀 Implement Bluetooth / Wi-Fi (ESP8266) Communication
🚀 Add LCD Display for Real-Time Status