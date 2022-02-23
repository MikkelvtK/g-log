#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "data.h"

const char *BUCKETS[4] = {"Backlog", "In progress", "Finished", "Paused"};

void add(char *game) {

    printf("Game: %s\n", game);

    entry new_entry = {
        .bucket = "Backlog",
        .added_on = "Today",
        .updated_on = "Today",
    };

    strcpy(new_entry.name, game);

    insert_data(new_entry);
}
