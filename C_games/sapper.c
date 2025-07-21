#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

int poleSize = 0;
int bombCount = 0;
int flagsCount = 0;

void** createPole(int, int);

void freePole(char**, int, int);

void printArray(char*, char*, int);

void printPole(char**, char**, int, int);

void inputPole(char**, char);

void addBombes(char**);

void countOfNeigbhourBombs(char**, int, int);

void inedexesOfBombesInPole(char**, int**);

void openPole(char**, char**, int, int, int, int, int, int);

void clearStdinBuffer(void);

int menu(void);

void aboutUs(void);

int chooseDifficult(void);

void inputIndex(int*, char*);

bool isValidIndex(char**, char**, int, int);

void openPoleOrPutFlag(int*);

bool putFlag(char**, char**, int, int);

void removeFlag(char**, char**, int**, int, int);

bool isLose(char**, int, int);

void showBombs(char**, char**);

bool isWin(char**, int, int);

void startGame(void);

void sapper(void);

int main(int argc, char *argv[])
{
    sapper();
    
    return 0;
}

void** createPole(int row, int col)
{
    char** res = (char**) malloc(sizeof(char**) * row);

    if (!res) {
        perror("Can not crete game pole!");
        exit(1);
    }

    for (int i = 0; i < row; ++i) {
        res[i] = (char*) malloc(sizeof(char*) * col);
        
        if (!res[i]) {
            for (int j = 0; j < i; ++j) {
                free(res[j]);
            }
            
            free(res);
            
            perror("Can not crete game pole!");
            exit(1);
        }
    }

    return (void**) res;
}

void freePole(char** pole, int row, int col)
{
    for (int i = 0; i < row; ++i) {
        free(pole[i]);
        pole[i] = NULL;
    }

    free(pole);
    pole = NULL;

    return;
}

void printArray(char* arr, char* maskArr, int size)
{
    static int count = 0;
    
    printf(count <= 10 ? "%d |" : "%d|", count++);
    for (int i = 0; i < size; ++i) {
        printf("%c ", maskArr[i] == 0 ? '#' : arr[i]);
    }
    printf("\n");

    if (count > poleSize - 1) count = 0;

    return;
}

void printPole(char** pole, char** maskPole, int row, int col)
{
    int count = 0;
    
    system("clear");

    printf("   %c ", count++ + 65);

    while (count < col) {
        printf("%c ", count++ + 65);
    }

    printf("\n");

    count = 0;

    printf("  ");

    while (count++ < col) {
        printf("--");
    }

    printf("\n");
    
    for (int i = 0; i < row; ++i) {
        printArray(pole[i], maskPole[i], col);
    }

    return;
}

void inputPole(char** pole, char sym)
{
    for (int i = 0; i < poleSize; ++i) {
        for (int j = 0; j < poleSize; ++j) {
            pole[i][j] = sym;
        }
    }

    return;
}

void addBombes(char** pole)
{
    int count = 0;
    int i = 0;
    int j = 0;

    system("clear");

    srand(time(NULL));
    
    while (count < bombCount) {

        i = rand() % poleSize;
        j = rand() % poleSize;

        if (pole[i][j] == '0') {
            pole[i][j] = '*';
            ++count;
        }
    }
    
    return;
}

void countOfNeigbhourBombs(char** pole, int rows, int columns)
{
    int row = 0;
    int col = 0;
    int tmp = 0;
    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            row = i;
            col = j;
            count = 0;

            if (pole[i][j] == 48) {
                if (row > 0) --row;
                if (col > 0) --col;

                while (i < rows - 1 ? row <= i + 1 : row < rows) {
                    tmp = col;
                    
                    while (j < columns - 1 ? tmp <= j + 1 : tmp < columns) {
                        if (pole[row][tmp] == '*') {
                            ++count;
                        } 

                        ++tmp;
                    }

                    ++row;
                }
            }

            if (pole[i][j] == 48) pole[i][j] = count + 48;
        }
    }

    return;
}

void inedexesOfBombesInPole(char** pole, int** indexes)
{
    int index = 0;
    
    for (int i = 0; i < poleSize; ++i) {
        for (int j = 0; j < poleSize; ++j) {
            if (pole[i][j] == '*') {
                indexes[index][0] = i;
                indexes[index++][1] = j;
            }
        }
    }

    return;
}

void openPole(char** pole, char** maskPole, int i, int j, int minRow, int maxRow, int minCol, int maxCol)
{
    if (maskPole[i][j] > 0 || pole[i][j] == '*') return;

    maskPole[i][j] = 1;

    // Up

    if (i - 1 >= minRow && i - 1 <= maxRow && pole[i - 1][j] != '*') {
        openPole(pole, maskPole, i - 1, j, minRow, maxRow, minCol, maxCol); }

    // Down
    
    if (i + 1 >= minRow && i + 1 <= maxRow && pole[i + 1][j] != '*') {
        openPole(pole, maskPole, i + 1, j, minRow, maxRow, minCol, maxCol);
    }

    // Left

    if (j - 1 >= minCol && j - 1 <= maxCol && pole[i][j - 1] != '*') {
        openPole(pole, maskPole, i, j - 1, minRow, maxRow, minCol, maxCol);
    }

    // Right

    if (j + 1 >= minCol && j + 1 <= maxCol && pole[i][j + 1] != '*') {
        openPole(pole, maskPole, i, j + 1, minRow, maxRow, minCol, maxCol);
    }

    // Up and Left

    if (i - 1 >= minRow && i - 1 <= maxRow && j - 1 >= minCol && j - 1 <= maxCol 
        && pole[i - 1][j - 1] != '*') {
        openPole(pole, maskPole, i - 1, j - 1, minRow, maxRow, minCol, maxCol);
    }

    // Up and Right

    if (i - 1 >= minRow && i - 1 < maxRow && j + 1 >= minCol && j + 1 <= maxCol 
        && pole[i - 1][j + 1] != '*') {
        openPole(pole, maskPole, i - 1, j + 1, minRow, maxRow, minCol, maxCol);
    }

    // Down and Left

    if (i + 1 >= minRow && i + 1 <= maxRow && j - 1 >= minCol && j - 1 <= maxCol 
        && pole[i + 1][j - 1] != '*') {
        openPole(pole, maskPole, i + 1, j - 1, minRow, maxRow, minCol, maxCol);
    }

    // Down and Right

    if (i + 1 >= minRow && i + 1 <= maxRow && j + 1 >= minCol && j + 1 <= maxCol 
        && pole[i + 1][j + 1] != '*') {
        openPole(pole, maskPole, i + 1, j + 1, minRow, maxRow, minCol, maxCol);
    }
}

void clearStdinBuffer(void)
{
    int clearBuffer = 0;

    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);

    return;
}

int menu(void)
{
    char choose[5];

    system("clear");
    
    printf("################################################\n");
    printf("|~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*|\n");
    printf("|~                                            ~|\n");
    printf("|~                  ~ MENU ~                  ~|\n");
    printf("|~                                            ~|\n");
    printf("|~              1 - Start Game                ~|\n");
    printf("|~                                            ~|\n");
    printf("|~              2 - About Us                  ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                                            ~|\n");
    printf("|~    Press 'Q' or 'q' for leave the game     ~|\n");
    printf("|~                                            ~|\n");
    printf("|~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*|\n");
    printf("################################################\n");

    printf("\nIf you want to start game press - 1\n");
    printf("If you want to read about us press - 2\n");
    printf("... ");

    scanf("%s", choose);
    
    if (choose[0] == 'q' || choose[0] == 'Q') {
        printf("You leave the game!\n");
        exit(0);
    }

    // Check is valid move in manu
    
    start:
    if (atoi(choose) <= 0|| atoi(choose) > 2) {
        printf("Invalid move please try again\n");
        clearStdinBuffer();
        scanf("%s", choose);

        if (choose[0] == 'q' || choose[0] == 'Q') {
            printf("You leave the game!\n");
            exit(0);
        }
        
        goto start;
    }

    return atoi(choose);
}

void aboutUs(void)
{
    char prev = 0;

    system("clear");
    
    printf("################################################\n");
    printf("|~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*|\n");
    printf("|~                                            ~|\n");
    printf("|~           The game was written             ~|\n");
    printf("|~            By Ashot Poghosyan              ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                25.04.2025                  ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                                            ~|\n");
    printf("|~    Press anywhere for previus page         ~|\n");
    printf("|~                                            ~|\n");
    printf("|~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*|\n");
    printf("################################################\n");

    clearStdinBuffer();

    scanf("%c", &prev);
    
    return;
}

int chooseDifficult(void)
{
    char chooseLvL[5];

    system("clear");
    
    printf("################################################\n");
    printf("|~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*|\n");
    printf("|~            Please choose difficult         ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                  1 - Easy                  ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                  2 - Medium                ~|\n");
    printf("|~                                            ~|\n");
    printf("|~                  3 - Hard                  ~|\n");
    printf("|~                                            ~|\n");
    printf("|~              Press 1 or 2 or 3             ~|\n");
    printf("|~           For previus page press 4         ~|\n");
    printf("|~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*|\n");
    printf("################################################\n");

    printf("... ");
    scanf("%s", chooseLvL);
    
    if (chooseLvL[0] == 'q' || chooseLvL[0] == 'Q') {
        printf("You leave the game!\n");
        exit(0);
    }


    // Check is valid move for difficult
    
    start:
    if (atoi(chooseLvL) <= 0 || atoi(chooseLvL) > 4) {
        printf("Invalid move please try again\n");
        clearStdinBuffer();
        scanf("%s", chooseLvL);

        if (chooseLvL[0] == 'q' || chooseLvL[0] == 'Q') {
            printf("You leave the game!\n");
            exit(0);
        }
        
        goto start;
    }

    clearStdinBuffer();

    return atoi(chooseLvL);
}

void inputIndex(int* i, char* j)
{
start:
    printf("\n\nPlease input the index for row: ");
    if (!scanf("%d", i)) {
        clearStdinBuffer();
        printf("Invalid move try again\n");
        goto start;
    }

    clearStdinBuffer();
    
    printf("Please input the index for column: ");
    scanf("%c", j);
    
    clearStdinBuffer();

    printf("\n");

    return;
}

bool isValidIndex(char** pole, char** maskPole, int i, int j)
{
    if (i < 0 || i > poleSize - 1 || j < 0 || j > poleSize - 1) return false;
    
    if (maskPole[i][j] > 0 && pole[i][j] != 'F') return false;

    return true;
}

void openPoleOrPutFlag(int* openOrFlag)
{
start:
    printf("Please press 0 for the open pole or press 1 for put the flag: ");
    if (!scanf("%d", openOrFlag)) {
        clearStdinBuffer();
        puts("Invalid move please try again");
        goto start;
    }

    clearStdinBuffer();
    
    if (*openOrFlag < 0 || *openOrFlag > 1) {
        printf("Invalid move please try again\n");
        goto start;
    }

    return;
}

bool putFlag(char** pole, char** maskPole, int i, int j)
{
    if (flagsCount) {
        pole[i][j] = 'F';
        maskPole[i][j] = 1;

        --flagsCount;
        return true;
    }

    return false;
}

void removeFlag(char** pole, char** maskPole, int** inedexesOfBombes, int i, int j)
{
    char ifRemove;
    
    printf("Remove flag?\n\n");
    printf("if yes press 'y'\n");
    printf("if no press 'n'\n");

start:
    scanf("%c", &ifRemove); 
    clearStdinBuffer();

    if (ifRemove != 'y' && ifRemove != 'Y'
        && ifRemove != 'n' && ifRemove != 'N') {
        printf("Invalid move please try again!\n");
        goto start;
    }

    if (ifRemove == 'n' || ifRemove == 'N') return;
    
    for (int k = 0; k < bombCount; ++k) {
        if (inedexesOfBombes[k][0] == i && inedexesOfBombes[k][1] == j) {
            pole[i][j] = '*';
            maskPole[i][j] = 0;
            ++flagsCount;
            return;
        }
    }

    pole[i][j] = '0'; 
    countOfNeigbhourBombs(pole, poleSize, poleSize);

    maskPole[i][j] = 0;
    ++flagsCount;

    return;
}

bool isLose(char** pole, int i, int j)
{
    if (pole[i][j] == '*') return true;

    return false;
}

void showBombs(char** pole, char** maskPole)
{
    for (int i = 0; i < poleSize; ++i) {
        for (int j = 0; j < poleSize; ++j) {
            if (pole[i][j] == '*') {
                maskPole[i][j] = 1;
            }
        }
    }

    return;
}

bool isWin(char** maskPole, int row, int col)
{
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (maskPole[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

void startGame(void)
{
    int lvl = chooseDifficult();
    int minRow = 0, maxRow = 0;
    int minCol = 0, maxCol = 0;
    int i = 0, j = 0;
    char scanJ = 0;
    int openOrFlag = 0;

    if (lvl == 4) return;

    switch (lvl) {
        case 1: 
            poleSize = 10;
            bombCount = 20;
            flagsCount = 20;
            break;

        case 2:
            poleSize = 15;
            bombCount = 30;
            flagsCount = 30;
            break;
        
        case 3:
            poleSize = 20;
            bombCount = 60;
            flagsCount = 60;
            break;
    }

    char** pole = (char**) createPole(poleSize, poleSize);
    char** maskPole = (char**) createPole(poleSize, poleSize);
    int** inedexesOfBombes = (int**) createPole(sizeof(int*) * bombCount, sizeof(int) * 2);

    inputPole(pole, '0');
    inputPole(maskPole, 0);    
    
    addBombes(pole);
    countOfNeigbhourBombs(pole, poleSize, poleSize);

    inedexesOfBombesInPole(pole, inedexesOfBombes);
    
    printPole(pole, maskPole, poleSize, poleSize);
    printf("\nThe flags count => %d", flagsCount);

    while (true) {
        j = -1;
        
        inputIndex(&i, &scanJ);
        
        printPole(pole, maskPole, poleSize, poleSize);
        printf("\nThe flags count => %d", flagsCount);

        if (scanJ >= 65 && scanJ <= 90) j = scanJ - 65;

        if (scanJ >= 97 && scanJ <= 122) j = scanJ - 97;

        printf("\ni - %d\n", i);
        printf("j - %d\n", j);

        if (pole[i][j] == 'F') {
            removeFlag(pole, maskPole, inedexesOfBombes, i, j);
            printPole(pole, maskPole, poleSize, poleSize);
            printf("\nThe flags count => %d", flagsCount);
            continue;
        }

        if (!isValidIndex(pole, maskPole, i, j)) {
            printf("Invalid move please try again\n");
            continue;
        }

        openPoleOrPutFlag(&openOrFlag);

        if (openOrFlag == 0) {
            
            if (isLose(pole, i, j)) {
                puts("You Lose");
                puts("Thank you for the game!");

                showBombs(pole, maskPole);
                printPole(pole, maskPole, poleSize, poleSize);
                
                freePole(pole, poleSize, poleSize);
                freePole(maskPole, poleSize, poleSize);

                sleep(3);
                
                return;
            }

            minRow = i > 1 ? i - 2 : i;
            maxRow = i < poleSize - 2 ? i + 2 : i;
            minCol = j > 1 ? j - 2 : j;
            maxCol = j < poleSize - 2 ? j + 2 : j;

            openPole(pole, maskPole, i, j, minRow, maxRow, minCol, maxCol);
            printPole(pole, maskPole, poleSize, poleSize);
            printf("\nThe flags count => %d", flagsCount);
        }

        if (openOrFlag == 1) {
            if (!putFlag(pole, maskPole, i, j)) {
                printf("Flags limit is sold out\n");
                continue;
            }
            
            printPole(pole, maskPole, poleSize, poleSize);
            printf("\nThe flags count => %d", flagsCount);
        }

        if (isWin(maskPole, poleSize, poleSize)) {
            puts("You WIN !!!");
            puts("Thank you for the game!");

            freePole(pole, poleSize, poleSize);
            freePole(maskPole, poleSize, poleSize);
            
            sleep(3);
            return;
        }
    }
    
    return;
}

void sapper(void)
{
    int stepChoose = 0;

    while (true) {
        stepChoose = menu();

        if (stepChoose == 1) {
            startGame();
        }

        if (stepChoose == 2) {
            aboutUs();
        }
    }

    return;
}
