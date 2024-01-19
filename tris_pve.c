#include "tris.h"

void    print_field(char arr[6][5])
{
    int flag = 1;
    printf("\t0   1   2\n\n");
    for (int i = 0; i < 6; i++)
    {
        if (flag)
        {
            printf("%d\t", i / 2);
            flag = 0;
        }
        else
        {
            printf(" \t");
            flag = 1;
        }
        for (int j = 0; j < 5; j++)
            printf("%c ", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}

int     valid_move(int x, int y)
{
    if (x < 3 && x >= 0 && y < 3 && y >=0)
        return (1);
    return (0);
}

void    fill_field(const char sign, char arr[6][5])
{
        int x = 0;
        int new_x;
        int y = 0;
        int valid = 0;
        while (valid == 0)
        {
            printf("%c insert your move as follow [X][Y]:", sign);
            printf("\n");
            scanf("%d%d", &x, &y);
            new_x = (x == 0)? 0: (x == 1)? 2: 4;
            if (!isalpha(arr[y * 2][new_x]) && valid_move(x, y))
            {
                arr[y * 2][new_x] = sign;
                valid = 1;
            }
            else
                printf("Move not allowed.\nTry again.\n");
        }
        print_field(arr);
}

void    clean_field(char arr[6][5], int *counter)
{
    arr[0][0] = ' ';
    arr[0][2] = ' '; 
    arr[0][4] = ' ';
    arr[2][0] = ' ';
    arr[2][2] = ' '; 
    arr[2][4] = ' '; 
    arr[4][0] = ' ';
    arr[4][2] = ' ';
    arr[4][4] = ' '; 
    *counter = 0;
    printf("Field cleaned.\n");
}

int    endgame(char field[6][5], int *counter, int score[2])
{
    char    play = '\0';

    printf("You've ran out of possible moves.\nWanna start a new game[y/n]\n");
    scanf(" %c", &play);
    if (play == 'y')
    {
        clean_field(field, counter);
        print_field(field);
        return (1);
    }
    else
    {
        printf("Final score:\nPlayer: %d\tBot: %d\n", score[0], score[1]);
        printf("See you next time!\n");
        exit (0);
    }
    return (0);
}

int    check_win(char field[6][5], int *counter, int score[2], int team)
{
    int win = 0;

    for (int i = 0; i < 5; i++)
    {
        if ((isalpha(field[i][0]) && (field[i][0] == field[i][2] && field[i][4] == field[i][0])))
        {
            printf("Victory of %c team.\n\n", field[i][0]);
            win = 1;
            break ;
        }
    }
    for (int i = 0; i < 5 && !win; i++)
    {
        if ((isalpha(field[0][i]) && (field[0][i] == field[2][i] && field[4][i] == field[0][i])))
        {
            printf("Victory of %c team.\n\n", field[0][i]);
            win = 1;
            break ;
        }
    }
    if (!win && isalpha(field[2][2]) && ((field[0][0] == field[2][2] && field[0][0] == field[4][4])
        || (field[0][4] == field[2][2] && field[0][4] == field[4][0])))
    {
        win = 1;
    }
    if (win == 1)
    {
        score[team]++;
        return (endgame(field, counter, score));
    }
    return (0);
}

int main()
{
    int     counter = 0;
    char    player = 'X';
    char    bot = 'O';
    int     score[2] = {0};
    char    field[6][5] = {' ', '|', ' ', '|', ' ',
                           '_', '|', '_', '|', '_',
                           ' ', '|', ' ', '|', ' ',
                           '_', '|', '_', '|', '_',
                           ' ', '|', ' ', '|', ' ',
                           ' ', '|', ' ', '|', ' '};
                    
    printf("Simple tic-tac-toe game versus a basic AI.");
    printf("Player starts first, every turn teams will be swapped.");
    printf("First turn player team is %c\nHave fun!\n", player);
    print_field(field);

    while (1)
    {
        fill_field(player, field);
        if (check_win(field, &counter, score, 0) == 1)
        {
            player = (player == 'X')? 'O': 'X';
            bot = (bot == 'X')? 'O': 'X';
            continue ;
        }
        counter++;
        printf("counter %d\n", counter);
        if (counter == 9)
        {
            if (endgame(field, &counter, score))
            {
                player = (player == 'X')? 'O': 'X';
                bot = (bot == 'X')? 'O': 'X';
                continue ;
            }
        }
        // bot
        best_move(field, bot, player, counter);
        print_field(field);
        if (check_win(field, &counter, score, 1) == 1)
        {
            player = (player == 'X')? 'O': 'X';
            bot = (bot == 'X')? 'O': 'X';
            continue ;
        }
        counter++;
    }
}