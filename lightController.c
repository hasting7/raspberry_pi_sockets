#include <wiringPi.h>

#include "server.h"

void white() {
	digitalWrite(RED, HIGH);
	digitalWrite(BLUE, HIGH);
	digitalWrite(GREEN, HIGH);

	printf("on\n");
}

void setup() {
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);
} 
