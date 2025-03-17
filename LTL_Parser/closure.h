#ifndef CLOSURE_H_INCLUDED
#define CLOSURE_H_INCLUDED

#include<vector>
#include<string>
#include<fstream>
#include<map>
#include"TS.h"
#include"lang.h"

using namespace std;

enum ExprOp{E_VAR,E_NOT,E_AND,E_OR,E_IMP,E_NXT,E_UNT};

struct Expr
{
  int op;	// type
  int a,b;	// two operands
};

struct Closure
{
// 0 - true ; 1..A - APs ; (A+1)..N - subformulas
  int N;	// size of closure
  int A;	// # of APs
  vector<Expr>v;// expressions in closure
};

void ComputeClosure(TS&ts,struct expr*e,Closure&C);
void PrintClosure(Closure&C);

#endif
