



#include "stdafx.h"

struct linked_list_node_s
{
    char* word;
    struct linked_list_node_s* next;
};

typedef struct linked_list_node_s linked_list_node_t;

linked_list_node_t* create_linked_list_node();

linked_list_node_t* create_linked_list_node(char* word)
{
    linked_list_node_t* linked_list_node = malloc(sizeof(linked_list_node_t));

    if (linked_list_node == NULL)
    {
        return NULL;
    }
    else
    {
        linked_list_node->word = word;
        linked_list_node->next = NULL;

        return linked_list_node;
    }
}

linked_list_node_t* append_to_linked_list(char* word, linked_list_node_t* node)
{
    linked_list_node_t* new_node = create_linked_list_node(word);

    while (node->next != NULL)
    {

        //node = node.next;
    }


}