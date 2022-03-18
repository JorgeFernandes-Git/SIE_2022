/*
 * File: PWM_OC
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "config_bits.h" 
#include "main.h"

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

// variables
const uint8_t channel = 0; // ADC channel to read (here is A0)
int duty_cycle; // duty cycle in percentage
int duty = 0; // value to duty cycle from input

int main(int argc, char** argv) {

    /* INITIALIZATION */

    /* configure timers */
    Timer2Config();
    ADCconfig(channel);

    /* initialise UART communication */
    if (UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        // LD4 will go on if there is any error
        PORTAbits.RA3 = 1;
        while (1);
    }

    /* pin directions */
    /* board LEDs for debug*/
    TRISAbits.TRISA3 = 0; // LD5
    TRISCbits.TRISC1 = 0; // LD4

    /* initial pin state */
    PORTCbits.RC1 = 0;
    PORTAbits.RA3 = 0;


    /* initiate sampling 
     * see sections 17.4.15 and 17.5.8 of the reference manual
     */
    AD1CON1bits.SAMP = 0;

    /* PROCESSING LOOP */

    while (1) {
        /* PWM control - GENERATE PWM ON PIN 3 - OC1 see chipkit max32 pinout table */

        uint16_t ADCval; // variable to store the converted value

        /* wait for conversion to complete: */
        while (AD1CON1bits.DONE == 0);

        /* the value is converted, read the new value */
        ADCval = ADC1BUF0;
        //        printf("ADC: %d\r\n", ADCval);

        // pass value of ADC (0 to 1023) to duty and to OC1RS
        duty = ADCval;
        OC1RS = duty;

        // change on board LEDs LD5 and LD4
        if (duty <= 50) {
            PORTCbits.RC1 = 1;
            PORTAbits.RA3 = 0;
        } else if (duty >= 950) {
            PORTCbits.RC1 = 0;
            PORTAbits.RA3 = 1;
        }

        /* convert duty cycle to percentage values */
        duty_cycle = duty / 10;
        if (duty_cycle > 100) {
            duty_cycle = 100;
        }

        printf("Duty Cycle: %d\r\n\n\n", duty_cycle);

        /* Start the new conversion */
        /* Clearing the SAMP bit terminates sampling and starts conversion */
        AD1CON1bits.SAMP = 0;
    }
    return (EXIT_SUCCESS);
}
