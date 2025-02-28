#include "M1_control.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"

// Define motor control pins
#define IN1 GPIO_PIN_3
#define IN2 GPIO_PIN_4
#define ENA GPIO_PIN_6

void M1_control() {
    // Set PWM clock divider to 1
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Enable necessary peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Wait for peripherals to be ready
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0));

    // Configure PB6 as a PWM output (M0PWM0)
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    // Configure PA3 & PA4 as digital output for motor direction
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, IN1 | IN2);

    // Set initial motor direction to STOP (both low)
    GPIOPinWrite(GPIO_PORTA_BASE, IN1 | IN2, 0);

    // Configure PWM Generator 0 for count-down mode
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    // Set PWM period (defines frequency)
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 1000);

    // Set PWM duty cycle (50% of 1000)
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 500);

    // Enable PWM generator
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Enable PWM output on PB6 (PWM0 Output 0)
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
}
