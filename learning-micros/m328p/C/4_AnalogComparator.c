#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
    ADMUX = 0x00;
	ADCSRA = 0x00;
	ADCSRB = 0x00;
	ACSR = 0x08;
	DDRB = 0x01;
	sei();
	
    while (1) {
    }
}

ISR(ANALOG_COMP_vect) {
	PORTB ^= 0x01; // para que haga toggle
}

