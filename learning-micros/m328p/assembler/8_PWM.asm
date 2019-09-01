

.include "m328pdef.inc"
.def tmp = R16
.org 0x00
	rjmp RESET

RESET:
	ldi tmp, 0B10000011 ; val para conf TCCR0A como PWM rápido
	out TCCR0A, tmp
	ldi tmp, 0B00000001 ; val para conf TCCR0B sin preescalador
	out TCCR0B, tmp
	ldi tmp, 0x7f ; para trabajar con 50% del ciclo de trabajo
	out OCR0A, tmp
	ldi tmp, 0x40 ; definir coo salida el PIN6 del puerto D
	out DDRD, tmp

LOOP:
	rjmp LOOP