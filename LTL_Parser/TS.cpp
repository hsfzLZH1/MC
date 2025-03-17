#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"TS.h"
using namespace std;

int ReadTS(TS&ts,const char*filename)
{
  ifstream file(filename,ios::in);
  if(file.is_open())
  {
    file>>ts.S>>ts.T;

    string str;
    int x;
    stringstream ss;

    getline(file>>ws,str);
    ss.clear();ss.str(str);
    while(ss>>x)ts.I.push_back(x);

    string s;
    getline(file>>ws,str);
    ss.clear();ss.str(str);
    while(ss>>s)ts.A.push_back(s);

    getline(file>>ws,str);
    ss.clear();ss.str(str);
    while(ss>>s)ts.AP.push_back(s);
    ts.P=ts.AP.size();

    Edge edge;
    for(int i=0;i<ts.T;i++)
    {
      file>>edge.u>>edge.k>>edge.v;
      ts.edges.push_back(edge);
    }

    ts.L.resize(ts.S);
    for(int i=0;i<ts.S;i++)
    {
      ts.L[i].clear();
      getline(file>>ws,str);
      ss.clear();ss.str(str);
      while(ss>>x)if(x!=-1)ts.L[i].push_back(x),cout<<"label "<<i<<":"<<x<<endl;
    }
    return true;
  }
  else return false;
}
