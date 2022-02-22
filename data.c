#include <stdio.h>
#include <stdlib.h>

#include "data.h"

// Initialise linked list
node *data = NULL;

void insert_data(entry g) {

    // Allocate memory for new node
    node *new_entry = malloc(sizeof(node));
    if (new_entry == NULL) {
        return;
    }

    // Fill new node with data
    new_entry->game = g;

    // Add new node to list
    new_entry->next = data;
    data = new_entry;

    // Set indices
    set_index(data, 0);
}

// ---- Add remove_data function
void remove_data(int i) {

    // Initialise temp and cursor nodes
    node *tmp = NULL;
    node *cursor = NULL;

    // Set temp and cursor to head
    tmp = data;
    cursor = data;

    // Check if head itself holds index
    if (cursor != NULL && cursor->index == i) {
        data = cursor->next;

        // Free node with index
        free(cursor);

        // Set new indices
        set_index(data, 0);
        return;
    }

    // Search for node with index
    while (cursor != NULL && cursor->index != i) {
            tmp = cursor;
            cursor = cursor->next;
    }

    // Unlink node with index
    tmp->next = cursor->next;

    // Free node with index
    free(cursor);

    // Set new indices
    set_index(data, 0);
}

// Checker function for testing
void print_data() {
    
    node *tmp = data;

    while (tmp != NULL) {
        printf("Index of %s: %i\n", tmp->game.name, tmp->index);
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

    while (cursor != NULL) {

        // Set cursor to next node
        cursor = cursor->next;

        // Free temp's node
        free(tmp);

        // Set tmp to cursor
        tmp = cursor;
    }
    return 0;
}

void set_index(node *n, int i) {
    
    // Confirm if end of list
    if (n == NULL) {
        return;
    }

    // Set index of next node
    set_index(n->next, i + 1);

    // Set index of current node
    n->index = i;
}