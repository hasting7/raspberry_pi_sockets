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
#define MAX_LEN 256

void setupSegPins();
void displayValue(int);

int main() {
	wiringPiSetup();
	setupSegPins();
	displayValue(0);


	struct sockaddr_in dest; // info about machine connecting to server
	struct sockaddr_in serv; // info about server
	int mysocket;
	char message[MAX_LEN] = { 0 };

	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv)); // zero out server struct
	serv.sin_family = AF_INET; // set type of connection to TCP/IP
	serv.sin_addr.s_addr = htonl(INADDR_ANY); // set our address to any interface
	serv.sin_port = htons(PORT);

	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr)); // bind serv information to mysocket

	// start listening and allow a queue of 'n' connections
	
	int connections = 0;

	for(;;) {
		listen(mysocket, 1);
		int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
		int *sock = malloc(sizeof(int *));
		memcpy(sock, &consocket, sizeof(int));

		// establish connetion
		displayValue(++connections);
		
		//server waits on client
		
		for (;;) {
			recv(*sock, message, MAX_LEN, 0);
			printf("message from client: %s\n", message);
	
			memset(message, 0, MAX_LEN);
	
			message = "heard that\n";

			send(*sock, message, MAX_LEN, 0);
		}

		close(*sock);

	}

	close(mysocket);

	return 0;
}
