;
; Ejercicio5.asm
;
; Created: 28/02/2019 08:27:08 p. m.
; Author : david
;


.include "m328pdef.inc"
.def tmp = R17
.def umbral = R18
.def mask1 = R19
.org 0x0000
	rjmp RESET

RESET:
	ldi mask1, 0x01
	ldi umbral, 0x07
	ldi tmp, 0x00
	out OCR0A, tmp		; valor de comparación para la salida 0CR0A
	ldi tmp, 0x10
	out OCR0B, tmp		; valor de comparación para la salida 0CR0B
	ldi tmp, 0x00
	out TCCR0A, tmp		; Modo NORMAL, o sea, timer o temporizador
	ldi tmp, 0x07 
	out TCCR0B, tmp		; flanco ascendente
	ldi tmp, 0xff		; porque todas son las salidas, entonces seteamos con puros 1
	out DDRB, tmp
	ldi tmp, 0x00	
	sts TIMSK0, tmp		; cargamos un 00, para decir que no active las interrupciones
	ldi tmp, 0x00		; para que el contador comience en 0
	out TCNT0, tmp
	ldi tmp, 0x01
	out DDRC, tmp
	sei

LOOP:
	in tmp, TCNT0; TIENE EL CONTEO DEL TIMER
	cp tmp, umbral ; comparamos el valor del contador para saber si ya llegó a 7
	breq equal ; si son iguales salta a BRANCH
	; de otra forma
	out PORTB, tmp ; escribir el valor del contador en la salida
	rjmp LOOP

equal:
	ldi tmp, 0x00 ; cargar un 0 en tmp
	out TCNT0, tmp ; reiniciar el contador
	ldi tmp, 0x01 ; cargar un 1 en tmp
	out PORTC, tmp ; escribir ese 1 en el pin0 del puerto 0, encender el led
	ldi tmp, 0x00 ; cargar un 0 en tmp
	out PORTB, tmp ; escriibir en el puerto D el 0, ya que se reinició el contador
	rjmp LOOP ; vuelver a LOOP

