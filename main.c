#include <stdio.h>

void askNumbers();
void divideNumbers();

int main(){
    printf("Hi! How old are you? ");
    int age;
    scanf("%d", &age);

    if (age == 15) {
        printf ("Wow! You're same age as me!\n");
    } else {
        printf("Well, you're not same age as me!\n");
    }

    askNumbers();

    return 0;
}

void askNumbers(){
    printf("Can you enter first number? ");
    int first;
    scanf("%d", &first);

    printf("Now second ");
    int second;
    scanf("%d", &second);

    printf("%d * %d will be %d\n", first, second, first * second);

    divideNumbers();
}

void divideNumbers(){
    int divide = 8;
    printf("How much is going to be if we divide 24 by 3\n");
    int answer;
    scanf ("%d", &answer);

    if (answer == divide) {
        printf("You guessed right!");
    } if (answer > divide) {
        printf("No, it's smaller. Answer is 8.");
    } if (answer < divide) {
        printf("No, it's bigger. Answer is 8.");
    }
}