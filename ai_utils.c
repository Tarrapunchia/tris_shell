#include "tris.h"

void    arr_cpy(char src[6][5], char dst[6][5])
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 5; j++)
            dst[i][j] = src[i][j];
}

int     check_win_bot(char field[6][5], char team) // returns 1/ -1/ 0 
{                                                 // dependign on a winning pos for team/enemy/tie
    int  ret = 0;

    for (int i = 0; i < 6; i++)
    {
        if ((isalpha(field[i][0]) && (field[i][0] == field[i][2] && field[i][4] == field[i][0])))
        {
            ret = (field[i][0] == team)? 1: -1;
            break ;
        }
    }
    for (int i = 0; i < 5 && ret == 0; i++)
    {
        if ((isalpha(field[0][i]) && (field[0][i] == field[2][i] && field[4][i] == field[0][i])))
        {
            ret = (field[0][i] == team)? 1: -1;
            break ;
        }
    }
    if (ret == 0 && isalpha(field[2][2]) && ((field[0][0] == field[2][2] && field[0][0] == field[4][4])
        || (field[0][4] == field[2][2] && field[0][4] == field[4][0])))
    {
        ret = (field[2][2] == team)? 1: -1;
    }
    return (ret);
}

void    best_move(char field[6][5], char team, char enemy, int counter)
{
    if (counter == 8) // last move remains, no need for complex logic, ofc
    {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (field[i][j] == ' ')
                    field[i][j] = team;
        return;
    }

    char    buf[6][5]; // i create a copy of the field on wich i'll test
    arr_cpy(field, buf);

    while (1)
    {
        for (int i = 0; i < 5; i++) // check if bot/enemy can win in 1 move
        {
            for (int j = 0; j < 5; j++)
            {
                if (buf[i][j] == ' ')
                {
                    buf[i][j] = team;
                    if (check_win_bot(buf, team) == 1)
                    {
                        field[i][j] = team;
                        return ;
                    }
                    buf[i][j] = enemy;
                    if (check_win_bot(buf, team) == -1)
                    {
                        field[i][j] = team;
                        return ;
                    }
                    buf[i][j] = ' ';
                }
            }
        }
        if (field[2][2] == ' ')
        {
            field[2][2] = team;
            return ;
        }
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (buf[i][j] == ' ')
                {
                    field[i][j] = team;
                    return ;
                }
    }
}
