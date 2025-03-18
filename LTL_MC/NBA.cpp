#include"NBA.h"
#include<iostream>
using namespace std;

NBA::~NBA()
{
  for(int i=0;i<act.size();i++)for(int j=0;j<act[i].size();j++)
    if(act[i][j])delete[](act[i][j]);
  for(int i=0;i<act.size();i++)act[i].clear();
  act.clear();
}

void NBA::Construct(GNBA&g)
{
  for(int i=0;i<act.size();i++)for(int j=0;j<act[i].size();j++)
    if(act[i][j])delete[](act[i][j]);
  for(int i=0;i<act.size();i++)act[i].clear();
  act.clear();
  G.clear();I.clear();F.clear();

  // init
  int k=g.F.size();
  V=g.V*k;
  // [0...g.V-1]*[0...k-1]
  // (i,j) -> i*k+j
  E=0;
  A=g.A;
  G.resize(V);act.resize(V);

  // compute transitions
  for(int x=0;x<V;x++)
  {
    G[x].clear();act[x].clear();

    int q=x/k,j=x%k;
    for(int i=0;i<g.G[q].size();i++)
    {
      bool*tf=new bool[A];
      for(int t=0;t<A;t++)tf[t]=g.Elem[q][t+1];
      int qq=g.G[q][i];
      int y;
      if(g.F[j][q])// (q,j)->(qq,(j+1)%k)
        y=qq*k+(j+1)%k;
      else // (q,j)->(qq,j)
        y=qq*k+j;
      G[x].push_back(y);
      act[x].push_back(tf);
    }
  }

  // construct I,F
  for(int i=0;i<g.V;i++)
    if(g.Elem[i][g.N])// varphi in Elem[i]
      I.push_back(i*k+0);
  for(int i=0;i<g.V;i++)
    if(g.F[0][i])// i in F[0]
      F.push_back(i*k+0);
}

void NBA::Print()
{
  cout<<V<<" "<<E<<" "<<A<<endl;
  for(int i=0;i<V;i++)for(int j=0;j<G[i].size();j++)
  {
    cout<<"edge "<<i<<"->"<<G[i][j]<<" action:";
    for(int k=0;k<A;k++)if(act[i][j][k])cout<<"1";else cout<<"0";
    cout<<endl;
  }
  cout<<"I:";for(int i=0;i<I.size();i++)cout<<I[i]<<" ";cout<<endl;
  cout<<"F:";for(int i=0;i<F.size();i++)cout<<F[i]<<" ";cout<<endl;
}
