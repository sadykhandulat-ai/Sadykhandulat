#include <stdio.h>

void inner_function(int sum) 
{
    printf("внутреняя функция: получила значение %i\n", sum);
    int result = sum * 2;
    printf("внутреняя функция: удвоила и воспроизвела %i\n", result);
}

void outer_function(int a, int b) 
{
    printf("внешняя функция: получила значение %i и %i\n", a, b);
    int sum = a + b;
    printf("внешняя функция: завершилась\n");
}

int main()
{
    printf("основная программа началась\n");
    outer_function(8, 2);
    printf("основная программа завершилась\n");
}