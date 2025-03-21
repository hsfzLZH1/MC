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

int main(int argc, char * * argv) {
  ts.ReadTS("TS.txt");

  ifstream file("benchmark.txt",ios::in);

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
    //print_expr(root);cout<<endl;//
    C.ComputeClosure(ts,root);
    //C.PrintClosure();//
    GN.ComputeElem(C);
    //GN.PrintElem();//
    GN.ComputeGF(C);
    //GN.PrintGF();//
    N.Construct(GN);
    //N.Print();//
    //ProdVerbose=true;//
    ProdConstruction(ts,N,prod);
    if(NestDFS(prod))printf("1\n");
    else printf("0\n");//,PrintCounterEg();//
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
    //print_expr(root);cout<<endl;//
    C.ComputeClosure(ts,root);
    //C.PrintClosure();//
    GN.ComputeElem(C);
    //GN.PrintElem();//
    GN.ComputeGF(C);
    //GN.PrintGF();
    N.Construct(GN);
    //N.Print();//
    ProdConstruction(ts,N,prod);
    if(NestDFS(prod))printf("1\n");
    else printf("0\n");//,PrintCounterEg();
  }
  return 0;
}
