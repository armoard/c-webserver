#include "helpers.h"

char *convert_bytes(char *body) {
    char *sizes[] = { "B", "KB", "MB", "GB", "TB" };
    double bytes;
    char unit_from[3], unit_to[3];
    int from_index = -1, to_index = -1;

    // extract the units and value from the input string
    sscanf(body, "%2s %2s %lf", unit_from, unit_to, &bytes);

    char *output = malloc(MIN_MALLOC);  

    // determine the indexes of source and destination units in the sizes array
    for (int i = 0; i < 5; i++) {
        if (strcmp(unit_from, sizes[i]) == 0) {
            from_index = i;
        }
        if (strcmp(unit_to, sizes[i]) == 0) {
            to_index = i;
        }
    }

    // check if the units are valid
    if (from_index == -1 || to_index == -1) {
        snprintf(output, MIN_MALLOC, "Invalid unit: %s or %s", unit_from, unit_to);
        return output;
    }

    // convert the source unit to bytes
    bytes *= pow(1024, from_index);

    // convert bytes to the target unit
    bytes /= pow(1024, to_index);

    snprintf(output, MIN_MALLOC, "%.2f %s", bytes, unit_to);

    return output;
}