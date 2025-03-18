#ifndef MC_H_INCLUDED
#define MC_H_INCLUDED

#include<vector>
#include<iostream>
#include"TS.h"
#include"NBA.h"
using namespace std;

void ProdConstruction(TS&ts,NBA&N,TS&prod);

vector<int>CounterEg;
bool NestDFS(TS&ts);

#endif
