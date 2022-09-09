void Init_External_Int1() {

    /* TEACHER CONFIGURATION */
    /* INT 1 ON PIN 2 */
    TRISEbits.TRISE8 = 1; //RE8 as input (INT1)
    //TRISDbits.TRISD8 = 1; // Set pin as input
    INTCONbits.INT1EP = 0; // Generat interrupts on {rising edge-1 falling edge - 0}
    IFS0bits.INT1IF = 0; // Reset int flag
    IPC1bits.INT1IP = 6; // Set interrupt priority (1..7) *** Set equal to IPLX in ISR
    IEC0bits.INT1IE = 1; // Enable Int1 interrupts
    
}