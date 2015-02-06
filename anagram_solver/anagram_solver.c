// Fill this in sometime.

#include "stdafx.h"

#define max_word_len 32

// Determines if a word has any unsupported characters.
// Supported characters exist between decimal 32 and 126 with the exception of the apostrophe, which is decimal 39. 
// Assumes that each word ends with a newline.
bool_t has_unsupported_chars(char* word)
{
    //TODO: I should actually strip that new line character. 
    int ind = 0;
    unsigned char c = word[ind];

    while (c != '\n')
    {
        if ((c < 32) | (c > 126) | (c == 39))
        {
            return true;
        }
        
        ind++;
        c = word[ind];
    }

    return false;
}

// Determines if a word is supported.
// Supported words do not contain unsupported characters and contain more than 1 character. 
// Assumes that each word ends with a new line.
bool_t is_supported(char* word)
{
    return !has_unsupported_chars(word) & (strlen(word) > 2);
}

// TODO:
// Update to void pointer.
void build_hashtable(char* input_file_name)
{
    FILE* input_file;
   
    errno_t error;
    error = fopen_s(&input_file, input_file_name, "r");

    if (error != 0)
    {
        fprintf(stderr, "Can't open input file: %s\n", input_file_name);
        return NULL;
    }
    
    linked_list_node_t* head = NULL;
    linked_list_node_t* tail = NULL;

    //testing by just placing everything in a linked list for now.
    char word_buffer[max_word_len];
    while (fgets(word_buffer, max_word_len, input_file))
    {
        if (is_supported(word_buffer))
        {
            char* word = malloc(sizeof(char) * strlen(word_buffer) + 1);
            
            if (word == NULL)
            {
                return NULL;
            }
            else
            {
                
                error = strcpy_s(word, strlen(word_buffer) + 1, word_buffer); //Check this errno later

                if (error != 0)
                {
                    fprintf(stderr, "Failed copying a string.: %s\n", word_buffer);
                    return NULL;
                }

                if (head == NULL)
                {
                    head = create_linked_list_node(word);
                    tail = head;
                }
                else
                {
                    tail = append_to_linked_list(word, tail);
                }
            }
        }
    }

    //Printing the linked list
    linked_list_node_t* curr = head;
    while (curr != NULL)
    {
        printf("%s", curr->word);
        curr = curr->next;
    }
    
    free_linked_list(head);

    fclose(input_file);

    //Return hash
}

int _tmain(int argc, _TCHAR* argv[])
{
    // Allow memory-leak checks to occur at each exit point in the program.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    char* input_file_name = "../data/words";
    
    
    //build_hashtable(input_file_name);


    hash_table_t* hash_table = hash_table_create();
    
    //26
    hash_table_insert_word("dog", hash_table);
    hash_table_insert_word("god", hash_table);

    //56
    hash_table_insert_word("this", hash_table);
    hash_table_insert_word("hits", hash_table);

    //24
    hash_table_insert_word("cat", hash_table);
    hash_table_insert_word("act", hash_table);


    hash_node_t* hash_node = hash_table->table + 24;

    //Printing the linked list
    linked_list_node_t* curr = hash_node->head;
    while (curr != NULL)
    {
        printf("%s\n", curr->word);
        curr = curr->next;
    }

    //free_linked_list(head);



    //unsigned int x = hash_table_hash("this");
    //printf("%d\n", x);



    getchar();
    
   
    
    
    //prompt user for words and stuff
    return 0;
}

