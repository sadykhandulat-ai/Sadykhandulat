#include <stdio.h>

void greetUser(char name[])
{
    printf("Hello, %s! Welcome!\n", name);
}

int main()
{
    greetUser("Amir");
    greetUser("Zhenis");
    
    return 0;
}