push:
	git add .
	git commit -am 'update'
# 	git checkout -b update
# 	git push origin update
# 	git branch -d update


website:
	git pull origin main
	gcc -Wall -Werror -std=c17 -o ready pi_ready.c -lwiringPi -lpthread -lm
	gcc -Werror -std=c17 -o web lightController.c webserver.c -lwiringPi -lpthread -lm

test:
	gcc -Werror -std=c17 -o web-local webserver.c -lpthread -lm