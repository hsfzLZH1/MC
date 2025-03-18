#ifndef TS_H_INCLUDED
#define TS_H_INCLUDED

#include<vector>
#include<string>
#include<fstream>
#include<map>
using namespace std;

struct TS
{
  int S,T;		// # of states, # of transitions
  vector<int>I;		// set of initial states
  vector<string>A;	// set of actions
  int P;		// # of atomic propositions
  vector<string>AP;	// set of atomic propositions
  map<string,int>mp;	// map from AP to its index
  vector<vector<int> >G;// adjacency matrix
  vector<vector<int> >a;// actions on transitions
  vector<vector<int> >L;// label function

  int ReadTS(const char*filename); // read TS from file
};

#endif
