#include <stdio.h>
#include <wiringPi.h>

#define PIN 26


int main() {
	wiringPiSetup();
	pinMode(PIN, PWM_OUTPUT);

	int signal = 0xf;
	
	pwmWrite(PIN, signal);

	return 0;
}
