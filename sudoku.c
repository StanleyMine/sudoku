#include <stdlib.h>
#include <stdio.h>

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
    //printf("\n");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }

    return 1;
}