%{
#include <stdio.h>
#include<ctype.h>
int yylex();
int yyerror();
int yyparse();
int flag=0; 
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS

%%

input: /* empty */
     | input line
     ;

line: '\n'
    | exp '\n' { printf("Result = %d\n", $$); return 0; }; 
    ;

exp: NUMBER
   | exp '+' exp  { $$ = $1 + $3; }
   | exp '-' exp  { $$ = $1 - $3; }
   | exp '*' exp  { $$ = $1 * $3; }
   | exp '/' exp  { $$ = $1 / $3; }
   | '-' exp %prec UMINUS { $$ = -$2; }
   | '(' exp ')'  { $$ = $2; }
   ;
%%

int main()
{
    printf("Kindly enter expression: "); 
    yyparse();
    if(flag==0) 
   	printf("Entered arithmetic expression is Valid\n"); 
}

int yyerror(char *s)
{
    printf("Entered arithmetic expression is Invalid\n"); 
    flag=1;
}

int yylex()
{
    int c = getchar();
    if (c == EOF)
        return 0;
    if (isdigit(c)) {
        ungetc(c, stdin);
        scanf("%d", &yylval);
        return NUMBER;
    }
    return c;
}
