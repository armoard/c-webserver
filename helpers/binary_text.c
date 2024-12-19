#include "helpers.h"

char* text_to_binary(char* text) {
    size_t len = strlen(text);
    char* binary_output = malloc(len * 8 + 1);  // 8 bits is a char +1 for \0
    binary_output[len * 8] = '\0'; 

    // convert each char to binary
    for (size_t i = 0; i < len; i++) {
        unsigned char ch = text[i]; //handle negs
        for (int j = 7; j >= 0; j--) {
            binary_output[i * 8 + (7 - j)] = ((ch >> j) & 1) ? '1' : '0';  //shift bits to extract each bit and store 1 or 0
        }
    }

    return binary_output;
}

char* binary_to_text(char* binary_input) {
    size_t len = strlen(binary_input);
    size_t text_len = len / 8;  // same as above 
    char* text_output = malloc(text_len + 1);  
    text_output[text_len] = '\0';  

    // process 8 bits into a char 
    for (size_t i = 0; i < text_len; i++) {
        char byte[9] = {0}; 
        strncpy(byte, &binary_input[i * 8], 8);  // take 8 bits

        // convert to ascii
        text_output[i] = (char)strtol(byte, NULL, 2);
    }

    return text_output;
}
