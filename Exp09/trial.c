#include <stdio.h>
#include <string.h>

#define MAX_RULE_COUNT 10
#define MAX_RULE_LENGTH 10
#define MAX_STRING_LENGTH 20

int main()
{
    char input[MAX_STRING_LENGTH], stack[MAX_STRING_LENGTH], ch[2], *substring;
    int i, j, stack_length, substring_length, stack_top, rule_count = 0;
    char productionrules[MAX_RULE_COUNT][MAX_RULE_LENGTH];
    char start_symbol[MAX_RULE_LENGTH];

    stack[0] = '\0';

    // User input for the number of production rules
    printf("\nKindly enter the number of production rules: ");
    scanf("%d", &rule_count);

    // User input for each production rule in the form 'left->right'
    printf("\nKindly enter the production rules (in the form 'left->right'): \n");
    for (i = 0; i < rule_count; i++)
    {
        scanf("%s", productionrules[i]);

        // Extract the start symbol from the first rule
        if (i == 0)
        {
            char *arrowsignpos = strstr(productionrules[i], "->");
            if (arrowsignpos != NULL)
            {
                // Calculate the position of '->' in the string
                size_t position = arrowsignpos - productionrules[i];

                // Extract lhs (start symbol)
                strncpy(start_symbol, productionrules[i], position);
                start_symbol[position] = '\0'; // Null-terminate the start symbol
            }
        }
    }

    // User input for the input string
    printf("\nKindly enter the input string: ");
    scanf("%s", input);

    i = 0;
    while (1)
    {
        // If there are more characters in the input string, add the next character to the stack
        if (i < strlen(input))
        {
            ch[0] = input[i];
            ch[1] = '\0';
            i++;
            strcat(stack, ch);
            printf("%s\t", stack);
            for (int k = i; k < strlen(input); k++)
            {
                printf("%c", input[k]);
            }
            printf("\tShift %s\n", ch);
        }

        // Iterate through the production rules
        for (j = 0; j < rule_count; j++)
        {
            // Split the production rule into left and right parts
            char *arrowsignpos = strstr(productionrules[j], "->");
            if (arrowsignpos != NULL)
            {
                // Calculate the position of '->' in the string
                size_t position = arrowsignpos - productionrules[j];

                // Extract lhs and rhs
                char lhs[MAX_RULE_LENGTH];
                char rhs[MAX_RULE_LENGTH];

                strncpy(lhs, productionrules[j], position);
                lhs[position] = '\0'; // Null-terminate the lhs string

                strcpy(rhs, arrowsignpos + 2); // Skip the '->'

                // Check if the right-hand side of the production rule matches a substring in the stack
                substring = strstr(stack, rhs);
                if (substring != NULL)
                {
                    // Replace the matched substring with the left-hand side of the production rule
                    stack_length = strlen(stack);
                    substring_length = strlen(substring);
                    stack_top = stack_length - substring_length;
                    stack[stack_top] = '\0';
                    strcat(stack, lhs);
                    printf("%s\t", stack);
                    for (int k = i; k < strlen(input); k++)
                    {
                        printf("%c", input[k]);
                    }
                    printf("\tReduce %s->%s\n", lhs, rhs);
                    j = -1; // Restart the loop to ensure immediate reduction of the newly derived production rule
                }
            }
        }

        // Check if the stack contains only the start symbol and if the entire input string has been processed
        if (strcmp(stack, start_symbol) == 0 && i == strlen(input))
        {
            printf("\nInput string accepted\n");
            break;
        }

        // Check if the entire input string has been processed but the stack doesn't match the start symbol
        if (i == strlen(input))
        {
            printf("\nInput string rejected\n");
            break;
        }
    }

    return 0;
}

