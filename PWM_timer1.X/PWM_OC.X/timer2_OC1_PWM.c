#include <xc.h>

void Timer2Config(void) {

    /* initialise TIMER2 for PWM */
    
     /* PBCLOCK = 40 MHz
     * prescaler 1:2 -> timer1 frequency -> 40000000/2 = 20000000 Hz = 0.00000005 = 0.05 μs
     * disered frequency -> 2000 Hz = 0.0005 s
     * PR2 = 0.0005/0.00000005 = 10000
     * note that prescaler was arbitrary
     * see Section 14. Timers
     */

    /* Set timer2 */
    T2CONbits.ON = 0; // stop timer
    IFS0bits.T2IF = 0; // reset interrupt flag 
    IPC4bits.T4IP = 5; // set interrupt priority (1..7) *** Make sure it matches iplx in ISR declaration ***  
    IEC0bits.T4IE = 0; // enable T2 interrupts
    T2CONbits.TCKPS = 1; // 1:64 prescaler 
    T2CONbits.T32 = 0; // 16 bit timer operation

    PR2 = 999; // PR = 1024 , Prescaler = 256 , (Hz/2)=40000000/(PR*Prescaler) => Hz~2441  
    TMR2 = 0; // reset timer T2 count register

    /* Set OC1 - Output Compare for PWM */
    OC1CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode, PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL = 0; // Timer 2 is clock source of OCM, timer T2 as the time base for PWM generation

    /* the OC1RS set the next value of OC1R see Section 16. Output Compare */
    //OC1RS = 1000;

    OC1CONbits.ON = 1; // Enable OC1

    // Start PWM generation
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the timer configuration sequence)
}
