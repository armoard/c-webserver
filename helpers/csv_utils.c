#include "helpers.h"

// splits a string into tokens based on a given delimiter. used for splitting the body into lines first and then by , for csv fields
int split_string_by_delimiter(char *line, char *tokens[], int max_tokens, char *delimiter) {
    int token_count = 0;
    char *token = strtok(line, delimiter);
    while (token != NULL && token_count < max_tokens) {
        tokens[token_count++] = token;
        token = strtok(NULL, delimiter);
    }
    return token_count;
}

// generate the json by headers and values
void generate_json_object(char *json_buffer, char *fields[], int field_count, char *values[], int value_count) {
    strcat(json_buffer, "  {\n");
    for (int j = 0; j < field_count; j++) {
        char temp[MAX_LINE_LEN];
        snprintf(temp, sizeof(temp), "    \"%s\": \"%s\"", fields[j], values[j]);
        strcat(json_buffer, temp);
        if (j < field_count - 1) {
            strcat(json_buffer, ",\n");
        } 
        else {
            strcat(json_buffer, "\n");
        }
    }
    strcat(json_buffer, "  }");
}

// main fun
char *process_csv_to_json(char *body) {
    char *json_buffer = malloc(MAX_JSON_SIZE);

    json_buffer[0] = '\0';  // initialize as an empty string to avoid garbage values when using strcat

    // get lines from body
    
    char *lines[MAX_LINE_LEN];
    int line_count = split_string_by_delimiter(body, lines, MAX_LINE_LEN, "\r\n");

    if (line_count < 2) {
        snprintf(json_buffer, MAX_JSON_SIZE, "{\"error\": \"Not enough lines in the CSV!\"}");
        return json_buffer;  
    }

    // get headers
    char *fields[MAX_FIELDS];
    int field_count = split_string_by_delimiter(lines[0], fields, MAX_FIELDS, ",");

    // start the json
    strcat(json_buffer, "[\n");

    // process each line 
    for (int i = 1; i < line_count; i++) {
        if (i > 1) strcat(json_buffer, ",\n");

        char *values[MAX_FIELDS];
        int value_count = split_string_by_delimiter(lines[i], values, field_count, ",");

        generate_json_object(json_buffer, fields, field_count, values, value_count);
    }

    strcat(json_buffer, "\n]\n");

    return json_buffer;  
}