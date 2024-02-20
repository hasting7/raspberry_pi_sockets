#include <stdio.h>

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1],"r");
	int timer;
	fscanf(fp, "%d\n", &timer);
	return timer - 1;
}