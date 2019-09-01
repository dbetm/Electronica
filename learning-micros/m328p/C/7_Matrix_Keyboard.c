#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    short tiempo = 50;
	DDRB &= ~(2 << 0); // PB0 a PB1 como entradas digitales, filas
	PORTB |= (2 << 0); // Pull-Up de PB0 y PB1
	DDRB |= (3 << 2); // PB2 a PB3 como salidas digitales, columnas
	PORTB |= (3 << 2); // PB2 a PB3 en alto (1)
	DDRD |= 7;
	PORTD &= ~7;
	 
    while (1) {
		for (short c = 2; c <= 3; c++) { // recorremos por columna, PB2 a PB3
			PORTB = ~(1 << c); // para ir haciendo de PB2 y PB3 a 0.
			for (short f = 0; f < 2; f++) { // verificar si alguna fila está en 0
				if((PINB & (1 << f)) == 0) { // si la fila está en 0, quiere decir que ha sido presionado
					PORTD = ((c - 2) + 1) + (2 * f);
					// evitar el rebote mecánico
					while((PINB & (1 << f)) == 0)
						_delay_ms(tiempo);
				}
			}
			PORTB |= (1 << c);
		}
    }
}

