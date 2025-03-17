#include"closure.h"
#include<iostream>
using namespace std;

int Closure::DFS_Expr(TS&ts,struct expr*e)
{
  int cnt,x,y;
  switch(e->t)
  {
    case T_TRUE:
      return 0;
    case T_VAR:
    {
      //cout<<"find VAR "<<e->d.VAR.name<<endl;
      string str(e->d.VAR.name);
      return ts.mp[str];
    }
    case T_UNOP:
    {
      x=DFS_Expr(ts,e->d.UNOP.arg);
      switch(e->d.UNOP.op)
      {
        case T_N:
          cnt=++N;
	  v.push_back((Expr){E_NOT,x,0});
	  break;
	case T_X:
	  cnt=++N;
          v.push_back((Expr){E_NXT,x,0});
	  break;
	case T_G://todo
          cnt=++N;
	  v.push_back((Expr){E_NOT,x,0});
	  cnt=++N;
	  v.push_back((Expr){E_UNT,0,cnt-1});
	  cnt=++N;
	  v.push_back((Expr){E_NOT,cnt-1,0});
	  break;
	case T_F://todo
	  cnt=++N;
	  v.push_back((Expr){E_UNT,0,x});
	  break;
      }
      return cnt;
    }
    case T_BINOP:
    {
      x=DFS_Expr(ts,e->d.BINOP.left);
      y=DFS_Expr(ts,e->d.BINOP.right);
      switch(e->d.BINOP.op)
      {
        case T_AND:
          cnt=++N;
          v.push_back((Expr){E_AND,x,y});
          break;
        case T_OR:
          cnt=++N;
          v.push_back((Expr){E_OR,x,y});
          break;
        case T_IMP:
	  cnt=++N;
	  v.push_back((Expr){E_IMP,x,y});
          break;
        case T_U:
	  cnt=++N;
	  v.push_back((Expr){E_UNT,x,y});
          break;
      }
      return cnt;
    }
  }
  cout<<"something wrong"<<endl;
  return -1;
}

void Closure::ComputeClosure(TS&ts,struct expr*e)
{
  v.clear();
  N=A=ts.P;
  v.resize(A+1);
  for(int i=0;i<=A;i++)
    v[i].op=E_VAR,v[i].a=i;

  DFS_Expr(ts,e);
}

void Closure::PrintClosure()
{
  cout<<A<<" "<<N<<" "<<v.size()<<endl;
  for(int i=0;i<=N;i++)
  {
    switch(v[i].op)
    {
      case E_VAR:cout<<"VAR ";break;
      case E_NOT:cout<<"NOT ";break;
      case E_AND:cout<<"AND ";break;
      case E_OR:cout<<"OR ";break;
      case E_IMP:cout<<"IMP ";break;
      case E_NXT:cout<<"NXT ";break;
      case E_UNT:cout<<"UNT ";break;
    }
    cout<<v[i].a<<" "<<v[i].b<<" : "<<i<<endl;
  }
}
