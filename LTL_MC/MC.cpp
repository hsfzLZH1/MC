#include"NBA.h"
#include<queue>
#include<string>
#include<iostream>
using namespace std;

// given TS ts and NBA A, construct product in prod
// only the reachable part from initial states
void ProdConstruction(TS&ts,NBA&N,TS&prod)
{
  // init
  prod.I.clear();
  prod.A.clear();
  prod.AP.clear();
  prod.mp.clear();
  for(int i=0;i<prod.G.size();i++)prod.G[i].clear();
  for(int i=0;i<prod.a.size();i++)prod.a[i].clear();
  for(int i=0;i<prod.L.size();i++)prod.L[i].clear();
  prod.G.clear();
  prod.a.clear();
  prod.L.clear();

  queue<int>Q;
  int K=N.V;

  prod.S=ts.S*N.V;
  prod.G.resize(prod.S);
  prod.a.resize(prod.S);
  prod.L.resize(prod.S);
  prod.T=0;
  for(int i=0;i<ts.A.size();i++)prod.A.push_back(ts.A[i]);
  prod.P=N.V+1;// atomic propositions are NBA states + whether in NBA.F
  for(int i=0;i<N.V;i++)
  {
    string str=to_string(i);
    prod.mp[str]=i;
  }
  string ss("F");
  prod.mp[ss]=prod.P-1;

  bool*vis=new bool[prod.S];
  for(int i=0;i<prod.S;i++)vis[i]=false;

  // compute initial states
  for(int i=0;i<ts.I.size();i++)
  for(int j=0;j<N.I.size();j++)
  {
    int s=ts.I[i],q=N.I[j];
    if(ts.P!=N.A)cerr<<"Error!"<<endl;
    bool*tf=new bool[ts.P];
    for(int k=0;k<ts.P;k++)tf[k]=false;
    for(int k=0;k<ts.L[s].size();k++)tf[ts.L[s][k]]=true;
    for(int t=0;t<N.G[q].size();t++)
    {
      bool eq=true;
      for(int k=0;k<ts.P;k++)if(tf[k]!=N.act[q][t][k])eq=false;
      if(eq)// (s,qq) in prod.I
      {
        int qq=N.G[q][t];
	int x=s*K+qq;
	if(!vis[x])vis[x]=true,prod.I.push_back(x),Q.push(x);
      }
    }
    delete[]tf;
  }

  // to generate the whole product construction:
  /*{
   *  Q.clear();
   *  for(int i=0;i<S;i++)Q.push(i),vis[i]=true;
   *}*/

  // BFS, add reachable states
  while(!Q.empty())
  {
    //todo
    //when state x is expanding, label it
    Q.pop();
  }
}

bool NestDFS(TS&ts)
{
  return false;
}
