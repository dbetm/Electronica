#include <avr/io.h>

int main() {
	char entrada1, entrada2, OR, AND, XOR;
	DDRB = 0xE0;
	PORTB = 0x03;
	while(1) {
		entrada1 = ~PINB & 0x01;
		entrada2 = (~PINB & 0x02) >> 1;
		OR = (entrada1 | entrada2) << 5;
		AND = (entrada1 & entrada2) << 6;
		XOR = (entrada1 ^ entrada2) << 7;
		PORTB = OR | AND | XOR;
	}
}
