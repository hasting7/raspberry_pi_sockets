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


#define PORT 5566
#define MAX_LEN 256

#define LIGHT 15

volatile int connections = 0;

typedef struct button_info_struct {
	int pin;
	void (*callback)();
	time_t last_press;
	time_t pause;
} Button;

void setupSegPins();
void displayValue(int);
void *thread_func(void *);
void *button_thread_func(void *);
void reset_button();

void *thread_func(void *data) {
	printf("thread created\n");

	return NULL;
}

void *button_thread_func(void *data) {
	Button *btn = (Button *) data;
	wiringPiSetup();
	pinMode(btn->pin, INPUT);
	pullUpDnControl(btn->pin, PUD_UP);

	printf("button on pin %d\n",btn->pin);

	for (;;) {
		if ((digitalRead(btn->pin) == HIGH) && (btn->last_press + btn->pause < time(NULL))) {
			btn->callback();
			btn->last_press = time(NULL);
		}
	}
	
	return NULL;
}

void reset_button() {
	printf("reset\n");
	connections = 0;
	// displayValue(0);
}

int main() {
	wiringPiSetup();
	pinMode(LIGHT, OUTPUT);

	digitalWrite(LIGHT, LOW);


	struct sockaddr_in dest; // info about machine connecting to server
	struct sockaddr_in serv; // info about server
	int mysocket;
	pthread_t thread; 
	//char message[MAX_LEN] = { 0 };


	// Button lights = { .pin = 21, .callback = &reset_button, .last_press = time(NULL), .pause = 0.1};
	// pthread_create(&thread, NULL, button_thread_func, (void *) &lights);


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
	
		pthread_create(&thread, NULL, thread_func, (void *) &socket);


		digitalWrite(LIGHT, HIGH);
		

		close(*sock);

	}

	close(mysocket);

	return 0;
}
