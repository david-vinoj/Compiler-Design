#include <stdio.h>
#include <string.h>

#define MAX_EXPRESSIONS 10
#define MAX_LENGTH 30

void generateTargetCode(char icode[MAX_EXPRESSIONS][MAX_LENGTH], int numExpressions);

int main()
{
    int numExpressions;

    printf("\n Kindly enter the number of 3 address codes: ");
    scanf("%d", &numExpressions);

    if (numExpressions <= 0 || numExpressions > MAX_EXPRESSIONS)
    {
        printf("Invalid number of codes. Exiting.\n");
        return 1;
    }

    char icode[MAX_EXPRESSIONS][MAX_LENGTH];
	
    printf("\n");
    for (int i = 0; i < numExpressions; ++i)
    {
        printf(" Kindly enter 3 address code no %d: ",i+1);
        scanf("%s", icode[i]);
    }

    printf("\n Target code generation");
    printf("\n ************************");

    generateTargetCode(icode, numExpressions);

    printf("\n");
    return 0;
}

void generateTargetCode(char icode[MAX_EXPRESSIONS][MAX_LENGTH], int numExpressions)
{
    char str[MAX_LENGTH], opr[10];

    for (int i = 0; i < numExpressions; ++i)
    {
        strcpy(str, icode[i]);

        switch (str[3]) 
        {
            case '+':
                strcpy(opr, "ADD ");
                break;
            case '-':
                strcpy(opr, "SUB ");
                break;
            case '*':
                strcpy(opr, "MUL ");
                break;
            case '/':
                strcpy(opr, "DIV ");
                break;
            default:
                //strcpy(opr, "UNKNOWN ");
                break;
        }

        printf("\n\tMOV %c,R%d", str[2], i);
        printf("\n\t%s%c,R%d", opr, str[4], i);
        printf("\n\tMOV R%d,%c", i, str[0]);
    }
}
