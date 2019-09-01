;
; E2_Interrupciones.asm
;
; Created: 07/03/2019 07:49:41 p. m.
; Author : david
;

.include "m328pdef.inc"

.def tmp = R16
.org 0x0000
	rjmp RESET

.org OC0Aaddr
	rjmp OC0_ISR

RESET:
	ldi tmp, 0x00
	out TCCR0A, tmp
	ldi tmp, 0x07
	out TCCR0B, tmp
	ldi tmp, 0x02		; para usar el comparador de A
	sts TIMSK0, tmp
	ldi tmp, 0x10
	out PORTD, tmp
	ldi tmp, 0xff
	out DDRB, tmp
	ldi tmp, 0x00		; para que el contador comience en 0
	out TCNT0, tmp
	ldi tmp, 0x01
	out DDRC, tmp
	ldi tmp, 0x00
	out OCR0A, tmp		; valor de comparación para la salida 0CR0A
	ldi tmp, 0x10
	out OCR0B, tmp		; valor de comparación para la salida 0CR0B
	sei

LOOP:
	in tmp, TCNT0
	out PORTB, tmp
	ldi tmp, PINC
	cpi tmp, 0x01
	breq APAGAR
	rjmp LOOP

APAGAR:
	cbi PORTC, 0 ; apagar el bit 0
	rjmp LOOP

OC0_ISR:
	ldi tmp, 0
	out TCNT0, tmp
	sbi PORTC, 0 ; encender el bit 0
	reti
	