#ifndef SERVER_H

struct GetRoute {
    char* path;
    char* file;
};

struct PostRoute {
    char* path;
    char* (*process_func)(char* body);
};

void serve_file(int sockfd, char *path, char *header);
void handle_request(int sockfd, char *method_str, char *uri, char *body);

#endif 
