/*  Initialize the TIMER0A to interrupt at 0.25 seconds.
    This interrupt in turn will update the LCD DISPLAY
*/

#include "timer.h"
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/*
    Clock cycles for delay = 16Mhz * .25 = 4000000
    prescaler values : 4000000/256 = 15625
*/

void init_timer(){
    TCCR1B |= (1<<WGM12); //Enable CTC Mode
    TIMSK1 |= (1<<OCIE1A); // Enable timer interrupts
    OCR1A = 15625; //counting to 15625@256
    TCCR1B |= (1<<CS12); // set prescaler to 256 to start.
//    sei();
}
