
// Max length for properties
#define LENGTH 255

// Represents a game entry in the backlog
typedef struct {
    char name[LENGTH];
    char status[LENGTH];
    char added_on[LENGTH];
    char updated_on[LENGTH];
} entry;

// Represents a node in a linked list
typedef struct node {
    entry game;
    struct node *next;
} node;

// Blueprints for functions
int insert_data(entry g);
void print_data();
int unload_data();