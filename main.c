#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

void Refresh(int (*)[][22],int (*)[][22],int,int);
void PrintState(int (*)[][22],int,int);
void waitFor(unsigned int);
void getPattern(int grid[][22],int rows,int columns);
void FillRandom(int grid[][22],int rows,int columns);

int main(void){
    int Current[22][22],Next[22][22];
    int (*CurPtr)[22][22],(*NxtPtr)[22][22],(*temp)[22][22];
    int i,j;
    struct timespec tim,tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 150000000L;
    for(i = 0;i<22;i++)
        for(j = 0;j<22;j++){
            Current[i][j] = 0;
            Next[i][j] = 0;
        }

    getPattern(Current,22,22);

    CurPtr = &Current;
    NxtPtr = &Next;

    while(1){
        Refresh(CurPtr,NxtPtr,22,22);
        temp = CurPtr;
        CurPtr = NxtPtr;
        NxtPtr = temp;
        PrintState(CurPtr,22,22);
        nanosleep(&tim,&tim2);
    }
    return 0;
}

void PrintState(int (*Current)[][22],int rows,int columns){
    int i,j;
    system("tput reset");
    for(i = 0;i<rows;i++){
        for(j=0;j<columns;j++)
            printf("%s",(((*Current)[i][j]==1) ? "+" : " "));
        printf("\n");
    }
}

void Refresh(int (*Current)[][22],int (*Next)[][22],int rows,int columns){
    int neighbours = 0,flagLEFT,flagRIGHT,flagUP,flagDOWN,i,j;
    int (*temp)[rows][columns];
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            neighbours = 0;
            flagLEFT = (j-1 >= 0);
            flagRIGHT = (j+1 < columns);
            flagUP = (i-1 >= 0);
            flagDOWN = (i+1 < rows);

            if(flagLEFT && flagUP)
                neighbours += (*Current)[i-1][j-1];
            if(flagLEFT && flagDOWN)
                neighbours += (*Current)[i+1][j-1];
            if(flagRIGHT && flagUP)
                neighbours += (*Current)[i-1][j+1];
            if(flagRIGHT && flagDOWN)
                neighbours += (*Current)[i+1][j+1];
            if(flagLEFT)
                neighbours += (*Current)[i][j-1];
            if(flagRIGHT)
                neighbours += (*Current)[i][j+1];
            if(flagUP)
                neighbours += (*Current)[i-1][j];
            if(flagDOWN)
                neighbours += (*Current)[i+1][j];

            if((*Current)[i][j] == 1){
                if(neighbours < 2 || neighbours > 3)
                    (*Next)[i][j] = 0;
                else if(neighbours == 2 || neighbours == 3)
                    (*Next)[i][j] = 1;
            }
            else{
                if(neighbours == 3)
                    (*Next)[i][j] = 1;
                else
                    (*Next)[i][j] = 0;
            }
        }
    }
}

void waitFor(unsigned int secs){
    unsigned int returnTime = time(NULL) + secs;
    while(time(NULL) < returnTime);
}

void getPattern(int grid[][22],int rows,int columns){
    int i,j;
    char element;

    for(i= 0; i< rows; i++){
        j = 0;
        while(j<columns){
            element = getchar();
            if(element == '1'){
                grid[i][j] = 0;
                j++;
            }
            else if(element == '0'){
                grid[i][j] = 1;
                j++;
            }
        }
    }
}

void FillRandom(int grid[][22],int rows,int columns){
    int i,j;
    char element;


    for(i= 0; i< rows; i++){
        j = 0;
        while(j<columns){
            if((time(NULL)/3 + 7)%5){
                grid[i][j] = 0;
                j++;
            }
            else{
                grid[i][j] = 1;
                j++;
            }
        }
    }
}

