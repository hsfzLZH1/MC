#include"GNBA.h"
#include<iostream>
using namespace std;

GNBA::~GNBA()
{
  for(int i=0;i<Elem.size();i++)if(Elem[i])
    delete[](Elem[i]);
  Elem.clear();
}

bool*tf;
void DFS_Elem(Closure&C,GNBA&gnba,int n)
{
  if(n==gnba.N+1)
  {
    bool*elem=new bool[gnba.N+1];
    for(int i=0;i<=gnba.N;i++)elem[i]=tf[i];
    gnba.Elem.push_back(elem);
    gnba.V++;
    return;
  }
  if(C.v[n].op==E_VAR||C.v[n].op==E_NXT)
  {
    tf[n]=true;
    DFS_Elem(C,gnba,n+1);
    tf[n]=false;
    DFS_Elem(C,gnba,n+1);
    return;
  }
  if(C.v[n].op==E_NOT)
  {
    tf[n]=(!tf[C.v[n].a]);
    DFS_Elem(C,gnba,n+1);
    return;
  }
  if(C.v[n].op==E_AND)
  {
    tf[n]=(tf[C.v[n].a]&&tf[C.v[n].b]);
    DFS_Elem(C,gnba,n+1);
    return;
  }
  if(C.v[n].op==E_OR)
  {
    tf[n]=(tf[C.v[n].a]||tf[C.v[n].b]);
    DFS_Elem(C,gnba,n+1);
    return;
  }
  if(C.v[n].op==E_IMP)
  {
    tf[n]=((!tf[C.v[n].a])||tf[C.v[n].b]);
    DFS_Elem(C,gnba,n+1);
    return;
  }
  if(C.v[n].op==E_UNT)
  {
    if(!((!tf[C.v[n].a])&&(!tf[C.v[n].b])))
    {
      tf[n]=true;
      DFS_Elem(C,gnba,n+1);
    }
    if(!tf[C.v[n].b])
    {
      tf[n]=false;
      DFS_Elem(C,gnba,n+1);
    }
    return;
  }
}

void ComputeElem(Closure&C,GNBA&gnba)
{
  //mem leak
  for(int i=0;i<gnba.Elem.size();i++)
    if(gnba.Elem[i])delete[](gnba.Elem[i]);
  gnba.V=0;
  gnba.Elem.clear();
  gnba.N=C.N;gnba.A=C.A;
  tf=new bool[gnba.N+1];
  tf[0]=true;
  DFS_Elem(C,gnba,1);
  delete[]tf;
}

void PrintElem(GNBA&gnba)
{
  cout<<gnba.V<<" "<<gnba.Elem.size()<<endl;
  for(int i=0;i<gnba.V;i++)
  {
    for(int j=0;j<=gnba.N;j++)if(gnba.Elem[i][j])cout<<"1";else cout<<"0";
    cout<<endl;
  }
}
