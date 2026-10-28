#include <stdio.h>
#include <ctype.h>

char shift_letter(char letter, int key);

int main()
{
    char plain_letter = 'x';
    int secret_key = 1;
    char cipher_letter = shift_letter(plain_letter, secret_key);
    printf("Зашифрованная буква: %c\n", cipher_letter);
}

char shift_letter(char letter, int key)
{
    if (!isalpha(letter)) {
        return letter;
    }
    
    char base;
    if (isupper(letter)) 
    {
        base = 'A'; // 65
    } else
    {
        base = 'a'; // 97
    }

    return ((letter - base + key) % 26) + base;
}