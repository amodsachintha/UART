#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include  "uart.h"


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif
#include <util/setbaud.h>


void init_uart(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0B |= (1<<RXCIE0); //RX complete enable interrupt

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */

}


void uart_putchar(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}


char uart_getchar() {
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void transmit() {
	uart_putchar('A');
	_delay_ms(50);
}


void txString(char *str){
    while(*str != '\0'){
        uart_putchar(*str);
        str++;
    }


}


/*
int main(void) {
	char myChar='a';
	pinMode(13,OUTPUT);


	while(1) {
		myChar = uart_getchar();

		if(myChar == 'A') {
			digitalWrite(13,HIGH);
			_delay_ms(500);
			digitalWrite(13,LOW);
		}
//       transmit();

	}

}

*/

