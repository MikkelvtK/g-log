#include <stdio.h>
#include <stdlib.h>

#include "data.h"

// Initialise linked list
node *data = NULL;

int insert_data(game_entry g) {

    // Allocate memory for new node
    node *new_entry = malloc(sizeof(node));
    if (new_entry == NULL) {
        printf("Could not allocate memory for new data\n");
        return 1;
    }

    // Fill node with data
    new_entry->entry = g;

    // Set new entry as first node
    new_entry->next = data;
    data = new_entry;
}

void print_data() {
    
    node *tmp = data;

    while (tmp != NULL) {
        printf("Title of the game: %s\n", tmp->entry.game);
        tmp = tmp->next;
    }
}

int unload_data() {

    // Initialise temp and cursor nodes
    node *tmp = NULL;
    node *cursor = NULL;

    // Set temp and cursor to head
    tmp = data;
    cursor = data;

    while (cursor != NULL)
    {
        // Set cursor to next node
        cursor = cursor->next;

        // Free temp's node
        free(tmp);
        tmp = cursor;
    }
    return 0;
}