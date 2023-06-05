#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <string.h>

#define PIN 26

void generate_code(uint8_t *bits, int length) {
	for (int i = 0; i < length * 3; i += 3) {
		bits[i] = 0xff;
		bits[i+2] = 0x00; 
	}
}


int main() {
	wiringPiSetup();
	pinMode(PIN, PWM_OUTPUT);

	//int length = 5;

	//uint8_t signal[length * 24];

	//generate_code(signal, length);


	//for (int i = 0; i < (length * 24); i++) {
		//pwmWrite(PIN, signal[i]);
	//}

	pwmWrite(PIN, 2);


	return 0;
}
