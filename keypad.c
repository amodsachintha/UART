#include "keypad.h"
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

const int rows = 3;
const int cols= 3;
bool found = false;
char keypad[rows][cols] ={
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};


void init_keypad(){
    DDRD |= 0x1C;
}

char keyPressed(){

    unsigned char tempRow = 0x04;
    unsigned char tempCol = 0x20;
	while(!found){
		for(int i = 0; i<rows; i++){
            PORTD |= tempRow;
			for(int j =0; j<cols; j++){
                if(PIND & (tempCol) == 0){
                    return keypad[i][j];
                }
                tempCol=tempCol<<1;
			}
			PORTD &= ~tempRow;
			tempRow = tempRow << 1;
		}
	}
	tempRow = 0x04;
    tempCol = 0x20;
}
