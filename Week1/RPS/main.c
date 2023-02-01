#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int player, computer;
    srand(time(NULL));
    player = rand() % 3;
    computer = rand() % 3;
    printf("My choice:");
    switch (player)
    {
        case 0: printf("Rock\n"); break;
        case 1: printf("Scissors\n"); break;
        case 2: printf("Paper\n"); break;
    }
    printf("Computer choice：");
    switch (computer)
    {
        case 0: printf("Rock\n"); break;
        case 1: printf("Scissors\n"); break;
        case 2: printf("Paper\n"); break;
    }
    if (player == computer)
        printf("Result: Draw\n");
    else if (player == 0 && computer == 1 || player == 1 && computer == 2 || player == 2 && computer == 0)
        printf("Result: Win\n");
    else
        printf("Result: Lose\n");
    return 0;
}

