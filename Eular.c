#define DATASIZE 4
#include<stdio.h>


#define size DATASIZE
//Job Desc Eular
float f(float x,float y)
{
   //FOR THE FUNCTION dy/dx=-y
   return -y;
}

int main()
{
   float xinit=2.2,yinit=4.5,x=5,y,h=1.1;
   int size1=size;

   printf("Input size = %d",size1);

/*   printf("\nENTER INITIAL x AND y:");
   scanf("%f %f",&xinit,&yinit);
   printf("\nENTER x(FOR WHICH YOU WANT TO KNOW f(x)) :");
   scanf("%f",&x);
   printf("\nENTER h:");
   scanf("%f",&h);	*/

   y=0;
   while(xinit<=x)
   {
      y=yinit+h*f(xinit,y);
      xinit=xinit+h;
      yinit=y;
   }

   printf("\n\ny(%f)=%f\n",x,y);
//getch();
return 0;
}
