#ifndef NBA_H_INCLUDED
#define NBA_H_INCLUDED

#include<vector>
#include"GNBA.h"

struct NBA
{
  int V,E;		// # of nodes and # of transitions
  int A;		// size of AP (action in 2^AP)
  vector<vector<int>>G;	// Transitions
  vector<vector<bool*>>act;// Actions on transitions
  vector<int>I,F;	// initial & accepting sets

  ~NBA();

  // construct NBA from GBA
  void Construct(GNBA&g);
  void Print();
};

#endif
