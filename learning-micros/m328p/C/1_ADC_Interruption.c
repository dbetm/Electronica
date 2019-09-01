/*
 * ADC.c
 *
 * Created: 11/04/2019 06:25:04 p. m.
 * Author : david
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definir la frecuencia
#define F_CPU 8000000UL

int main(void) {
    ADMUX = 0x60; //0b011000000;
	ADCSRA = 0xAF; //0b10000111;
	ADCSRB = 0x02; //0b00000010;
	DIDR0 = 0b00000001;
	DDRB = 0xFF; //0b11111111;
	PORTD = 0b00000100; // pin 3 de INT0
	// Configurar la interrupción INT0
	EICRA = 0x03;
	EIMSK = 0x01;
	EIFR = 0x01;
	// set interruption
	sei();
	
    while (1) {
		/*
		_delay_ms(10);
		ADCSRA |= 0x40; // el bit 6, para comenzar la conversión
		while((ADCSRA & 0x10) == 0);
		// desactivamos la bandera
		ADCSRA |= 0x10;
		// Grabamos la salida
		PORTB = ADCH;
		*/
    }
}

ISR(INT0_vect);

ISR(ADC_vect) {
	// aquí va la lógica
	ADCSRA |= 0x40; // el bit 6, para comenzar la conversión
	while((ADCSRA & 0x10) == 0);
	// desactivamos la bandera
	ADCSRA |= 0x10;
	// Grabamos la salida
	PORTB = ADCH;
}

