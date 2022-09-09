#include <xc.h>

void Timer3Config(void) {

    /* Timer3 configuration */


    /* PBCLOCK = 40 MHz
     * prescaler 1:256 -> timer3 frequency -> 40000000/256 = 156250 Hz = 0.0000064 s = 6.4 μs
     * disered frequency -> 10 Hz = 0.1 s = 100 ms
     * PR3 = 0.1/0.0000064 = 15625
     * note that prescaler was arbitrary
     * see Section 14. Timers
     */

    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF = 0; //reset interrupt flag
//    IPC3bits.T3IP = 2; //set interrupt priority (1..7) *** Make sure it matches iplx in ISR declaration ***
    IPC3bits.T3IP = 5;
    IEC0bits.T3IE = 1; // Enable T3 interrupts
    T3CONbits.TCKPS = 7; // 1:256

    //PR3 = 64298; 
    PR3 = 15625; // 10 Hz -> 0.1 s
    //PR3=156249; // 1 Hz -> 1 s
    //PR3=31249; // 5 Hz -> 0.2 s
    //PR3=78124; // 2 Hz -> 0.5 s

    TMR3 = 0; // Reset timer T3 count register 
    T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the timer configuration sequence)
}