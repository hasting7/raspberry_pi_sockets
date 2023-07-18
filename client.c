#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_LEN 256 // 256

int main() {
	int mysocket;
	struct sockaddr_in dest;
	// char message[MAX_LEN] = { 0 };
	
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("192.168.4.84");
	dest.sin_port = htons(PORT);
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
	printf("connected to server\n");

	// for (;;) {
	// 	send(mysocket, "Hello world", MAX_LEN, 0);

	// 	recv(mysocket, message, MAX_LEN, 0);

	// 	printf("server message: %s\n",message);
	// }
	// printf("sending close\n");
	// // send(mysocket, "exit", MAX_LEN, 0);
	close(mysocket);	

	return 0;
}
