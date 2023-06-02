build:
	gcc -Wall -Werror -std=c17 toggle.c server.c -o server -lwiringPi
