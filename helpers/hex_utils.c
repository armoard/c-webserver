#include "helpers.h"

char *hex_to_rgb(char *body) {
    int r, g, b;
    char hexColor[7];
    char *response = malloc(MIN_MALLOC);
    // extract hexdecimal value from the body
    sscanf(body, "#%6s", hexColor);
    // convert to int 
    sscanf(hexColor, "%2x%2x%2x", &r, &g, &b);

    snprintf(response, 30, "RGB: (%d, %d, %d)", r, g, b);

    return response;
}