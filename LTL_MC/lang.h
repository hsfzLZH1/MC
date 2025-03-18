#ifndef LANG_H_INCLUDED
#define LANG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

enum BinOpType {
  T_AND,
  T_OR,
  T_IMP,
  T_U
};

enum UnOpType {
  T_N,
  T_X,
  T_G,
  T_F
};

enum ExprType {
  T_VAR,
  T_BINOP,
  T_UNOP,
  T_TRUE
};

struct expr {
  enum ExprType t;
  union {
    struct {char * name; } VAR;
    struct {enum BinOpType op; struct expr * left; struct expr * right; } BINOP;
    struct {enum UnOpType op; struct expr * arg; } UNOP;
  } d;
};

struct expr * TTrue();
struct expr * TVar(char * name);
struct expr * TBinOp(enum BinOpType op, struct expr * left,
                     struct expr * right);
struct expr * TUnOp(enum UnOpType op, struct expr * arg);

void print_binop(enum BinOpType op);
void print_unop(enum UnOpType op);
void print_expr(struct expr * e);

#endif // LANG_H_INCLUDED
