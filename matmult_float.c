#include <stdlib.h>
#include <stdio.h>
#define DATASIZE 500
//Job Desc matrix multiplication float

int main(int argc, char **argv) {

  float matrixa[DATASIZE][DATASIZE];
  float matrixb[DATASIZE][DATASIZE];
  float mresult[DATASIZE][DATASIZE];
 
  long  int i,j,k,t;


for ( i=0; i<DATASIZE*DATASIZE; i++ ){
    mresult[0][i] = 0.0;
    matrixa[0][i] = matrixb[0][i] = rand()*(float)2.1; }
for(t=0;t<100;t++)
 for (i=0;i<DATASIZE;i++)
   for(j=0;j<DATASIZE;j++)
    for(k=0;k<DATASIZE;k++)
      mresult[i][j]=mresult[i][j] + matrixa[i][k] * matrixb[k][j];
 
 return 0;

}
