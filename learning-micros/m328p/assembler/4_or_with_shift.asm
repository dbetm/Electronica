;
; Ejercicio4.asm
;
; Created: 07/02/2019 01:41:03 p. m.
; Author : david
;

.include "m328pdef.inc"
.def configB = R16
.def pullUp = R17
.def temp0 = R18
.def temp1 = R19
.def salida = R20
.org 0x0000
	rjmp RESET

RESET:
	ldi configB, 0x03
	ldi salida, 0x00
	ldi pullUp, 0x44
	out DDRB, configB
	out PORTB, pullUp

LOOP:
	in temp0, PINB
	in temp1, PINB
	lsr temp0
	or salida, temp0
	lsr temp1
	lsr temp1
	lsr temp1
	lsr temp1
	lsr temp1
	lsr temp1
	or salida, temp1
	eor salida, configB
	out PORTB, salida
	rjmp LOOP
