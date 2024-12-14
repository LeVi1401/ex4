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


int task1_robot_paths(int row, int column);
float task2_human_pyramid(int row, int column, float humanPyramid[][COLUMNS], int rowNum);
int task3_parenthesis_validator(char c, int i);
int isOpenBracket(char c);
int isClosedBracket(char c);
char getOtherBracket(char c);
void task4_queens_battle();
void task5_crossword_generator();

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
                task4_queens_battle();
                break;
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
            scanf(" %c", &current);
            if(isClosedBracket(current))
                current = getOtherBracket(current);
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
void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}