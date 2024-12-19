#include "server.h"
#include "helpers/helpers.h"



struct GetRoute get_routes[] = {
    {"/", "html/index.html"},
    {"/hex-to-rgb", "html/hex-to-rgb.html"},
    {"/csv-to-json", "html/csv-to-json.html"},
    {"/encode-url", "html/encode-url.html"},
    {"/binary-text", "html/binary-text.html"},
    {"/string-inspect", "html/string-inspect.html"},
    {"/convert-bytes", "html/convert-bytes.html"},
    {"/styles.css", "html/styles.css"},

};


struct PostRoute post_routes[] = {
    {"/app/hex-to-rgb", hex_to_rgb},
    {"/app/csv-to-json", process_csv_to_json},
    {"/app/encode-url", encode_url},
    {"/app/binary-to-text", binary_to_text},
    {"/app/text-to-binary", text_to_binary},
    {"/app/string-inspect", count_string_properties},
    {"/app/convert-bytes", convert_bytes}

};

void send_http_response(int sockfd, char *header, char *content) {
    char response[BUFFER_SIZE];
    
    // create full answer
    snprintf(response, sizeof(response), "%s%s", header, content);

    // send to client
    send(sockfd, response, strlen(response), 0);
}


// process post
void process_generic_post(int sockfd, char* body, char* (*process_func)(char*), char* content_type) {
    char* output = process_func(body);  // process body 
    send_http_response(sockfd, content_type, output);  // send response
    free(output);  // free the output from functions 
}


// function to handle post requests based on route
void handle_post_request(int sockfd, char* uri, char* body) {
    int num_post_routes = sizeof(post_routes) / sizeof(post_routes[0]);

    for (int i = 0; i < num_post_routes; i++) {
        if (strcmp(uri, post_routes[i].path) == 0) {
            // call the generic function and pass the appropriate processing function
            process_generic_post(sockfd, body, post_routes[i].process_func, HTTP_HEADER_OK_PLAIN);
            return;
        }
    }

    // the route does not match, send 404 
    send_http_response(sockfd, HTTP_HEADER_404, "");
}

// function to handle get requests 
void handle_get_request(int sockfd, char* uri) {
    // checks css
    if (strcmp(uri, "/styles.css") == 0) {
        serve_file(sockfd, "html/styles.css", "text/css");
        return;
    }

    // checks html
    int num_get_routes = sizeof(get_routes) / sizeof(get_routes[0]);

    for (int i = 0; i < num_get_routes; i++) {
        if (strcmp(uri, get_routes[i].path) == 0) {
            serve_file(sockfd, get_routes[i].file, HTTP_HEADER_OK_HTML);
            return;
        }
    }

    // the route does not match, send 404 
    send(sockfd, HTTP_HEADER_404, strlen(HTTP_HEADER_404), 0);
}

// main fuc to handle requests
void handle_request(int sockfd, char *method_str, char *uri, char *body) {
    if (strcmp(method_str, "GET") == 0) {
        handle_get_request(sockfd, uri);  
    } 
    else if (strcmp(method_str, "POST") == 0) {
        handle_post_request(sockfd, uri, body);  
    } 
    else {
        send_http_response(sockfd, HTTP_HEADER_405, "");
    }
}

// func to serve html and css files
void serve_file(int sockfd, char *path, char *content_type) {
    FILE *file;
    char buffer[1024];
    size_t bytes_read;

    file = fopen(path, "rb");
    if (file == NULL) {
        send(sockfd, HTTP_HEADER_404, strlen(HTTP_HEADER_404), 0);
        return;
    }

    // send HTTP header with appropriate content type
    char header[256];
    snprintf(header, sizeof(header), "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", content_type);
    send(sockfd, header, strlen(header), 0);

    // read and send file content in blocks
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(sockfd, buffer, bytes_read, 0);
    }

    fclose(file);
}
