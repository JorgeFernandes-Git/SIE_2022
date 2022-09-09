#include <xc.h>

void ADCconfig(uint8_t channel) {

    /* configure ADC */

    AD1PCFG = 0; // initialize analog component
    TRISBSET = (1 << channel); // select pin in port B as input
    AD1CHSbits.CH0SA = channel; // Select analog input
    AD1CHSbits.CH0NA = 0; // Channel 0 negative input is VR- 
    AD1CON1bits.FORM = 0b000; // Integer 16-bits  
    AD1CON1bits.SSRC = 0b000; // manual mode
    AD1CON1bits.ASAM = 1; // Auto sampling
    AD1CON2bits.VCFG = 0b000; // reference voltage
    AD1CON2bits.CSCNA = 0; // Disable Scan Mode

    // Set the number of conversions per interrupt to 1
    // (see PIC32 Family Reference Manual DS61104E-page 17-8)
    AD1CON2bits.SMPI = 0b000;

    // Set Buffer Fill Mode
    // The Buffer Fill mode allows the output buffer to be used as a 
    // single 16-word buffer or two 8-word buffers. 
    // When the Dual Buffer Mode bit, BUFM (AD1CON2<1>), is ?0?, 
    // the complete 16-word buffer is used for all conversion sequences
    // Setting for Single Buffer
    // (see PIC32 Family Reference Manual DS61104E-page 17-22)
    AD1CON2bits.BUFM = 0;

    // Selecting the MUX to be Connected to the ADC (Ref Man, 17.4.11)
    // Choosing 17.4.11.1  SINGLE INPUT SELECTION
    // ALTS : 0 = Always use MUX A input multiplexer settings
    // This is the simplest way: only one MUX is used
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
    // LAST THING TO DO!
    AD1CON1bits.ON = 1;
}
