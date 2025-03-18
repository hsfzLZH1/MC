#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"TS.h"
using namespace std;

int TS::ReadTS(const char*filename)
{
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

    Edge edge;
    for(int i=0;i<T;i++)
    {
      file>>edge.u>>edge.k>>edge.v;
      edges.push_back(edge);
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
