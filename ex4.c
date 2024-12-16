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
#define ROW 0
#define COLUMN 1
#define LENGTH 2

//part 1
int task1_robot_paths(int row, int column);
//part 2
float task2_human_pyramid(int row, int column, float humanPyramid[][COLUMNS], int rowNum);
//part 3
int task3_parenthesis_validator(char c, int i);
//checks if the char is ( / { / [ / < or not
int isOpenBracket(char c);
//checks if the char is ) / } / ] / < or not
int isClosedBracket(char c);
//returns the opposite bracket (,),{,},[,],<,>
char getOtherBracket(char c);
//part 4
int task4_queens_battle(int row, int column, char invalidArea[], int areaAmount, char board [][GRID], char solve [][GRID], int n);
//checks whether it can place a queen on the current spot in the array solve
int placeQueen(int row, int column, char invalidArea [], int areaAmount, char area, char solve [][GRID], int n);
//checks whether the current area was already used before or not (using invalidArea)
int isAreaValid(char invalidArea [], int areaAmount, int i, char area);
//checks whether the current place isn't adjacent to other queens or in the same column
int canPlaceQueen(int i, int j, char solve [][GRID], int n);
//checks whether there are any queens in the current column
int checkColumn(int row, int column, int i, char solve[][GRID]);
//checks whether there are any queens adjacent to the current place
int checkAdjacent(int row, int column, char solve[][GRID], int n);
//prints the solved queen board according to the instructions
void printSolve(char solve [][GRID], int n);
//part 5
int task5_crossword_generator(int slots[][POS], char type[], int slot, char words[][WORD_LEN], int usedWords[], int word, char solve[][SIZE], int slotNum, int wordsNum, int gridSize);
//places the word in the current spot if its legal and returns whether it succeeded or not
int placeWord(int slots[][POS], char type[], int i, char word[], int usedWords[], int j, char solve[][SIZE]);
//places a word vertically if it fits the board position and returns whether it succeeded or not
int placeWordVertical(int length, char word[], char solve [][SIZE], int row, int column, int j);
//places a word horizontally if it fits the board position and returns whether it succeeded or not
int placeWordHorizontal(int length, char word[], char solve [][SIZE], int row, int column, int i);
//copies the array board to the array new
void makeCopy(char new[][SIZE], char board[][SIZE], int n, int i);
//prints the solved crossword board according to the instructions
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
                    //adds the cheerleaders weights from top to bottom
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
                    //prints the weights
                    for(int i = ROWS - 1; i >= 0; i--)
                    {
                        for(int j = 0; j < COLUMNS - i; j++)
                        {
                            scanf("%*[^\n]%*c");
                            //gets the weight value of the current cheerleader
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
                    //gets first character
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
                    //gets the puzzle board
                    for(int i = 0 ; i < n; i++)
                        for(int j = 0 ; j < n; j++)
                            scanf(" %c", &board[i][j]);
                    //reset the solved board
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
                        //positions
                        for(int j = 0 ; j < POS ; j++)
                        {
                            scanf("%d", &slots[i][j]);
                        }
                        //vertical or horizontal
                        scanf(" %c", &type[i]);
                    }
                    for(int i = 0 ; i < n ; i++)
                        for(int j = 0 ; j < n ; j++)
                            grid[i][j] = '#';
                    //sets up the board
                    for(int i = 0 ; i < slot ; i++)
                    {
                        if(type[i] == 'V')
                        {
                            int index = slots[i][COLUMN];
                            for(int j = slots[i][ROW] ; j < (slots[i][LENGTH] + slots[i][ROW]) ; j++)
                            {
                                grid[j][index] = ' ';
                            }
                        }
                        else if(type[i] == 'H')
                        {
                            int index = slots[i][ROW];
                            for(int j = slots[i][COLUMN] ; j < (slots[i][LENGTH  ] + slots[i][COLUMN]) ; j++)
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
//part 1
int task1_robot_paths(int row, int column)
{
    if (row == 0 && column == 0)
        return 1;
    if (row == -1 || column == -1)
        return 0;
    //goes down and left and sums the amount of different ways
    int down = task1_robot_paths(row - 1, column);
    int left = task1_robot_paths(row, column - 1);

    return down + left;
}
//part 2
float task2_human_pyramid(int row, int column, float humanPyramid[][COLUMNS], int rowNum)
{
    if(row == rowNum)
        return humanPyramid[row][column];
    if(column == rowNum - row || column < 0)
        return 0;
    //gets the weight of the 2 people above
    float weight1 = task2_human_pyramid(row + 1, column, humanPyramid, rowNum);
    float weight2 = task2_human_pyramid(row + 1, column - 1, humanPyramid, rowNum);
    //calculations
    return weight1/2 + weight2/2 + humanPyramid[row][column];
}
//part 3
int task3_parenthesis_validator(char c, int i)
{
    //whether the check already failed
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
    //gets one char from main so it changes it to not affect the function
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
    //gets one char from buffer
    char current = 'x';
    int flag = scanf("%c", &current);
    if(flag == -1 || current == '\n')
    {
        //checks whether there is an unclosed bracket
        if(isClosedBracket(c))
            return 0;
        return 1;
    }
    //checks whether current bracket is closed correctly
    if(current == c)
    {
        //continues the check in case of an open and close bracket at the beginning (example:"()d{ds}a")
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
    //checks whether the bracket is closed incorrectly (example:"(]")
    if(isClosedBracket(current))
    {
        return task3_parenthesis_validator('x', -1) && 0;
    }
    //checks whether there is another open bracket before the current one is closed (or it's the first one)
    if(isOpenBracket(current))
    {
        //calls for the function to check if the new bracket is closed correctly and then checks if the current one is
        char temp = getOtherBracket(current);
        int check = task3_parenthesis_validator(temp, i + 1);
        return check && task3_parenthesis_validator(c, i + 1);
    }
    return task3_parenthesis_validator(c, i + 1);
}
//checks if the char is ( / { / [ / < or not
int isOpenBracket(char c)
{
    if(c == '(' || c == '{' || c == '[' || c == '<')
        return 1;
    return 0;
}
//checks if the char is ) / } / ] / < or not
int isClosedBracket(char c)
{
    if(c == ')' || c == '}' || c == ']' || c == '>')
        return 1;
    return 0;
}
//returns the opposite bracket (,),{,},[,],<,>
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
//part 4
int task4_queens_battle(int row, int column, char invalidArea[], int areaAmount, char board [][GRID], char solve [][GRID], int n)
{
    //checks whether it couldn't place a queen on the current row
    if(column >= n)
    {
        return 0;
    }
    //checks whether it finished placing a queen on every row
    if(row >= n)
    {
        return 1;
    }
    //gets the current position's area
    char area = board[row][column];
    //checks whether it can place a queen in this position
    if(placeQueen(row, column, invalidArea, areaAmount, area, solve, n))
    {
        //places a queen and adds the current area to the used areas
        solve[row][column] = 'X';
        if(areaAmount < n)
        {
            invalidArea[areaAmount] = area;
            areaAmount++;
        }
        //checks if you can place a queen on the next row
        int check = task4_queens_battle(row + 1, 0, invalidArea, areaAmount, board, solve, n);
        //if the current queen location didn't lead to a solution
        if(check == 0)
        {
            //removes the current queen and the current area
            solve[row][column] = '*';
            if (areaAmount > 0)
            {
                invalidArea[--areaAmount] = ' ';
            }
            //checks the next column because the current one failed
            return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);
        }
        return 1;
    }
    //checks the next column because the current one failed
    return task4_queens_battle(row, column + 1, invalidArea, areaAmount, board, solve, n);
}
//checks whether it can place a queen on the current spot in the array solve
int placeQueen(int row, int column, char invalidArea [], int areaAmount, char area, char solve [][GRID], int n)
{
    if (canPlaceQueen(row, column, solve, n) && isAreaValid(invalidArea, areaAmount, 0, area))
    {
        return 1;
    }
    return 0;
}
//checks whether the current area was already used before or not (using invalidArea)
int isAreaValid(char invalidArea [], int areaAmount, int i, char area)
{
    if(i >= areaAmount)
        return 1;
    if(invalidArea[i] == area)
        return 0;
    return isAreaValid(invalidArea, areaAmount, i + 1, area);
}
//checks whether the current place isn't adjacent to other queens or in the same column
int canPlaceQueen(int i, int j, char solve [][GRID], int n)
{
    return checkColumn(i, j, 0, solve) && checkAdjacent(i, j, solve, n);
}
//checks whether there are any queens in the current column
int checkColumn(int row, int column, int i, char solve[][GRID])
{
    //checking only the rows above because of the way the main function works
    if (i == row)
    {
        return 1;
    }
    if (solve[i][column] == 'X') {
        return 0;
    }
    return checkColumn(row, column, i + 1, solve);
}
//checks whether there are any queens adjacent to the current place
int checkAdjacent(int row, int column, char solve[][GRID], int n)
{
    //checking only the 3 positions above because of the way the main function works
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
//prints the solved queen board according to the instructions
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
//part 5
int task5_crossword_generator(int slots[][POS], char type[], int slot, char words[][WORD_LEN], int usedWords[], int word, char solve[][SIZE], int slotNum, int wordsNum, int gridSize)
{
    //makes a copy to the current board position so if the check fails the words that didn't work would be deleted automatically
    char temp[SIZE][SIZE];
    makeCopy(temp, solve, gridSize, 0);
    //finished checking all the slots
    if (slot >= slotNum)
    {
        return 1;
    }
    //no word worked for the current slot
    if(word >= wordsNum)
    {
        return 0;
    }
    //checks whether it can place the current work in this slot
    if(placeWord(slots, type, slot, words[word], usedWords, word, temp))
    {
        //adds the current work to the used words
        usedWords[word] = 1;
        //checks if you can place a word in the next slot
        int check = task5_crossword_generator(slots, type, slot + 1, words, usedWords, 0, temp, slotNum, wordsNum, gridSize);
        //if the current word in the current slot didn't lead to a solution
        if(check == 0)
        {
            //removes the word and checks if the next word works
            usedWords[word] = 0;
            return task5_crossword_generator(slots, type, slot, words, usedWords, word + 1, solve, slotNum, wordsNum, gridSize);
        }
        //if the word lead to a solution then copy the solution board to the current one
        makeCopy(solve, temp, gridSize, 0);
        return 1;
    }
    //checks the next word because the current one failed
    return task5_crossword_generator(slots, type, slot, words, usedWords, word + 1, solve, slotNum, wordsNum, gridSize);
}
//places the word in the current spot if its legal and returns whether it succeeded or not
int placeWord(int slots[][POS], char type[], int i, char word[], int usedWords[], int j, char solve[][SIZE])
{
    int row = slots[i][ROW];
    int column = slots[i][COLUMN];
    int length1 = slots[i][LENGTH];
    int length2 = (int)(strlen(word));
    //checks if the word length fits the slot
    if(length2 != length1)
    {
        return 0;
    }
    //checks if the current word was already used
    if(usedWords[j] == 1)
    {
        return 0;
    }
    //checks in which direction to place the word
    if(type[i] == 'V')
        return placeWordVertical(length1, word, solve, row, column, 0);
    if(type[i] == 'H')
        return placeWordHorizontal(length1, word, solve, row, column, 0);
    return 0;
}
//places a word vertically if it fits the board position and returns whether it succeeded or not
int placeWordVertical(int length, char word[], char solve [][SIZE], int row, int column, int j)
{
    //checks whether it finished placing the word
    if(j >= length)
    {
        return 1;
    }
    //checks if the word fits the letters placed already onto this slot
    if(solve[row][column] == word[j])
    {
        //checking if the next character in the word fits
        int check = placeWordVertical(length, word, solve, row + 1, column, j + 1);
        if(check == 0)
        {
            return 0;
        }
        return 1;
    }
    //checks if the space is empty to place a letter
    if(solve[row][column] == ' ')
    {
        solve[row][column] = word[j];
        //checking if the next character in the word fits
        int check = placeWordVertical(length, word, solve, row + 1, column, j + 1);
        if(check == 0)
        {
            //if it put a letter in an empty space and in the end the word didn't work then remove the newly added letters
            solve[row][column] = ' ';
            return 0;
        }
        return 1;
    }
    //the word didn't fit
    return 0;
}
//places a word horizontally if it fits the board position and returns whether it succeeded or not
int placeWordHorizontal(int length, char word[], char solve [][SIZE], int row, int column, int i)
{
    //checks whether it finished placing the word
    if(i >= length)
    {
        return 1;
    }
    //checks if the word fits the letters placed already onto this slot
    if(solve[row][column] == word[i])
    {
        //checking if the next character in the word fits
        int check = placeWordHorizontal(length, word, solve, row, column + 1, i + 1);
        if(check == 0)
        {
            return 0;
        }
        return 1;
    }
    //checks if the space is empty to place a letter
    if(solve[row][column] == ' ')
    {
        solve[row][column] = word[i];
        //checking if the next character in the word fits
        int check = placeWordHorizontal(length, word, solve, row, column + 1, i + 1);
        if(check == 0)
        {
            //if it put a letter in an empty space and in the end the word didn't work then remove the newly added letters
            solve[row][column] = ' ';
            return 0;
        }
        return 1;
    }
    return 0;
}
//copies the array board to the array new
void makeCopy(char new[][SIZE], char board[][SIZE], int n, int i)
{
    if(i < n)
    {
        strcpy(new[i], board[i]);
        makeCopy(new, board, n, i + 1);
    }
}
//prints the solved crossword board according to the instructions
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