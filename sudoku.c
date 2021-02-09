#include <stdlib.h>
#include <stdio.h>

#define FALSE (1 == 0)
#define TRUE (1 == 1)

int puzzle[9][9];

int solvePuzzle();
int backtrack(int r, int c);
void printboard();

int main()
{
    // assume given grid of 9x9 we need to first solve it

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

    if (backtrack(0, 0))
    {
        printboard();
    }
    else
    {
        printf("No solution found\n");
    }

    return 0;
}

// Using backtrack algo to solve puzzle, 1 means puzzle is solved
int solvePuzzle()
{
    int row, col, subRow, subCol, value, r, c;

    for (row = 0; row < 9; row++)
    { // int array of all values being in row being assigned
        int contains[9];
        for (value = 0; value < 9; value++)
        {
            contains[value] = FALSE;
        }

        for (col = 0; col < 9; col++)
        {
            if (puzzle[row][col] != 0)
            { // check if value is already in the row, and if so, return false
                if (contains[puzzle[row][col] - 1])
                    return FALSE;
            } // else, add the value to the int array
            contains[puzzle[row][col] - 1] = TRUE;
        }
    }

    for (col = 0; col < 9; col++)
    {
        int contains[9];
        for (value = 0; value < 9; value++)
        { // int array of all values being in col being assigned
            contains[value] = FALSE;
        }

        for (row = 0; row < 9; row++)
        {
            if (puzzle[row][col] != 0)
            { // check if value is in col
                if (contains[puzzle[row][col] - 1] == 1)
                    return FALSE;
            } // assign value
            contains[puzzle[row][col] - 1] = TRUE;
        }
    }
    // add by 3 because of the grids of 9
    for (subRow = 0; subRow < 9; subRow += 3)
    {
        for (subCol = 0; subCol < 9; subCol += 3)
        { // same idea, array of nums 1-9 with 1 for existence
            int contains[9];
            for (value = 0; value < 9; value++)
            {
                contains[value] = FALSE;
            }

            for (row = 0; row < 3; row++)
            { // this is checking the grid
                for (col = 0; col < 3; col++)
                { // this is utilizing outer for loops
                    r = row + subRow;
                    c = col + subCol;

                    if (puzzle[r][c] != 0)
                    { // filled in values have been skipped, so this is only checking values that have been assigned
                        if (contains[puzzle[r][c] - 1])
                            return 0;
                        contains[puzzle[r][c] - 1] = TRUE;
                    }
                }
            }
        }
    }

    return TRUE;
}

int backtrack(int r, int c)
{
    // check if valid puzzle
    if (!solvePuzzle())
    {
        return FALSE;
    }
    // reached end of col, loop to next row
    if (c == 9)
    {
        return backtrack(r + 1, 0);
    }
    // if at end of rows, must be at the end of the puzzle
    if (r == 9)
    {
        return TRUE;
    }
    // skipping over filled in values
    if (puzzle[r][c] != 0)
    {
        return backtrack(r, c + 1);
    }
    // trying to use all possible values
    int attempt;
    for (attempt = 1; attempt <= 9; attempt++)
    {
        puzzle[r][c] = attempt;
        // move onto next square and see if this attempt is legit
        // as soon as a fail is hit, need to revert back
        // this is where the call stack goes insane, it's going to attempt to fill
        // all of the empties until it fails or hits end of puzzle
        if (backtrack(r, c + 1) == 1)
        {
            return TRUE;
        }
        // set value back because it did not work
        puzzle[r][c] = 0;
    }
    return FALSE;
}

void printboard()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
}