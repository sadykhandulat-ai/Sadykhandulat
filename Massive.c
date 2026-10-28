#include <stdio.h>

int main()
{
    int highscores [5];

    highscores[0] = 10000;
    highscores[1] = 9000;
    highscores[2] = 8000;
    highscores[3] = 7000;
    highscores[4] = 6000;

    printf("Лучший результат!: %d\n", highscores[0]);

    for (int i = 0; i < 5; i++)
    {
        printf("Результат #%i: %i\n", i + 1, highscores[i]);
    }
}