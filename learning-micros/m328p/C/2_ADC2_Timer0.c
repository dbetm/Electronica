#include <avr/io.h>
#include <util/delay.h>

// Definir la frecuencia
#define F_CPU 8000000UL

int main(void) {
    ADMUX = 0x60; //0b011000000; Ref 5v (Vcc) y modo izquierdo
	ADCSRA = 0x87; //0b10000111; Habilitar ADC y modo preescalador en máximo (128)
	ADCSRB = 0b00000011; // Modo Timer0 CompA
	DIDR0 = 0b00000001;
	
    while (1) {
		
    }
}

