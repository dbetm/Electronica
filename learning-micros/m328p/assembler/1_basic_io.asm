; Author : david
;

; definiciones de bibliotecas
.include "m328pdef.inc"
; poner una etiqueta a los registros
; como declaración de variables
.def configB = R16
.def configD = R17
.def pullupB = R18
.def salida = R19
; código del programa
.org 0x0000 ; cada que inicie al programa se corre el reset, ahí es donde inicia el programa
rjmp RESET

RESET:
	ldi configB, 0x00 ; cargar puros ceros
	ldi configD, 0xff ; cargar puros unos
	ldi pullupB, 0xff
	out DDRB, configB ; asignar puros ceros a DDRB
	out DDRB, configD
	out PORTB, pullupB

; Ciclo infinito
LOOP:
	in salida, PINB ; guardar B en un registros temporal
	eor salida, pullupB ; XOR de lo que entro con el puerto B con puros 1
	out PORTD, salida ; en el puerto D mandamos lo que tiene salida
	rjmp LOOP ; para que se vuelva a repetir
