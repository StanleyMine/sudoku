#include <stdlib.h>
#include <stdio.h>

int solvePuzzle(int puzzle[9][9]);
int isPuzzleEmpty(int puzzle[9][9]);
int isNumberRepeat(int puzzle[9][9], int num, int col, int row);
int checkBox(int puzzle[9][9], int row, int col, int num);

int main()
{
    // assume given grid of 9x9 we need to first solve it
    int puzzle[9][9];
    FILE *fp = fopen("EazyPuzzle.txt", "r");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int c = fgetc(fp);
            if (c == ' ' || c == '\n' || c == '\r')
            {
                j--;
                continue;
            }
            puzzle[i][j] = (c) - '0';
        }
    }
    fclose(fp);

    // reading in puzzle correctly from file, now to implement solving technique

    return 1;
}

// Using backtrack algo to solve puzzle
int solvePuzzle(int puzzle[9][9])
{
}

// Function to check if puzzle is empty, and returns 1 when puzzle has empty squares
int isPuzzleEmpty(int puzzle[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (puzzle[i][j] == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Function to check if number is valid, returns 1 if number is not valid
int isNumberRepeat(int puzzle[9][9], int num, int col, int row)
{
    for (int i = 0; i < 9; i++)
    { // checking row and col
        if (num == puzzle[row][i] || num == puzzle[i][col])
            return 1;
    }
    return 0;
}

// Checking 3x3 box for matching number, per sudoku rules
int checkBox(int puzzle[9][9], int row, int col, int num)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[row + i][col + j] == num)
                return 1;
        }
    }
    return 0;
}