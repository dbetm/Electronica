#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void) {
	/* Se agregan las siguientes 3 líneas 
	   para poder cambiar el reloj y funcione en la simulación */
	CLKPR |= 0x80; // reloj sin preescalador
	CLKPR = 0x00; // permite configuración
	CLKPR = 0x00; // Cierra la configuración
	 
    TCCR0A = 0b10000001; // PWM en modo fase corregida
	TCCR0B = 0b00000100; // 256
	DDRD = 0x40;
	
    while (1) {
		OCR0A = 0x0f; // 15, 1.2, con regla de 3, (1.2 * 255) / 20
		_delay_ms(1000);
		OCR0A = 0X17; // 23, 1.6, 
		_delay_ms(1000);
		OCR0A = 0X21; // 33, 2.2
		_delay_ms(1000);
    }
}

