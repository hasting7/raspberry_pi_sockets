build:
	git pull origin main
	gcc -Wall -Werror -std=c17 lightController.c server.c -o server -lwiringPi -lpthread -lm


client_side:
	git add .
	git commit -am 'update'
	git push origin main
	gcc -Wall -Werror -std=c17 client.c -o client


website:
	git pull origin main
	gcc -Wall -Werror -std=c17 -o web lightController.c webserver.c