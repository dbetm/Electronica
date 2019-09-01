;
; Ejercicio2.asm
;
; Created: 07/02/2019 03:59:44 a. m.
; Author : david
;


.include "m328pdef.inc"
.def configB = R16
.def pullUp = R17
.def salida = R18
.org 0x0000
	rjmp RESET

RESET:
	ldi configB, 0x02
	ldi pullUp, 0x01
	out DDRB, configB
	out PORTB, pullUp

LOOP:
	in R18, PINB; leer datos del PINB
	lsl R18; desplazamiento lógico un bit hacia la izquierda
	eor R18, configB; hacer XOR con el 2
	out PORTB, R18; escribir en PORTB lo que tiene R18
	rjmp LOOP
