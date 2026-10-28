#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr1 = malloc (100 * sizeof(int));
    int *arr2 = calloc (100, sizeof(int));

    printf("malloc (может быть мусор): %d\n", *arr1);
    printf("calloc (гарантированна 0): %d\n", *arr2);

    free(arr1);
    free(arr2);
}