#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int height;
    printf("Укажите высоту: ");
    scanf("%d", &height);
    for (int i =1; i <= height; i++) 
    {
        for (int g =0; g < height - i; g++) 
        {
            printf(" ");
        }
        for (int g =0; g < i; g++) 
        {
            printf("!");
        }
        printf("\n");
    }
    return 0;
}
