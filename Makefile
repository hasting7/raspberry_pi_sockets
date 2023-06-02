build:
	git pull origin main
	gcc -Wall -Werror -std=c17 seven_seg.c server.c -o server -lwiringPi
