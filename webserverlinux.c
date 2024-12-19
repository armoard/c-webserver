#include "config.h"
#include "server.h"  
int main() {
    char buffer[BUFFER_SIZE];
    char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
    char body[BUFFER_SIZE] = {0};

    // create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }
    printf("Socket created successfully\n");

    // addr for socket
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // listening from any

    // bind socket to addr
    if (bind(sockfd, (struct sockaddr*)&host_addr, host_addrlen) != 0) {
        perror("webserver (socket)");
        close(sockfd);  
        return 1;
    }
    printf("Socket successfully bound to address\n");

    // start listening 
    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("webserver (listen)");
        close(sockfd);  
        return 1;
    }
    printf("Server listening for connections\n ");

    // accept incoming connections
    for (;;) {
        struct sockaddr_in client_addr;
        socklen_t client_addrlen = sizeof(client_addr);

        int newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addrlen);
        if (newsockfd < 0) {
            perror("webserver (accept)");
            continue;   
        }

        memset(buffer, 0, sizeof(buffer));  // clean main buffer
        memset(body, 0, sizeof(body));      // clean body buffer

        // print the client's IP address and port directly from accept()
        printf("Client connected: [%s:%u]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // receive data from the client using recv()
        int valread = recv(newsockfd, buffer, BUFFER_SIZE, 0);
        if (valread < 0) {
            perror("webserver (recv)");
            close(newsockfd);
            continue;
        }

        // read the HTTP request method, URI, and version
        sscanf(buffer, "%s %s %s", method, uri, version);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), method, version, uri);

        // if its a post method read to body
        if (strcmp(method, "POST") == 0) {
            char *content_start = strstr(buffer, "\r\n\r\n");
            if (content_start) {
                strcpy(body, content_start + 4);  // Saltar los encabezados
            }
        }

         // handle get or post request
        handle_request(newsockfd, method, uri, body);

        // close the accepted connection
        close(newsockfd);
    }

    // close the main socket after use (won't be reached in the current loop)
    close(sockfd);

    return 0;
}