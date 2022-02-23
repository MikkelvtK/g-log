#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "helpers.h"

void format_date(char *d, int s) {

    // Create tmp to store date
    char tmp[s];

    // Get current time
    const time_t t = time(NULL);
    struct tm *now = localtime(&t);

    // Format date
    strftime(tmp, sizeof(tmp), "%x - %I:%M%p", now);

    // Copy string to argument
    strcpy(d, tmp);
}