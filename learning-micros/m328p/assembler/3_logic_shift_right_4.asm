;
; Ejercicio3.asm
;
; Created: 07/02/2019 04:26:29 a. m.
; Author : david
;

.include "m328pdef.inc"
.def configD = R16
.def pullUp = R17
.def salida = R18
.org 0x0000
	jmp RESET

RESET:
	ldi configD, 0xf0
	ldi pullUp, 0xf
	out DDRD, configD
	out PORTD, pullUp

LOOP:
	in R18, PIND; leer datos de cada pin del puerto D
	; hacer 4 desplazamientos lógicos a la izquierda
	lsl R18
	lsl R18
	lsl R18
	lsl R18
	eor R18, configD; hacer xor
	out PORTD, R18; escribir en el puerto D lo que guarda R18
	rjmp LOOP
