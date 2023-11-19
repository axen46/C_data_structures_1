#define DATASIZE 5
#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
//Job Desc Gauss Method




int factorial(int num)
{
   int i,counter;
   counter=num;
   if(num==0)
      return 1;
   for(i=counter-1;i>0;i--)
      num=num*i;
   return num;
}


int main()
{
   float *x , *y ,a,h,result , *dely,factor,p;
   int i,point=DATASIZE,j,mid,num;
  // clrscr();
   //printf("\nHOW MANY INTERPOLATING POINT?:");
   //scanf("%d",&point);
   mid=point/2-1;
   x=( float * )malloc(point*sizeof(float));
   y=( float * )malloc(point*sizeof(float));
   dely=( float * )malloc((point-1)*sizeof(float));
//   printf("\nENTER THE POINTS:\n");
   for(i=0;i<point;i++)
   {
     // printf("x[%d],y[%d]=",i,i);
     // scanf("%f %f",&x[i],&y[i]);
	x[i]=i; y[i]=i;
   }
//   printf("\nENTER x :");
 //  scanf("%f",&a);
	a=2.4;
   h=x[1]-x[0];
   p=(a-x[point/2])/h;
   printf("\nx	       y       dely0	   dely2y0	      del3y0	     del4y0\n\n");
   for(i=0;i<point;i++)
      printf("%f   %f\n",x[i],y[i]);
   printf("\n\n");

   result=y[point/2];

   /*CALCULATION OF Dely Del2y  Del3y etc.*/
   for(i=0;i<point-1;i++)
   {
      for(j=0;j<point-i-1;j++)
      {
	 y[j]=y[j+1]-y[j];
	 if(i%2) //MEANS 2nd,4th,6th STEP
	 {
	       if(j==mid)
	       {
		  dely[i]=y[j];
		  mid--;
	       }
	 }
	 else
	 {
		  if(j==mid)
		     dely[i]=y[j];
	 }
	 //gotoxy(23+10*i,point+11+j);
	 printf(" %f ",y[j]);
      }
      printf("\n\n");
   }
   result=result+p*dely[0];

   /*CALCULATING THE FINAL EXPRESSION i.e.
   yn(x)=y0 + pDy0 + p(p-1)D2y0/2! + ......*/
   factor=p;
   num=1;
   for(i=0;i<point-2;i++)
   {
      if(!(i%2))
      {
	 factor=(p+num)*factor;
	 num++;
      }
      else
	 factor=factor*(p-num);
      result=result+factor*dely[i+1]/factorial(i+2);
   }
//   gotoxy(1,38+point);
   printf("\n\n\n\n\n THE RESULT IS:%f\n",result);

//getch();
return 0;
}


