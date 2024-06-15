#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int statecount=0,ipsymbolcount=0;
int ipsymbols[10];
int transitions[10][10][10];
char nfa_table[10][10][10];
char final_dfa[10][10][10];

void main()
{
	printf("Kindly enter number of states: ");
	scanf("%d",&statecount);
	printf("\n");
	
	printf("Kindly enter number of input symbols: ");
	scanf("%d",&ipsymbolcount);
	for(int i=0;i<ipsymbolcount;i++)
	{
		printf("Kindly enter i/p symbol %d: ",i+1);
		scanf("%d",&ipsymbols[i]);
	}
	printf("\n");
	for(int i=0;i<ipsymbolcount;i++)
	{
		printf("Kindly enter NFA Matrix for i/p symbol %d: \n",ipsymbols[i]);
		for(int j=0;j<statecount;j++)
		{
			for(int k=0;k<statecount;k++)
			{
				scanf("%d",&transitions[i][j][k]);
			}
		}
	}
	
	char str[10];
	for (int i = 0; i < statecount; i++)
	{
		for (int j = 0; j < statecount; j++)
		{
	    		for (int k = 0; k < ipsymbolcount; k++)
	    		{
	        		if (transitions[k][i][j] == 1)
	        		{	
	            			sprintf(str, "q%d", j);
	            			if (strcmp(nfa_table[i][k], str) != 0)
	            			{
	                			strcat(nfa_table[i][k], str);
	            			}
	        		}
	    		}
		}
    	}
    	printf("\n");
    	printf("The NFA table is as follows: \n");
    	for(int i=0;i<ipsymbolcount;i++)
    	{
    		printf("\t%d",ipsymbols[i]);
    		
    	}
    	printf("\n");
    	printf("   _____________________\n");
	for(int i=0;i<statecount;i++)
	{
		printf("q%d |",i);
		for(int j=0;j<ipsymbolcount;j++)
		{
			printf("\t%s",nfa_table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	 // Conversion to DFA starts here. A queue is maintained to keep track of the new states that are found.
	char queue[20][10];
	int front = 0;
   	int rear = 0;
	int rows = 0; // Total rows of the final DFA table

    	for (int i = 0; i < 20; i++)
		strcpy(queue[i], "");
    	strcpy(queue[rear], "q0");
    	rear++;
    	strcpy(final_dfa[rows][0], "q0");

	// Repeat until queue is empty
    	while (strcmp(queue[front], "") != 0)
	{
		// Keeps track of new rows of DFA table when new states are added
		int temp_rows = rows;
		// Contains the new states that are found for an input symbol transition for each state
		char new_states[20];

		// Reset the new states list
		for (int i = 0; i < 20; i++)
		    strcpy(new_states, "");

		// For each input symbol
		for (int j = 0; j < ipsymbolcount; j++)
		{
		    // Reset the new states list
		    for (int i = 0; i < 20; i++)
			strcpy(new_states, "");

		    // Loop to find the transitions for each input of the current state in the front of the queue
		    // i = 1; i += 2: For each sub-state in the current state - i.e., q0, q1, q2 in q0q1q2
		    //queue stores values as q0q1q2...ignores q and jumps to the digit section only hence i+=2
		    for (int i = 1; i < strlen(queue[front]); i += 2)
		    {
			if (isdigit(queue[front][i])) //ensures state number is actually selected as 1 and not q1
			{
			    int n = queue[front][i] - '0'; //converts to integer..q1 where 1 is stores as char/str in queue

			    // Loop to find the transitions of the current state that is being checked
			    //l+=2 to skip character and focus on transition number...0 from q0 in queue
			    for (int l = 1; l < strlen(nfa_table[n][j]); l += 2)
			    {
				int num1;
				if (isdigit(nfa_table[n][j][l])) //if character selected is numeric transition
				{
				    num1 = nfa_table[n][j][l] - '0'; //converts char_number to integer
				}

			        // Loop to check if a transition creates duplicate states;
			        // eg:- if q0q1 has input 0 transitions as q0 -> q1 and q1 -> q1, q1 need not be added twice to new_states
			        int flag2 = 0;
			        int num2;
			        for (int m = 1; m < strlen(new_states); m += 2)
			        {
			            if (isdigit(new_states[m]))
			            {
			                num2 = new_states[m] - '0';
			                if (num1 == num2)
			                    flag2 = 1;
			            }
			        }

			        if (flag2 == 0)
			        {
			            char temp[20];
			            sprintf(temp, "q%d", num1);
			            strcat(new_states, temp);
			        }
			    }
			}
		    }

		    // Sort the new states list in ascending order of state number
		    int temp_states[20];
		    int temp_index = 0;
		    for (int d = 0; d < strlen(new_states); d++)
		    {
			if (isdigit(new_states[d])) //if selected char is a digit
			{
			    temp_states[temp_index++] = new_states[d] - '0';  //converts to integer
			}
		    }
			
		    for (int q = 0; q < temp_index; q++)
		    {
			for (int r = 0; r < temp_index - q - 1; r++)
			{
			    if (temp_states[r] > temp_states[r + 1])
			    {
			        int swap = temp_states[r];
			        temp_states[r] = temp_states[r + 1];
			        temp_states[r + 1] = swap;
			    }
			}
		    }

		    char tempstr[20];
		    strcpy(new_states, "");
		    for (int q = 0; q < temp_index; q++)
		    {
			sprintf(tempstr, "q%d", temp_states[q]);
			strcat(new_states, tempstr);
		    }

		    // Check if new state is already in queue, if not, add it to queue
		    int flag = 0;
		    for (int a = 0; a < rear; a++)
		    {
			if (strcmp(queue[a], new_states) == 0)
			{
			    flag = 1;
			}
		    }

		    if (flag == 0)
		    {
			strcpy(queue[rear], new_states);
			rear++;
			// Add new state to the next row of the final DFA table
			strcpy(final_dfa[++temp_rows][0], new_states);
		    }

		    strcpy(final_dfa[rows][j + 1], new_states);
		}

		rows++;
		front++;
	}
	
	printf("\nThe DFA table is as follows:\n");
    	printf("%-10s|", " ");
    	for (int i = 0; i < ipsymbolcount; i++)
		printf("Input %-4d|", ipsymbols[i]);
    	printf("\n");
    	for (int i = 0; i < 11 * (ipsymbolcount + 1); i++)
		printf("%s", "=");
    	printf("\n");
    	for (int i = 0; i < rows; i++)
    	{
		for (int j = 0; j < ipsymbolcount + 1; j++)
		{
	    		printf("%-10s|", final_dfa[i][j]);
		}
	printf("\n");
    	}
}

