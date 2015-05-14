This folder contains firmware for the 3-Racing winch controller so
that it can be used with a 2-position switch.

The original 3-Racing winch controller works with a transmitter that has
a 3-position switch on CH3.

This firmware hooks in-between the receiver output and the 3-Racing winch
controller. It reads the CH3 2-pos switch info from the receiver and on
change of the switch outputs a servo signal simulating a 3-position switch.

After power on the winch is off. Every CH3 change modifies the servo
signal output to the 3-Racing controller:

Off         1500us
Winch out   2000us
Off         1500us
Winch in    1000us
Off         1500us
Winch out   2000us
...