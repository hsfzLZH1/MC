%{
	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	void yyerror(char*);
	int yylex(void);
    struct expr*root;
%}

%union {
char*i;
struct expr*e;
void*none;
}

// Terminals
%token <i> TM_ID
%token <none> TM_NEG TM_T TM_AND TM_OR TM_IMP TM_NXT TM_ALW TM_EVE TM_UTL TM_L TM_R

// Nonterminals
%type <e> EXPR
%type <e> WHOLE

// Priority
%left TM_IMP
%left TM_OR
%left TM_AND
%right TM_NEG TM_NXT TM_ALW TM_EVE TM_UTL

%%

WHOLE:
  EXPR
  {
    $$=($1);
    root=$$;
  };

EXPR:
  TM_T
  {
    $$=(TTrue());
  };
| TM_ID
  {
    $$=(TVar($1));
  }
| TM_L EXPR TM_R
  {
    $$=($2);
  }
| TM_NEG EXPR
  {
    $$=(TUnOp(T_N,$2));
  }
| TM_NXT EXPR
  {
    $$=(TUnOp(T_X,$2));
  }
| TM_ALW EXPR
  {
    $$=(TUnOp(T_G,$2));
  }
| TM_EVE EXPR
  {
    $$=(TUnOp(T_F,$2));
  }
| EXPR TM_AND EXPR
  {
    $$=(TBinOp(T_AND,$1,$3));
  }
| EXPR TM_OR EXPR
  {
    $$=(TBinOp(T_OR,$1,$3));
  }
| EXPR TM_IMP EXPR
  {
    $$=(TBinOp(T_IMP,$1,$3));
  }
| EXPR TM_UTL EXPR
  {
    $$=(TBinOp(T_U,$1,$3));
  }

%%

void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}
