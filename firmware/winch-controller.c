#include <pic12f1840.h>

extern void Init_input(void);
extern void Read_input(void);

unsigned char winch_mode = 0;

void Init_hardware(void) {
    //-----------------------------
    // Clock initialization
    OSCCON = 0b01111010;    // 4x PLL disabled, 16 MHz HF, Internal oscillator

    //-----------------------------
    // IO Port initialization
    PORTA = 0;
    LATA = 0;
    ANSELA = 0;
    TRISA = 0b11111111;     // Make all ports A input
    APFCON = 0b00000000;    // Use RA0/RA1 for UART TX/RX
    
    //-----------------------------
    // Initialize Timer1 for 1 MHz operation
    T1CON = 0b00100000; 
}

void main(void) {
    Init_hardware();
    Init_input();
    
    while (1) {
        Read_input();
    }
}

