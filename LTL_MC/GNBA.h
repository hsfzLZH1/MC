#ifndef GNBA_H_INCLUDED
#define GNBA_H_INCLUDED

#include<vector>
#include"closure.h"

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
