#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include  "uart.h"
#include "timer.h"

void blink();
void fillGlobal(char c);
/*
    state -> 0 <- Idle
    state -> 1 <- Rxing
    state -> 2 <- Txing
*/
volatile int state = 0;

char rx_data = 0;
char tx_data = 0;


char GLOBALDATA [16];
int GLOBALDATA_POINTER = 0;
int main(void){

    init_uart();
    init_lcd();
    init_keypad();
    init_timer();
    DDRB |= 0x20;

    fillGlobal('a');
    fillGlobal('m');
    fillGlobal('o');
    fillGlobal('d');

while(1){

    for(int i=0; i<GLOBALDATA_POINTER+1; i++)
        uart_putchar(GLOBALDATA[i]);

    _delay_ms(500);
}

return 0;
}


ISR(USART_TX_vect){ //TX Complete.... Interrupt not enabled in init_usart(); fyi
    state = 0; //Idle
}

ISR(TIMER1_COMPA_vect){
    //update LCD
    for(int i=0; i<GLOBALDATA_POINTER+1; i++)
        writedata(GLOBALDATA[i]);
}


ISR (USART_RX_vect){
    GLOBALDATA_POINTER = 0;
    writedata(UDR0);
}


void blink(){
    PORTB |= 0x20;
    _delay_ms(500);
    PORTB &= ~(0x20);
    _delay_ms(500);
}

void fillGlobal(char c){
    GLOBALDATA[GLOBALDATA_POINTER] = c;
    GLOBALDATA_POINTER++;
}


