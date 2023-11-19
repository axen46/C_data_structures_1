/* factorial.c -- It computes repeatedly the factorial of an integer entered 
 *        by the user. It terminates when the integer entered is not
 *        positive.
 */
#include <stdio.h>
#define DATASIZE 5000
//Job Desc factorial


int main()  
{   
    int lp,i;    /* loop control variable */
  int product=1;      /* set to the product of the first lcv positive integers */

for(i=1;i<DATASIZE;i++)  
{product=1;
for(lp=2; lp <= 10;lp++)
     product=product*lp; 
     }
	return 0;
} 


