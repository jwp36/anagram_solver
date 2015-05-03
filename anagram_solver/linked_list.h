struct linked_list_node_s
{
    char* word;
    int len;
    struct linked_list_node_s* next;
};

typedef struct linked_list_node_s linked_list_node_t;

// Create a linked list node.
// The node's word is set to the argument to the function.
// Return a pointer to the linked list node if successful.
// Return NULL if unsuccessful.
linked_list_node_t* create_linked_list_node(char* word);

// Append a word to a linked list. 
// The node parameter specifies the member of the linked list that will have a word appended to it.
// A new linked list node is created in this function.
// Returns a pointer to the tail of the linked list if successful.
// Return NULL if unsuccessful.
linked_list_node_t* append_to_linked_list(char* word, linked_list_node_t* node);

// Free all the nodes of a linked list. The contents of each linked list node are also freed.
void free_linked_list(linked_list_node_t* head);