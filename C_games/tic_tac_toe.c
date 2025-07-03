#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define SIZE 3

const char Xplayer = 'X';
const char Oplayer = 'O';
char player = Xplayer;

char** create_board();

void free_board(char**);

void input_board(char**, char);

void print_board(char**);

void print_message(void);

void clear_stdin_buffer(void);

void input_index(int*);

bool is_valid_index(char**, int*);

void input_X_or_O_in_board(char**, int*);

bool is_win(char**);

bool is_draw(char**);

void tic_tac_toe(void);

int main(int argc, char *argv[])
{
    tic_tac_toe();
    
    return 0;
}

char** create_board()
{
    char** res = (char**) malloc(sizeof(char*) * SIZE);

    if (!res) {
        perror("");
        exit(errno);
    }

    for (int i = 0; i < SIZE; ++i) {
        res[i] = (char*) malloc(sizeof(char) * SIZE);

        if (!res[i]) {
            for (int j = 0; j < i; ++j) {
                free(res[j]);
            }
            exit(errno);
        }
    }

    return res;
}

void free_board(char** board)
{
    for (int i = 0; i < SIZE; ++i) {
        free(board[i]);
    }

    free(board);

    return;
}

void input_board(char** board, char symbol)
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = symbol;
        }
    }

    return;
}

void print_board(char** board)
{
    system("clear");
    
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);    
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);    
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);    

    return;
}

void print_message(void)
{ 
    printf("You are %c player\n", player);
    printf("Please input from 1 to 9: ");

    return;
}

void clear_stdin_buffer(void)
{
    char clear = 0;

    while ((clear = getchar()) != '\n' && clear != EOF);

    return;
}

void input_index(int* index)
{
    start:
    
    if (!scanf("%d", index)) {
        clear_stdin_buffer();
        printf("Invalid number please try again: ");
        goto start;
    }

    return;
}

bool is_valid_index(char** board, int* index) 
{
    if (*index < 0 || *index > 9) return false;

    // row 0
    if (board[0][0] != ' ' && *index == 1) return false;
    if (board[0][1] != ' ' && *index == 2) return false;
    if (board[0][2] != ' ' && *index == 3) return false;
    
    // row 1
    if (board[1][0] != ' ' && *index == 4) return false;
    if (board[1][1] != ' ' && *index == 5) return false;
    if (board[1][2] != ' ' && *index == 6) return false;
    
    // row 2
    if (board[2][0] != ' ' && *index == 7) return false;
    if (board[2][1] != ' ' && *index == 8) return false;
    if (board[2][2] != ' ' && *index == 9) return false;

    return true;
}

void input_X_or_O_in_board(char** board, int* index)
{
    switch (*index) {
        // row 0
        case 1: board[0][0] = player; break;
        case 2: board[0][1] = player; break;
        case 3: board[0][2] = player; break;

        // row 1
        case 4: board[1][0] = player; break;
        case 5: board[1][1] = player; break;
        case 6: board[1][2] = player; break;

        // row 2
        case 7: board[2][0] = player; break;
        case 8: board[2][1] = player; break;
        case 9: board[2][2] = player; break;
    }

    return;
}

bool is_win(char** board)
{
    // rows
    
    if (board[0][0] == player && board[0][1] == player && board[0][2] == player) return true;
    if (board[1][0] == player && board[1][1] == player && board[1][2] == player) return true;
    if (board[2][0] == player && board[2][1] == player && board[2][2] == player) return true;

    // columns

    if (board[0][0] == player && board[0][1] == player && board[0][2] == player) return true;
    if (board[1][0] == player && board[1][1] == player && board[1][2] == player) return true;
    if (board[2][0] == player && board[2][1] == player && board[2][2] == player) return true;

    // diaganal
    
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

bool is_draw(char** board)
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;
}

void tic_tac_toe(void)
{
    char** board = create_board();
    int index_board = 0;
    input_board(board, ' ');

    print_board(board);
    
    while (true) {
        print_message();
        input_index(&index_board);

        if (!is_valid_index(board, &index_board)) {
            printf("Invalid index please try again\n");
            continue;         
        }

        input_X_or_O_in_board(board, &index_board);
        print_board(board);

        if (is_win(board)) {
            printf("The player %c has Won!!!\n", player);
            break;
        }

        if (is_draw(board)) {
            printf("DRAW!!!\n");
            break;
        }

        player = player == Xplayer ? Oplayer : Xplayer;
    }

    free_board(board);
    board = NULL;

    return;
}
