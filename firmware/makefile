.PHONY: all
all: rc-winch-controller-uart

#############################################################################
LIBS = /usr/local/share/sdcc/lib/pic14/libsdcce.lib /usr/local/share/sdcc/non-free/lib/pic14/pic12f1840.lib


#############################################################################
.PHONY: rc-winch-controller-uart
rc-winch-controller-uart: rc-winch-controller-uart.hex

rc-winch-controller-uart.hex: winch-controller.o uart-input.o
	gplink -w -r -m -o $@ $^ $(LIBS) 


.c.o:
	sdcc -V --use-non-free -mpic14 -p12f1840 -c $<


clean :
	$(RM) *.hex
	$(RM) *.lst
	$(RM) *.map
	$(RM) *.cod
	$(RM) *.o
	$(RM) *.asm
	
