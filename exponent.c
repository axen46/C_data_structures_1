#include<stdio.h>
#define DATASIZE 5000
//Job Desc expo
main()
{
 int n, count;
 float x=2.4, term, sum;

 //printf("Enter value of x:");
 //scanf("%f", &x);

 n = term = sum = count = 1;

 while (n <= DATASIZE)
     {
     term = term * x/n;
     sum = sum + term;
     count = count + 1;
     n = n + 1;
    }

 printf("Terms = %d Sum = %fn", count, sum);
 }
