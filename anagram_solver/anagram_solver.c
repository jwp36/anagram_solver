#include "stdafx.h"

static const int MAX_WORD_LEN = 64;
static const int MIN_WORD_LEN = 2;

static const char ERROR_UNABLE_TO_OPEN_FILE[] = "ERROR: Unable to open input file: %s\n";

int cmpfunc(const void * a, const void * b)
{
    return (*(char*)a - *(char*)b);
}

errno_t anagram_solver_create(hash_table_t** hash_table_addr, char* input_file_name)
{
    //Open the input file for reading
    FILE* input_file;
    errno_t error;
    error = fopen_s(&input_file, input_file_name, "r");

    if (error != 0)
    {
        fprintf(stderr, ERROR_UNABLE_TO_OPEN_FILE, input_file_name);
        return error;
    }

    //Create an empty hash table
    hash_table_t* hash_table = hash_table_create();

    if (hash_table == NULL)
    {
        return -1;
    }

    //Insert valid words from the input file into the hash table
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
                //Copy contents of the word buffer into word
                if (strcpy_s(word, word_len + 1, word_buffer) != 0)
                {
                    return -1;
                }

                //Insert the word into the hash table
                if (hash_table_insert_word(word, hash_table) == NULL)
                {
                    return -1;
                }
            }
        }
    }

    *hash_table_addr = hash_table;
    fclose(input_file);
    return 0;
}

bool_t anagram_solver_word_is_supported(char* word)
{
    return is_supported(word);
}

// Determine if a word is supported.
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
    bool_t length_verified = (len >= MIN_WORD_LEN + 1) && (len <= MAX_WORD_LEN);

    //Argument must end in a newline.
    char last = word[len - 1];
    bool_t last_char_verified = (last == '\n');

    return newline_count_verified && length_verified && last_char_verified && !has_unsupported_chars(word);
}

// Determine if a word has an unsupported characters. Assumes that the word ends with a newline.
// Only letters without diacritical marks are supported characters.
bool_t has_unsupported_chars(char* word)
{
    int ind = 0;
    unsigned char c = word[ind];

    while (c != '\n')
    {
        //If c is not a letter...
        if (!(((c >= 0x41) && (c <= 0x5A)) || ((c >= 0x61) && (c <= 0x7A))))
        {
            return true;
        }

        ind++;
        c = word[ind];
    }

    return false;
}

//TODO: This funcion should return a list of anagrams. The list may be empty. 
// The function invoking this function can then render the anagrams arbitrarily.
void anagram_solver_solve(hash_table_t* hash_table, char* control_word)
{
    unsigned hash = hash_table_hash(control_word);

    if (hash <= hash_table->size)
    {
        hash_node_t* hash_node = hash_table->table + hash;

        //Make a copy of the argument
        int control_word_len = strlen(control_word);
        char* sorted_control_word = strdup(control_word);

        //Set all chars to lowercase and sort the word
        for (int i = 0; i < control_word_len; i++)
        {
            sorted_control_word[i] = tolower(sorted_control_word[i]);
        }
        qsort(sorted_control_word, control_word_len, sizeof(char), cmpfunc);

        //Search the linked list corresponding to the current hash for anagrams
        linked_list_node_t* curr = hash_node->head;
        while (curr != NULL)
        {
            //If the length of the word in the linked list doesn't match the length of the control word, immediately move to the next node.
            if (curr->len != control_word_len)
                goto next;

            //Create a copy of the word in the linked list so that it doesn't get destroyed by sorting inside are_anagrams.
            char* ll_word = strdup(curr->word);

            if (are_anagrams(sorted_control_word, ll_word))
            {
                printf("\t%s\n", curr->word);
            }

            next:
                curr = curr->next;
        }

        free(sorted_control_word);
    }
}

// Determine if word is an anagram of sorted_control_word. 
bool_t are_anagrams(char* sorted_control_word, char* word)
{
    //Set all chars to lowercase and sort the word
    int word_len = strlen(word);
    for (int i = 0; i < word_len; i++)
    {
        word[i] = tolower(word[i]);
    }
    qsort(word, word_len, sizeof(char), cmpfunc);

    return strcmp(sorted_control_word, word) == 0;
}

