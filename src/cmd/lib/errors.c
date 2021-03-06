#include <stdio.h>

const char *errors[] = {
    "Unable to allocate memory",
    "There is no data",
    "Index is not found",
    "Could not open file",
    "Unable to unload memory",
    "No environment variable found for data path",
};

void print_error(int i) {
    printf("Error: (%i) %s\n", i, errors[i - 1]);
}
