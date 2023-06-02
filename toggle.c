#include <stdio.h>
#include <wiringPi.h>

#define BLUE (0) 
#define RED (2) 

void toggle (const int pin, const int state) { 
	digitalWrite(pin, state);
}

void setup() {
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
} 
