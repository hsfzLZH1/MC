#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"TS.h"
using namespace std;

int TS::ReadTS(const char*filename)
{
  // init
  I.clear();
  A.clear();
  AP.clear();
  mp.clear();
  for(int i=0;i<G.size();i++)G[i].clear();
  for(int i=0;i<a.size();i++)a[i].clear();
  for(int i=0;i<L.size();i++)L[i].clear();
  G.clear();
  a.clear();
  L.clear();
  
  ifstream file(filename,ios::in);
  if(file.is_open())
  {
    file>>S>>T;

    string str;
    int x;
    stringstream ss;

    getline(file>>ws,str);
    ss.clear();ss.str(str);
    while(ss>>x)I.push_back(x);

    string s;
    getline(file>>ws,str);
    ss.clear();ss.str(str);
    while(ss>>s)A.push_back(s);

    mp.clear();
    getline(file>>ws,str);
    ss.clear();ss.str(str);
    while(ss>>s)
    {
      AP.push_back(s);
      P++;
      mp[s]=P;
    }

    G.resize(S);a.resize(S);
    for(int i=0;i<T;i++)
    {
      int u,k,v;
      file>>u>>k>>v;
      G[u].push_back(v);
      a[u].push_back(k);
    }

    L.resize(S);
    for(int i=0;i<S;i++)
    {
      L[i].clear();
      getline(file>>ws,str);
      ss.clear();ss.str(str);
      while(ss>>x)if(x!=-1)L[i].push_back(x);
    }

    file.close();
    return true;
  }
  else return false;
}
