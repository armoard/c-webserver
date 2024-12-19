#include "helpers.h"

int is_safe_character(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
           (c >= '0' && c <= '9') || c == '-' || c == '_' || 
           c == '.' || c == '~';
}

char *encode_url(char *body) {
    size_t len = strlen(body);
    char *output = malloc(len * 3 + 1); // each caracter can expand by %xx + for \0
    int pos = 0; 
    while (*body) {
        if (is_safe_character(*body)) {
            output[pos++] = *body;
        } 
        else {
            snprintf(&output[pos], 4, "%%%02X", (unsigned char)*body); //handle negs
            pos += 3;  
        }
        body++;
    }

    output[pos] = '\0';  
    return output;  
}