#include <stdbool.h>

// Max length for properties
#define LENGTH 25

// Represents a game entry in the backlog
typedef struct {
    char name[LENGTH];
    char bucket[LENGTH];
    char added_on[LENGTH];
    char updated_on[LENGTH];
} entry;

// Represents a node in a linked list
typedef struct node {
    int index;
    entry game;
    struct node *next;
} node;

// Blueprints for functions
int insert_data(entry g);
int remove_data(int i, char *name);
void print_data(char *filter);
int unload_data();
int save_to_file();
int load_from_file();
int update_data(int i, char *status, char *date, char *name);