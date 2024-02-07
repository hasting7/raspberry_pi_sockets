#include <wiringPi.h>

#include "server.h"

#define ON_LIGHT 4

int main(int argc, char **argv) {
	wiringPiSetup();
	pinMode(ON_LIGHT, OUTPUT);

	digitalWrite(ON_LIGHT,LOW);
	digitalWrite(ON_LIGHT,HIGH);

	return 0;
}