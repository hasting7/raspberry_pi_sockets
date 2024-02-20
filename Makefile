push:
	git add .
	git commit -am 'update'
	git push origin main


website:
	git pull origin main
	gcc -Wall -Werror -std=c17 -o ready pi_ready.c -lwiringPi -lpthread -lm
	gcc -Wall -Werror -std=c17 -o web lightController.c webserver.c -lwiringPi -lpthread -lm
	gcc -Wall -Werror -std=c17 -o ./timer-info/decrement_time ./timer-info/decrease_timer.c

test:
	gcc -Wall -Werror -std=c17 -o web-local webserver.c -lpthread -lm