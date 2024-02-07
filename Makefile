push:
	git add .
	git commit -am 'update'
	git push origin main


website:
	git pull origin main
	gcc -Wall -Werror -std=c17 -o web lightController.c webserver.c -lwiringPi -lpthread -lm
