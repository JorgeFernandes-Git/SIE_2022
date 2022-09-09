/*
 * 
 * File: Sensor Distance
 * Author: Jorge Fernandes and Rodrigo Ferreira
 * Created on Mar 9, 2022
 * 
 * Target: Digilent chipKIT MAx32 board 
 * Configurations:
 *      HSPLL; CPUCLK=80MHz, PBCLCK=40MHz; Watchdog timer disabled
 * 
 * Overview:
 *      This code converts the the value from ADC channel 0
 *      connected to a infrared sensor distance, from voltage
 *      to a corresponding distance in mm, and then print the result.
 *      The same voltage is use to generate 
 *      a proportional PWM OUTPUT
 *      It also turn on a LED when in range
 * 
 */

#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config_bits.h" 
#include "main.h"

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

int main(int argc, char** argv) {

    // Variable declarations;
    const uint8_t channel = 0; // ADC channel to read (here is A0)
    float voltage; // sampled voltage
    float mm_distance; // distance in mm
    float pwm; // for current circuit

    // call configuration functions
    Timer2Config();
    ADCconfig(channel);

    // Disable JTAG interface as it uses a few ADC ports
    DDPCONbits.JTAGEN = 0;

    /* pin direction */
    TRISGbits.TRISG6 = 0; // pin 52 for LED 

    // Init UART and redirect tdin/stdot/stderr to UART
    if (UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while (1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/

    // Main loop
    while (1) {
        // Get one sample
        IFS1bits.AD1IF = 0; // Reset interrupt flag
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0); // Wait fo EOC

        // Convert to 0..3.3V 
        voltage = (ADC1BUF0 * 3.3) / 1023;

        // quadratic function to convert voltage in distance in mm
        mm_distance = ((1.9166 * pow(voltage, 4))-(16.047 * pow(voltage, 3))+(50.496 * pow(voltage, 2))-(77.964 * voltage) + 67.634)*10;

        // invert pwm curve to make it proportional
        pwm = abs(ADC1BUF0 - 1023);

        // adjust output
        if (mm_distance > 600) {
            mm_distance = 610;
            pwm = 0;
        }
        if (mm_distance < 109) {
            pwm = 50;
        }

        // print result
        printf(",%3.0f", mm_distance);

        // turn on and off the LED
        if (mm_distance > 109 && mm_distance < 610) {
            LATGbits.LATG6 = 1; // LED ON
        } else {
            LATGbits.LATG6 = 0; // LED OFF
        }

        // PWM for current output circuit
        OC1RS = pwm;
    }

    return (EXIT_SUCCESS);


}