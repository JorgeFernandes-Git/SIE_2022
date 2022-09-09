/* 
 * File:   adc_read_multi.c
 * Author: Pedro Fonseca
 * Adapted by: Jorge Fernandes 104580 - Jun 2022
 *
 * Reading of multiple channels using the Scan mode and Timer3 as clock source. 
 * Example configuration reads channels AN0, AN1. 
 * Timer3 is configured for 2Hz frequency (1 set of 2 readings every 0.5 second). 
 * 
 * Note that sampling is sequential: at every 1/2 of 0.5 second, one of the 
 * channels is read and converted. When 2 channels are read, the ADC raises
 * the interrupt flag (AD1IF). 
 * 
 * More info: https://microchipdeveloper.com/32bit:adc-overview 
 *
 */

#include <xc.h>

// Bit map to define the analog channels to read
#define ADCSCANMAP   0b00000011    // Read AN channels 0 and 1

/**
 * Configures the Timer3
 * 
 * Timer3 is set to a 2Hz frequency (a set of 2 reading every 0.5 second)
 * 
 */

/**
 * ADC configuration
 * 
 * Fixed features: 
 * - 16-bit format
 * - manual mode
 * - Autosampling
 * - Scan mode enabled
 * - Voltage references: AVdd and AVss
 * - 2 conversions per interrupt
 * - single 16-word buffer
 * - Always use MUX A
 * - ADC Clock from PB clock
 */

void ADCconfig(void) {

    //Configuração ADC

    //Ativação da componente analógica
    AD1PCFG = 0;

    //Todos os pinos da porta B como input
    TRISB = 0xFF;

    // Select analog input
    AD1CHSbits.CH0SA = 2;

    // Channel 0 negative input is VR- 
    AD1CHSbits.CH0NA = 0;

    //Integer 16-bits
    AD1CON1bits.FORM = 0b000;

    // Conversion Trigger Source Select bits
    // Timer3 period match ends sampling and starts conversion
    AD1CON1bits.SSRC = 0b010;

    // In Automatic Mode, rate  selected  by  the  SAMC<4:0> bits (AD1CON3<12:8>
    AD1CON3bits.SAMC = 31;

    //Auto sampling
    AD1CON1bits.ASAM = 1;

    // Tensão de referência
    AD1CON2bits.VCFG = 0b000;

    // Enable Scan Mode
    // Scan mode allows to read from a set of different analogue inputs. 
    // See Ref. Man. section 17.4.8.1
    AD1CON2bits.CSCNA = 1;
    // When Scan mode is enabled, AD1CSSL register defines the analogue
    // channels to read
    AD1CSSL = ADCSCANMAP; // Read AN0 and AN1


    // Set the number of conversions per interrupt to 2
    // (there are 2 channels to read in sequence)
    // (see PIC32 Family Reference Manual DS61104E-page 17-8)
    AD1CON2bits.SMPI = 1;

    // Set Buffer Fill Mode
    // The Buffer Fill mode allows the output buffer to be used as a 
    // single 16-word buffer or two 8-word buffers. 
    // When the Dual Buffer Mode bit, BUFM (AD1CON2<1>), is ‘0’, 
    // the complete 16-word buffer is used for all conversion sequences
    // Setting for Single Buffer
    // (see PIC32 Family Reference Manual DS61104E-page 17-22)
    AD1CON2bits.BUFM = 0;

    // Selecting the MUX to be Connected to the ADC (Ref Man, 17.4.11)
    // Choosing 17.4.11.1  SINGLE INPUT SELECTION
    // ALTS : 0 = Always use MUX A input multiplexer settings
    // 
    // (See PIC32 Family Reference Manual DS61104E-page 17-22)
    AD1CON2bits.ALTS = 0;

    // 17.4.12   Selecting the ADC Conversion Clock Source and Prescaler
    // The ADC module can use the internal RC oscillator or the Peripheral 
    // Bus Clock (PBCLK) as the conversion clock source. 
    //
    // This allows to choose the clock source for the ADC to be the Internal RC
    // oscillator or the Peripheral Bus (PB) Clock. Note that the RC oscillator
    // is not calibrated and it is intended to be used in Sleep Mode. 
    // 
    // So will choose the PB clock. Check figure 23-2 in PIC32MX5/6/7 datasheet
    // https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MX5XX6XX7XX_Family)Datasheet_DS60001156K.pdf 
    AD1CON3bits.ADRC = 0;
    // When using the PB clock, we must program the 
    // ADC Conversion Clock Multiplier (bits ADCS<7:0>)
    // The minimum value for T_AD is 83.33ns.
    // When using PB clock, T_AD is 
    // T_AD = 2 (T_PB*(ADCS+1))
    // where T_PB is the PB clock period. 
    // We have a running frequency of 40MHz for PB, so T_PB=25ns
    // Setting a "comfortable" value for T_AD = 400ns, yields ADCS = 7
    AD1CON3bits.ADCS = 7;

    // Turn ADC on
    // *** THIS IS THE LAST THING TO DO! ***
    AD1CON1bits.ON = 1;

    /*
     *  End of ADC configuration 
     */

}

void Timer3Config(void) {
    /* Program Timer 3 */

    /* PBCLOCK = 20 MHz
     * see Section 14. Timers
     */

    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF = 0; /* Clear Interrupt Flag */
    IEC0bits.T3IE = 0; /* Clear Interrupt Enable bit */
    T3CONbits.TCKPS = 7; /* Set prescaler to divide by 256 */
    PR3 = 39063; /* Set the period register */

    TMR3 = 0; /* Clear the timer register */
    T3CONbits.TON = 1; /* Start the timer */
}