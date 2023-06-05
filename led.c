#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>

#define ROOT 0x7E200000;

void *gpio = (void *) ROOT;



int main() {

	printf("%ls\n",(int *) gpio);
	return 0;
}
