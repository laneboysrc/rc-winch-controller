;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (May 11 2013) (Linux)
; This file was generated Thu Jul  4 20:24:40 2013
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"uart-input.c"
	list	p=12f1840
	radix dec
	include "p12f1840.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
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

	extern PSAVE
	extern SSAVE
	extern WSAVE
	extern STK12
	extern STK11
	extern STK10
	extern STK09
	extern STK08
	extern STK07
	extern STK06
	extern STK05
	extern STK04
	extern STK03
	extern STK02
	extern STK01
	extern STK00
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_Init_input

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
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
; code
;--------------------------------------------------------
code_uart_input	code
;***
;  pBlock Stats: dbName = C
;***
;entry:  _Init_input	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_Init_input	;Function start
; 2 exit points
;	.line	4; "uart-input.c"	return;
	RETURN	
; exit point of _Init_input


;	code size estimation:
;	    1+    0 =     1 instructions (    2 byte)

	end
