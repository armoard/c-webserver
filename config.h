#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")  
    #define close(s) closesocket(s)     
    typedef int socklen_t;             
#else
    // Cabeceras y configuración para Linux/Unix
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#define MAX_WORDS 100
#define MAX_WORD_LEN 50
#define MAX_JSON_SIZE 10000
#define BUFFER_SIZE 10000
#define MAX_LINE_LEN 1024  
#define MAX_FIELD_LEN 100
#define MAX_FIELDS 10
#define MIN_MALLOC 50

#define PORT 8080

#define HTTP_HEADER_OK_HTML "HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n"
#define HTTP_HEADER_OK_TEXT "HTTP/1.0 200 OK\r\nContent-type: text/plain\r\n\r\n"
#define HTTP_HEADER_OK_PLAIN "HTTP/1.0 200 OK\r\nContent-type: text/plain\r\n\r\n"
#define HTTP_HEADER_404 "HTTP/1.0 404 Not Found\r\nContent-type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>"
#define HTTP_HEADER_405 "HTTP/1.0 405 Method Not Allowed\r\nContent-type: text/html\r\n\r\n<html><body><h1>405 Method Not Allowed</h1></body></html>"

#endif