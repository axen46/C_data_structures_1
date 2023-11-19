#include<stdio.h>
#define DATASIZE 15
#include<math.h>
//Job Desc Bisection Method
float f(float);
int main()

{
float x0,x1=0,x2=DATASIZE,EPS=0.00001;      //EPS used for accuracy purposes



//printf("Enter two initial points such that {f(x1)*f(x2)}<0");

//scanf(“%f  %f”, &x1,&x2);

while(1)

{

x0=(x1+x2)/2;

if((f(x0)==0.0) || (fabs(f(x0))<EPS))

{

printf("\nRoot of the given equation is %f",x0);

break;

}

if(f(x1)*f(x0)<0)

x2=x0;

else

x1=x0;

}

return 0;

}

 

float f(float x)

{

return (x*x-2*x-1);     // for example we consider equation here is x*x-2*x+1=0(sample)

}
