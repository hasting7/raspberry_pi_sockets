#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <wiringPi.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#include "server.h"


#define PORT 8080
#define MAX_LEN 256


void *thread_func(void *data) {
	int *socket = (int *) data;
	// char message[MAX_LEN] = { 0 };

	printf("new thread %d\n", *socket);

	// for (;;) {
	// 	recv(*socket, message, MAX_LEN, 0);
	// 	if (message[0] == '\0') continue;
	// 	printf("message: %s\n", message);
	// 	if (strcmp(message, "exit") == 0) {
	// 		printf("closing thread %d\n", *socket);
	// 		break;
	// 	}
	// 	send(*socket, "ok", MAX_LEN, 0);
	// }


	return NULL;
}


int main() {
	setup();

	set_color(CYAN);

	
	struct sockaddr_in dest; // info about machine connecting to server
	struct sockaddr_in serv; // info about server
	int mysocket;
	// pthread_t thread; 

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

		// establish connetion
		
		//server waits on client

		int *socket = malloc(sizeof(int *));

		memcpy(socket, &consocket, sizeof(int));
	
		// pthread_create(&thread, NULL, thread_func, (void *) &socket);


		close(*sock);

	}

	close(mysocket);

	return 0;
}
