#include <xc.h>

void Timer2Config(void) {

    /* initialise TIMER2 for PWM */

    /* PBCLOCK = 40 MHz
     * see Section 14. Timers
     * OC1RS GOES FROM 0 TO PR2
     */

    /* Set timer2 */
    T2CONbits.ON = 0; // stop timer
    IFS0bits.T2IF = 0; // reset interrupt flag 
    IEC0bits.T2IE = 0; /* Clear Interrupt Enable bit */
    T2CONbits.TCKPS = 1; // 1:2 prescaler
    T2CONbits.T32 = 0; // 16 bit timer operation

    PR2 = 1000; // 20 kHz // PR = 1000 , Prescaler = 16, (40MHz/16 = 20MHz; (1/20M)*1000 ~ 0.0004s ~ 2500 hz)
    TMR2 = 0; // reset timer T2 count register

    /* Set OC1 - Output Compare for PWM */
    OC1CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode, PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL = 0; // Timer 2 is clock source of OCM, timer T2 as the time base for PWM generation
    OC1CONbits.ON = 1; // Enable OC1
    TRISDbits.TRISD0 = 0; // PIN 3 AS OUTPUT
    ODCDbits.ODCD0 = 1; // set as open-drain

    // Start PWM generation
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the timer configuration sequence)
}
