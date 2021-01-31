# Ideas for Mk2

* Up to 3S operation (12.6V)
* LEDs and push-button for configuration
* Inputs
    - Servo input 3-pos switch
    - Servo input 2-pos switch
    - External 3-pos switch
    - External 2-pos switch
    - External push-button (any difference from 2-pos switch?)
    - Internal push-button
    - Light Controller protocol
* Arming function
    * Can be disabled in the settings
    * Applies to all input modes except Light Controller
* Configurable motor reversal
    * Do we need that? User can just plug in the motor the other way around ...
* Firmware update
    * Hold button to start
* Configurable safety timeout for motor running
* Mini-ESC mode
    - 8 kHz to 16 kHz PWM frequency?
    - Drag brake adjustable?
    - Different modes: F/B/R, Crawler mode, F/B?
    - End-point learning
    - Channel reversing
    - Punch?

## Building blocks

* LPC812 16p (or QFN?)
* Use Wuxi RZ7899 or RZ7889 motor driver
* LDO 3V3
* 100uF polymer 16V 5x9mm
* Low-cost 3.3V-side buffer cap? 10u MLCC?
* Pushbutton
* External 2-pos switch connects to S/RX - GND
* External 3-pos switch connects to S/RX - Tx - GND
* RGB LED
* Power input
    * Allow various combinatoins:
        * Motor and electronics powered from servo connector
        * Motor and electronics powered from external supply
        * Motor powered from external supply, electronics powered from servo connector
    * Feed MCU from BAT54C! SOT-23
        * Motor-side use 6p connector with same jumper arrangement as on Mk4P/Mk4S