#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define STACKSIZE 100
struct stack
{
	//int top;
	char items[1000];
}s[STACKSIZE];
char choice[1000];
int len[1000],n=0,m=0,p=0,Max;
void push();
void pop();
void disp();
int max();
int main()
{
	menu:
	printf("\n\t___________________________________________________________________________________\n");
	printf("\t|* BASIC  OPERATIONS  ON  A  STACK (STACKSIZE %d) USING  ARRAY { PUSH & POP } *  |\n",STACKSIZE);
	printf("\t|_________________________________________________________________________________|\n\n\n");
	printf("\t\t\t________________________________________\n");
	printf("\t\t\t|       ***~~~~~MAIN MENU~~~~~***      |\n\t\t\t|            ---------------           |\n");
	printf("\t\t\t|                                      |\n");
	printf("\t\t\t|  1.Press 1 to perform push operation.|\n");
	printf("\t\t\t|                                      |\n");
	printf("\t\t\t|  2.Press 2 to Display the Stack.     |\n");
	printf("\t\t\t|                                      |\n");
	printf("\t\t\t|  3.Enter 3 to perform pop operation. |\n");
	printf("\t\t\t|                                      |\n");
	printf("\t\t\t|  4.Enter 4 to EXIT the portal.       |\n");
	printf("\t\t\t|______________________________________|\n\n\n\n");
	printf("\n\n\t\t\t|>Enter your choice \n\t\t\t-------------------->  ");
	gets(choice);
	system("cls");
	if(strcmp("1",choice)==0)
	{
		push();
		printf("\n\n\n\n");
		system("pause");
		system("cls");
		goto menu;
	}
	else if(strcmp("2",choice)==0)
	{
		disp();
		printf("\n\n\n\n");
		system("pause");
		system("cls");
		goto menu;
	}
	else if(strcmp("3",choice)==0)
	{
		pop();
		system("pause");
		system("cls");
		goto menu;
	}
	else if(strcmp("4",choice)==0)
	{
		printf("\n\n");
		printf("\t\t\t| STACK IS NOTHING BUT A MEMORY SPACE **LIFO ALGO**|\n");
		printf("\t\t\t|__________________________________________________|\n\n\n");
		printf("\n\n\n\n");
		printf("\t\t\t________________________________________\n");
		printf("\t\t\t|                                      |\n");
		printf("\t\t\t|   Thanks for visiting :)   !!!       |\n");
		printf("\t\t\t|______________________________________|\n");
		printf("\n\n\n\n");
		system("pause");
		system("cls");
		exit(0);
	}
	else
	{
		printf("\n\t\t\t________________________________________\n");
		printf("\t\t\t|                                      |\n");
		printf("\t\t\t| You have entered an wrong input!  :( |\n");
		printf("\t\t\t|                                      |\n");
		printf("\t\t\t|   Please enter between 1 to 4...  :) |\n");
		printf("\t\t\t|______________________________________|\n");
		printf("\n\n\n\n");
		system("pause");
		system("cls");
		goto menu;
	}
	getch();
	return 0;
} 
void push()
{
	if(n<STACKSIZE)
	{
		printf("\n\tEnter the item : ");
		gets(s[n].items);
		len[n]=strlen(s[n].items);
		printf("\n\n\n");
		printf("\n\t_______________________________________");
		printf("\n\t|PUSH OPERATION IS SUCCESSFULLY DONE. |");
		printf("\n\t|_____________________________________|");
		printf("\n\n\n\n");
		n++;
	}
	else if(n==STACKSIZE)
	{
		printf("\n\t\t\t\t_______________________");
		printf("\n\t\t\t\t|OVERFLOW OCCURS...!!!|");
		printf("\n\t\t\t\t|_____________________|");
		printf("\n\n\n\n");
	}
}
void disp()
{
	int i,x,a;
	if(n==1)
	{
		printf("\n\t\t| %s |",s[m].items);
		printf("\n\t\t|");
		for(i=0;i<len[0]+2;i++)
		{
			printf("_");
		}
		printf("|");
		printf("\n\n\n\t\tCURRENT element at the TOP position ---> %s \n",s[n-1].items);
	}
	else if(n>1)
	{
		for(x=n-1;x>=0;x--)
		{
			if(strlen(s[x].items)==max())
			{
				printf("\n\t\t| %s ",s[x].items);
				printf("|");
				printf("\n\t\t|");
				for(i=0;i<max()+2;i++)
				{
					printf("_");
				}
				printf("|");
			}
			else
			{
				printf("\n\t\t| %s",s[x].items);
				for(a=0;a<(max()-strlen(s[x].items))+1;a++)
				{
					printf(" ");
				}
				printf("|");
				printf("\n\t\t|");
				for(i=0;i<max()+2;i++)
				{
					printf("_");
				}
				printf("|");
			}
		}
		printf("\n\n\n\t\tCURRENT element at the TOP position ---> %s \n",s[n-1].items);
	}
	else
	{
		printf("\n\n");
		printf("\n\t\t_____________________________");
		printf("\n\t\t|The stack is Empty now !!! |");
		printf("\n\t\t|___________________________|");
		printf("\n\n\n\n");
	}
}
void pop()
{
	int k;
	if(n>0)
	{
		for(k=0;k<len[n-1];k++)
		{
			s[n-1].items[k]='\0';	
		}
		printf("\n\n\n");
		printf("\n\t______________________________________");
		printf("\n\t|POP OPERATION IS SUCCESSFULLY DONE. |");
		printf("\n\t|____________________________________|");
		printf("\n\n\n\n");
		n--;
	}
	else if(n==0)
	{
		printf("\n\t\t\t\t________________________");
		printf("\n\t\t\t\t|UNDERFLOW OCCURS...!!!|");
		printf("\n\t\t\t\t|______________________|");
		printf("\n\n\n\n");	
	}
}
int max()
{
	int j;
	Max=len[0];
	for(j=0;j<n;j++)
	{
		if(Max<len[j])
		Max=len[j];
	}
	return Max;
}

