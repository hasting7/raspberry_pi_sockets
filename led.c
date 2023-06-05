#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>

#define PIN 26

void generate_code(uint8_t *bits, int length) {

}


int main() {
	wiringPiSetup();
	pinMode(PIN, PWM_OUTPUT);

	int length = 5;

	uint8_t signal[length * 24] = { 0 };


	pwmWrite(PIN, signal);

	return 0;
}
