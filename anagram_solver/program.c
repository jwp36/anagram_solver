#include "stdafx.h"

static const char INPUT_FILE_NAME[] = "../data/words";

static const char WELCOME_MSG[] = "Welcome to Anagram Solver!\nEnter \"exit()\" to quit at any time.";
static const char USER_PROMPT[] = "Enter an anagram to solve: ";

static const char INVALID_INPUT[] = "Invalid anagram: The anagram must only contain letters.";

static const char ERROR_HASH_TABLE_CREATE_FAILED[] = "ERROR: Failed to create hash table. Aborting. Press any key to exit. . . ";

static const char EXIT_KEYWORD[] = "exit()\n";

int _tmain(int argc, _TCHAR* argv[])
{
    //Allow memory-leak checks to occur at each exit point in the program.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //Disable Control-C handling
    SetConsoleCtrlHandler(NULL, true);
    
    hash_table_t* hash_table;
    errno_t error;

    //Create the hash table
    error = anagram_solver_create(&hash_table, INPUT_FILE_NAME);
    if (error != 0)
    {
        fprintf(stderr, "%s", ERROR_HASH_TABLE_CREATE_FAILED);
        getchar();
        exit(-1);
    }

    printf("%s\n\n", WELCOME_MSG);

    //Start the primary REPL 
    char word_buffer[WORD_BUFFER_SIZE];
    while (true)
    {
        printf("%s", USER_PROMPT);
        
        fgets(word_buffer, WORD_BUFFER_SIZE, stdin);

        if (strcmp(word_buffer, EXIT_KEYWORD) == 0)
        {
            goto exit;
        }

        if (anagram_solver_word_is_supported(word_buffer))
        {
            //Strip the newline at the end of the word
            int word_len = strlen(word_buffer);
            word_buffer[word_len - 1] = '\0';

            anagram_solver_solve(hash_table, word_buffer);
        }
        else
        {
            printf("\t%s\n", INVALID_INPUT);
        }
    }

    exit:
        free_hash_table(hash_table);
        exit(0);

}

