#include <stdio.h>
#include <wiringPi.h>

#define PIN 26


int main() {
	wiringPiSetup();
	pinMode(PIN, PWM_OUTPUT);

	pwmWrite(PIN, 0x000000);

	//int signal = 0xf;
	
	//pwmWrite(PIN, signal);

	return 0;
}
