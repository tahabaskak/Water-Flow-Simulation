#include <stdio.h>
#include <stdlib.h>

                    /*ALL FUNCTIONS*/
void firstStateArray(int *array,int n);
void printArray(FILE *outFile,int *array,int n);
void changeOpenCell(int *array,int currentArrayPos);
void changeFullCell(int *array,int currentArrayPos);
void checkArrayLeftCells(int *array, int n, int row, int column);
void checkArrayRightCells(int *array, int n, int row, int column);
void checkArrayUpCells(int *array, int n, int row, int column);
void checkArrayBottomCells(int *array, int n, int row, int column);
void mean(FILE *outfile,int *counterCellArray,int m,int n,double* result);
void standartDev(FILE *outFile,int *counterCellArray,int m,int n,double meanResult);

int main(int argc,char *argv[]){
    int n,m,*ptr,counterCell,randomRowCell,randomColumnCell,i,k, ik, isBottomFull,*counterCellArray;
    double meanResult=0;
    FILE *outFile;
    n=atoi(argv[1]);
    m=atoi(argv[2]);
    outFile =fopen("output.txt","w");

    ptr=(int*)malloc(n*n*sizeof(int));                      //create dynamic pointer for 2d array
    counterCellArray = (int*)malloc(m*sizeof(int));         //create dynamic pointer for open cell
    for(i=0;i<m;i++){
        counterCellArray[i]=0;                              //Opening cell counter array is first state zero;
    }
    for(k=0;k<m;k++){                                       //repeat m times
        isBottomFull = 0;                                   //Checking system
        firstStateArray(ptr,n);                             //First state system
        while(1){
            randomRowCell=rand()%n;                         //Random number for row
            randomColumnCell=rand()%n;                       //Random number for column
            int  currentArrayPos = randomRowCell*n+randomColumnCell;        //Open cell position on array
            if(ptr[currentArrayPos]==1 || ptr[currentArrayPos]==2){         //Checking cell before opening
                continue;
            }
            if(randomRowCell==0){                   // First Row makes fulled
                changeFullCell(ptr,currentArrayPos);                    //If opened cell,cell is full(2)
                checkArrayBottomCells(ptr, n, randomRowCell, randomColumnCell); //Checking bottom cell is open?
                continue;
            }

            changeOpenCell(ptr,currentArrayPos);            //Opening Cell function
            checkArrayBottomCells(ptr, n, randomRowCell, randomColumnCell);         //Checking bottom cell open?
            checkArrayLeftCells(ptr, n, randomRowCell, randomColumnCell);         //Checking left cell open?
            checkArrayRightCells(ptr, n, randomRowCell, randomColumnCell);         //Checking right cell open?
            checkArrayUpCells(ptr, n, randomRowCell, randomColumnCell);         //Checking up cell open?

            for(ik=(n*n - 1);ik >= (n*n - n + 1);ik--){              // Is the last transmit?
                if(ptr[ik] == 2){
                    isBottomFull = 1;
                }
            }
            if(isBottomFull == 1){
                 break;
            }
            counterCell++;    // cell counting
        }// ending while loop
        counterCellArray[k]=counterCell;
        counterCell=0;
    }// ending repeat times m
    fprintf(outFile,"\n");
    printArray(outFile,ptr,n);             // printing system
    mean(outFile,counterCellArray,m,n,&meanResult);        //go to mean function
    standartDev(outFile,counterCellArray,m,n,meanResult);  //go to stddev() function
}

void firstStateArray(int *array,int n){         //System is first State
    int i,j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            array[(i*n) +j]=0;                  //All cell is zero
        }
    }
}

void printArray(FILE *outFile,int * array,int n){             //System is printing
    int i,j;

    for(i=0;i<n;i++){
        fprintf(outFile,"\n");
        for(j=0;j<n;j++){
            fprintf(outFile,"%d ",array[(i*n) +j]);
        }

    }
    fprintf(outFile,"\n\n");
}

void changeOpenCell(int *array,int currentArrayPos){    //Cell is changing open
    array[currentArrayPos]=1;
}

void changeFullCell(int *array,int currentArrayPos){    //Cell is changing full
    array[currentArrayPos]=2;
}

void checkArrayLeftCells(int *array, int n, int row, int column){  //Checking cella left cell
    int currentArrayPos = row * n + column;
    int isCellFulled = 0;
    if(array[currentArrayPos - n]==2 || ((column + 1) < n && array[currentArrayPos+ 1 ] == 2) ||
           ((column - 1) >= 0 && array[currentArrayPos - 1 ] == 2) ||
           ((row + 1) < n && array[currentArrayPos + n ] == 2)){

        changeFullCell(array,currentArrayPos);
        isCellFulled = 1;
    }

    int ik, isBottomFull;
    isBottomFull = 0;
    for(ik=(n*n - 1);ik >= (n*n - n + 1);ik--){
        if(array[ik] == 2){
            isBottomFull = 1;
        }
    }

    if(isBottomFull == 0 && isCellFulled == 1 && (column -1) >= 0 && array[currentArrayPos - 1] == 1){
        checkArrayLeftCells(array, n, row, (column -1));
        checkArrayRightCells(array, n, row, (column + 1));
        checkArrayUpCells(array, n, (row -1), column);
        checkArrayBottomCells(array, n, (row +1), column);
    }
}

void checkArrayRightCells(int *array, int n, int row, int column){  //Checking cella right cell
    int currentArrayPos = row * n + column;
    int isCellFulled = 0;
    if(array[currentArrayPos - n]==2 || ((column + 1) < n && array[currentArrayPos+ 1 ] == 2) ||
           ((column - 1) >= 0 && array[currentArrayPos - 1 ] == 2) ||
           ((row + 1) < n && array[currentArrayPos + n ] == 2)){

        changeFullCell(array,currentArrayPos);
        isCellFulled = 1;
    }

    int ik, isBottomFull;
    isBottomFull = 0;
    for(ik=(n*n - 1);ik >= (n*n - n + 1);ik--){
        if(array[ik] == 2){
            isBottomFull = 1;
        }
    }

    if(isBottomFull == 0 && isCellFulled == 1 && (column + 1) < n && array[currentArrayPos + 1] == 1){
        checkArrayRightCells(array, n, row, (column + 1));
        checkArrayLeftCells(array, n, row, (column -1));
        checkArrayUpCells(array, n, (row -1), column);
        checkArrayBottomCells(array, n, (row +1), column);
    }
}

void checkArrayUpCells(int *array, int n, int row, int column){     //Checking cells up cell
    int currentArrayPos = row * n + column;
    int isCellFulled = 0;
    if(array[currentArrayPos - n]==2 || ((column + 1) < n && array[currentArrayPos+ 1 ] == 2) ||
           ((column - 1) >= 0 && array[currentArrayPos - 1 ] == 2) ||
           ((row + 1) < n && array[currentArrayPos + n ] == 2)){

        changeFullCell(array,currentArrayPos);
        isCellFulled = 1;
    }

    int ik, isBottomFull;
    isBottomFull = 0;
    for(ik=(n*n - 1);ik >= (n*n - n + 1);ik--){
        if(array[ik] == 2){
            isBottomFull = 1;
        }
    }

    if(isBottomFull == 0 && isCellFulled == 1 && (row -1) >= 0 && array[currentArrayPos - n] == 1){
        checkArrayUpCells(array, n, (row -1), column);
        checkArrayLeftCells(array, n, row, (column -1));
        checkArrayRightCells(array, n, row, (column + 1));
        checkArrayBottomCells(array, n, (row +1), column);
    }
}

void checkArrayBottomCells(int *array, int n, int row, int column){//Checking cells bottom cell
    int currentArrayPos = row * n + column;
    int isCellFulled = 0;
    if(array[currentArrayPos - n]==2 || ((column + 1) < n && array[currentArrayPos+ 1 ] == 2) ||
           ((column - 1) >= 0 && array[currentArrayPos - 1 ] == 2) ||
           ((row + 1) < n && array[currentArrayPos + n ] == 2)){

        changeFullCell(array,currentArrayPos);
        isCellFulled = 1;
    }

    int ik, isBottomFull;
    isBottomFull = 0;
    for(ik=(n*n - 1);ik >= (n*n - n + 1);ik--){
        if(array[ik] == 2){
            isBottomFull = 1;
        }
    }

    if(isBottomFull == 0 && isCellFulled == 1){
            if((row +1) < n && array[currentArrayPos + n] == 1){
                checkArrayBottomCells(array, n, (row +1), column);
                checkArrayLeftCells(array, n, row, (column -1));
                checkArrayRightCells(array, n, row, (column + 1));
                checkArrayUpCells(array, n, (row -1), column);
            }
    }
}

void mean(FILE *outFile,int *counterCellArray,int m,int n,double* result){
    int i;
    double temp=0,temp2=0;

    for(i=0;i<m;i++){
        temp =temp + (((double) counterCellArray[i])/((double)n*n)/((double)m));    //Calculating mean value
    }
    *result=temp;
    fprintf(outFile,"mean() %f\n",temp);
}

void standartDev(FILE *outFile,int *counterCellArray,int m,int n,double meanResult){
    int i;
    double temp=0,stdDevSquared=0;

    for(i=0;i<m;i++){
        temp = (((double) counterCellArray[i])/((double)n*n)/((double)m));
        stdDevSquared= stdDevSquared + (((temp - meanResult)*(temp - meanResult))/(double)(m-1));       // calculating standart devision value
        temp=0;
    }
    fprintf(outFile,"stddev() : %f\n",stdDevSquared);
}
