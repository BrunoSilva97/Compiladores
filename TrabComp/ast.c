// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <string.h>

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_var(char* string) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = strdup(string);
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

ExprBool* ast_truefalse(int val) {
  ExprBool* node = (ExprBool*) malloc(sizeof(ExprBool));
  node->kind = E_TRUEFALSE;
  node->attr.var = val;
  return node;
}

ExprBool* ast_operationBool(int operator, Expr* left, Expr* right) {
  ExprBool* node = (ExprBool*) malloc(sizeof(ExprBool));
  node->kind = E_OPERATIONBOOL;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Cmd* ast_atrib(char* string, Expr* expr) {
	Cmd* node = (Cmd*) malloc(sizeof(Cmd));
	node->kind = E_ATRIB;
	node->attr.atrib.left = strdup(string);
	node->attr.atrib.right = expr;
	return node;
}

Cmd* ast_if(ExprBool* expr, Cmd* next) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IF;
  node->attr._if.expr = expr;
  node->attr._if.list = next;
  return node;
}

Cmd* ast_ifelse(ExprBool* expr, Cmd* cmd1, Cmd* cmd2) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IFELSE;
  node->attr._ifelse.expr = expr;
  node->attr._ifelse.list1 = cmd1;
  node->attr._ifelse.list2 = cmd2;
  return node;
}

Cmd* ast_forShort(ExprBool* expr, Cmd* next) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_FORSHORT;
  node->attr._forShort.expr = expr;
  node->attr._forShort.list = next;
  return node;
}

Cmd* ast_forLong(char* string, Expr* expr, ExprBool* expr1, char* string2, Expr* expr2, Cmd* cmd2) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_FORLONG;
  node->attr._forLong.cmd1 = ast_atrib(string, expr);
  node->attr._forLong.expr1 = expr1;
  node->attr._forLong.cmd3 = ast_atrib(string2,expr2);
  node->attr._forLong.cmd2 = cmd2;
  return node;
}

Cmd* ast_Cmdlist(Cmd* cmd, Cmd* next) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_LISTCMD;
  node->attr.listcmd.head = cmd;
  node->attr.listcmd.tail = next;
  return node;
}

