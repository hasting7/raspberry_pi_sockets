#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>

#define ROOT 0x7E200000;

int *gpio;

gpio = ROOT;


int main() {

	printf("%d\n",*gpio);
	return 0;
}
