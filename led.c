#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <string.h>

#define PIN 26

void generate_code(uint8_t *bits, int length) {

}


int main() {
	wiringPiSetup();
	pinMode(PIN, PWM_OUTPUT);

	int length = 5;

	uint8_t signal[length * 24];

	memset(signal, 0, sizeof(uint8_t) * 24 * 5);

	for (int i = 0; i < (length * 24); i++) {
		pwmWrite(PIN, signal[i]);
	}

	return 0;
}
