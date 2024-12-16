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
#define SIZE 30
#define SLOTS 100
#define POS 3
#define WORD_LEN 15

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
int checkAdjacent(int row, int column, char solve[][GRID], int n);
void printSolve(char solve [][GRID], int n);
int task5_crossword_generator(int slots[][POS], char type[], int slot, char words[][WORD_LEN], int usedWords[], int word, char solve[][SIZE], int slotNum, int wordsNum, int gridSize);
int placeWord(int slots[][POS], char type[], int i, char word[], int usedWords[], int j, char solve[][SIZE]);
int placeWordVertical(int length, char word[], char solve [][SIZE], int row, int column, int j);
int placeWordHorizontal(int length, char word[], char solve [][SIZE], int row, int column, int i);
void makeCopy(char new[][SIZE], char board[][SIZE], int n, int i);
void printCrossword(char board[][SIZE], int n);

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
                    isSolvable = task4_queens_battle(0, 0, invalidArea, 0, board, solve, n);
                    if(isSolvable)
                        printSolve(solve, n);
                    else
                        printf("The puzzle board is invalid.\n");
                    break;
                }
            case 5:
                {
                    int n = 0, slot = 0, wordCount = 0;
                    char grid [SIZE][SIZE], type[SLOTS], words[SLOTS][WORD_LEN];
                    int usedWords[SLOTS] = {0}, slots[SLOTS][POS];
                    printf("Please enter the dimensions of the crossword grid:\n");
                    scanf("%d", &n);
                    printf("Please enter the number of slots in the crossword:\n");
                    scanf("%d", &slot);
                    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                    for(int i = 0 ; i < slot ; i++)
                    {
                        for(int j = 0 ; j < POS ; j++)
                        {
                            scanf("%d", &slots[i][j]);
                        }
                        scanf(" %c", &type[i]);
                    }
                    for(int i = 0 ; i < n ; i++)
                        for(int j = 0 ; j < n ; j++)
                            grid[i][j] = '#';
                    for(int i = 0 ; i < slot ; i++)
                    {
                        if(type[i] == 'V')
                        {
                            int index = slots[i][1];
                            for(int j = slots[i][0] ; j < (slots[i][2] + slots[i][0]) ; j++)
                            {
                                grid[j][index] = ' ';
                            }
                        }
                        else if(type[i] == 'H')
                        {
                            int index = slots[i][0];
                            for(int j = slots[i][1] ; j < (slots[i][2] + slots[i][1]) ; j++)
                            {
                                grid[index][j] = ' ';
                            }
                        }
                    }
                    printf("Please enter the number of words in the dictionary:\n");
                    scanf("%d", &wordCount);
                    while(wordCount < slot)
                    {
                        scanf("%*[^\n]%*c");
                        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slot);
                        scanf("%d", &wordCount);
                    }
                    printf("Please enter the words for the dictionary:\n");
                    for(int i = 0 ; i < wordCount ; i++)
                    {
                        scanf("%s", words[i]);
                    }
                    int check = task5_crossword_generator(slots, type, 0, words, usedWords, 0, grid, slot, wordCount, n);
                    if(check)
                    {
                        printf("The crosswords are balanced correctly.\n");
                        printCrossword(grid, n);
                    }
                    else
                        printf("This crossword cannot be solved.\n");
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
    if(i == -1)
    {
        char current = 'x';
        int flag = scanf("%c", &current);
        if(flag == -1 || current == '\n')
        {
            return 0;
        }
        return task3_parenthesis_validator(c, i);
    }
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
        return task3_parenthesis_validator('x', -1) && 0;
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
            solve[row][column] = '*';
            if (areaAmount > 0)
            {
                invalidArea[--areaAmount] = ' ';
            }
            return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);
        }
        return 1;
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
    return checkColumn(i, j, 0, solve) && checkAdjacent(i, j, solve, n);
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

int checkAdjacent(int row, int column, char solve[][GRID], int n)
{
    if(row == 0)
    {
        return 1;
    }
    if(column == 0)
    {
        int upperRight = (solve[row-1][column+1] != 'X');
        int upperMid = (solve[row-1][column] != 'X');
        return upperRight && upperMid;
    }
    if(column == n)
    {
        int upperMid = (solve[row-1][column] != 'X');
        int upperLeft = (solve[row-1][column-1] != 'X');
        return upperMid && upperLeft;
    }
    int upperRight = (solve[row-1][column+1] != 'X');
    int upperMid = (solve[row-1][column] != 'X');
    int upperLeft = (solve[row-1][column-1] != 'X');
    return upperRight && upperMid && upperLeft;
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
            if(j != n - 1)
                printf(" ");
        }
        printf("\n");
    }
}
int task5_crossword_generator(int slots[][POS], char type[], int slot, char words[][WORD_LEN], int usedWords[], int word, char solve[][SIZE], int slotNum, int wordsNum, int gridSize)
{
    char temp[SIZE][SIZE];
    makeCopy(temp, solve, gridSize, 0);
    if (slot >= slotNum)
    {
        return 1;
    }
    if(word >= wordsNum)
    {
        return 0;
    }
    if(placeWord(slots, type, slot, words[word], usedWords, word, temp))
    {
        usedWords[word] = 1;
        int check = task5_crossword_generator(slots, type, slot + 1, words, usedWords, 0, temp, slotNum, wordsNum, gridSize);
        if(check == 0)
        {
            usedWords[word] = 0;
            return task5_crossword_generator(slots, type, slot, words, usedWords, word + 1, solve, slotNum, wordsNum, gridSize);
        }
        makeCopy(solve, temp, gridSize, 0);
        return 1;
    }
    return task5_crossword_generator(slots, type, slot, words, usedWords, word + 1, solve, slotNum, wordsNum, gridSize);


}
int placeWord(int slots[][POS], char type[], int i, char word[], int usedWords[], int j, char solve[][SIZE])
{
    int row = slots[i][0];
    int column = slots[i][1];
    int length1 = slots[i][2];
    int length2 = strlen(word);
    if(length2 != length1)
    {
        return 0;
    }
    if(usedWords[j] == 1)
    {
        return 0;
    }
    if(type[i] == 'V')
        return placeWordVertical(length1, word, solve, row, column, 0);
    if(type[i] == 'H')
        return placeWordHorizontal(length1, word, solve, row, column, 0);
    return 0;
}
int placeWordVertical(int length, char word[], char solve [][SIZE], int row, int column, int j)
{
    if(j >= length)
    {
        return 1;
    }
    if(solve[row][column] == word[j])
    {
        int check = placeWordVertical(length, word, solve, row + 1, column, j + 1);
        if(check == 0)
        {
            return 0;
        }
        return 1;
    }
    if(solve[row][column] == ' ')
    {
        solve[row][column] = word[j];
        int check = placeWordVertical(length, word, solve, row + 1, column, j + 1);
        if(check == 0)
        {
            solve[row][column] = ' ';
            return 0;
        }
        return 1;
    }
    return 0;
}
int placeWordHorizontal(int length, char word[], char solve [][SIZE], int row, int column, int i)
{
    if(i >= length)
    {
        return 1;
    }
    if(solve[row][column] == word[i])
    {
        int check = placeWordHorizontal(length, word, solve, row, column + 1, i + 1);
        if(check == 0)
        {
            return 0;
        }
        return 1;
    }
    if(solve[row][column] == ' ')
    {
        solve[row][column] = word[i];
        int check = placeWordHorizontal(length, word, solve, row, column + 1, i + 1);
        if(check == 0)
        {
            solve[row][column] = ' ';
            return 0;
        }
        return 1;
    }
    return 0;
}
void makeCopy(char new[][SIZE], char board[][SIZE], int n, int i)
{
    if(i < n)
    {
        strcpy(new[i], board[i]);
        makeCopy(new, board, n, i + 1);
    }
}
void printCrossword(char board[][SIZE], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("|");
        for(int j = 0; j < n; j++)
        {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    }
}