#include <wiringPi.h>

#include "server.h"

void setup() {
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);
} 
