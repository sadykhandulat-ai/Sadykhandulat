#include <stdio.h>

int main()
{
    int treasure = 52;
    int *treasure_map;

    treasure_map = &treasure;

    printf ("само значение: %d\n", treasure);
    printf ("адрес значения: %p\n", treasure_map);

    printf ("А что если пройти по адресу? будет... %d\n", *treasure_map);
}