#include <stdio.h>

int main()
{
    char game_board[3][3] = {
        {'X', ' ','O'},
        {'O', 'X',' '},
        {'O', ' ','X'},
    };

    printf("Элемент в центре: %c\n", game_board[1][1]);

    printf("Доска крестики-нолики\n");

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            printf("%c ", game_board[row][col]);
        }
        printf("\n")
    }
}