#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void main()
{
	int statecount=0,ipsymbolcount=0,strcount=0,finalcount=0;
	char ipsymbols[100],str[100],states[100];
	int table[100][100],finalstate[100];
	char ch;
	
	printf("Kindly enter number of states: ");
	scanf("%d",&statecount);
	printf("\n");
	
	printf("Kindly enter number of input symbols: ");
	scanf("%d",&ipsymbolcount);
	for(int i=0;i<ipsymbolcount;i++)
	{
		printf("Kindly enter i/p symbol %d: ",i+1);
		scanf("%s",&ipsymbols[i]);
	}
	printf("\n");
	
	for(int i=0;i<statecount;i++)
	{
		for(int j=0;j<ipsymbolcount;j++)
		{
			printf("Kindly enter State %d Symbol %d: ",i,j);
			scanf("%d",&table[i][j]);
		}
	}
	
	printf("The table is as follows: \n");
	for(int i=0;i<statecount;i++)
	{
		for(int j=0;j<ipsymbolcount;j++)
		{
			//printf("Kindly enter State ",i," Symbol ","j");
			printf("%d ",table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("Kindly enter number of final states: ");
	scanf("%d",&finalcount);
	for(int i=0;i<finalcount;i++)
	{
		printf("Kindly enter final state %d: ",i+1);
		scanf("%d",&finalstate[i]);
	}
	printf("\n");
	
	printf("Kindly enter size of input string: ");
	scanf("%d",&strcount);
	printf("Kindly enter string: ");
	for(int i=0;i<strcount;i++)
	{
		scanf("%s",&str[i]);
	}
	for(int i=0;i<strcount;i++)
	{
		printf("%c",str[i]);
	}
	printf("\n");

	ch=str[0];
	
	int ip=0;
	int state=0,ip_index=0;
	do
	{
		for(int i=0;i<ipsymbolcount;i++)
		{
			if(ch==ipsymbols[i])
			{
				ip_index=i;
			}
		}
		state=table[state][ip_index];
		ip++;
		printf("Character:%c\n",ch);
		printf("Current state:%d\n",state);
		ch=str[ip];
	} while(ch!='\0');
	
	int flag=0;
	for(int i=0;i<finalcount;i++)
	{
		if(state==finalstate[i])
		{
			flag=1;
		}
	}
	if(flag==1)
	{
		printf("ACCEPTED");
	}
	else
	{
		printf("REJECTED");
	}
	printf("\n");
	
}
	
	
	
	
	
