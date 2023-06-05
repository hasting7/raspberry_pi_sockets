#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>


int *root = (int *) 0x7E200000;

int main() {

	root += 9;
	printf("%u\n",sizeof(int));

	printf("%p\n",root);
	printf("%d\n",*root);

	int mask = 1;
	for (int i = 0; i < 32; i++) {
		printf(((mask & *root) != 0) ? "1" : "0");
		mask = mask << 1;
	}
	printf("\n");
	
	return 0;
}
