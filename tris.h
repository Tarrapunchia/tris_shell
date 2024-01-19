#ifndef TRIS_H
# define TRIS_H
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

void    print_field(char arr[6][5]);
int     valid_move(int x, int y);
void    fill_field(const char sign, char arr[6][5]);
void    clean_field(char arr[6][5], int *counter);
int     endgame(char field[6][5], int *counter, int score[2]);
int     check_win(char field[6][5], int *counter, int score[2], int team);


void    arr_cpy(char src[6][5], char dst[6][5]);
int     check_win_bot(char field[6][5], char team);
void    best_move(char field[6][5], char team, char enemy, int counter);


#endif