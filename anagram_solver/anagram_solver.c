// Fill this in sometime.

#include "stdafx.h"

#define WORD_BUFFER_SIZE 128

static const int MAX_WORD_LEN = 64;
static const int MIN_WORD_LEN = 2;

//Determines if a word has an unsupported characters.
//Assumes that the word ends with a newline.
bool_t has_unsupported_chars(char* word)
{
    int ind = 0;
    unsigned char c = word[ind];

    while (c != '\n')
    {
        //TODO: This needs to be changed.
        //Supported characters are letters and spaces only. 


        //Supported characters exist between 0x20 and 0x7E.
        //The apostrophe, 0x27, is not supported. 
        if ((c < 0x20) | (c > 0x7E) | (c == 0x27))
        {
            return true;
        }
        
        ind++;
        c = word[ind];
    }

    return false;
}

//Determines if a word is supported.
bool_t is_supported(char* word)
{
    int len = strlen(word);

    //Argument must contain at most one newline character. 
    int newline_count = 0;
    for (int i = 0; i < len; i++)
    {
        char c = word[i];

        if (c == '\n')
        {
            newline_count++;
        }
    }

    bool_t newline_count_verified = newline_count == 1;

    //Argument must adhere to the min and max word lengths.
    //MIN_WORD_LEN is increased by 1 compensate for the newline character.
    bool_t length_verified = (len >= MIN_WORD_LEN + 1) & (len <= MAX_WORD_LEN);

    //Argument must end in a newline.
    char last = word[len - 1];
    bool_t last_char_verified = (last == '\n');
    
    return newline_count_verified & length_verified & last_char_verified & !has_unsupported_chars(word);
}

errno_t anagram_solver_create(hash_table_t** hash_table_addr, char* input_file_name)
{
    FILE* input_file;

    errno_t error;
    error = fopen_s(&input_file, input_file_name, "r");

    //how do I do my error checking properly?
    if (error != 0)
    {
        fprintf(stderr, "Can't open input file: %s\n", input_file_name);
        return error;
    }

    hash_table_t* hash_table = hash_table_create();

    //needs to be errno_t
    if (hash_table == NULL)
    {
        return -1;
    }

    char word_buffer[WORD_BUFFER_SIZE];
    while (fgets(word_buffer, WORD_BUFFER_SIZE, input_file))
    {
        if (is_supported(word_buffer))
        {
            //Strip the newline at the end of the word
            int word_len = strlen(word_buffer);
            word_buffer[word_len - 1] = '\0';
            word_len--;

            char* word = malloc(sizeof(char) * word_len + 1);

            if (word == NULL)
            {
                return -1;
            }
            else
            {
                error = strcpy_s(word, word_len + 1, word_buffer); 

                if (error != 0)
                {
                    fprintf(stderr, "Failed copying string.: %s\n", word_buffer);
                    return -1;
                }
               
                //This needs to return errno instead of NULL.
                void* error2 = hash_table_insert_word(word, hash_table);

                if (error2 == NULL)
                {
                    fprintf(stderr, "Failed creating hash table.: %s\n", word_buffer);
                    return -1;
                }
            }
        }
    }
    
    *hash_table_addr = hash_table;
    fclose(input_file);
    return 0;
}

void anagram_solver_solve(hash_table_t* hash_table, char* word)
{
    unsigned hash = hash_table_hash(word);

    if (hash <= hash_table->size)
    {
        hash_node_t* hash_node = hash_table->table + hash;

        //now print everything at that node..
        linked_list_node_t* curr = hash_node->head;
        while (curr != NULL)
        {
            printf("%s\n", curr->word);
            curr = curr->next;
        }

    }
    else
    {
        printf("Hash table doesn't contain any anagrams for that word.");
    }
}