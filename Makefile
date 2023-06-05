build:
	git pull origin main
	gcc -Wall -Werror -std=c17 server.c -o server -lwiringPi -lpthread -lm


client_side:
	git add .
	git commit -am 'update'
	git push origin main
	gcc -Wall -Werror -std=c17 client.c -o client

led_test:
	git pull origin main
	gcc -Wall -Werror -std=c17 led.c -o led -lwiringPi
