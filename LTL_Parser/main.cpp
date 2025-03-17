#include <stdio.h>
#include<cstring>
#include<fstream>
#include<iostream>
#include "lang.h"
#include "lexer.h"
#include "parser.h"
#include "TS.h"
#include "closure.h"

extern struct expr * root;
int yyparse();

TS ts;
Closure C;

int main(int argc, char * * argv) {
  ReadTS(ts,"TS.txt");

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
    print_expr(root);cout<<endl;//
    ComputeClosure(ts,root,C);
    PrintClosure(C);//
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
    print_expr(root);cout<<endl;//
    ComputeClosure(ts,root,C);
    PrintClosure(C);//
  }
  return 0;
}
