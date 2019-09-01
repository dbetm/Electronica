#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void) {
    /* Se agregan las siguientes 3 líneas 
	   para poder cambiar el reloj y funcione en la simulación */
	CLKPR |= 0x80; // reloj sin preescalador
	CLKPR = 0x00; // permite configuración
	CLKPR = 0x00; // Cierra la configuración
	
	TCCR1A = 0b10000011;
	TCCR1B = 0b00000011;

	// OCR1A -> PB1 -> DDRB =
	DDRB = 0b00000010;
	
    while (1) {
		OCR1A = 0x3c; // 0.95
		/*
		_delay_ms(1000);
		OCR1A = 0x5f; // 1.5
		_delay_ms(1000);
		OCR1A = 0x86; // 2.1
		_delay_ms(1000);
		*/
    }
}

