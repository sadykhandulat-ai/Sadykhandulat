#include <stdio.h>

#define hellomacro10raz 10
const int hellomacro5raz = 5;

int main(void)
{
    for (int i = 0; i < hellomacro10raz; i++)
    {
        printf("HELLO\n");
    }

    for (int i = 0; i < hellomacro5raz; i++)
    {
        printf("hello\n");
    }
}

enum OperationStatus
{
    Status_new,
    Status_processing,
    Status_shipped,
    Status_delivered,
    Status_cancelled
};