#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "data.h"

// Initialise linked list
node *data = NULL;

bool insert_data(entry g) {

    // Allocate memory for new node
    node *new_entry = malloc(sizeof(node));
    if (new_entry == NULL) {
        printf("Failed to allocate memory\n");
        return false;
    }

    // Fill new node with data
    new_entry->game = g;
    new_entry->next = NULL;

    // NULL check
    if (data == NULL) {
        data = new_entry;
        set_index(data, 0);
        return true;
    }

    // Initialise temp head
    node *tmp = data;

    // Traverse the list to the end
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    // Insert new node
    tmp->next = new_entry;
    set_index(data, 0);
    return true;
}

void remove_data(int i) {

    // NULL check
    if (data == NULL) {
        printf("There is nothing to remove\n");
        return;
    }

    // Initialise temp and cursor heads
    node *tmp = data;
    node *cursor = data;

    // Remove node if head itself has index
    if (cursor->index == i) {
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

    // Return if node with index is not in list
    if (cursor == NULL) {
        printf("Index was not in list\n");
        return;
    }

    // Remove node with index
    tmp->next = cursor->next;
    free(cursor);
    set_index(data, 0);
}

void print_data(char *filter) {
    
    // Initialise temp head
    node *tmp = data;
    
    // format row
    char *row = "\t\xBA%5i \xB3%25s \xB3%25s \xB3%25s \xB3%25s \xBA\n";

    // Check if results are found
    bool results = false;

    while (tmp != NULL) {

        // Check if node matches filter
        if (filter == NULL || filter == tmp->game.bucket) {
            results = true;

            // Print row
            printf(row, tmp->index, tmp->game.name, tmp->game.bucket, tmp->game.added_on, tmp->game.updated_on);
        }

        // Set temp to next node
        tmp = tmp->next;
    }

    // Print feedback if no results were found
    if (!results) {
        printf("\n\tNO RESULTS WERE FOUND\n\n");
    }
}

void unload_data() {

    // NULL check
    if (data == NULL) {
        return;
    }

    // Initialise temp and cursor heads
    node *tmp = data;
    node *cursor = data;

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

void save_to_file(FILE *f, char *path) {

    // Open file to save data
    f = fopen(path, "w");
    if (f == NULL) {
        printf("Could not open file\n");
        return;
    }

    // Initialise temp head
    node *tmp = data;

    while (tmp != NULL) {   

        // Write data to file
        entry buffer = tmp->game;
        fwrite(&buffer, sizeof(entry), 1, f);

        // Get next node
        tmp = tmp->next;
    }
    fclose(f);
}

void load_from_file(FILE *f, char *path) {

    // Open file to load data
    f = fopen(path, "r");
    if (f == NULL) {
        printf("Could not open file\n");
        return;
    }

    // Load data from file
    entry buffer;
    while (fread(&buffer, sizeof(entry), 1, f)) {
        insert_data(buffer);
    }
    
    fclose(f);
}
