build:
	git pull origin main
	gcc -Wall -Werror -std=c17 seven_seg.c server.c -o server -lwiringPi -lpthread


client_side:
	git add .
	git commit -am 'update'
	git push origin main
	gcc -Wall -Werror -std=c17 client.c -o client
