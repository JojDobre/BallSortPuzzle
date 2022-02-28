#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ballsortpuzzle.h"

void generator(const int rows, const int columns, char field[rows][columns]){
    char znak[8] = {'@','*','^','+','-','$','#','%'};
    int pocet = (rows*columns)-(rows*2);
    char znaky [pocet];
    int i = 0;

    srand(time(NULL));
    int stlpec1 = rand() % columns;
    int stlpec2 = rand() % columns;

    while (stlpec1 == stlpec2){
        stlpec2 = rand() % columns;
    }
    for (int i = 0; i < rows; i++){
        field[i][stlpec1] = BLANK;
    }
    for (int i = 0; i < rows; i++){
        field[i][stlpec2] = BLANK;
    }

    for (int z = 0; z < columns-2; z++){
        for (int k = 0; k < rows; k++){
            znaky[i] = znak[z];
            i++;
        }
    }

    int cz = 0;

    //printf("%d ",pocet);
    //for (int k = 0; k <= pocet; k++){
    //    printf("%c ", znaky[k]);
    //}

    for (int k = 0; k < columns; k++){
        if (k != stlpec1 && k != stlpec2){
            for(int j = 0; j < rows; j++){
                cz = rand() % pocet;
                if (znaky[cz] != ' '){
                    field[j][k] = znaky[cz];
                    znaky[cz] = ' ';
                }
                else if (znaky[cz] == ' '){
                    while (znaky[cz] == ' '){
                        cz = rand() % pocet;
                    }
                    field[j][k] = znaky[cz];
                    znaky[cz] = ' ';
                }
            }
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y){
    int i = 0;
    char znak = BLANK;
    int oldznak;

    if (x == y){
        printf("\nChar is already in this column.\n");
        return;
    }

    //SKOPIROVANIE ZNAKU Z RIADKU X
    if (znak == BLANK) {
        if (field[0][x-1] != BLANK) {
            i = 14;
            oldznak = 0;
        }
        if (field[0][x-1] == BLANK) {
            for (int z = 0; z < rows; z++) {
                if (field[z][x-1] != BLANK) {
                    i = z;
                    oldznak = i;
                    break;
                }
            }
        }
    }

    if (i > 0 && i < 14){
        znak = field[i][x-1];
    }
    if (i == 14){
        znak = field[0][x-1];
    }
    if (i == 0){
        printf("\nColumn %d is empty!\n",x);
        return;
    }

    //PREKOPIROVANIE ZNAKU DO RIADKU Y
    if (znak != BLANK){
        if (field[0][y-1] != BLANK){
            printf("\nColumn %d is full.\n", y);
            return;
        }
        else if (field[rows-1][y-1] == BLANK){
            field[rows-1][y-1] = znak;
            field[oldznak][x-1] = BLANK;
            return;
        }
        else if (field[0][y-1] == BLANK){
            for (int z = 0; z < rows; z++){
                if (field[z][y-1] != BLANK){
                    if (znak == field[z][y-1]){
                        field[z-1][y-1] = znak;
                        field[oldznak][x-1] = BLANK;
                        return;
                    }
                    else if (znak != field[z][y-1]){
                        printf("\nError, chars are not the same!\n");
                        return;
                    }
                }
            }

        }
    }



}

bool check(const int rows, const int columns, char field[rows][columns]){
    int kontrola = 0;
    int j = 0;
    for (int i = 0; i < columns; i++){
        for (int k = 1; k <= rows; k++){
            if (field[k][i] == field[k-1][i]){
                kontrola++;
            }
        }
        if (kontrola == rows-1) {
            j++;
        }
        kontrola = 0;
    }
    if (j == columns){
        return true;
    }
    else {
        return false;
    }
}

void game_field(const int rows, const int columns, char field[rows][columns]) {
    printf("\n");
    //printf("   ");
    /*for (int x = 0; x < columns; x++) {
        printf("┎   ┒");
    }*/
    //printf("\n");
    for (int y = 0; y < rows; y++) {
        printf(" %d ", y + 1);
        for (int x = 0; x < columns; x++) {
            printf("┃ %c ┃", field[y][x]);
        }
        printf("\n");
    }
    printf("   ");
    for (int x = 0; x < columns; x++) {
        printf("┗━━━┛");
    }
    printf("\n");
    printf("   ");
    for (int x = 0; x < columns; x++) {
        printf("  %d  ", x + 1);
    }
    printf("\n");

    /*
    for (int y = 0; y < rows; y++) {
        printf(" %d ", y + 1);
        for (int x = 0; x < columns; x++) {
            printf("| %c |", field[y][x]);
        }
        printf("\n");
    }
    printf("   ");
    for (int x = 0; x < columns; x++) {
        printf(" --- ");
    }
    printf("\n");
    printf("   ");
    for (int x = 0; x < columns; x++) {
        printf("  %d  ", x + 1);
    }
    printf("\n");
    */

}

void ball_sort_puzzle(){

    srand(time(NULL));

    int rows = (rand() % 8) + 2;
    int columns = (rand() % 6) + 4;


    char field[rows][columns];
    generator(rows, columns, field);
    printf("Welcome to the game!\n");

    while (check(rows, columns, field) == false){
        game_field(rows, columns,field);
        int x = 0;
        int y = 0;
        printf("\nEnter what: ");
        scanf("%d", &x);
        while ( getchar() != '\n' )
            ;
        printf("Enter where: ");
        scanf("%d", &y);
        while ( getchar() != '\n' )
            ;
        down_possible(rows, columns, field, x, y);
    }
    game_field(rows, columns,field);
    printf("\n Congratulations! You won!\n");

}

