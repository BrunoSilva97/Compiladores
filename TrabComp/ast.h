
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VAR,
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
    char* var;
  } attr;
};
struct _ExprBool {
    enum {
        E_OPERATIONBOOL,
        E_TRUEFALSE,
    }kind;
    union {
        struct {
            int operator;
            struct _Expr* left;
            struct _Expr* right;
        }op;
        int var;
    }attr;
};

struct _Cmd {
    enum {
        E_ATRIB,
		E_IF,
		E_IFELSE,
		E_FORSHORT,
        E_FORLONG,
        E_SCAN,
        E_PRINT,
		E_LISTCMD
    }kind;
    union {
		struct {
			char* left;
			struct _Expr* right;
		} atrib;
		struct {
			struct _ExprBool* expr;
			struct _Cmd* list;
		} _if;
		struct {
			struct _ExprBool* expr;
			struct _Cmd* list1;
			struct _Cmd* list2;
		} _ifelse;
		struct {
			struct _ExprBool* expr;
			struct _Cmd* list;
		} _forShort;
        struct {
			struct _Cmd* cmd1;
			struct _ExprBool* expr1;			
			struct _Cmd* cmd3;
			struct _Cmd* cmd2;
		} _forLong;
		struct {
			struct _Cmd* head;
			struct _Cmd* tail;
		} listcmd;
	} attr;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _ExprBool ExprBool;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;

// Constructor functions (see implementation in ast.c)
ExprBool* ast_operationBool(int operator, Expr* left, Expr* right);
Expr* ast_integer(int v);
Expr* ast_var(char* string);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Cmd* ast_if(ExprBool* expr, Cmd* next);
Cmd* ast_ifelse(ExprBool* expr, Cmd* cmd1, Cmd* cmd2);
Cmd* ast_forShort(ExprBool* expr, Cmd* next);
Cmd* ast_forLong(char* string, Expr* expr, ExprBool* expr1, char* string2, Expr* expr2, Cmd* cmd2);
Cmd* ast_Cmdlist(Cmd* cmd, Cmd* next);
Cmd* ast_atrib(char* string, Expr* expr);
ExprBool* ast_truefalse(int val);
#endif
