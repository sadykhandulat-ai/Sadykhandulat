#include <stdio.h>

void countdown(int n)
{
    if (n == 0)
    {
        printf("%d\n", n);
        return ;
    }
    
    printf("%d\n", n);
    countdown(n - 1);
}

int main()
{
    int number = 5;

    countdown(number);

    return 0;
}