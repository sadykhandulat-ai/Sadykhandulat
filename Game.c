#include <stdio.h>

int main()
{
    int secret_number = 5;
    int guess;

    printf("Я загадал число от 1 до 10.\n");

    printf("Твоя догадка: ");
    scanf("%d", &guess);

    while (guess != secret_number)
    {
        if (guess < secret_number)
        {
            printf("Мое число больше!\n");
        }
        else
        {
            printf("Мое число меньше!\n");
        }

        printf("Попробуй еще раз: ");
        scanf("%d", &guess);
    }

    printf("Поздравляю! Ты угадал!\n");

    return 0;
}