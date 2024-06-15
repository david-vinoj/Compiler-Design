%{
#include <stdio.h>
%}
%option noyywrap
%%
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+"/" 
"//"(.*)[\r\n]   
[ \t]+  
.   { printf("%c", yytext[0]); }
%%

int main() {
    yyin = fopen("pgm1.txt", "r");
    yylex();
    fclose(yyin);
    return 0;
}

