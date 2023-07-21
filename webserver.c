// webserver.c
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 5566
#define BUFFER_SIZE 1024

#define MAX_FILE_SIZE 100000

char *read_file(char *);



char *read_file(char *name) {
    printf("READING\n");
    FILE *fp = fopen(name, "r");
    FILE *header_p = fopen("header", "r");
    char *file_content = calloc(MAX_FILE_SIZE, sizeof(char));
    int index = 0;
    char resp;

    while(!feof(header_p)) {
        resp = fgetc(header_p);
        if (feof(header_p)) break;
        file_content[index] = resp;
        if (resp == '\n') {
            printf("newline\n");
            index++;
            file_content[index] = '\r';
        }
        index++;
    }

    file_content[index] = '\n';
    file_content[index + 1] = '\r';
    index += 2;

    printf("header file read:\n%s",file_content);

    while (!feof(fp)) {
        resp = fgetc(fp);
        if (feof(fp)) break;
        file_content[index] = resp;
        index++;
    }
    // *file_content = "\r";
    fclose(fp);
    fclose(header_p);

    printf("final file read:\n%s",file_content);
    return file_content;
}

int main() {
    char buffer[BUFFER_SIZE];

    // char *file = read_file("main.html");

    char *resp = read_file("main.html");


    printf("%s",resp);

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("webserver (socket)");
        return 1;
    }
    printf("socket created successfully\n");

    // Create the address to bind the socket to
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Create client address
    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    // Bind the socket to the address
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("webserver (bind)");
        return 1;
    }
    printf("socket successfully bound to address\n");

    // Listen for incoming connections
    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("webserver (listen)");
        return 1;
    }
    printf("server listening for connections\n");


    for (;;) {
        // Accept incoming connections
        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                               (socklen_t *)&host_addrlen);
        if (newsockfd < 0) {
            perror("webserver (accept)");
            continue;
        }
        printf("connection accepted\n");

        // Get client address
        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr,
                                (socklen_t *)&client_addrlen);
        if (sockn < 0) {
            perror("webserver (getsockname)");
            continue;
        }

        // Read from the socket
        int valread = read(newsockfd, buffer, BUFFER_SIZE);
        if (valread < 0) {
            perror("webserver (read)");
            continue;
        }

        // Read the request
        char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        sscanf(buffer, "%s %s %s", method, uri, version);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), method, version, uri);

        // Write to the socket
        int valwrite = write(newsockfd, resp, strlen(resp));
        if (valwrite < 0) {
            perror("webserver (write)");
            continue;
        }

        close(newsockfd);
    }

    return 0;
}