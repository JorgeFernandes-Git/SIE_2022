/*
 * File: Sensor_Termopar
 */
#include "config_bits.h" 
#include "main.h"
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/attribs.h>
#include <stdlib.h>
#include <math.h>

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

/* call functions */
void PI_calc();

/* variables */
char receive; // uart receive char

// thermistor variables
const int beta = 3250; // beta for thermistor, from datasheet
const int r0 = 330; // thermistor resistance at 25ºC
const int r1 = 1000; // resistor in series with the thermistor
float rt = 0.0; // convert ADC value in thermistor resistance
const float t0 = 298; // 25ºC
float t_tm = 0.0; // real thermistor temperature
const float vcc = 2.51; // voltage supply thermistor
float v_tm = 0.0; // thermistor voltage at a temperature

// thermocouple variables
float t_tc = 0.0;
float v_tc = 0.0;

// general variables
float final_T = 0;
float SP_temperature = 0; // value of speed from UART
float PV_temperature = 0; // value from encoder pulses
float PI_temperature = 0; // speed after PI adjustment
const uint8_t min_temperature = 40; // min temperature in interface
const uint8_t max_temperature = 100; // max temperature in interface
const uint8_t res_max_temperature = 110; // max temp (above 100ºC to heat faster)

/* PI params - make all volatile 
 * to inform the controller to watch this variables
 * and don't make assumptions about it */
volatile float kp = 0.04; // PI kp from interface
volatile float ki = 0.03; // PI ki from interface
volatile int error = 0; // PI error
volatile int sum_error = 0; // PI sum of errors
volatile int erroarray[3]; 
int c=0; 

/* PI calculation to send to OC1RS PWM - PIN 3 */
void PI_calc() {
    if (c<3){
        erroarray[c]=SP_temperature - PV_temperature;
        c++; 
    }else{
        c=0;
    }
    error = SP_temperature - PV_temperature; // PV comes from encoder pulses
    //sum_error += error;
    sum_error = erroarray[0]+erroarray[1]+erroarray[2];
    PI_temperature = error * kp + sum_error*ki;
    if (PI_temperature < 0) {
        PI_temperature = 1;
    }
    /* PWM control - GENERATE PWM ON PIN 3 - OC1 see chipkit max32 pinout table */
    OC1RS = (PI_temperature * 1000) / res_max_temperature; // OC1RS GOES FROM 0 TO 1023 BY TIMER2 PARAMS

    printf("%.1f,%.1f,%.1f \n", PV_temperature,t_tm,t_tc);
}

/* main */
int main(int argc, char** argv) {

    /* INITIALIZATION */

    uint32_t ADCval[2]; /** variable to store the converted value */
    //rx = r0 * exp(-beta / t0); // from beta method for thermistors

    /* initialise UART communication */
    if (UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        // LD4 will go on if there is any error
        PORTAbits.RA3 = 1;
        while (1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1 */

    /* pin directions */
    //TRISGbits.TRISG6 = 0; // pin 52 as output

    /* board LEDs for debug*/
    TRISAbits.TRISA3 = 0;
    TRISCbits.TRISC1 = 0;

    /* initial pin state */
    PORTCbits.RC1 = 0;
    PORTGbits.RG6 = 0;

    //    printf("TEST\r\n");
    //    printf("TEST 1\r\n");
    //    printf("TEST 2\r\n");
    //    printf("TEST 3\r\n\r\n");

    /* configure timers and ADC */
    Timer1Config(); // for use delay function
    Timer2Config(); // generate PWM on OC1
    Timer3Config(); // timer for multiple ADC
    ADCconfig(); // ADC config

    /* PROCESSING LOOP */
    while (1) {

        if (GetChar(&receive) == UART_SUCCESS) {
            switch (receive) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
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

            if (receive >= min_temperature && receive <= max_temperature) {
                SP_temperature = receive;
            }
        }

        /* Wait for conversion to complete: */
        /* The configuration is set for 2 conversions per interrupt (SMPI=1) */
        /* The interrupt flag is set after performing 2 conversions */
        IFS1bits.AD1IF = 0; // Reset interrupt flag
        AD1CON1bits.ASAM = 1; // Start conversion
        //while (IFS1bits.AD1IF == 0);

        /* The value is converted, read the new value */
        /* As we have 2 readings per interrupt, the values are stored 
         * in the first 2 buffers. */
        ADCval[0] = ADC1BUF0; // First buffer: AN0 - THERMISTOR
        ADCval[1] = ADC1BUF1; // Second buffer: AN1 - THERMOCOUPLE

        /* Clear the interrupt flag */
        /* Note: the ADC1BUFx registers must be read before clearing the flag
         * Trying to clear the AD1IF bit before reading all the necessary ADC 
         * buffers has no effect (the flag remains active). The hardware circuit 
         * allows clearing the flag only after reading all the converted values
         */
        IFS1bits.AD1IF = 0;

        /* Print the result */
        //        int i;
        //        for (i = 0; i < 2; i++) {
        //            printf("ADC[%d]: %d\t", i, ADCval[i]);
        //        }
        //        printf("\r\n");

        // THERMISTOR CODE ***************************
        if (ADCval[0] > 1022) {
            ADCval[0] = 1022;
        }
        if (ADCval[0] < 1) {
            ADCval[0] = 1;
        }
        v_tm = (3.3 * ADCval[0]) / 1023; // convert ADC to voltage
        rt = v_tm / ((vcc - v_tm) / r1); // convert voltage to resistance - ohms law
        // calculate temperature //
        //        t_tm = log(rt / r0); // ln(R/R0)
        //        t_tm = t_tm * 1 / beta; // ln(R/R0)*1/beta
        //        t_tm = t_tm + 1 / t0; // ln(R/R0)*1/beta + 1/T0
        //        t_tm = 1 / t_tm; // 1/(ln(R/R0)*1/beta + 1/T0)
        t_tm = 1 / ((1 / t0) + (log(rt / r0) / beta));
        t_tm = t_tm - 273; // K to ºC
        //printf("Thermistor T: %.0f ºC, ADC: %d\r\n", t_tm, ADCval[0]);
        // *******************************************

        // THERMOCOUPLE CODE *************************
        v_tc = (3.3 * ADCval[1]) / 1023; // convert from ADC to voltage
        t_tc = 48 * v_tc; // equation for temperature from voltage - EXCEL
        //printf("Thermocouple T: %.0f ºC\r\n", t_tc);
        // *******************************************

        // REAL TEMPERATURE **************************
        final_T = t_tc + t_tm; // thermocouple temp minus thermistor temp
        //printf("Real T: %.0f ºC\r\n", final_T);
        // *******************************************

        delayms(1000);

        //OC1RS = 300; // PIN 3

        PV_temperature = final_T; // real temperature
        PI_calc(); // calc PI value

    }

    return (EXIT_SUCCESS);

}