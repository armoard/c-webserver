#ifndef UTILS_H
#define UTILS_H
#include "../config.h"

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;


char *text_to_binary(char *text);
char *binary_to_text(char *binary_input);

char *convert_bytes(char *body);

char *count_string_properties(char *body);

char *hex_to_rgb(char *body);

char *encode_url(char *body);

char *process_csv_to_json(char *body);



#endif // UTILS_H