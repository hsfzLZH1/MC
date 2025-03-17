#include <stdio.h>
#include "lang.h"
#include "lexer.h"
#include "parser.h"
#include "TS.h"

extern struct expr * root;
int yyparse();

TS ts;

int main(int argc, char * * argv) {
	/*
  if (argc == 1) {
    printf("Error, not enough arguments!\n");
    return 0;
  }
  if (argc >= 3) {
    printf("Error, too many arguments!\n");
    return 0;
  }
  yyin = fopen(argv[1], "rb");
  if (yyin == NULL) {
    printf("File %s can't be opened.\n", argv[1]);
    return 0;
  }*/
  ReadTS(ts,"TS.txt");
  char str[]="X a";
  YY_BUFFER_STATE buf;
buf = yy_scan_string(str);
yy_switch_to_buffer(buf);
  yyparse();
  yy_delete_buffer(buf);
  //fclose(yyin);
  print_expr(root);
}
