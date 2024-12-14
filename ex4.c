/******************
Name: Roei Lev
ID: 216015164
Assignment: ex4
*******************/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLUMNS 5
#define GRID 20

char solve [GRID][GRID];

int task1_robot_paths(int row, int column);
float task2_human_pyramid(int row, int column, float humanPyramid[][COLUMNS], int rowNum);
int task3_parenthesis_validator(char c, int i);
int isOpenBracket(char c);
int isClosedBracket(char c);
char getOtherBracket(char c);
int task4_queens_battle(int row, int column, char invalidArea[], int areaAmount, char board [][GRID], char solve [][GRID], int n);
int placeQueen(int row, int column, char invalidArea [], int areaAmount, char area, char solve [][GRID], int n);
int isAreaValid(char invalidArea [], int areaAmount, int i, char area);
int canPlaceQueen(int i, int j, char solve [][GRID], int n);
int checkColumn(int row, int column, int i, char solve[][GRID]);
int checkDiagonals(int row, int column, int j, char solve[][GRID], int n);
void printSolve(char solve [][GRID], int n);
void task5_crossword_generator();

int solveQueen(int row, int column, int n, char board [][GRID], char solve [][GRID])
{
    if(row >= n)
        return 1;
    if(column >= n)
        return 0;
    int safe = placeQueen(row, column, NULL, 0, ' ', solve, n);
    if(safe)
    {
        solve[row][column] = 'X';

        if(solveQueen(row + 1, 0, n, board, solve))
            return 1;

        board[row][column] = '*';
    }
    else
    {
        if(solveQueen(row, column + 1, n, board, solve))
            return 1;
    }
    return 0;
}

void printBoard(char board[][GRID], int n)
{
    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0 ; j < n; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 1:
                {
                    int column, row, steps;
                    printf("Please enter the coordinates of the robot (column, row):\n");
                    scanf("%d %d", &column, &row);
                    steps = task1_robot_paths(row, column);
                    printf("The total number of paths the robot can take to reach home is: %d\n", steps);
                    break;
                }
            case 2:
                {
                    //{{72.31, 108.62, 171.24, 151.33, 93.32}, {53.43, 139.61, 134.06, 121.63}, {69.05, 133.66, 132.82}, {55.90, 131.25}, {51.18}};
                    float humanPyramid[ROWS][COLUMNS];
                    int isWeightValid = 1;
                    printf("Please enter the weights of the cheerleaders:\n");
                    for(int i = ROWS - 1; isWeightValid && i >= 0; i--)
                    {
                        for(int j = 0; j < COLUMNS - i; j++)
                        {
                            scanf("%f", &humanPyramid[i][j]);
                            if(humanPyramid[i][j] < 0)
                                isWeightValid = 0;
                        }
                    }
                    if(!isWeightValid)
                    {
                        printf("Negative weights are not supported.\n");
                        break;
                    }
                    for(int i = ROWS - 1; i >= 0; i--)
                    {
                        for(int j = 0; j < COLUMNS - i; j++)
                        {
                            scanf("%*[^\n]%*c");
                            float weight = task2_human_pyramid(i, j, humanPyramid, ROWS);
                            printf("%.2f", weight);
                            if(j < COLUMNS - i - 1)
                                printf(" ");
                        }
                        printf("\n");
                    }
                    break;
                }
            case 3:
                {
                    int check;
                    char temp;
                    printf("Please enter a term for validation:\n");
                    scanf(" %c", &temp);
                    check = task3_parenthesis_validator(temp, 0);
                    if(check == 1)
                        printf("The parentheses are balanced correctly.\n");
                    else
                        printf("The parentheses are not balanced correctly.\n");
                    break;
                }
            case 4:
                {
                    char invalidArea[GRID] = {0}, board[GRID][GRID], solve[GRID][GRID] = {{0}};
                    int n = 0, isSolvable = 0;
                    printf("Please enter the board dimensions:\n");
                    scanf("%d", &n);
                    printf("Please enter the %d*%d puzzle board\n", n, n);
                    for(int i = 0 ; i < n; i++)
                        for(int j = 0 ; j < n; j++)
                            scanf(" %c", &board[i][j]);
                    for(int i = 0 ; i < n; i++)
                        for(int j = 0 ; j < n; j++)
                            solve[i][j] = '*';
                    /*for(int i = 0 ; i < n; i++)
                    {
                        for(int j = 0 ; j < n; j++)
                            printf("%d: %c ", (i + j), solve[i][j]);
                        printf("\n");
                    }
                    for(int i = 0 ; i < n; i++)
                    {
                        isSolvable = canPlaceQueen(2, i, solve, n);
                        if(isSolvable)
                            printf("The puzzle board is valid.\n");
                        else
                            printf("The puzzle board is invalid.\n");
                    }*/
                    //isSolvable = task4_queens_battle(0, 0, invalidArea, 0, board, solve, n);
                    //printSolve(solve, n);
                    isSolvable = canPlaceQueen(2, 3, solve, n);
                    if(isSolvable)
                        printf("The puzzle board is valid.\n");
                    else
                        printf("The puzzle board is invalid.\n");
                    break;
                }
            case 5:
                {
                    int n = 0;
                    char grid [GRID][GRID];
                    printf("Please enter the dimensions of the crossword grid:\n");
                    scanf("%d", &n);
                    task5_crossword_generator();
                    break;
                }
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int task1_robot_paths(int row, int column)
{
    if (row == 0 && column == 0)
        return 1;
    if (row == -1 || column == -1)
        return 0;
    int down = task1_robot_paths(row - 1, column);
    int left = task1_robot_paths(row, column - 1);

    return down + left;
}

float task2_human_pyramid(int row, int column, float humanPyramid[][COLUMNS], int rowNum)
{
    if(row == rowNum)
        return humanPyramid[row][column];
    if(column == rowNum - row || column < 0)
        return 0;
    float weight1 = task2_human_pyramid(row + 1, column, humanPyramid, rowNum);
    float weight2 = task2_human_pyramid(row + 1, column - 1, humanPyramid, rowNum);

    return weight1/2 + weight2/2 + humanPyramid[row][column];
}
int task3_parenthesis_validator(char c, int i)
{
    if(i == 0)
    {
        if(isOpenBracket(c))
        {
            c = getOtherBracket(c);
        }
        else if(isClosedBracket(c))
        {
            c = getOtherBracket(c);
        }
    }
    char current = 'x';
    int flag = scanf("%c", &current);
    if(flag == -1 || current == '\n')
    {
        if(isClosedBracket(c))
            return 0;
        return 1;
    }
    if(current == c)
    {
        if(i == 0)
        {
            flag = scanf("%c", &current);
            if(isClosedBracket(current))
                current = getOtherBracket(current);
            if(flag == -1 || current == '\n')
                return 1;
            return task3_parenthesis_validator(current, 0);
        }
        return 1;
    }
    if(isClosedBracket(current))
    {
        return task3_parenthesis_validator(c, i + 1) && 0;
    }
    if(isOpenBracket(current))
    {
        char temp = getOtherBracket(current);
        int check = task3_parenthesis_validator(temp, i + 1);
        return check && task3_parenthesis_validator(c, i + 1);
    }
    return task3_parenthesis_validator(c, i + 1);
}
int isOpenBracket(char c)
{
    if(c == '(' || c == '{' || c == '[' || c == '<')
        return 1;
    return 0;
}
int isClosedBracket(char c)
{
    if(c == ')' || c == '}' || c == ']' || c == '>')
        return 1;
    return 0;
}
char getOtherBracket(char c)
{
    if(c == '(')
        return ')';
    if(c == '[')
        return ']';
    if(c == '{')
        return '}';
    if(c == '<')
        return '>';
    if(c == ')')
        return '(';
    if(c == ']')
        return '[';
    if(c == '}')
        return '{';
    if(c == '>')
        return '<';
    return 0;
}
/*
int task4_queens_battle(int row, int column, char invalidArea[], int areaAmount, char board [][GRID], char solve [][GRID], int n)
{
    if(column == n)
    {
        return 0;
    }
    if(row == n)
    {
        if(areaAmount == n)
            return 1;
        return 0;
    }
    char area = board[row][column];
    int queen = placeQueen(row, column, invalidArea, areaAmount, area, board, solve, n);
    if(queen)
    {
        printBoard(solve, n);
        if(areaAmount < n)
        {
            //invalidArea[areaAmount++] = area;
            areaAmount++;
        }
        column = 0;
        int check = task4_queens_battle(row + 1, column, invalidArea, areaAmount, board, solve, n);
        if(check)
            return 1;
        solve[row][column] = '*';
        //areaAmount--;
        return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);;
    }
    return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);
}*/
int task4_queens_battle(int row, int column, char invalidArea[], int areaAmount, char board [][GRID], char solve [][GRID], int n)
{
    if(column >= n)
    {
        return 0;
    }
    if(row >= n)
    {
        return 1;
    }
    char area = board[row][column];
    if(placeQueen(row, column, invalidArea, areaAmount, area, solve, n))
    {
        solve[row][column] = 'X';
        if(areaAmount < n)
        {
            invalidArea[areaAmount] = area;
            areaAmount++;
        }
        int check = task4_queens_battle(row + 1, 0, invalidArea, areaAmount, board, solve, n);
        if(check == 0)
        {
            areaAmount--;
            invalidArea[areaAmount] = ' ';
            solve[row][column] = '*';
            return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);
        }
        return check;
    }
    return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);
}
int placeQueen(int row, int column, char invalidArea [], int areaAmount, char area, char solve [][GRID], int n)
{
    if (canPlaceQueen(row, column, solve, n) && isAreaValid(invalidArea, areaAmount, 0, area))
    {
        return 1;
    }
    return 0;
}
int isAreaValid(char invalidArea [], int areaAmount, int i, char area)
{
    if(i >= areaAmount)
        return 1;
    if(invalidArea[i] == area)
        return 0;
    return isAreaValid(invalidArea, areaAmount, i + 1, area);
}
int canPlaceQueen(int i, int j, char solve [][GRID], int n)
{
    //return checkColumn(i, j, 0, solve) && checkDiagonals(i, j, j, solve, n);
    return checkDiagonals(i, j, j, solve, n);
}
int checkColumn(int row, int column, int i, char solve[][GRID])
{
    if (i == row)
    {
        return 1;
    }
    if (solve[i][column] == 'X') {
        return 0;
    }
    return checkColumn(row, column, i + 1, solve);
}

int checkDiagonals(int row, int column, int j, char solve[][GRID], int n)
{
    if (row < 0 || j >= n || j < 0)
    {
        return 1;
    }
    if (solve[row][j] == 'X')
    {
        return 0;
    }
    if (j == column)
    {
        return checkDiagonals(row - 1, column, j + 1, solve, n) && checkDiagonals(row - 1, column, j - 1, solve, n);
    }
    if (j > column)
    {
        return checkDiagonals(row - 1, column, j + 1, solve, n);
    }
    return checkDiagonals(row - 1, column, j - 1, solve, n);
}
void printSolve(char solve [][GRID], int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(solve[i][j] == 'X')
                printf("X");
            else
                printf("*");
            if(j == n - 1)
                printf(" ");
        }
        printf("\n");
    }
}
void task5_crossword_generator()
{
    // Todo
}