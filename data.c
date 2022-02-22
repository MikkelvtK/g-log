#include <stdio.h>
#include <stdlib.h>

#include "data.h"

// Initialise linked list
node *data = NULL;

void insert_data(entry g) {

    // Allocate memory for new node
    node *new_entry = malloc(sizeof(node));
    if (new_entry == NULL) {
        printf("Failed to allocate memory\n");
        return;
    }

    // Fill new node with data
    new_entry->game = g;

    // Add new node to list
    new_entry->next = data;
    data = new_entry;
    set_index(data, 0);
}

void remove_data(int i) {

    // NULL check
    if (data == NULL) {
        printf("There is nothing to remove\n");
        return;
    }

    // Initialise temp and cursor nodes
    node *tmp = NULL;
    node *cursor = NULL;

    // Set temp and cursor to head
    tmp = data;
    cursor = data;

    // Remove node if head itself has index
    if (cursor != NULL && cursor->index == i) {
        data = cursor->next;
        free(cursor);
        set_index(data, 0);
        return;
    }

    // Search for node with index
    while (cursor != NULL && cursor->index != i) {
            tmp = cursor;
            cursor = cursor->next;
    }

    // Remove node with index
    tmp->next = cursor->next;
    free(cursor);
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

void unload_data() {

    // NULL check
    if (data == NULL) {
        printf("There is nothing to unload\n");
        return;
    }

    // Initialise temp and cursor nodes
    node *tmp = NULL;
    node *cursor = NULL;

    // Set temp and cursor to head
    tmp = data;
    cursor = data;

    while (cursor != NULL) {

        // Free memory of current node
        cursor = cursor->next;
        free(tmp);
        tmp = cursor;
    }
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