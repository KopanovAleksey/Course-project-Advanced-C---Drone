#include "drone.h"

void updateField(char (*field)[WIDTH], drone_t drone[DRONECOUNT], pumpkin_t (*pumpkin)[WIDTH]){
    for(int i = HEIGHT - STORAGEHIGHT; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == HEIGHT - STORAGEHIGHT)
                field[i][j] = '-';
            else
                field[i][j] = ' ';
        }
    }

     for(int i = 0; i < HEIGHT-STORAGEHIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(pumpkin[i][j].isRipe == 1)
                field[pumpkin[i][j].y][pumpkin[i][j].x] = 'O';
            else if(pumpkin[i][j].isRipe == 0)
                field[pumpkin[i][j].y][pumpkin[i][j].x] = 'o';
            else
                field[pumpkin[i][j].y][pumpkin[i][j].x] = ' ';
        }
    }
    for(int j = 0; j < DRONECOUNT; j++){
        field[drone[j].y][drone[j].x] = '%';
        for (int i = 0; i < drone[j].currentCartSize; i++){
            field[drone[j].cart[i].y][drone[j].cart[i].x] = '@';
        }
    }
}

void printField(char (*field)[WIDTH]){
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0; i < WIDTH + 2; i++){
        printf("#");
    }
    printf("\n");
    for(int i = 0; i < HEIGHT; i++){
        printf("#");
        for (int j = 0; j < WIDTH; j++){
            
            if(field[i][j] == 'O')
                SetConsoleTextAttribute(hStdOut,YELLOW);
            if(field[i][j] == '%')
                SetConsoleTextAttribute(hStdOut,GREEN);
            if(field[i][j] == '@')
                SetConsoleTextAttribute(hStdOut,DARKGREEN);
            printf("%c",field[i][j]);
            SetConsoleTextAttribute(hStdOut,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }
        printf("#\n");
    }
    for(int i = 0; i < WIDTH + 2; i++){
        printf("#");
    }
}