#include <pic12f1840.h>
#include <stdint.h>

extern enum {
    WINCH_MODE_UNINITIALIZED = 0,
    WINCH_MODE_OFF = 1,
    WINCH_MODE_OUT = 2,
    WINCH_MODE_OFF2 = 3,
    WINCH_MODE_IN = 4
} winch_mode;

static struct {
    unsigned ch3_initialized : 1;
    unsigned ch3_state : 1;
    unsigned ch3_last_state : 1;
    unsigned ch3_transitioned : 1;
} f = {0, 0, 0, 0};


static uint8_t init_timer;


// All units are in 32.768 ms resolution
#define INITIALIZATION_TIMEOUT 30


/*****************************************************************************
 Service_soft_timer()

 Soft timer with a resolution of 32.768ms
 ****************************************************************************/
static void Service_soft_timer(void) {
    if (TMR2IF) {
        TMR2IF = 0;

        if (init_timer) {
            --init_timer;
        }
    }
}


/*****************************************************************************
 Init_input()

 Called once during start-up of the firmware.
 ****************************************************************************/
void Init_input(void) {
    /* Use Timer2 as soft timer with an interval of 32.768ms. This is half
       of what we would like to have, so software has to adjust for it.
    */
    PR2 = 0xff;
    T2CON = 0b00111111;     // 1:8 post scaler; timer on; Prescaler is 64
}


/*****************************************************************************
 Read_input

 Called once per mainloop to read the input signal.
 This function shall set the global variable winch_mode depending on the
 state transition logic desired.
 ****************************************************************************/
void Read_input(void) {
    unsigned int ch3;

    // If we are starting up delay this function for approx 1 second.
    if (winch_mode == WINCH_MODE_UNINITIALIZED) {
        init_timer = INITIALIZATION_TIMEOUT;
        while (init_timer) {
            Service_soft_timer();
        }
    }

    Service_soft_timer();


    // ##################################
    // Read the CH3 servo input into the variable ch3 (time value in us)
    TMR1H = 0;
    TMR1L = 0;

    // Wait until servo signal is LOW
    // This ensures that we do not start in the middle of a pulse
    while (RA1 != 0) ;

    // Wait until servo signal is high; start of pulse
    while (RA1 != 1) ;

    // Start the time measurement
    TMR1ON = 1;

    // Wait until servo signal is LOW again; end of pulse
    while (RA1 != 0) ;

    // Stop the time measurement
    TMR1ON = 0;

    // Check if the measured pulse time is between 600 and 2500 us. If it is
    // outside we consider it an invalid servo pulse and stop further execution.
    ch3 = (TMR1H << 8) | TMR1L;

    if (ch3 < 600 || ch3 > 2500) {
        if (winch_mode != WINCH_MODE_UNINITIALIZED) {
            winch_mode = WINCH_MODE_OFF;
        }
        return;
    }


    // Apply a hysteresis function: If the servo input was "high" during
    // the last valid measurement, the value must drop below 1375 us before it
    // is considered "low".
    // If it was "low" during the last measurement it must rise above 1625 us
    // before it is considred "high" again.
    // This assumes that the servo pulses are centered around 1500us.
    if (f.ch3_last_state) {
        if (ch3 < 1375) {
            f.ch3_state = 0;
        }
        else {
            f.ch3_state = 1;
        }
    }
    else {
        if (ch3 > 1625) {
            f.ch3_state = 1;
        }
        else {
            f.ch3_state = 0;
        }
    }

    // If it is the first measurement after power-up we save the value
    // as initial value and consider the firmware initialized.
    if (winch_mode == WINCH_MODE_UNINITIALIZED) {
        f.ch3_last_state = f.ch3_state;
        winch_mode = WINCH_MODE_OFF;
    }

    // Determine whether CH3 has been toggled
    f.ch3_transitioned = 0;
    if (f.ch3_state != f.ch3_last_state) {
        f.ch3_last_state = f.ch3_state;
        f.ch3_transitioned = 1;
    }

    if (f.ch3_transitioned) {
        switch(winch_mode) {
            case WINCH_MODE_OFF:
                winch_mode = WINCH_MODE_OUT;
                break;

            case WINCH_MODE_OUT:
                winch_mode = WINCH_MODE_OFF2;
                break;

            case WINCH_MODE_OFF2:
                winch_mode = WINCH_MODE_IN;
                break;

            case WINCH_MODE_IN:
                winch_mode = WINCH_MODE_OFF;
                break;

            case WINCH_MODE_UNINITIALIZED:
            default:
                winch_mode = WINCH_MODE_OFF;
                break;
        }
    }
}

