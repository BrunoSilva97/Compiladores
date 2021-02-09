#include <stdio.h>
#include "parser.h"
#include "ast.h"

void printTabs(int tabs){
    int i = 0;
    for(;i<tabs;i++)
        printf("  ");
    return;
}

void evalExpr(Expr* expr, int tabs) {
  
    if (expr->kind == E_INTEGER) {
        printTabs(tabs);
        printf("%d\n",expr->attr.value);
        return;
    }  
    else if (expr->kind == E_VAR){
        printTabs(tabs);
        printf("%s\n",expr->attr.var);
        return;
    }
    else if (expr->kind == E_OPERATION) {
        switch (expr->attr.op.operator) {
        case PLUS:
            printTabs(tabs);
            printf("PLUS\n");
            evalExpr(expr->attr.op.left, tabs+1);
            evalExpr(expr->attr.op.right, tabs+1);
            break;
        case MINUS:
            printTabs(tabs);
            printf("MINUS\n");
            evalExpr(expr->attr.op.left, tabs+1);
            evalExpr(expr->attr.op.right, tabs+1);
            break;
        case MULT:
            printTabs(tabs);
            printf("MULT\n");
            evalExpr(expr->attr.op.left, tabs+1);
            evalExpr(expr->attr.op.right, tabs+1);
            break;
        case DIV:
            printTabs(tabs);
            printf("DIV\n");
            evalExpr(expr->attr.op.left, tabs+1);
            evalExpr(expr->attr.op.right, tabs+1);
            break;
        case MOD:
            printTabs(tabs);
            printf("MOD\n");
            evalExpr(expr->attr.op.left, tabs+1);
            evalExpr(expr->attr.op.right, tabs+1);
            break;
        }
    }
    return;
}

void evalExprBool(ExprBool* expr, int tabs) {
  if(expr->kind == E_OPERATIONBOOL) {
    switch(expr->attr.op.operator) {
      case EQUAL:
        printTabs(tabs);
        printf("EQUAL\n");
        evalExpr(expr->attr.op.left, tabs+1);
        evalExpr(expr->attr.op.right, tabs+1);
        break;
      case DIFF:
        printTabs(tabs);
        printf("DIFF\n");
        evalExpr(expr->attr.op.left, tabs+1);
        evalExpr(expr->attr.op.right, tabs+1);
        break;
      case LESS:
        printTabs(tabs);
        printf("LESS\n");
        evalExpr(expr->attr.op.left, tabs+1);
        evalExpr(expr->attr.op.right, tabs+1);
        break;
      case BIGGER:
        printTabs(tabs);
        printf("BIGGER\n");
        evalExpr(expr->attr.op.left, tabs+1);
        evalExpr(expr->attr.op.right, tabs+1);
        break;
      case LEQ:
        printTabs(tabs);
        printf("LEQ\n");
        evalExpr(expr->attr.op.left, tabs+1);
        evalExpr(expr->attr.op.right, tabs+1);
        break;
      case BEQ:
        printTabs(tabs);
        printf("BEQ\n");
        evalExpr(expr->attr.op.left, tabs+1);
        evalExpr(expr->attr.op.right, tabs+1);
        break;
    }
  }
  else {
    if(expr->attr.var == 270){          
      printTabs(tabs);
      printf("TRUE\n");
    }
    else {
      printTabs(tabs);
      printf("FALSE\n");
    }
  }

  return;
}

void evalCmd(Cmd* list, int tabs) {
    switch (list->kind) {
        case E_ATRIB:
            printTabs(tabs);
            printf ("ATRIB\n");
            printTabs(tabs+1);
            printf ("%s\n", list->attr.atrib.left);
            evalExpr(list->attr.atrib.right, tabs+1);
            break;
        case E_IF:
            printTabs(tabs);
            printf ("IF\n");
            evalExprBool(list->attr._if.expr, tabs+1);
            evalCmd(list->attr._if.list, tabs+1);
            break;
        case E_IFELSE:
            printTabs(tabs);
            printf ("IF\n");
            evalExprBool(list->attr._ifelse.expr, tabs+1);
            evalCmd(list->attr._ifelse.list1, tabs+1);
            printTabs(tabs);
            printf ("ELSE\n");
            evalCmd(list->attr._ifelse.list2, tabs+1);
            break;
        case E_FORSHORT:
            printTabs(tabs);
            printf ("FOR\n");
            evalExprBool(list->attr._forShort.expr, tabs+1);
            evalCmd(list->attr._forShort.list, tabs+1);
            break;
        case E_FORLONG:
            printTabs(tabs);
            printf ("FOR\n");
            evalCmd(list->attr._forLong.cmd1, tabs+1);
            evalExprBool(list->attr._forLong.expr1, tabs+1);
            evalCmd(list->attr._forLong.cmd3, tabs+1);
            evalCmd(list->attr._forLong.cmd2, tabs+1);
            break;
        case E_LISTCMD:
            evalCmd(list->attr.listcmd.head, tabs+1);
            if (list->attr.listcmd.tail != NULL) {
                printTabs(tabs-1);
                evalCmd(list->attr.listcmd.tail, tabs);
            }
            break;
    }
    return;
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
    printf("MAIN\n");
    Cmd* list = root;      
    evalCmd(list,1);
  }
  return 0;


}
