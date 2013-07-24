#include <pic12f1840.h>

extern unsigned char winch_mode;

#define FOSC 16                 // Osc frequency in MHz
#define BAUDRATE 38400          // Desired baudrate
#define BRGH_VALUE 1            // Either 0 or 1
#define SPBRG_VALUE (((10*FOSC*1000000/((64-(48*BRGH_VALUE))*BAUDRATE))+5)/10)-1


void Init_input(void) {
	TRISA1 = 1;             // RX port must be 1 for UART to work

	SPBRG = SPBRG_VALUE;	// Baud Rate register, calculated by macro
	BRGH = BRGH_VALUE;

	SYNC=0;			// Disable Synchronous/Enable Asynchronous
	SPEN=1;			// Enable serial port
	TXEN=0;			// Disable transmission mode
	CREN=1;			// Enable reception mode
}

void Read_input(void) {
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
	    
    winch_mode = RCREG;	
}

