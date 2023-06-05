#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

int main() {
	INP_GPIO(7);
	GPIO_CLR;
	return 0;
}
