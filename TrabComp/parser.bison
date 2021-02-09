// Tokens
%token 
  INT  
  VAR
  MAIN
  OPEN_PAREN
  CLOSE_PAREN
  OPEN_BRKT
  CLOSE_BRKT
  IF
  ELSE
  FOR
  TRUE
  FALSE
  PV
  VIRG
  ATRIB
  ADDREF
  FMT
  PRINT
  SCAN
  ASPA
  READINT

// Operator associativity & precedence
%left EQUAL DIFF LESS LEQ BIGGER BEQ
%left PLUS MINUS
%left MOD MULT DIV

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  Cmd* list;
  Cmd* cmd;
  char* var;
  ExprBool* exprBool; 
}

%type <intValue> INT
%type <exprValue> expr
%type <list> cmd_list
%type <cmd> cmd
%type <var> VAR
%type <exprBool> expr_bool

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Cmd* root;
}

%%
program: MAIN OPEN_PAREN CLOSE_PAREN OPEN_BRKT cmd_list CLOSE_BRKT { root = $5; }

cmd_list:
    { $$ = NULL; }
    | cmd cmd_list { $$ = ast_Cmdlist($1, $2); }

cmd:
    VAR ATRIB expr PV {
        $$ = ast_atrib($1, $3);
    }
    |
    IF OPEN_PAREN expr_bool CLOSE_PAREN OPEN_BRKT cmd_list CLOSE_BRKT {
		$$ = ast_if($3, $6);
	}
	|
    IF expr_bool OPEN_BRKT cmd_list CLOSE_BRKT {
        $$ = ast_if($2, $4);
    }
    |
    IF OPEN_PAREN expr_bool CLOSE_PAREN OPEN_BRKT cmd_list CLOSE_BRKT ELSE OPEN_BRKT cmd_list CLOSE_BRKT{
        $$ = ast_ifelse($3,$6,$10);
    }
    |
    IF expr_bool OPEN_BRKT cmd_list CLOSE_BRKT ELSE OPEN_BRKT cmd_list CLOSE_BRKT {
        $$ = ast_ifelse($2,$4,$8);
    }   
    |
    FOR OPEN_PAREN VAR ATRIB expr PV expr_bool PV VAR ATRIB expr CLOSE_PAREN OPEN_BRKT cmd_list CLOSE_BRKT {
	    	$$ = ast_forLong($3,$5,$7,$9,$11,$14);
	}
	|
    FOR OPEN_PAREN expr_bool CLOSE_PAREN OPEN_BRKT cmd_list CLOSE_BRKT {
        $$ = ast_forShort($3,$6);
    }
    ;
expr_bool:
    expr EQUAL expr {
        $$ = ast_operationBool(EQUAL, $1,$3);
    }
    |
    expr DIFF expr {
        $$ = ast_operationBool(DIFF,$1,$3);
    }
	|
	expr LESS expr {
		$$ = ast_operationBool(LESS, $1, $3);
	}
	|
	expr BIGGER expr {
		$$ = ast_operationBool(BIGGER, $1, $3);
	}
	|
	expr LEQ expr {
		$$ = ast_operationBool(LEQ, $1, $3);
	}
	|
	expr BEQ expr {
		$$ = ast_operationBool(BEQ, $1, $3);
	}
	|
	TRUE { 
		$$ = ast_truefalse(TRUE);
	}
	|
	FALSE {
		$$ = ast_truefalse(FALSE);
	}
	;
expr: 
    INT { 
        $$ = ast_integer($1); 
    }
    |
    VAR {
        $$ = ast_var($1);
    }
    |
	expr PLUS expr { 
		$$ = ast_operation(PLUS, $1, $3); 
	}
	|
	expr MINUS expr {
		$$ = ast_operation(MINUS, $1, $3);
	}
	|
	expr MULT expr {
		$$ = ast_operation(MULT, $1, $3);
	}
	|
	expr DIV expr {
		$$ = ast_operation(DIV, $1, $3);
	}
	|
	expr MOD expr {
		$$ = ast_operation(MOD, $1, $3);
	}
	;


%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

