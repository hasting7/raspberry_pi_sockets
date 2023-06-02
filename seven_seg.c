#include <stdio.h>
#include <wiringPi.h>

#define MAX 7

#define A 12
#define B 30
#define C 0
#define D 2
#define E 3
#define F 14
#define G 9
int seg_pins[] = { A, B, C, D, E, F, G };

unsigned char values[] = {
	126,
	48,
	109,
	121,
	51,
	91,
	95,
	112,
	127,
	115,
	119,
	31,
	13,
	125,
	79,
	71
}; 

void setupSegPins() {
	for (int i = 0; i < 7; i++) {
		pinMode(seg_pins[i], OUTPUT);
	}
}

void displayValue(int value) {
	unsigned char code = values[value];
	unsigned char mask = 64;
	for (int i = 0; mask != 0; i++) {
		digitalWrite(seg_pins[i], ((code & mask) != 0) ? 1 : 0);
		mask = mask >> 1;
	}
}
