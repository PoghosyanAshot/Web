#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3
#define WIN 3

int pc = 0;
int player = 0;
char choise[SIZE] = {'R', 'P', 'S'};

void message(void);

bool isValid(char);

void printChoise(char, int);

void getPoint(char, int);

bool isWin(void);

void printScore(void);

void game(void);

int main(int argc, char *argv[])
{
    game();
    
    return 0;
}

void message(void)
{
    printf("\nR = Rock\nP = Paper\nS = Scissors\n\n");
    printf("Please choose R or P or S\n\n");
    printf("If you want leave the game press 'q' or 'Q'\n\n");

    return;
}

bool isValid(char choise)
{
    if (choise == 'R' || choise == 'P' || choise == 'S') {
        return true;
    }

    return false;
}

void printChoise(char mychoise, int randNum)
{
    // Player chose
    
    if (mychoise == choise[0]) {
        printf("\nThe player chose Rock\n");
    }

    if (mychoise == choise[1]) {
        printf("\nThe player chose Paper\n");
    }

    if (mychoise == choise[2]) {
        printf("\nThe player chose Scissors\n");
    }
    
    // PC chose

    if (randNum == 0) {
        printf("The PC chose Rock\n\n");
    }

    if (randNum == 1) {
        printf("The PC chose Paper\n\n");
    }

    if (randNum == 2) {
        printf("THe PC chose Scissors\n\n");
    }

    return;
}

void getPoint(char mychoise, int randNum)
{
    if ((mychoise == choise[0] && randNum == 0)
        || (mychoise == choise[1] && randNum == 1)
        || (mychoise == choise[2] && randNum == 2)) {
        printf("The raund is draw\n\n");
        return;
    }

    // Rock

    if (mychoise == choise[0] && randNum == 1) {
        printf("The PC win this raund!\n\n"); 
        ++pc;
        return;
    }

    if (mychoise == choise[0] && randNum == 2) {
        printf("The Player win this raund!\n\n");
        ++player;
        return;
    }

    // Paper

    if (mychoise == choise[1] && randNum == 0) {
        printf("The Player win this raund!\n\n");
        ++player;
        return;
    }

    if (mychoise == choise[1] && randNum == 2) {
        printf("The PC win this raund!\n\n");
        ++pc;
        return;
    }

    // scissors

    if (mychoise == choise[2] && randNum == 0) {
        printf("The PC win this raund!\n\n");
        ++pc;
        return;
    }

    if (mychoise == choise[2] && randNum == 1) {
        printf("The Player win this raund!\n\n");
        ++player;
        return;
    }
}

bool isWin(void)
{
    if (player == WIN) {
        printf("The Player WIN!!!\n"); 
        return true;
    }

    if (pc == WIN) {
        printf("The PC WIN!!!\n");
        return true;
    }

    return false;
}

void printScore(void)
{
    printf("The game will continue until 3 points:\n");
    printf("[The player = %d]\n", player);
    printf("[The PC = %d]\n", pc);

    return;
}

void game(void)
{
    char mychoise = 0;
    int randNum = 0;

    printf("Welcome to our game!\n");

    while (true) {
        srand(time(NULL));    
        randNum = rand() % 3;

        message();

        scanf("%c", &mychoise);
        getchar();

        if (mychoise == 'q' || mychoise == 'Q') {
            printf("You leave the game!\n");
            break;
        }

        if (!isValid(mychoise)) {
            system("clear");
            printf("\nInvalid move please try again!\n");
            continue;
        }

        system("clear");

        printChoise(mychoise, randNum);

        getPoint(mychoise, randNum);

        printScore();

        if (isWin()) {
            break;
        }

    }

    return;
}
