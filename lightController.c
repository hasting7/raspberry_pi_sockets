#include <stdio.h>
#include <wiringPi.h>

#include "server.h"

int rgb[3] = { RED, GREEN, BLUE };

void set_color(int color) {
	for (int i = 0; i < 3; i++) {
		digitalWrite(rgb[i], ((1 < i) & color) != 0 ? HIGH : LOW);
	}
}

void setup() {
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);
} 
