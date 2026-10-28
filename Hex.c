#include <stdio.h>


int main()
{
    int decimal_number = 255;
    int hex_number = 0xFF;

    printf("десятичное: %d\n", decimal_number);
    printf("шестидесятичное: 0x%X\n", hex_number);

    printf("Они равны? %s\n", decimal_number == hex_number ? "Да" : "Нет");

    printf("адрес переменной Decimal_number в памяти: %p\n", &decimal_number);
}