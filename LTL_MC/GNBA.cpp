#include"GNBA.h"
#include<iostream>
using namespace std;

GNBA::~GNBA()
{
  for(int i=0;i<Elem.size();i++)if(Elem[i])
    delete[](Elem[i]);
  Elem.clear();
  for(int i=0;i<F.size();i++)if(F[i])delete[](F[i]);
  F.clear();
}

void GNBA::DFS_Elem(Closure&C,int n)
{
  if(n==N+1)
  {
    bool*elem=new bool[N+1];
    for(int i=0;i<=N;i++)elem[i]=tf[i];
    Elem.push_back(elem);
    V++;
    return;
  }
  if(C.v[n].op==E_VAR||C.v[n].op==E_NXT)
  {
    tf[n]=true;
    DFS_Elem(C,n+1);
    tf[n]=false;
    DFS_Elem(C,n+1);
    return;
  }
  if(C.v[n].op==E_NOT)
  {
    tf[n]=(!tf[C.v[n].a]);
    DFS_Elem(C,n+1);
    return;
  }
  if(C.v[n].op==E_AND)
  {
    tf[n]=(tf[C.v[n].a]&&tf[C.v[n].b]);
    DFS_Elem(C,n+1);
    return;
  }
  if(C.v[n].op==E_OR)
  {
    tf[n]=(tf[C.v[n].a]||tf[C.v[n].b]);
    DFS_Elem(C,n+1);
    return;
  }
  if(C.v[n].op==E_IMP)
  {
    tf[n]=((!tf[C.v[n].a])||tf[C.v[n].b]);
    DFS_Elem(C,n+1);
    return;
  }
  if(C.v[n].op==E_UNT)
  {
    if(!((!tf[C.v[n].a])&&(!tf[C.v[n].b])))
    {
      tf[n]=true;
      DFS_Elem(C,n+1);
    }
    if(!tf[C.v[n].b])
    {
      tf[n]=false;
      DFS_Elem(C,n+1);
    }
    return;
  }
}

void GNBA::ComputeElem(Closure&C)
{
  for(int i=0;i<Elem.size();i++)
    if(Elem[i])delete[](Elem[i]);
  V=0;
  Elem.clear();
  N=C.N;A=C.A;
  tf=new bool[N+1];
  tf[0]=true;
  DFS_Elem(C,1);
  delete[]tf;
}

void GNBA::PrintElem()
{
  cout<<V<<" "<<Elem.size()<<endl;
  for(int i=0;i<V;i++)
  {
    for(int j=0;j<=N;j++)if(Elem[i][j])cout<<"1";else cout<<"0";
    cout<<endl;
  }
}

void GNBA::ComputeGF(Closure&C)
{
  for(int i=0;i<G.size();i++)G[i].clear();G.clear();
  G.resize(V);for(int i=0;i<V;i++)G[i].clear();

  for(int i=0;i<V;i++)for(int j=0;j<V;j++)
  // check whether elementary set i->j (action determined by i)
  {
    bool tf=true;
    for(int k=A+1;k<=N;k++)
    {
      if(C.v[k].op==E_NXT)
        if(!(Elem[i][k]==Elem[j][C.v[k].a]))tf=false;
      if(C.v[k].op==E_UNT)
        if(!(Elem[i][k]==(Elem[i][C.v[k].b]||(Elem[i][C.v[k].a]&&Elem[j][k]))))
	  tf=false;
    }
    if(tf)G[i].push_back(j);
  }
  for(int i=0;i<F.size();i++)if(F[i])delete[](F[i]);
  F.clear();
  for(int k=A+1;k<=N;k++)if(C.v[k].op==E_UNT)
  {
    bool*tf=new bool[V];
    for(int i=0;i<V;i++)
    {
      if(!(Elem[i][k]&&((!Elem[i][C.v[k].b]))))tf[i]=true;
      else tf[i]=false;
    }
    F.push_back(tf);
  }
  if(!F.size())
  {
    bool*tf=new bool[V];
    for(int i=0;i<V;i++)tf[i]=true;
    F.push_back(tf);
  }
}

void GNBA::PrintGF()
{
  for(int i=0;i<V;i++)for(int j=0;j<G[i].size();j++)
    cout<<"edge "<<i<<" -> "<<G[i][j]<<endl;
  for(int i=0;i<F.size();i++)
  {
    bool*tf=F[i];
    cout<<i<<": ";
    for(int j=0;j<V;j++)if(tf[j])cout<<j<<" ";cout<<endl;
  }
}
