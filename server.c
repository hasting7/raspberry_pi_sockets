#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <wiringPi.h>


#define PORT 5566

void setupSegPins();
void displayDigit(int);

int main() {
	wiringPiSetup();
	setupSegPins();
	displayValue(0);


	struct sockaddr_in dest; // info about machine connecting to server
	struct sockaddr_in serv; // info about server
	int mysocket;

	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv)); // zero out server struct
	serv.sin_family = AF_INET; // set type of connection to TCP/IP
	serv.sin_addr.s_addr = htonl(INADDR_ANY); // set our address to any interface
	serv.sin_port = htons(PORT);

	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr)); // bind serv information to mysocket

	// start listening and allow a queue of 'n' connections

	for(;;) {
		listen(mysocket, 1);
		int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
		int *sock = malloc(sizeof(int *));
		memcpy(sock, &consocket, sizeof(int));

		printf("connected to client\ngonna send a message to client\n");

		char buff[16] = "hello world";
		send(*sock, buff, 16, 0);

		displayValue(1);

		close(*sock);

	}

	close(mysocket);

	return 0;
}
