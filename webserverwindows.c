#include "config.h"
#include "server.h"  
// gcc webserverwindows.c server.c helpers/csv_utils.c helpers/hex_utils.c helpers/encode_utils.c helpers/binary_text.c helpers/string_inspect.c helpers/convert_bytes.c -o webserver -lws2_32
int main() {
    WSADATA wsaData;
    char buffer[BUFFER_SIZE];
    char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
    char body[BUFFER_SIZE] = {0};

    // initialize winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    // create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        perror("webserver (socket)");
        WSACleanup();  // clean up winsock on error
        return 1;
    }
    printf("Socket created successfully\n");

    // create the address to bind the socket to 
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind the socket to the address
    if (bind(sockfd, (struct sockaddr*)&host_addr, host_addrlen) != 0) {
        perror("webserver (bind)");
        closesocket(sockfd);  // close socket on error
        WSACleanup();         // clean up Winsock on error
        return 1;
    }
    printf("Socket successfully bound to address\n");

    // listen for incoming connections
    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("webserver (listen)");
        closesocket(sockfd);  // close socket on error
        WSACleanup();         // clean up Winsock on error
        return 1;
    }
    printf("Server listening for connections\n");

    // accept incoming connections
    for (;;) {
        struct sockaddr_in client_addr;
        socklen_t client_addrlen = sizeof(client_addr);

        int newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addrlen);
        if (newsockfd == INVALID_SOCKET) {
            perror("webserver (accept)");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));  // clean main buffer
        memset(body, 0, sizeof(body));      // clean buffer body 

        // print the client's IP address and port directly from accept()
        printf("Client connected: [%s:%u]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // receive data from the client using recv()
        int valread = recv(newsockfd, buffer, BUFFER_SIZE, 0);
        if (valread == SOCKET_ERROR) {
            perror("webserver (recv)");
            closesocket(newsockfd);
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
                strcpy(body, content_start + 4);  // skip to headers
            }
        }

        // handle get or post request
        handle_request(newsockfd, method, uri, body);

        // close the accepted connection
        closesocket(newsockfd);
    }

    // close the main socket after use (won't be reached in the current loop)
    closesocket(sockfd);
    
    // clean up winsock
    WSACleanup();
    
    return 0;
}