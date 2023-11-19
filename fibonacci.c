#define DATASIZE 2000
#include <stdio.h>
#include <stdlib.h>
//Job Desc Fib
int main()
{
   int OldNo, NewNo, FibNo, MaxNo,i,count;

  // printf("Generate Fibonacci Numbers till what number? ");
  // scanf("%d", &MaxNum);

   OldNo=0;
   NewNo=1;
   FibNo = OldNo + NewNo;

   //printf("%d, %d, %d, ", OldNo, NewNo, FibNo);

for(i=0;i<2000;i++)
{
   OldNo=0;
   NewNo=1;
   count=0;
   FibNo = OldNo + NewNo;
   
for(;;)
   {
      OldNo = NewNo;
      NewNo = FibNo;
      FibNo = OldNo + NewNo;
      if(count >4)
      {
         printf("  ");
         break;
      }
      count++;
      //printf("%d, ", FibNo);
   }
}
   return 0;
}

