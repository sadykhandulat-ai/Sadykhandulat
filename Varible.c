#include <stdio.h>

int global_mission = 10;

int main()
{
    int local_secret = 7;
    printf("В main global_mission: %i", global_mission);
    printf("В main local_secret: %i", local_secret);
    printf("В main function_secret: %i", function_secret);
}

void my_function()
{
    int function_secret = 5;
    printf("В main global_mission: %i", global_mission);
    printf("В main local_secret: %i", local_secret);
    printf("В main function_secret: %i", function_secret);
}