;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (May 11 2013) (Linux)
; This file was generated Thu Jul  4 20:24:40 2013
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"winch-controller.c"
	list	p=12f1840
	radix dec
	include "p12f1840.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_Init_input
	extern	_STATUSbits
	extern	_BSRbits
	extern	_INTCONbits
	extern	_PORTAbits
	extern	_PIR1bits
	extern	_PIR2bits
	extern	_T1CONbits
	extern	_T1GCONbits
	extern	_T2CONbits
	extern	_CPSCON0bits
	extern	_CPSCON1bits
	extern	_TRISAbits
	extern	_PIE1bits
	extern	_PIE2bits
	extern	_OPTION_REGbits
	extern	_PCONbits
	extern	_WDTCONbits
	extern	_OSCTUNEbits
	extern	_OSCCONbits
	extern	_OSCSTATbits
	extern	_ADCON0bits
	extern	_ADCON1bits
	extern	_LATAbits
	extern	_CM1CON0bits
	extern	_CM1CON1bits
	extern	_CMOUTbits
	extern	_BORCONbits
	extern	_FVRCONbits
	extern	_DACCON0bits
	extern	_DACCON1bits
	extern	_SRCON0bits
	extern	_SRCON1bits
	extern	_APFCONbits
	extern	_APFCON0bits
	extern	_ANSELAbits
	extern	_EECON1bits
	extern	_VREGCONbits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_BAUDCONbits
	extern	_WPUAbits
	extern	_SSP1STATbits
	extern	_SSPSTATbits
	extern	_SSP1CON1bits
	extern	_SSPCONbits
	extern	_SSPCON1bits
	extern	_SSP1CON2bits
	extern	_SSPCON2bits
	extern	_SSP1CON3bits
	extern	_SSPCON3bits
	extern	_CCP1CONbits
	extern	_PWM1CONbits
	extern	_CCP1ASbits
	extern	_ECCP1ASbits
	extern	_PSTR1CONbits
	extern	_IOCAPbits
	extern	_IOCANbits
	extern	_IOCAFbits
	extern	_CLKRCONbits
	extern	_MDCONbits
	extern	_MDSRCbits
	extern	_MDCARLbits
	extern	_MDCARHbits
	extern	_STATUS_SHADbits
	extern	_INDF0
	extern	_INDF1
	extern	_PCL
	extern	_STATUS
	extern	_FSR0
	extern	_FSR0L
	extern	_FSR0H
	extern	_FSR1
	extern	_FSR1L
	extern	_FSR1H
	extern	_BSR
	extern	_WREG
	extern	_PCLATH
	extern	_INTCON
	extern	_PORTA
	extern	_PIR1
	extern	_PIR2
	extern	_TMR0
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_T1CON
	extern	_T1GCON
	extern	_TMR2
	extern	_PR2
	extern	_T2CON
	extern	_CPSCON0
	extern	_CPSCON1
	extern	_TRISA
	extern	_PIE1
	extern	_PIE2
	extern	_OPTION_REG
	extern	_PCON
	extern	_WDTCON
	extern	_OSCTUNE
	extern	_OSCCON
	extern	_OSCSTAT
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_ADCON0
	extern	_ADCON1
	extern	_LATA
	extern	_CM1CON0
	extern	_CM1CON1
	extern	_CMOUT
	extern	_BORCON
	extern	_FVRCON
	extern	_DACCON0
	extern	_DACCON1
	extern	_SRCON0
	extern	_SRCON1
	extern	_APFCON
	extern	_APFCON0
	extern	_ANSELA
	extern	_EEADR
	extern	_EEADRL
	extern	_EEADRH
	extern	_EEDAT
	extern	_EEDATL
	extern	_EEDATH
	extern	_EECON1
	extern	_EECON2
	extern	_VREGCON
	extern	_RCREG
	extern	_TXREG
	extern	_SPBRG
	extern	_SPBRGL
	extern	_SPBRGH
	extern	_RCSTA
	extern	_TXSTA
	extern	_BAUDCON
	extern	_WPUA
	extern	_SSP1BUF
	extern	_SSPBUF
	extern	_SSP1ADD
	extern	_SSPADD
	extern	_SSP1MSK
	extern	_SSPMSK
	extern	_SSP1STAT
	extern	_SSPSTAT
	extern	_SSP1CON1
	extern	_SSPCON
	extern	_SSPCON1
	extern	_SSP1CON2
	extern	_SSPCON2
	extern	_SSP1CON3
	extern	_SSPCON3
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_CCP1CON
	extern	_PWM1CON
	extern	_CCP1AS
	extern	_ECCP1AS
	extern	_PSTR1CON
	extern	_IOCAP
	extern	_IOCAN
	extern	_IOCAF
	extern	_CLKRCON
	extern	_MDCON
	extern	_MDSRC
	extern	_MDCARL
	extern	_MDCARH
	extern	_STATUS_SHAD
	extern	_WREG_SHAD
	extern	_BSR_SHAD
	extern	_PCLATH_SHAD
	extern	_FSR0L_SHAD
	extern	_FSR0H_SHAD
	extern	_FSR1L_SHAD
	extern	_FSR1H_SHAD
	extern	_STKPTR
	extern	_TOSL
	extern	_TOSH
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_test

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_winch_controller_0	udata
_test	res	1

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_winch_controller	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _Init_input
;   _Init_input
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	8; "winch-controller.c"	test=0;
	BANKSEL	_test
	CLRF	_test
;	.line	9; "winch-controller.c"	Init_input();
	PAGESEL	_Init_input
	CALL	_Init_input
	PAGESEL	$
	RETURN	
; exit point of _main


;	code size estimation:
;	    3+    3 =     6 instructions (   18 byte)

	end
