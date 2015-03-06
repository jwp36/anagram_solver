#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
    // Allow memory-leak checks to occur at each exit point in the program.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    char* input_file_name = "../data/words";

    hash_table_t* hash_table;
    errno_t error;



    //char* x = malloc(sizeof(char) * 4);
    //x[0] = 'c';
    //x[1] = 'a';
    //x[2] = 't';
    //x[3] = '\0';


    //
    //strcpy_s(y, strlen(x) + 1, x);
    //y[0] = 'b';
    //

    //printf("x is %s\n", x);
    //printf("y is %s\n", y);
    //printf("z is %s and is %d long", z, strlen(z));
    //getchar();

    //free(x);


    error = anagram_solver_create(&hash_table, input_file_name);
    if (error != 0)
    {
        getchar();
    }

    anagram_solver_solve(hash_table, "Cat");

    getchar();

    //prompt user for words and stuff
    return 0;
}
