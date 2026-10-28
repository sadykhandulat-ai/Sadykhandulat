#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("сколько чисел вы хотите ввести?:");
    scanf("%d",&n);

    int *dynamic_array = malloc(n * sizeof(int));

    if (dynamic_array == NULL) 
    {
        printf("Ошибка выделения памяти!");
        return 1;
    }

    printf("Память успешно выделена! введите числа: \n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &dynamic_array[i]);
    }

    printf("Вы ввели: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");

    free(dynamic_array);
    dynamic_array = NULL;
}