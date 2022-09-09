#include <xc.h>

void Timer1Config(void) {

    /* Timer 1 configuration */
    T1CONbits.ON = 0;
    T1CONbits.TGATE = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0b10;
    T1CONbits.TSYNC = 0;
    PR1 = 625;
    T1CONbits.ON = 1;
}

void delayms(uint32_t maxval) {

    uint32_t cnt;

    for (cnt = 0; cnt < maxval; cnt++) {
        IFS0bits.T1IF = 0; /* clean timer1 interrupt flag */
        while (IFS0bits.T1IF == 0) {
        }
    }
    return;
}