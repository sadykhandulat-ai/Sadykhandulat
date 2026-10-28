#include <stdio.h>

int main (int argc, char* argv[])
{ 
    printf ("argc: %i\n", argc);
    
    for (int i = 0; i < argc; i++)
    {
        printf ("argv[%i]: %s\n", i, argv[i]);
    }
}