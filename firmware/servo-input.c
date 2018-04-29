#include <pic12f1840.h>

extern enum {
    WINCH_MODE_UNINITIALIZED = 0,
    WINCH_MODE_OFF = 0x80,
    WINCH_MODE_IDLE = 0x81,
    WINCH_MODE_IN = 0x82,
    WINCH_MODE_OUT = 0x83
} winch_mode;

static struct {
    unsigned ch3_initialized : 1;
    unsigned ch3_state : 1;
    unsigned ch3_last_state : 1;
    unsigned ch3_transitioned : 1;
} f = {0, 0, 0, 0};

static unsigned char ch3_clicks = 0;
static unsigned char ch3_click_counter = 0;

// All units are in 32.768 ms resolution
#define CH3_INITIALIZATION_TIMEOUT 90
#define CH3_BUTTON_TIMEOUT 12


/*****************************************************************************
 Service_soft_timer()

 Soft timer with a resolution of 32.768ms
 ****************************************************************************/
static void Service_soft_timer(void) {
    if (TMR2IF) {
        TMR2IF = 0;

        // Decrement ch3_click_counter if it is running
        if (ch3_click_counter) {
            --ch3_click_counter;
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

    // If we are starting up delay this function for approx 3 seconds.
    // This way we don't energize the motor (music!) straight away during
    // power-up, causing spikes in the system while the power supply is still
    // stabilizing.
    if (winch_mode == WINCH_MODE_UNINITIALIZED) {
        ch3_click_counter = CH3_INITIALIZATION_TIMEOUT;
        while (ch3_click_counter) {
            Service_soft_timer();
        }
    }

    Service_soft_timer();


    // ##################################
    // Read the CH3 servo input into the variable ch3 (time value in us)
    TMR1H = 0;
    TMR1L = 0;
    CCP1CON = 0b00000000;   // Compare mode off

    // Wait until servo signal is LOW
    // This ensures that we do not start in the middle of a pulse
    while (RA5 != 0) ;

    // Wait until servo signal is high; start of pulse
    while (RA5 != 1) ;

    // Start the time measurement
    TMR1ON = 1;

    // Wait until servo signal is LOW again; end of pulse
    while (RA5 != 0) ;

    // Start the time measurement
    TMR1ON = 0;

    // Check if the measured pulse time is between 600 and 2500 us. If it is
    // outside we consider it an invalid servo pulse and stop further execution.
    ch3 = (TMR1H << 8) | TMR1L;

    if (ch3 < 600 || ch3 > 2500) {
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

    // If CH3 has been toggled add a click and (re-) start the click timeout.
    // If the winch is running turn it off straight away.
    if (f.ch3_transitioned) {
        ++ch3_clicks;
        ch3_click_counter = CH3_BUTTON_TIMEOUT;

        if (winch_mode == WINCH_MODE_IN  ||  winch_mode == WINCH_MODE_OUT) {
            winch_mode = WINCH_MODE_IDLE;
            // Set an invalid clicks number to ignore multiple clicks
            ch3_clicks = 99;
        }
    }

    if (ch3_clicks == 0) {          // Any buttons pending?
        return;                     // No: done
    }

    if (ch3_click_counter) {        // Double-click timer expired?
        return;                     // No: wait for more buttons
    }


    // Implement the business logic:
    // 5 clicks activate/deactivate the winch
    // 1 click: winch in if winch is active
    // 2 clicks: winch out if winch is active
    if (ch3_clicks == 1) {
        if (winch_mode == WINCH_MODE_IDLE) {
            winch_mode = WINCH_MODE_IN;
        }
    }
    if (ch3_clicks == 2) {
        if (winch_mode == WINCH_MODE_IDLE) {
            winch_mode = WINCH_MODE_OUT;
        }
    }
    if (ch3_clicks == 5) {
        if (winch_mode == WINCH_MODE_IDLE) {
            winch_mode = WINCH_MODE_OFF;
        }
        else {
            winch_mode = WINCH_MODE_IDLE;
        }
    }
    ch3_clicks = 0;
}

