/*
 * File: MotorDC_encoder
 */
#include "config_bits.h" 
#include "main.h"
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/attribs.h>
#include <stdlib.h>

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

/* call functions */
void motor_direction();
void PI_calc();

/* variables */
int cw = 0; // clockwise
int ccw = 0; // counterclockwise

char receive; // uart receive char

int SP_in_percentage; // speed in percentage
int SP_motor = 10; // value of speed from UART
int PV_motor = 0; // value from encoder pulses
int PI_motor = 0; // speed after PI adjustment

uint8_t min_speed = 10; // motor min speed in interface
uint8_t max_speed = 50; // motor max speed in interface
uint8_t motor_max_rpm = 50; // CONFIRM ON THE MOTOR

/* PI params - make all volatile 
 * to inform the controller to watch this variables
 * and don't make assumptions about it */
volatile float kp = 0.01; // PI kp from interface
volatile float ki = 0.01; // PI ki from interface
volatile int error = 0; // PI error
volatile int sum_error = 0; // PI sum of errors
volatile int count = 0; // encoder pulse counts A channel

/* external interrupt on pin INT 1 - PIN 2 */
// Declare ISR. Be careful to put the right vector and match the IPL with 
// the one defined on the peripheral set-up

/* EXTERNAL INTERRUPTS NEED PULL DOWN RESISTOR */
void __ISR(_EXTERNAL_1_VECTOR, IPL6AUTO) ExtInt1ISR(void) {
    /* increment count for each encoder pulse - A channel */
    count++;
    IFS0bits.INT1IF = 0; // Reset interrupt flag
    //printf("%i", count);
}

/* interrupt by timer 3 - each 0.1 seconds - by timer3 config */
void __ISR(_TIMER_3_VECTOR, IPL5AUTO) T3Interrupt(void) {
    /* calculate real speed of motor each 0.1 sec 
     * and then adjust speed via PI control
     */
    PV_motor = ((count / 0.1)*60) / 180; // real rpm based on pulses
    count = 0; // reset counter for next iteration
    PI_calc(); // calc PI value
    //printf("%i", count);
    IFS0bits.T3IF = 0; // Reset interrupt flag
}

/* routine to assign motor direction */
void motor_direction() {
    if (ccw == 1) {
        LATDbits.LATD1 = 1;
    } else if (ccw == 0) {
        LATDbits.LATD1 = 0;
    }

    if (cw == 1) {
        LATDbits.LATD2 = 1;
    } else if (cw == 0) {
        LATDbits.LATD2 = 0;
    }
}

/* PI calculation to send to OC1RS PWM - PIN 3 */
void PI_calc() {
    error = SP_motor - PV_motor; // PV comes from encoder pulses
    sum_error += error;
    PI_motor = error * kp + sum_error*ki;

    /* PWM control - GENERATE PWM ON PIN 3 - OC1 see chipkit max32 pinout table */
    OC1RS = (PI_motor * 1023) / motor_max_rpm; // OC1RS GOES FROM 0 TO 1023 BY TIMER2 PARAMS

    /* convert speed to percentage values */
    SP_in_percentage = ((PI_motor * 1023) / motor_max_rpm) / 10;

    if (SP_in_percentage > 100) {
        SP_in_percentage = 100;
    }
    printf("%i", PV_motor);
}

/* main */
int main(int argc, char** argv) {

    /* INITIALIZATION */

    /* Disable JTAG interface as it uses a few ADC ports
     * just in case - probably not needed here */
    //DDPCONbits.JTAGEN = 0;

    /* needed to activate interrupts */
    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;

    /* pin directions */
    //TRISGbits.TRISG6 = 0; // pin 52 as output for LED
    TRISDbits.TRISD1 = 0; // pin 5 output
    TRISDbits.TRISD2 = 0; // pin 6 output

    /* board LEDs for debug*/
    TRISAbits.TRISA3 = 0;
    TRISCbits.TRISC1 = 0;

    /* initial pin state */
    PORTAbits.RA3 = 0;
    PORTCbits.RC1 = 0;

    /* initialise UART communication */
    if (UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        // LD4 will go on if there is any error
        PORTAbits.RA3 = 1;
        while (1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1 */

    //    printf("TEST\r\n");
    //    printf("TEST 1\r\n");
    //    printf("TEST 2\r\n");
    //    printf("TEST 3\r\n\r\n");

    /* configure timers */
    //Timer1Config(); // not used here
    Timer2Config(); // generate PWM on OC1
    Timer3Config(); // adjust PI control on each 0.1 sec

    /* init external interrupts INT1 - PIN 2 */
    //Init_External_Int1(); // initialise external interrupts

    /* Enable Interrupt Exceptions */
    // set the CP0 status IE bit high to turn on interrupts globally
    __builtin_enable_interrupts();

    /* PROCESSING LOOP */
    while (1) {

        while (GetChar(&receive) != UART_SUCCESS);

        switch (receive) {
            case 0: // stop
                ccw = 0;
                cw = 0;
                break;
            case 1: // start
                ccw = 0;
                cw = 1;
                break;
            case 2: // cw
                ccw = 1;
                cw = 0;
                break;
            case 3: // ccw
                ccw = 0;
                cw = 1;
                break;
            case 4: // kp inc
                kp = kp + 0.01;
                break;
            case 5: // kp inc
                kp = kp - 0.01;
                break;
            case 6: // kp inc
                ki = ki + 0.01;
                break;
            case 7: // kp inc
                ki = ki - 0.01;
                break;
            default:
                break;
        }

        /* assign SP speed from interface */
        if (receive >= min_speed && receive <= max_speed)SP_motor = receive;

        /* call direction */
        motor_direction();

        // printf("%i\r\n\n\n", receive);
        // printf("%i", count);
        // printf("%2.2f", ki);
    }
    return (EXIT_SUCCESS);
}