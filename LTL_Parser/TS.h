#ifndef TS_H_INCLUDED
#define TS_H_INCLUDED

#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct Edge{int u,v,k;};//u--a_k->v

struct TS
{
  int S,T;		// # of states, # of transitions
  vector<int>I;		// set of initial states
  vector<string>A;	// set of actions
  int P;		// # of atomic propositions
  vector<string>AP;	// set of atomic propositions
  vector<Edge>edges;
  vector<vector<int> >L;// label function
};

int ReadTS(TS&ts,const char*filename);

#endif
