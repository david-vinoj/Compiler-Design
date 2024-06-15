%{ 
  #include<stdio.h> 
  void yyerror();
  int yyparse();
  int yylex();
  int flag=0; 
%} 
%token NUMBER 
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%% 
  
ArithmeticExpression: E{ printf("\nResult = %d\n", $$); return 0; }; 
 E : E'+'E {$$=$1+$3;}
   |E'-'E {$$=$1-$3;} 
   |E'*'E {$$=$1*$3;} 
   |E'/'E {$$=$1/$3;} 
   |E'%'E {$$=$1%$3;} 
   |'('E')' {$$=$2;} 
   | NUMBER {$$=$1;} 
   ; 
%% 

void main() 
{ 
   printf("Kindly enter expression: "); 
   yyparse(); 
   if(flag==0) 
   	printf("Entered arithmetic expression is Valid\n"); 
} 
  
void yyerror() 
{ 
   printf("Entered arithmetic expression is Invalid\n"); 
   flag=1; 
}
 
