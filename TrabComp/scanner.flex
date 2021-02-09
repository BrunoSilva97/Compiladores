%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD; }

">" { return BIGGER; }
"<" { return LESS; }
">=" { return BEQ; }
"<=" { return LEQ; }
"==" { return EQUAL; }
"!=" { return DIFF; }

"func main" { return MAIN; }
"false" { return FALSE; }
"true" { return TRUE; }
"if" { return IF; }
"else" { return ELSE; }
"for" { return FOR; }
"(" { return OPEN_PAREN; }
")" { return CLOSE_PAREN; }
";" { return PV; }
"{" { return OPEN_BRKT; }
"}" { return CLOSE_BRKT; }
"," { return VIRG; }
":=" { return ATRIB; }



[a-z]([a-zA-Z0-9])* {
    yylval.var = strdup(yytext);
    return VAR;
}
.  { yyerror("unexpected character"); }
%%

