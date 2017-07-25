MCU := 12f1840
FLASH_TOOL := pk2cmd -ppic$(MCU) -t -m -f


.PHONY: all
all: rc-winch-controller-uart rc-winch-controller-servo


#############################################################################
.PHONY: rc-winch-controller-uart
rc-winch-controller-uart: rc-winch-controller-uart.hex

rc-winch-controller-uart.hex: winch-controller.o uart-input.o
	sdcc --use-non-free -mpic14 -p$(MCU) -o $@ $^

program-uart : rc-winch-controller-uart.hex
	$(FLASH_TOOL) $<

flash-uart : program-uart


#############################################################################
.PHONY: rc-winch-controller-servo program flash
rc-winch-controller-servo: rc-winch-controller-servo.hex

rc-winch-controller-servo.hex: winch-controller.o servo-input.o
	sdcc --use-non-free -mpic14 -p$(MCU) -o $@ $^

program-servo : rc-winch-controller-servo.hex
	$(FLASH_TOOL) $<

flash-servo : program-servo


#############################################################################
.c.o:
	sdcc --use-non-free -mpic14 -p$(MCU) -c $<




clean :
	$(RM) *.hex
	$(RM) *.lst
	$(RM) *.map
	$(RM) *.cod
	$(RM) *.o
	$(RM) *.asm

