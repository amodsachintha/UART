#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"


void init_lcd(void);
void moveto(unsigned char, unsigned char);
void stringout(char *);
void writecommand(unsigned char);
void writedata(unsigned char);
void writenibble(unsigned char);


void init_lcd() {
	DDRB |= 0b00000011 ;
	DDRD |= 0b11110000 ;

	_delay_ms(15);
	writecommand(0x03);
	_delay_ms(5);
	writecommand(0x03) ;
	_delay_us(120);
	writecommand(0x03) ;
	writecommand(0x02) ;
	_delay_ms(2);
	writecommand(0x28);
	_delay_ms(2);
	writecommand(0x0f);
	_delay_ms(2);
	_delay_ms(25);
	writecommand(0x01);
}

void moveto(unsigned char row, unsigned char col) {
	if(row==0) {
		writecommand(0x80+col);
	}
	if(row==1) {
		writecommand(0xc0+col);
	}
}

void stringout(char *str) {
	do {
		writedata(*str);
		str++;

	} while(*str!= '\0');

}

void writecommand(unsigned char cmd) {
	unsigned char temp;
	PORTB&=~(0x01);
	temp=cmd&0xF0;
	writenibble(temp);
	temp=cmd&0x0F;
	temp=temp<<4;
	writenibble(temp);
	_delay_ms(3);
}

void writedata(unsigned char dat) {
	unsigned char temp;
	PORTB|=0x01;
	temp=dat&0xF0;
	writenibble(temp);
	temp=dat&0x0F;
	temp=temp<<4;
	writenibble(temp);
	_delay_ms(3);
}


void writenibble(unsigned char lcdbits) {
	PORTD |= lcdbits ;
	PORTB &= ~(0x02);
	_delay_us(1);
	PORTB |= (0x02);
	_delay_ms(1);
	PORTB &= ~(0x02);
}
