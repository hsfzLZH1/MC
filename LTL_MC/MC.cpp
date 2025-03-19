#include"NBA.h"
#include<queue>
#include<string>
#include<iostream>
using namespace std;

extern bool ProdVerbose;

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
    prod.AP.push_back(str);
    prod.mp[str]=i;
  }
  string ss("F");
  prod.AP.push_back(ss);
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
	if(ProdVerbose)cout<<"Init "<<x<<endl;
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
  bool*isF=new bool[N.V];
  for(int i=0;i<N.V;i++)isF[i]=false;
  for(int i=0;i<N.F.size();i++)isF[N.F[i]]=true;
  while(!Q.empty())
  {
    int x=Q.front();Q.pop();
    int s=x/K,q=x%K;
    prod.L[x].push_back(q);
    if(isF[q])prod.L[x].push_back(K);// label F
				
    for(int i=0;i<ts.G[s].size();i++)
    {
      int t=ts.G[s][i];
      bool*tf=new bool[ts.P];
      for(int k=0;k<ts.P;k++)tf[k]=false;
      for(int k=0;k<ts.L[t].size();k++)tf[ts.L[t][k]]=true;

      for(int l=0;l<N.G[q].size();l++)
      {
        bool eq=true;
        for(int k=0;k<ts.P;k++)if(tf[k]!=N.act[q][l][k])eq=false;
        if(eq)// (s,q)->(t,p)
        {
          int p=N.G[q][l];
          int y=t*K+p;
          if(!vis[y])vis[y]=true,Q.push(y);
	  prod.T++;
	  prod.G[x].push_back(y);
	  prod.a[x].push_back(ts.a[s][i]);
	  if(ProdVerbose)cout<<"addedge "<<x<<"->"<<y<<" act:"<<ts.a[s][i]<<endl;
        }
      }
      delete[]tf;
    }
  }

  delete[]vis;
  delete[]isF;
}

bool ans;
extern vector<int>CounterEg;
extern bool NestedDFSVerbose;
bool*ovis,*ivis;// visit status of outer DFS and inner DFS

// Inner DFS at x start from st
void InnerDFS(TS&ts,int x,int st)
{
  if(NestedDFSVerbose)cout<<"Inner "<<x<<" "<<st<<endl;
  ivis[x]=true;
  for(int i=0;i<ts.G[x].size();i++)
  {
    if(ts.G[x][i]==st)
    {
      ans=false;
      if(NestedDFSVerbose)cout<<"Find CounterExample.\n";
      CounterEg.push_back(ts.a[x][i]);
      CounterEg.push_back(ts.G[x][i]);
      CounterEg.push_back(-1);
      return;
    }
    if(ans&&!ivis[ts.G[x][i]])
    {
      CounterEg.push_back(ts.a[x][i]);
      CounterEg.push_back(ts.G[x][i]);
      InnerDFS(ts,ts.G[x][i],st);
      if(ans)CounterEg.pop_back(),CounterEg.pop_back();
    }
  }
}

void OuterDFS(TS&ts,int x)
{
  if(NestedDFSVerbose)cout<<"Outer "<<x<<endl;
  ovis[x]=true;
  for(int i=0;i<ts.G[x].size();i++)if(ans&&!ovis[ts.G[x][i]])
  {
    CounterEg.push_back(ts.a[x][i]);
    CounterEg.push_back(ts.G[x][i]);
    OuterDFS(ts,ts.G[x][i]);
    if(ans)CounterEg.pop_back(),CounterEg.pop_back();
  }
  if(NestedDFSVerbose)cout<<"Fully"<<endl;
  // now x is fully expanded
  bool isFinal=false;
  for(int i=0;i<ts.L[x].size();i++)if(ts.L[x][i]==ts.P-1)
  {
    if(NestedDFSVerbose)cout<<"final state "<<x<<" "<<ts.AP.size()<<" "<<ts.P-1<<"is fully expanded"<<endl;
    if(ans&&!ivis[x])
    {
      CounterEg.push_back(-1);
      InnerDFS(ts,x,x);
      if(ans)CounterEg.pop_back();
    }
    break;
  }
}

bool NestDFS(TS&ts)
{
  ovis=new bool[ts.S];
  ivis=new bool[ts.S];
  for(int i=0;i<ts.S;i++)ovis[i]=ivis[i]=false;
  ans=true;
  CounterEg.clear();

  for(int i=0;i<ts.I.size();i++)if(ans&&!ovis[ts.I[i]])
  {
    CounterEg.push_back(ts.I[i]);
    OuterDFS(ts,ts.I[i]);
    if(ans)CounterEg.pop_back();
  }

  delete[]ovis;
  delete[]ivis;
  return ans;
}

void PrintCounterEg()
{
  int cnt=0;
  bool sa=false;// false-state,true-action
  for(int i=0;i<CounterEg.size();i++)
  {
    if(CounterEg[i]==-1)
    {
      if(!cnt)cout<<"(";
      else cout<<")^w";
      cnt++;
    }
    else if(!sa)cout<<CounterEg[i],sa=!sa;
    else cout<<"-["<<CounterEg[i]<<"]>",sa=!sa;
  }
  cout<<endl;
}
