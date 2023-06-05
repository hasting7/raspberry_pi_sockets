#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>

#define gpio 0x7E200000



int main() {

	printf("%d\n",*gpio);
	return 0;
}
