#ifndef GNBA_H_INCLUDED
#define GNBA_H_INCLUDED

#include<vector>
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

  // compute closure from TS and LTL formula
  void ComputeClosure(TS&ts,struct expr*e);
  void PrintClosure();
  int DFS_Expr(TS&ts,struct expr*e);// helper
};

struct GNBA
{
  int V,E;		// # of nodes and # of transitions
  int N,A;		// N,A of closure
  vector<bool*>Elem;	// Elementary subsets
  vector<vector<int>>G;	// Transitions
  vector<bool*>F;	// accepting sets

  ~GNBA();

  // compute Elementary subsets from closure
  void ComputeElem(Closure&C);
  void PrintElem();
  void ComputeGF(Closure&C);
  void PrintGF();

  // helpers
  bool*tf;
  void DFS_Elem(Closure&C,int n);
};

#endif
