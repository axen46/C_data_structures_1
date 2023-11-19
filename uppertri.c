#include< stdio.h>
#include< conio.h>
#define DATASIZE 50
//Job Desc upper traingle
void main()
{
int i,j,a[500][500],sum,m,n;

/* m - Number of rows 
   n - Number of Columns */

m=n=DATASIZE;
 srand (time(NULL));

/* Accept the Elements in m x n Matrix between 0 and 10*/

for( i = 0 ; i < m ; i++ )
       for( j = 0 ; j < n ; j++ )
       {
        a[i][j]=rand() % 10 + 1;
       }

/* Addition of all Diagonal Elements */

sum = 0;

for( i = 0 ; i < m ; i++ )
       for( j = 0 ; j < n ; j++ )
       {
        if ( i < j )             // Condition for Upper Triangle
        sum = sum + a[i][j];
       }
}
