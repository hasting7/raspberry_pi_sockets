// webserver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

char *ok_header = "HTTP/1.0 200 OK\n\rServer: webserver-c\n\rContent-Type: text/html; charset=UTF-8\n\rContent-Length: %d\n\rAccept-Ranges: bytes\r\nConnection: close\r\n\n\r";

struct thread_info {
    int socket;
    pthread_t thread;
};
int main_socket;
char *main_page_path;

//#define TESTING
//#define SHOW

#ifndef TESTING
#include "server.h"
#endif


#define PORT 5566
#define BUFFER_SIZE 2028
#define MAX_TIME_CHAR 3

#define MAX_WRITE_SIZE 1000000

char *read_file(char *, char *);
void parse_web_response(char *, char *);
char *generate_html_resp(char *, char *, int *);


int get_file_length(char *filename) {
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) {
        fprintf(stderr,"file reading error\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fclose(fp);
    fp = NULL;
    return length;
}

char *generate_html_resp(char *header, char *html_file, int *length) {
    int file_length = get_file_length(html_file);
    char complete_header[BUFFER_SIZE];
    char *final_message = calloc(MAX_WRITE_SIZE, sizeof(char));
    char *file_content = calloc(file_length + 1, sizeof(char));

    FILE *fp = fopen(html_file,"r");

    int index = 0;
    int resp = 0;
    while (!feof(fp)) {
        resp = fgetc(fp);
        if (feof(fp)) break;
        file_content[index] = resp;
        index++;
    }

    sprintf(complete_header, header, file_length);
    strcat(final_message, complete_header);
    strcat(final_message, file_content);

    *length = strlen(final_message) + 1;
    final_message[*length - 1] = '\0';

    free(file_content);
    fclose(fp);
    fp = NULL;
    return final_message;
}

void parse_web_response(char *uri, char *timer_filename) {
    static int state = 0;
    char time[MAX_TIME_CHAR] = { 0 };
    if (strncmp(uri,"/?", 2) != 0) return; 

    if (strncmp(uri, "/?timer=", 8) == 0) {
        for (; *uri != '='; uri++) {};
        uri++;
        for (int i = 0; *uri != '&'; uri++) {
            time[i++] = *uri;
            if (i > MAX_TIME_CHAR) {
                fprintf(stderr, "TIMER TOO LONG: %d\n", i);
                return;
            }
        };
        uri++;
        printf("%s %s\n",uri,time);
        FILE *timer_fp = fopen(timer_filename, "w");
        if (strcmp(uri,"set=") == 0) {
            fprintf(timer_fp, "timer: %d\n",atoi(time));
        }
        fclose(timer_fp);
        return;
    }

    if (strncmp(uri,"/?colors=",9) == 0) {
        sscanf(uri, "/?colors=%d", &state);
        fprintf(stderr,"state: %d\n",state);
#ifndef TESTING
        set_color(state);
#endif
        return;
    }

}

void *thread_func(void *data) {
    struct thread_info *info = (struct thread_info *) data;
    pthread_t thread = info->thread;
    int socket = info->socket;

    char temp[BUFFER_SIZE];
    char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
    int items = read(socket, temp, BUFFER_SIZE);
        
    sscanf(temp, "%s %s %s", method, uri, version);
    parse_web_response(uri, "./timer.info");
    fprintf(stderr,"client: %d):%s %s %s\n", socket, method, version, uri);

    int length = 0;
    char *buffer = generate_html_resp(ok_header, main_page_path, &length);

    send(socket, buffer, length, 0);

    free(buffer);
    close(socket);
    pthread_exit((void *) &thread);
    free(info);
    return NULL;
}

int main(int argc, char **argv) {
    main_page_path = argv[1];
  
    struct sockaddr_in dest; /* socket info about the machine connecting to us */
    struct sockaddr_in serv; /* socket info about our server */
    pthread_t thread = -1;
    socklen_t socksize = sizeof(struct sockaddr_in);

    memset(&serv, 0, sizeof(serv));           /* zero the struct before filling the fields */
    serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    serv.sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
    serv.sin_port = htons(PORT);           /* set the server port number */    

    main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (main_socket == -1) {
        fprintf(stderr,"webserver (socket)\n");
        return 1;
    }
  
    /* bind serv information to mysocket */
    int bind_resp = bind(main_socket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
    if (bind_resp != 0) {
        fprintf(stderr,"webserver (bind)\n");
        close(main_socket);
        return 1;
    }


    /* start listening, allowing a queue of up to 1 pending connection */

    while (1) {
        listen(main_socket, 1);
        int consocket = accept(main_socket, (struct sockaddr *)&dest, &socksize);

        // *sock = consocket;
        // *thread_id = thread;
        struct thread_info *info = malloc(sizeof(struct thread_info));
        info->socket = consocket;
        info->thread = thread;


        pthread_create(&thread, NULL, thread_func, (void *) info);

    }

    close(main_socket);
    return 0;
}
