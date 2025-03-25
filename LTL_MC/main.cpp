#include <stdio.h>
#include<cstring>
#include<fstream>
#include<iostream>
#include "lang.h"
#include "lexer.h"
#include "parser.h"
#include "TS.h"
#include "GNBA.h"
#include "NBA.h"
#include "MC.h"

extern struct expr * root;
int yyparse();

TS ts,prod;
Closure C;
GNBA GN;
NBA N;

int TSFile=-1,benchmarkFile=-1;
bool isVerbose=false;

int main(int argc, char * * argv) {
  // parse command line arguments
  for(int i=1;i<argc;i++)
  {
    if(strcmp(argv[i],"-v")==0)isVerbose=true;
    else if(strcmp(argv[i],"-t")==0)TSFile=i+1,i++;
    else if(strcmp(argv[i],"-b")==0)benchmarkFile=i+1,i++;
    else{printf("Invalid command line argument.\n");return 0;}
  }
  
  if(TSFile==-1)ts.ReadTS("TS.txt");
  else ts.ReadTS(argv[TSFile]);

  ifstream file((benchmarkFile==-1)?"benchmark.txt":argv[benchmarkFile],ios::in);

  int A,B,i;
  string str;
  file>>A>>B;

  while(A--)
  {
    getline(file>>ws,str);
    YY_BUFFER_STATE buf;
    buf=yy_scan_string(str.c_str());
    yy_switch_to_buffer(buf);
    yyparse();
    yy_delete_buffer(buf);
    if(isVerbose){cout<<"---\nPrint AST:\n";print_expr(root);cout<<endl;}//
    C.ComputeClosure(ts,root);
    if(isVerbose){cout<<"---\nPrint Closure:\n";C.PrintClosure();}//
    GN.ComputeElem(C);
    if(isVerbose){cout<<"---\nPrint Elementary Sets:\n";GN.PrintElem();}//
    GN.ComputeGF(C);
    if(isVerbose){cout<<"---\nPrint GNBA:\n";GN.PrintGF();}//
    N.Construct(GN);
    if(isVerbose){cout<<"---\nPrint NBA:\n";N.Print();}//
    if(isVerbose){cout<<"---\nPrint Product Construction:\n";ProdVerbose=true;}
    ProdConstruction(ts,N,prod);
    if(NestDFS(prod))printf("1\n");
    else
    {
      printf("0\n");
      if(isVerbose){cout<<"---\nPrint Counter Example:\n";PrintCounterEg();}
    }
  }

  while(B--)
  {
    file>>i;
    getline(file>>ws,str);
    YY_BUFFER_STATE buf;
    buf=yy_scan_string(str.c_str());
    yy_switch_to_buffer(buf);
    yyparse();
    yy_delete_buffer(buf);
    // change Initial set of TS to {i}
    ts.I.clear();ts.I.push_back(i);
    if(isVerbose){cout<<"---\nPrint AST:\n";print_expr(root);cout<<endl;}//
    C.ComputeClosure(ts,root);
    if(isVerbose){cout<<"---\nPrint Closure:\n";C.PrintClosure();}//
    GN.ComputeElem(C);
    if(isVerbose){cout<<"---\nPrint Elementary Sets:\n";GN.PrintElem();}//
    GN.ComputeGF(C);
    if(isVerbose){cout<<"---\nPrint GNBA:\n";GN.PrintGF();}//
    N.Construct(GN);
    if(isVerbose){cout<<"---\nPrint NBA:\n";N.Print();}//
    if(isVerbose){cout<<"---\nPrint Product Construction:\n";ProdVerbose=true;}
    ProdConstruction(ts,N,prod);
    if(NestDFS(prod))printf("1\n");
    else
    {
      printf("0\n");
      if(isVerbose){cout<<"---\nPrint Counter Example:\n";PrintCounterEg();}
    }
  }
  return 0;
}
