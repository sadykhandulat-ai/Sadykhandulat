#include <stdio.h>

int main()
{
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        printf("не удалось найти файл");
        return 1;
    }
    fprintf(file, "===логирование программы===\n");
    fprintf(file, "Строка 1: Создали и открыли файл\n");
    fprintf(file, "Строка 2: Записали данные успешно\n");

    fclose(file);
    printf("Данные успешно записаны в log.txt\n");

    file = fopen("log.txt", "r");
    char line[256];

    while(fgets(line, sizeof(line), file) !=NULL) {
        printf("%S", line);
    }

    fclose(file);
}