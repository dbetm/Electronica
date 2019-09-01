;
; E1_Interrupciones.asm
;
; Created: 22/02/2019 03:36:00 p. m.
; Author : david
;

.include "m328pdef.inc"
.def boton = R16
.def led = R17
.def configb = R18
.def pullup  = R19
.def tmp  = R20

.org 0x0000
    rjmp RESET

.org INT0addr
    rjmp INT0_ISR

RESET:
  ldi configb,0x01
  ldi pullup,0x04
  out DDRB,configb
  out PORTD,pullup
  ldi tmp,0x03
  sts EICRA,tmp
  sbi EIMSK,INT0
  sei

LOOP:
    rjmp LOOP

INT0_ISR:
    in tmp,PINB
	ldi led, 0x01
    eor tmp,led
	out PORTB, tmp
    reti
