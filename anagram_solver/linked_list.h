

struct linked_list_node_s
{
    char* word;
    struct linked_list_node_s* next;
};

typedef struct linked_list_node_s linked_list_node_t;

linked_list_node_t* create_linked_list_node(char* word);
linked_list_node_t* append_to_linked_list(char* word, linked_list_node_t* node);
void free_linked_list(linked_list_node_t* head);