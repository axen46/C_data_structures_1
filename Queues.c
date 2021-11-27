#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define QUEUESIZE 100
char choice[1000];
int i,j,n=0,m=0,k=0,a=0,b=0,count=0,count1=0;
struct QUEUE
{
	char items[1000];
}q[QUEUESIZE];
void insert();
void del();
void disp();
int main()
{
	menu:
		printf("\n");
		printf("\n\t________________________________________________________________________");
		printf("\n\t|* IMPLEMENTATION OF QUEUE BY ARRAY(SIZE 100) & IT'S BASIC OPERATIONS *|");
		printf("\n\t|______________________________________________________________________|");
		printf("\n");
		printf("\n\t\t\t____________________________________");
		printf("\n\t\t\t|       ***~~MAIN  MENU~~***       |");
		printf("\n\t\t\t|       ====================       |");
		printf("\n\t\t\t|                                  |");
		printf("\n\t\t\t|  1.Press 1 to insert an element. |");
		printf("\n\t\t\t|                                  |");
		printf("\n\t\t\t|  2.Press 2 to display the Queue. |");
		printf("\n\t\t\t|                                  |");
		printf("\n\t\t\t|  3.Press 3 to delete an element. |");
		printf("\n\t\t\t|                                  |");
		printf("\n\t\t\t|  4.Press 4 to EXIT the portal.   |");
		printf("\n\t\t\t|__________________________________|");
		printf("\n\n\t\t\t____________________");
		printf("\n\t\t\t|>Enter your choice \n\t\t\t ------------------->  ");
		gets(choice);
		printf("\n");
		system("cls");
	if(strcmp("1",choice)==0)
	{
		insert();
		count++;
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
		del();
		if(count>0)
		{
			count--;
		}
		printf("\n\n\n\n");
		system("pause");
		system("cls");
		goto menu;
	}
	else if(strcmp("4",choice)==0)
	{
		printf("\n\n");
		printf("\t\t\t____________________________________________________\n");
		printf("\t\t\t| QUEUE IS NOTHING BUT A MEMORY SPACE **FIFO ALGO**|\n");
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
void insert()
{
	if(n<QUEUESIZE)
	{
		menu1:
			printf("\n\t\t_____________________________________________");
			printf("\n\t\t| This is a queue of single characters .!!! |");
			printf("\n\t\t|___________________________________________|");
			printf("\n\n\n");
			printf("\tEnter the item: ");
			gets(q[n].items);
			printf("\n\n\n");
			if(strlen(q[n].items)==1||strlen(q[n].items)==0)
			{
				printf("\n\t________________________________________________________");
				printf("\n\t|INSERTION/ENQUEUE OF AN ELEMENT IS SUCCESSFULLY DONE. |");
				printf("\n\t|______________________________________________________|");
				printf("\n\n\n\n");
				n++;
				a++;
				count1++;
			}
			else
			{
				system("cls");
				printf("\n\t____________________________________________________");
				printf("\n\t|INSERTION/ENQUEUE OF AN ELEMENT IS UNSUCCESSFULL. |");
				printf("\n\t|                                                  |");
				printf("\n\t|                                                  |");
				printf("\n\t|  Please enter a single item ..._/\\_              |");
				printf("\n\t|__________________________________________________|");
				printf("\n\n\n\n");
				system("pause");
				system("cls");
				goto menu1;
			}
	}
	else if(n==QUEUESIZE)
	{
		printf("\n\t\t\t\t_______________________");
		printf("\n\t\t\t\t|OVERFLOW OCCURS...!!!|");
		printf("\n\t\t\t\t|_____________________|");
		printf("\n\n\n\n");
	}
}
void disp()
{
	if(n>0&&count>0)
	{
		printf("---->\n\n\t");
		for(j=0;j<n;j++)
		{
			printf("___");
		}
		printf("\n\t|");
		for(i=n-1;i>=0;i--)
		{
			if(strlen(q[i].items)==1)
			{
				printf("%s |",q[i].items);
				m++;
			}
			else
			{
				printf("  |",q[i].items);
				m++;
			}
		}
		printf("\n\t|");
		for(j=0;j<n;j++)
		{
			printf("__|");
		}
		printf("\n\n");
		printf("\n\t\tCURRENT item at the FRONT position ---> %s \n",q[k].items);
		if(n>1&&count>1)
		{
			printf("\n\t\tCURRENT item at the REAR position ---> %s \n",q[n-1].items);
		}
		printf("\n\n_____________________________________");
	}
	else if(n==0||count<=0)
	{
		printf("\n\n");
		printf("\n\t\t_____________________________");
		printf("\n\t\t|The Queue is Empty now !!! |");
		printf("\n\t\t|___________________________|");
		printf("\n\n\n\n");
		count=0;
		n=0;
		k=0;
	}
}
void del()
{
	if(n>1&&count>1)
	{
		q[k].items[0]='\0';	
		printf("\n\n\n");
		printf("\n\t____________________________________________________");
		printf("\n\t|DELETION/DEQUEUE OF AN ITEM IS SUCCESSFULLY DONE. |");
		printf("\n\t|__________________________________________________|");
		printf("\n\n\n\n");
		k++;
		a--;
		if(count==0)
		{
			n=0;
			k=0;
		}
	}
	else if(n==0||count<=0)
	{
		printf("\n\t\t\t\t________________________");
		printf("\n\t\t\t\t|UNDERFLOW OCCURS...!!!|");
		printf("\n\t\t\t\t|______________________|");
		printf("\n\n\n\n");
		count=0;
		n=0;
		k=0;	
	}
	else if(n==1||count==1)
	{
		q[k].items[0]='\0';	
		printf("\n\n\n");
		printf("\n\t____________________________________________________");
		printf("\n\t|DELETION/DEQUEUE OF AN ITEM IS SUCCESSFULLY DONE. |");
		printf("\n\t|__________________________________________________|");
		printf("\n\n\n\n");
		k++;
		a--;
		count=0;
		n=0;
		k=0;	
	}
}


