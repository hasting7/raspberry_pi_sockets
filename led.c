#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>

#define PIN 26


int main() {
	wiringPiSetup();
	pinMode(PIN, PWM_OUTPUT);


	uint8_t signal = 0x0;
	
	pwmWrite(PIN, signal);

	return 0;
}
