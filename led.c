#include <stdio.h>
#include <stdint.h>

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))

int main() {
	INP_GPIO(7);
	return 0;
}
