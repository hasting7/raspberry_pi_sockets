#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>


int *root;
root = 0x7E200000;

int main() {

	printf("%p\n",root);

	int mask = 512;
	for (int i = 0; i < 32; i++) {
		printf(((mask & *root) != 0) ? "1" : "0");
	}
	printf("\n");
	
	return 0;
}
