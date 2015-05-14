#include <pic12f1840.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_OFF & _CLKOUTEN_OFF & _IESO_OFF & _FCMEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_OFF & _STVREN_OFF & _LVP_OFF;


/*

Pin 7   RA0/ICSPDAT     Servo output to 3-Racing winch
Pin 6   RA1/ICSPCLK     Servo input from receiver
Pin 5   RA2/CCP1        NC
Pin 4   RA3/Vpp         ICSP
Pin 3   RA4             NC
Pin 2   RA5/RX          NC
Pin 1   Vdd             +4.7V
Pin 8   Vss             GND

*/

extern void Init_input(void);
extern void Read_input(void);

enum {
    WINCH_MODE_UNINITIALIZED = 0,
    WINCH_MODE_OFF = 1,
    WINCH_MODE_OUT = 2,
    WINCH_MODE_OFF2 = 3,
    WINCH_MODE_IN = 4
} winch_mode = WINCH_MODE_UNINITIALIZED;

static volatile unsigned char duration_counter;


/*****************************************************************************
 Init_hardware()

 Initializes all used peripherals of the PIC chip.
 ****************************************************************************/
static void Init_hardware(void) {
    //-----------------------------
    // Clock initialization
    OSCCON = 0b01111010;    // 4x PLL disabled, 16 MHz HF, Internal oscillator

    //-----------------------------
    // IO Port initialization
    ANSELA = 0;
    LATA = 0b00000001;
    TRISA = 0b11111110;     // Make all ports except RA0

    //-----------------------------
    // Initialize Timer1 for 1 MHz operation
    // Compare mode off
    T1CON = 0b00100000;
    CCP1CON = 0b00000000;

    // Enable interrupts (though non specific is active at this point)
    PEIE = 1;
    GIE = 1;
}


/*****************************************************************************
 Process_winch()

 Turns the winch on/off depending on the requested winch mode, and play
 songs if needed.
 ****************************************************************************/
static void Process_winch(void) {
    switch(winch_mode) {
        case WINCH_MODE_IN:
                CCPR1L = 1500;
                CCPR1H = 1500 >> 8;
            break;

        case WINCH_MODE_OUT:
                CCPR1L = 2000;
                CCPR1H = 2000 >> 8;
            break;

        case WINCH_MODE_UNINITIALIZED:
        case WINCH_MODE_OFF:
        case WINCH_MODE_OFF2:
        default:
                CCPR1L = 1500;
                CCPR1H = 1500 >> 8;
            break;
    }

    TMR1H = 0;          // Start the timer from 0
    TMR1L = 0;
    CCP1IF = 0;         // Clear the compare event flag

    TMR1ON = 1;         // Start timer 1
    LATA0 = 1;          // Set servo output
    while (!CCP1IF);    // Wait for compare value reached
    LATA0 = 0;          // Clear servo output

    TMR1ON = 0;         // Stop timer 1
}


/*****************************************************************************
 main()

 No introduction needed ...
 ****************************************************************************/
void main(void) {
    Init_hardware();
    Init_input();

    while (1) {
        Read_input();
        Process_winch();
    }
}

