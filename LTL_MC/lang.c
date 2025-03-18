#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.h"

struct expr * new_expr_ptr() {
  struct expr * res = (struct expr *) malloc(sizeof(struct expr));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct expr * TTrue() {
  struct expr * res = new_expr_ptr();
  res -> t = T_TRUE;
  return res;
}

struct expr * TVar(char * name) {
  struct expr * res = new_expr_ptr();
  res -> t = T_VAR;
  res -> d.VAR.name = name;
  return res;
}

struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right) {
  struct expr * res = new_expr_ptr();
  res -> t = T_BINOP;
  res -> d.BINOP.op = op;
  res -> d.BINOP.left = left;
  res -> d.BINOP.right = right;
  return res;
}

struct expr * TUnOp(enum UnOpType op, struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_UNOP;
  res -> d.UNOP.op = op;
  res -> d.UNOP.arg = arg;
  return res;
}

void print_binop(enum BinOpType op) {
  switch (op) {
  case T_AND:
    printf("AND");
    break;
  case T_OR:
    printf("OR");
    break;
  case T_IMP:
    printf("->");
    break;
  case T_U:
    printf("U");
  }
}

void print_unop(enum UnOpType op) {
  switch (op) {
  case T_N:
    printf("!");
    break;
  case T_X:
    printf("X");
    break;
  case T_G:
    printf("G");
    break;
  case T_F:
    printf("F");
    break;
  }
}

void print_expr(struct expr * e) {
  switch (e -> t) {
  case T_TRUE:
    printf("TRUE");
    break;
  case T_VAR:
    printf("VAR(%s)", e -> d.VAR.name);
    break;
  case T_BINOP:
    print_binop(e -> d.BINOP.op);
    printf("(");
    print_expr(e -> d.BINOP.left);
    printf(",");
    print_expr(e -> d.BINOP.right);
    printf(")");
    break;
  case T_UNOP:
    print_unop(e -> d.UNOP.op);
    printf("(");
    print_expr(e -> d.UNOP.arg);
    printf(")");
    break;
  }
}
