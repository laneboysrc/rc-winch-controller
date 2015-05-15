.PHONY: all clean program
all: rc-winch-controller-3racing


#############################################################################
.PHONY: rc-winch-controller-3racing
rc-winch-controller-3racing: rc-winch-controller-3racing.hex

rc-winch-controller-3racing.hex: winch-controller.o servo-input.o
	sdcc --use-non-free -mpic14 -p12f1840 -o $@ $^


#############################################################################
.c.o:
	sdcc --use-non-free -mpic14 -p12f1840 -c $<


#############################################################################
program: rc-winch-controller-3racing.hex
	pk2cmd -p pic12f1840 -m -f rc-winch-controller-3racing.hex -t


#############################################################################
clean:
	$(RM) *.hex
	$(RM) *.lst
	$(RM) *.map
	$(RM) *.cod
	$(RM) *.o
	$(RM) *.asm

