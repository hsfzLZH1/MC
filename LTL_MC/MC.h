#ifndef MC_H_INCLUDED
#define MC_H_INCLUDED

#include<vector>
#include<iostream>
#include"TS.h"
#include"NBA.h"
using namespace std;

// whether to show edges in Product Construction
bool ProdVerbose=false;
void ProdConstruction(TS&ts,NBA&N,TS&prod);

// whether to show nested DFS steps
bool NestedDFSVerbose=false;
vector<int>CounterEg;
bool NestDFS(TS&ts);
void PrintCounterEg();

#endif
