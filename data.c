#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    // Add new node to list
    new_entry->next = NULL;



    if (data == NULL) {
        data = new_entry;
        set_index(data, 0);
        return true;
    }

    node *tmp = data;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

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

    // Initialise temp and cursor nodes
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

// Checker function for testing
void print_data() {
  
    node *tmp = data;

    while (tmp != NULL) {
        printf("|%5i |%20s |%20s |%20s |%20s |\n",tmp->index,tmp->game.name,tmp->game.bucket,tmp->game.added_on,tmp->game.updated_on);


        tmp = tmp->next;
    }

}

void unload_data() {

    // NULL check
    if (data == NULL) {
        return;
    }

    // Initialise temp and cursor nodes
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

    // Initialise temp node
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
