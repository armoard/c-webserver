#include "helpers.h"

void add_word(char *current_word, WordCount word_list[], int *word_count) {
    if (strlen(current_word) == 0) return;  // if current word is empty

    // check if current word already exists
    int found = 0;
    for (int i = 0; i < *word_count; i++) {
        if (strcmp(word_list[i].word, current_word) == 0) {
            word_list[i].count++;
            found = 1;
            break;
        }
    }
    // if not add it 
    if (!found && *word_count < MAX_WORDS) {
        strcpy(word_list[*word_count].word, current_word);
        word_list[*word_count].count = 1;
        (*word_count)++;
    }
}

// fun to count letters, numbers and words, and add words to the list
void process_char(char c, char *current_word, int *letters, int *numbers, int *in_word, WordCount word_list[], int *word_count) {
    if (isalpha(c)) {
        (*letters)++;
        if (!(*in_word)) {
            *in_word = 1;
        }
        strncat(current_word, &c, 1);  // add letter to current word
    } 
    else if (isdigit(c)) {
        (*numbers)++;
        if (!(*in_word)) {
            *in_word = 1;
        }
        strncat(current_word, &c, 1);  // add number to current word
    } 
    else if (*in_word) {
        // if you hit a delimiter and it was inside a word, add the word
        *in_word = 0;
        add_word(current_word, word_list, word_count);
        current_word[0] = '\0';  // reset current word
    }
}

// main fun
char *count_string_properties(char *body) {
    int letters = 0, numbers = 0, len = 0;
    char current_word[MAX_WORD_LEN] = {0};
    int in_word = 0;
    WordCount word_list[MAX_WORDS] = {0};
    int word_count = 0;
    char *response = malloc(BUFFER_SIZE);

    while (*body) {
        len++;
        process_char(*body, current_word, &letters, &numbers, &in_word, word_list, &word_count);
        body++;
    }

    if (in_word) {
        add_word(current_word, word_list, &word_count);
    }

    snprintf(response, BUFFER_SIZE,
             "Letters: %d\nNumbers: %d\nLength of the string: %d\nWords: %d\n\nWord occurrences:\n",
             letters, numbers, len, word_count);

    for (int i = 0; i < word_count; i++) {
        char word_info[MAX_WORD_LEN + 20];  // buffer to store the information of each word
        snprintf(word_info, sizeof(word_info), "%s: %d times\n", word_list[i].word, word_list[i].count);
        strncat(response, word_info, BUFFER_SIZE - strlen(response) - 1); 
    }
    return response;
}