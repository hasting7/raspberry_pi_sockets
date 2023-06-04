#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 5566
#define MAX_LEN 256

void get_input(char *buffer) {
	memset(buffer, 0, MAX_LEN);
	fscanf(stdin, "%255[^\n]", buffer);
	fflush(stdin);
}

int main() {
	int mysocket;
	struct sockaddr_in dest;
	char message[MAX_LEN] = { 0 };
	
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("192.168.68.112");
	dest.sin_port = htons(PORT);
	
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));

	printf("connected to server\n");

	// established connection to server

	for (;;) {
		printf("type: ");
		get_input(message);

		if (message[0] == '\0') continue;

		printf("sending %s to server\n", message);

		send(mysocket, message, MAX_LEN, 0);
	
		recv(mysocket, message, MAX_LEN, 0);
	
		printf("message from server: %s\n", message);

		
	}	
	
	close(mysocket);	

	return 0;
}
