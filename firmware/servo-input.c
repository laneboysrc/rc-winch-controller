#include <pic12f1840.h>

extern unsigned char winch_mode;

void Init_input(void) {
    movlw   1000 >> 4
    movwf   ch3_ep0

    movlw   2000 >> 4
    movwf   ch3_ep1
}

void Read_input(void) {
Read_ch3
    BANKSEL ch3_value
    clrf    ch3_value       ; Prime the result with "timing measurement failed"

    BANKSEL T1CON
    bcf     T1CON, TMR1ON   ; Stop timer 1
    clrf    TMR1H           ; Reset the timer to 0
    clrf    TMR1L

    ; Wait until servo signal is LOW 
    ; This ensures that we do not start in the middle of a pulse
ch3_wait_for_low1
    btfsc   PORT_CH3
    goto    ch3_wait_for_low1

ch3_wait_for_high
    btfss   PORT_CH3    ; Wait until servo signal is high
    goto    ch3_wait_for_high

    bsf     T1CON, TMR1ON   ; Start timer 1

ch3_wait_for_low2
    btfsc   PORT_CH3    ; Wait until servo signal is LOW
    goto    ch3_wait_for_low2

    bcf     T1CON, TMR1ON   ; Stop timer 1

    call    Validate_servo_measurement
  
    ; Use the middle 12 bit as an 8 bit value since we don't need high
    ; accuracy for the CH3 
    rlf     xl, f
    rlf     xh, f
    rlf     xl, f
    rlf     xh, f
    rlf     xl, f
    rlf     xh, f
    rlf     xl, f
    rlf     xh, f

    movf    xh, w    
    BANKSEL ch3_value
    movwf   ch3_value

    // winch_mode = RCREG;	
}

Process_ch3_double_click
IFDEF ENABLE_GEARBOX
    BANKSEL gear_mode
    bcf     gear_mode, GEAR_CHANGED_FLAG
ENDIF    
    BANKSEL startup_mode
    movf    startup_mode, f
    bz      process_ch3_no_startup
    return

process_ch3_no_startup
    btfsc   flags, CH3_FLAG_INITIALIZED
    goto    process_ch3_initialized

    ; Ignore the potential "toggle" after power on
    bsf     flags, CH3_FLAG_INITIALIZED
    bcf     flags, CH3_FLAG_LAST_STATE
    BANKSEL ch3
    btfss   ch3, CH3_FLAG_LAST_STATE
    return
    BANKSEL flags               
    bsf     flags, CH3_FLAG_LAST_STATE
    return

process_ch3_initialized
    BANKSEL ch3
    movfw   ch3
    movwf   temp+1  

    ; ch3 is only using bit 0, the same bit as CH3_FLAG_LAST_STATE.
    ; We can therefore use XOR to determine whether ch3 has changed.
   
    BANKSEL flags               
    xorwf   flags, w        
    movwf   temp

IFDEF CH3_MOMENTARY
    ; -------------------------------------------------------    
    ; Code for CH3 having a momentory signal when pressed (Futaba 4PL)

    ; We only care about the switch transition from CH3_FLAG_LAST_STATE 
    ; (set upon initialization) to the opposite position, which is when 
    ; we add a click.
    btfsc   temp, CH3_FLAG_LAST_STATE
    goto    process_ch3_potential_click

    ; ch3 is the same as CH3_FLAG_LAST_STATE (idle position), therefore reset 
    ; our "transitioned" flag to detect the next transition.
    bcf     flags, CH3_FLAG_TANSITIONED        
    goto    process_ch3_click_timeout

process_ch3_potential_click
    ; Did we register this transition already?    
    ;   Yes: check for click timeout.
    ;   No: Register transition and add click
    btfsc   flags, CH3_FLAG_TANSITIONED
    goto    process_ch3_click_timeout

    bsf     flags, CH3_FLAG_TANSITIONED
    ;goto   process_ch3_add_click    

ELSE
    ; -------------------------------------------------------    
    ; Code for CH3 being a two position switch (HK-310, GT3B)

    ; Check whether ch3 has changed with respect to LAST_STATE
    btfss   temp, CH3_FLAG_LAST_STATE
    goto    process_ch3_click_timeout

    bcf     flags, CH3_FLAG_LAST_STATE      ; Store the new ch3 state
    btfsc   temp+1, CH3_FLAG_LAST_STATE     ; temp+1 contains ch3
    bsf     flags, CH3_FLAG_LAST_STATE
    ;goto   process_ch3_add_click    

    ; -------------------------------------------------------    
ENDIF

process_ch3_add_click
IFDEF ENABLE_WINCH
    ; If the winch is running any movement of CH3 immediately turns off
    ; the winch (without waiting for click timeout!)
    BANKSEL winch_mode
    movlw   WINCH_MODE_IN
    subwf   winch_mode, w
    bz      process_ch3_winch_off

    movlw   WINCH_MODE_OUT
    subwf   winch_mode, w
    bnz     process_ch3_no_winch

process_ch3_winch_off
    movlw   WINCH_MODE_IDLE
    movwf   winch_mode

    ; Disable this series of clicks by setting the click count to an unused
    ; high value
    BANKSEL ch3_clicks               
    movlw   99
    movwf   ch3_clicks
    movlw   CH3_BUTTON_TIMEOUT
    movwf   ch3_click_counter
    return
ENDIF

