#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Functions to calculate Follow
void followfirst(char, int, int);
void follow(char currentsymbol);

// Function to calculate firstset
void findfirst(char, int, int);

int count, n = 0;

// Stores the final result of the firstset Sets
char firstsets[10][100];

// Stores the final result of the Follow Sets
char followsets[10][100];
int m = 0;

// Maximum number of productions
#define MAX_PRODUCTIONS 10
// Maximum length of each productionrules
#define MAX_PRODUCTION_LENGTH 10

// Stores the productionrules rules
char productionrules[MAX_PRODUCTIONS][MAX_PRODUCTION_LENGTH];
char followset[10], firstset[10];
int setindex;
char currentnonterminal;
int followindex;

int main(int argc, char **argv)
{
    int firstsetindex = 0;
    int followsetindex = 0;
    int productionindex, choice;
    char currentsymbol, currentchar;

    // Taking the number of productions from the user
    printf("Kindly enter the number of productions: ");
    scanf("%d", &count);

    // Taking productionrules equations from the user with -> instead of =
    for(int productionindex = 0; productionindex < count; productionindex++)
    {
        printf("Kindly enter production rule %d: ", productionindex + 1);
        scanf("%s", productionrules[productionindex]);
    }

    printf("The productions are as follows: \n");
    for(int productionindex = 0; productionindex < count; productionindex++)
    {
        printf("%s\n", productionrules[productionindex]);
    }

    int doneproductionindex;
    char done[count];
    int ptr = -1;

    // Initializing the firstsets array
    for (setindex = 0; setindex < count; setindex++)
    {
        for (doneproductionindex = 0; doneproductionindex < 100; doneproductionindex++)
        {
            firstsets[setindex][doneproductionindex] = '!';
        }
    }
    int point1 = 0, point2, flag;

    for (setindex = 0; setindex < count; setindex++)
    {
        currentsymbol = productionrules[setindex][0];
        point2 = 0;
        flag = 0;

        // Checking if firstset of currentsymbol has already been calculated
        for (doneproductionindex = 0; doneproductionindex <= ptr; doneproductionindex++)
            if (currentsymbol == done[doneproductionindex])
                flag = 1;

        if (flag == 1)
            continue;

        // Function call
        findfirst(currentsymbol, 0, 0);
        ptr += 1;

        // Adding currentsymbol to the calculated list
        done[ptr] = currentsymbol;
        printf("\n firstset(%c) = { ", currentsymbol);
        firstsets[point1][point2++] = currentsymbol;

        // Printing the firstset Sets of the grammar
        for (productionindex = 0 + firstsetindex; productionindex < n; productionindex++)
        {
            int lark = 0, chk = 0;

            for (lark = 0; lark < point2; lark++)
            {

                if (firstset[productionindex] == firstsets[point1][lark])
                {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0)
            {
                printf("%c, ", firstset[productionindex]);
                firstsets[point1][point2++] = firstset[productionindex];
            }
        }
        printf("}\n");
        firstsetindex = n;
        point1++;
    }
    printf("\n");
    printf("-----------------------------------------------"
           "\n\n");
    char donee[count];
    ptr = -1;

    // Initializing the followsets array
    for (setindex = 0; setindex < count; setindex++)
    {
        for (doneproductionindex = 0; doneproductionindex < 100; doneproductionindex++)
        {
            followsets[setindex][doneproductionindex] = '!';
        }
    }
    point1 = 0;
    int land = 0;
    for (followindex = 0; followindex < count; followindex++)
    {
        currentnonterminal = productionrules[followindex][0];
        point2 = 0;
        flag = 0;

        // Checking if Follow of currentnonterminal
        // has already been calculated
        for (doneproductionindex = 0; doneproductionindex <= ptr; doneproductionindex++)
            if (currentnonterminal == donee[doneproductionindex])
                flag = 1;

        if (flag == 1)
            continue;
        land += 1;

        // Function call
        follow(currentnonterminal);
        ptr += 1;

        // Adding currentnonterminal to the calculated list
        donee[ptr] = currentnonterminal;
        printf(" Follow(%c) = { ", currentnonterminal);
        followsets[point1][point2++] = currentnonterminal;

        // Printing the Follow Sets of the grammar
        for (productionindex = 0 + followsetindex; productionindex < m; productionindex++)
        {
            int lark = 0, chk = 0;
            for (lark = 0; lark < point2; lark++)
            {
                if (followset[productionindex] == followsets[point1][lark])
                {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0)
            {
                printf("%c, ", followset[productionindex]);
                followsets[point1][point2++] = followset[productionindex];
            }
        }
        printf(" }\n\n");
        followsetindex = m;
        point1++;
    }
}

void follow(char currentsymbol)
{
    int productionindex, symbolindex;

    // Adding "$" to the follow set of the start symbol
    if (productionrules[0][0] == currentsymbol)
    {
        followset[m++] = '$';
    }
    for (productionindex = 0; productionindex < 10; productionindex++)
    {
        for (symbolindex = 2; symbolindex < 10; symbolindex++)
        {
            if (productionrules[productionindex][symbolindex] == currentsymbol)
            {
                if (productionrules[productionindex][symbolindex + 1] != '\0')
                {
                    // Calculate the firstset of the next Non-Terminal in the productionrules
                    followfirst(productionrules[productionindex][symbolindex + 1], productionindex,
                                (symbolindex + 2));
                }

                if (productionrules[productionindex][symbolindex + 1] == '\0' && currentsymbol != productionrules[productionindex][0])
                {
                    // Calculate the follow of the Non-Terminal in the L.H.S. of the productionrules
                    follow(productionrules[productionindex][0]);
                }
            }
        }
    }
}

void findfirst(char currentsymbol, int q1, int q2)
{
    int symbolindex;

    // The case where we encounter a Terminal
    if (!(isupper(currentsymbol)))
    {
        firstset[n++] = currentsymbol;
    }
    for (symbolindex = 0; symbolindex < count; symbolindex++)
    {
        if (productionrules[symbolindex][0] == currentsymbol)
        {
            if (productionrules[symbolindex][3] == '#')
            {
                if (productionrules[q1][q2] == '\0')
                    firstset[n++] = '#';
                else if (productionrules[q1][q2] != '\0' && (q1 != 0 || q2 != 0))
                {
                    // Recursion to calculate firstset of New Non-Terminal we encounter after epsilon
                    findfirst(productionrules[q1][q2], q1,
                              (q2 + 1));
                }
                else
                    firstset[n++] = '#';
            }
            else if (!isupper(productionrules[symbolindex][3]))
            {
                firstset[n++] = productionrules[symbolindex][3];
            }
            else
            {
                // Recursion to calculate firstset of New Non-Terminal we encounter at the beginning
                findfirst(productionrules[symbolindex][3], symbolindex, 4);
            }
        }
    }
}

void followfirst(char currentsymbol, int c1, int c2)
{
    int setindex;

    // The case where we encounter a Terminal
    if (!(isupper(currentsymbol)))
        followset[m++] = currentsymbol;
    else
    {
        int productionindex = 0, symbolindex = 1;
        for (productionindex = 0; productionindex < count; productionindex++)
        {
            if (firstsets[productionindex][0] == currentsymbol)
                break;
        }

        // Including the firstset set of the Non-Terminal in the Follow of the original query
        while (firstsets[productionindex][symbolindex] != '!')
        {
            if (firstsets[productionindex][symbolindex] != '#')
            {
                followset[m++] = firstsets[productionindex][symbolindex];
            }
            else
            {
                if (productionrules[c1][c2] == '\0')
                {
                    // Case where we reach the end of a productionrules
                    follow(productionrules[c1][0]);
                }
                else
                {
                    // Recursion to the next symbol in case we encounter a "#"
                    followfirst(productionrules[c1][c2], c1,
                                c2 + 1);
                }
            }
            symbolindex++;
        }
    }
}
