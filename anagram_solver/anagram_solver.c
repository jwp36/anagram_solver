// anagram_solver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef int bool_t;
#define true 1
#define false 0

#define max_word_len 25


// Determines if a word has any unsupported characters.
// Supported characters exist between decimal 32 and 126 with the exception of the apostrophe, which is decimal 39. 
// Assumes that each word ends with a newline
bool_t has_unsupported_chars(char* word)
{
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

void build_hashtable(char* input_file_name)
{
    FILE* input_file;
   
    errno_t fopen_err;
    fopen_err = fopen_s(&input_file, input_file_name, "r");

    if (fopen_err != 0)
    {
        fprintf(stderr, "Can't open input file: %s\n", input_file_name);
        //return NULL;
    }
    
    char word[max_word_len + 1];
    while (fgets(word, max_word_len, input_file))
    {
        if (is_supported(word))
        {
            printf("%s", word);
            //Add word to hashtable here 
        }
    }

    fclose(input_file);

    //Return hash
}

int _tmain(int argc, _TCHAR* argv[])
{
    // Allow memory-leak checks to occur at each exit point in the program.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    char* input_file_name = "../data/words";
    
    build_hashtable(input_file_name);

    //prompt user for words and stuff
    return 0;
}

