#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "M1_control.h"
#include "UART_comm.h"
int main(void)
{
    // Set system clock to 80 MHz
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);

    // Initialize motor control and UART communication
    M1_control();
    UART_COMM();

       while (1) {

            // Wait until a character is available
                    if (UARTCharsAvail(UART0_BASE)) {
                        char c = UARTCharGet(UART0_BASE);  // Receive character

                        switch (c) {
                            case 'a':  // Red LED (PF1)
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
                                UART_SendString("Red LED ON\r\n");
                                break;

                            case 's':  // Blue LED (PF2)
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
                                UART_SendString("Blue LED ON\r\n");
                                break;

                            case 'd':  // Green LED (PF3)
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
                                UART_SendString("Green LED ON\r\n");
                                break;

                            case 'f':  // Move forward
                                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);  // Set IN1 high
                                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);           // Set IN2 low
                                UART_SendString("Motor ON (Forward)\r\n");
                                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 750);  // Increase duty cycle (Speed up)
                                break;

                            case 'g':  // Stop motor
                                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4, 0);  // Set IN1 & IN2 low
                                UART_SendString("Motor OFF\r\n");
                                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 0);  // Stop PWM output (0% duty cycle)
                                break;

                            default:
                                UART_SendString("Unknown Command!\r\n");
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                                break;
                        }
                    }
        }
    return 0;
}
