#include <pic12f1840.h>

extern void Init_input(void);
extern void Read_input(void);

enum {
    WINCH_MODE_UNINITIALIZED = 0,
    WINCH_MODE_OFF = 0x30,
    WINCH_MODE_IDLE = 0x31,
    WINCH_MODE_IN = 0x32,
    WINCH_MODE_OUT = 0x33
} winch_mode = WINCH_MODE_UNINITIALIZED;

static unsigned char old_winch_mode = WINCH_MODE_UNINITIALIZED;

static void Init_hardware(void) {
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

static void Process_winch(void) {
    if (winch_mode != old_winch_mode) {
        switch(winch_mode) {
        case WINCH_MODE_OFF:
            break;
        case WINCH_MODE_IDLE:
            break;
        case WINCH_MODE_IN:
            break;
        case WINCH_MODE_OUT:
            break;
        default:
            break;
        }

        old_winch_mode = winch_mode;
    }
}

void main(void) {
    Init_hardware();
    Init_input();
    
    while (1) {
        Read_input();
        Process_winch();
    }
}

