%option noyywrap yylineno
%option outfile="lexer.c" header-file="lexer.h"
%{
#include "lang.h"
#include "parser.h"
#include "lib.h"
%}

%%
"!" {return TM_NEG;}
"T" {return TM_T;}
"True" {return TM_T;}
"/\\" {return TM_AND;}
"\\/" {return TM_OR;}
"->" {return TM_IMP;}
"X" {return TM_NXT;}
"G" {return TM_ALW;}
"F" {return TM_EVE;}
"U" {return TM_UTL;}
"(" {return TM_L;}
")" {return TM_R;}
[_a-z][_0-9a-zA-Z]* {
	yylval.i=new_str(yytext,yyleng);
	return TM_ID;
}
[ \t\n\r] {};
. {printf("%s",yytext);return -1;}
%%
