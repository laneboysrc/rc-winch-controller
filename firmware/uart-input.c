#include <pic12f1840.h>

extern unsigned char winch_mode;

#define FOSC 16                 // Osc frequency in MHz
#define BAUDRATE 38400          // Desired baudrate
#define BRGH_VALUE 1            // Either 0 or 1
#define SPBRG_VALUE (((10*FOSC*1000000/((64-(48*BRGH_VALUE))*BAUDRATE))+5)/10)-1

unsigned char rx;


/*****************************************************************************
 Init_input()

 Called once during start-up of the firmware.
 ****************************************************************************/
void Init_input(void) {
	SPBRG = SPBRG_VALUE;	// Baud Rate register, calculated by macro
	BRGH = BRGH_VALUE;

	SYNC=0;			// Disable Synchronous/Enable Asynchronous
	SPEN=1;			// Enable serial port
	TXEN=0;			// Disable transmission mode
	CREN=1;			// Enable reception mode
}


/*****************************************************************************
 Read_input

 Called once per mainloop to read the input signal.
 This function shall set the global variable winch_mode depending on the
 state transition logic desired.
 ****************************************************************************/
void Read_input(void) {
    // Note that for the UART input the state transition logic is handled
    // in whoever is sending the UART commands, the winch controller is
    // just setting winch_mode to whatever value comes in.

	do {
	    // Overflow error?
	    // Yes: toggle CREN and flush the receive register to clear the overflow
	    if (OERR) {
	        CREN = 0;
            WREG = RCREG;
            WREG = RCREG;
            WREG = RCREG;
	        CREN = 1;
	    }

	    // Frame error?
	    // Yes: read the receive register to clear the error
	    if (FERR) {
            WREG = RCREG;
	    }
	} while (!RCIF);    // Wait until valid character received

    rx = RCREG;
    if (rx >= 0x80  &&  rx <= 0x83) {
        winch_mode = rx;
    }
}

