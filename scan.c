#include <stdio.h>

int main (int argc, char* argv[])
{ 
    if (argc == 2)
    {
        printf ("Привет!, %s!\n", argv [1]);
    }
    else
    {
        printf ("Привет незнакомец! попробуй: ./scan [имя]\n");
    }
}