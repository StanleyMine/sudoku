#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int puzzle[9][9];
int newPuzzle[9][9];

void randomShuffles();
void shuffleColumns(int rand_num);
void shuffleRows(int rand_num);
void printOutput();

int main(){
    FILE *fp = fopen("Puzzles/EazyPuzzle.txt", "r");
    
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
    randomShuffles();
    printOutput();
}

void randomShuffles(){
    time_t t;
    srand((unsigned) time(&t));
    int l = 0, r = 4;
    int rand_num = (rand() % (r - l + 1)) + l;
    int rand_num2 = (rand() % (r - l + 1)) + l;
    shuffleRows(rand_num);
    shuffleColumns(rand_num2);
}

void shuffleColumns(int rand_num){
    if(rand_num == 0)
        return;
    int temp[3];
    // shifting columns in a row
    if(rand_num % 2 == 0){
        for (int row = 0; row < 9; row++){
            // grab first 3
            for (int col = 0; col < 3; col++){ 
                temp[col] = puzzle[row][col];
            } 
            // shift row right by 6
            for (int i = 0; i < 9; i++){
                if(i > 5){ // use temp to place numbers from temp
                    newPuzzle[row][i] = temp[i - 6];
                    continue;
                }
                // copy array shifted left by 3
                newPuzzle[row][i] = puzzle[row][i + 3];
            }
        }
    }
    else {
        for (int row = 0; row < 9; row++){
            // grab last 3
            for (int col = 6; col < 9; col++){ 
                temp[col-6] = puzzle[row][col];
            } 
            // shift row left by 6
            for (int i = 0; i < 9; i++){
                if(i < 3){ // use temp to place numbers from temp
                    newPuzzle[row][i] = temp[i];
                    continue;
                }
                // copy array shifted right by 3
                newPuzzle[row][i] = puzzle[row][i-3];
            }
        }
    } 
}

void shuffleRows(int rand_num){
    if(rand_num == 0)
        return;
    int temp[3];
    // shifting columns in a row
    if(rand_num % 2 == 0){
        for (int col = 0; col < 9; col++){
            // grab first 3
            for (int row = 0; row < 3; row++){ 
                temp[row] = puzzle[row][col];
            } 
            // shift row right by 6
            for (int i = 0; i < 9; i++){
                if(i > 5){ // use temp to place numbers from temp
                    newPuzzle[i][col] = temp[i - 6];
                    continue;
                }
                // copy array shifted left by 3
                newPuzzle[i][col] = puzzle[i+3][col];
            }
        }
    }
    else {
        for (int col = 0; col < 9; col++){
            // grab last 3
            for (int row = 6; row < 9; row++){ 
                temp[row-6] = puzzle[row][col];
            } 
            // shift row left by 6
            for (int i = 0; i < 9; i++){
                if(i < 3){ // use temp to place numbers from temp
                    newPuzzle[i][col] = temp[i];
                    continue;
                }
                // copy array shifted right by 3
                newPuzzle[i][col] = puzzle[i-3][col];
            }
        }
    }
}

void printOutput(){
    FILE *fp = fopen("OutputPuzzle.txt", "w+");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int c = newPuzzle[i][j] + '0';
            if (i>9) // end 
                break;
            
            if(j==8){ // put a new line
                fputc(c, fp);
                fputs("\n", fp);
                continue;
            }
            fputc(c, fp);
            fputc(' ', fp);
        }
    }
    fclose(fp);
}