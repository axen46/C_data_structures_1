/*--------------------------ORDINARY BUBBLE SORT--------------------------*/

#define DATASIZE 5 
#define    n    DATASIZE
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
//Job Desc Bubble Sort 




int main(){
	    int i,j,t;
	    int num[n];

            srand ( time (NULL) );
	  
	    for(i=0;i<n;i++)
                 num[i]=(rand() % 90 + 10);
		
	    
            printf("UNSORTED INTEGERS:-\n");
	    for(i=0;i<n;i++)
		printf("%d\n",num[i]);
	    
	    for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
		    if(num[j]>num[j+1]){
		       t=num[j];
		       num[j]=num[j+1];
		       num[j+1]=t;
		    }
		}
	    }
	    printf("SORTED INTEGERS:-\n");
	    for(i=0;i<n;i++){
		printf("%d\n",num[i]);
	    }
	  
}
                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
