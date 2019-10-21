%{
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <string>
    #include <cmath>
    #include "SymbolInfo.h" 
    #include "y.tab.h"   
    int newline = 1;
    int errors = 0;
    using namespace std ;
    void yyerror(char *);
    FILE* logout = fopen("scanner_log.txt","w") ;
    extern YYSTYPE yylval ;
%}

DIGITS [0-9]

DELIM [ \t\r\f\v]

WS  [DELIM]+

CHARACTERS .

ADDOP (\+|\-)

MULOP (\*|\/|\%)

INCOP (\+\+)

DECOP (\-\-)

RELOP (\<|\<\=|\>|\>\=|\=\=|\!\=)

ASSIGNOP \=

LOGICOP (\&\&|\|\|)

BITOP (\&|\||\^|\<\<|\>\>) 

NOT \!

LPAREN \(

RPAREN \)

LCURL \{

RCURL \}

LTHIRD \[

RTHIRD \]

COMMA \,

SEMICOLON \;

WNL [^\\\n][^'\n]+

WONL \\[^'\n][^'\n]+ 

STRING \"(([^\n\"]|(\\\"))*(\\\n)*)*\"

UFSTRING \"(([^\n\"]|(\\\"))*(\\\n)*)*

COMMENT \/\/.*(\\\n.*)*?\n

MULTILINECOMMENT \/\*([^*]|\*+[^/*])*\*+\/

UFMLCOMMENT \/\*([^*]|\*+[^/*])*

UNBACKSLASH \'\\'

UNRECOGCHAR [\:$#@]

ALPHABETS [a-zA-Z]

LETTER [a-zA-Z0-9]


ID (_|{LETTER})(_|{LETTER}|{DIGITS})* 

%%
{WS}    {}

{DIGITS}*\.({DIGITS}+\.)+{DIGITS}* {
                    fprintf(logout,"Error at Line:%d : Too many decimal points %s\n",newline,yytext) ;
                    errors++ ;
                }

{DIGITS}*(\.{DIGITS})*(E[+-]?({DIGITS}*\.{DIGITS}*)+)+    {
                        fprintf(logout,"Error at Line:%d : Ill formed number %s\n",newline,yytext) ;
                        errors++ ;
                } 

{DIGITS}+{ALPHABETS}+   {
                            fprintf(logout,"Error at Line:%d : Invalid Suffix on numaric constant or invalid prefix on idetifier %s\n",newline,yytext) ;
                            errors++ ;
                }

{DIGITS}*\.{DIGITS}+(E[+-]?{DIGITS}+)?{ALPHABETS}+    {
                            fprintf(logout,"Error at Line:%d : Invalid Suffix on numaric constant or invalid prefix on idetifier %s\n",newline,yytext) ;
                            errors++ ;   
} 


\'{WNL}\'           {
                            fprintf(logout,"Error at Line:%d : Invalid character sequence %s\n",newline,yytext) ;  
                            errors++ ;      
                }

\'{WONL}\'      {
                            fprintf(logout,"Error at Line:%d : Invalid character sequence %s\n",newline,yytext) ;  
                            errors++ ;      
                }

\'\'            {
                fprintf(logout,"Error at Line:%d : Empty character constant error %s\n",newline,yytext) ;  
                errors++ ;  
}

{UNRECOGCHAR}                  {
                            fprintf(logout,"Error at Line:%d : Unrecognised Character %s\n",newline,yytext) ;        
                            errors++ ;
                }

\'{CHARACTERS}                        {
                            fprintf(logout,"Error at Line:%d : Unfinished Character %s\n",newline,yytext) ;        
                            errors++ ;
                }

{UFSTRING}                  {
                            string s(yytext) ;
                            fprintf(logout,"Error at Line:%d : Unfinished String ",newline) ;
                            for(int i=0;i<s.size();i++){
                                if(s[i]=='\n'){
                                    newline++ ;
                                }
                                fprintf(logout,"%c",s[i]) ;
                            }
                            fprintf(logout," \n")   ;
                            errors++ ;
                }

{UNBACKSLASH}                        {
                            fprintf(logout,"Error at Line:%d : Unfinished Character %s\n",newline,yytext) ;        
                            errors++ ;
                }

"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"while" {return WHILE;}
"int" {return INT;}
"float" {return FLOAT;}
"double" {return DOUBLE;}
"char" {return CHAR;}
"return" {return RETURN;}
"void" {return VOID;}
"println" {return PRINTLN ;}


{DIGITS}+       {
                    fprintf(logout,"Line No.%d : Token <CONST_INT> Lexeme %s found\n",newline,yytext) ; 
                    string name(yytext) ;
                    string type("CONST_INT") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return CONST_INT ;
                }

{DIGITS}*(\.){DIGITS}+(E[+-]?{DIGITS}+)?     {
                                                fprintf(logout,"Line No.%d : Token <CONST_FLOAT> Lexeme %s found\n",newline,yytext) ;
                                                string name(yytext) ;
                                                string type("CONST_FLOAT") ;
                                                SymbolInfo *s = new SymbolInfo() ;
                                                s->setName(name) ;
                                                s->setType(type) ;
                                                yylval = (YYSTYPE) s ;         
                                                return CONST_FLOAT ;
                                            }

\n                         {
                            newline = newline + 1 ;
} 

\'(\\)?{CHARACTERS}\'     {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <CONST_CHAR> Lexeme %s found\n",newline,yytext) ;
                    if(s[1]=='\\'){
                        if(s[2]=='n'){
                            s = "\n" ;
                        }
                        if(s[2]=='t'){
                            s = "\t" ;
                        }
                        if(s[2]=='a'){
                            s = "\a" ;
                        }
                        if(s[2]=='f'){ 
                            s = "\f" ;
                        }
                        if(s[2]=='r'){
                            s = "\r" ;
                        }
                        if(s[2]=='b'){ 
                            s = "\b" ;
                        }
                        if(s[2]=='v'){
                            s = "\v" ;
                        }
                        if(s[2]=='0'){
                            //s = "\0" ;
                        }
                    }
                    else{
                        s = s[1] ;
                    }
                    string name = s ;
                    string type("CONST_CHAR") ;
                    SymbolInfo *symbol = new SymbolInfo() ;
                    symbol->setName(name) ;
                    symbol->setType(type) ;
                    yylval = (YYSTYPE) symbol ;         
                    return CONST_CHAR ;
    }



{ADDOP}         {
                    fprintf(logout,"Line No.%d : Token <ADDOP> Lexeme %s found\n",newline,yytext) ;
                    string name(yytext) ;
                    string type("ADDOP") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return ADDOP ;
                }


{MULOP}         {
                    fprintf(logout,"Line No.%d : Token <ADDOP> Lexeme %s found\n",newline,yytext) ;
                    string name(yytext) ;
                    string type("MULOP") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return MULOP ;
                }


{INCOP}         {
                    fprintf(logout,"Line No.%d : Token <INCOP> Lexeme %s found\n",newline,yytext) ; 
                    string name(yytext) ;
                    string type("INCOP") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return INCOP ; 
                }

{DECOP}         {
                    fprintf(logout,"Line No.%d : Token <DECOP> Lexeme %s found\n",newline,yytext) ; 
                    string name(yytext) ;
                    string type("DECOP") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return DECOP ; 
                }

{RELOP}         {
                    fprintf(logout,"Line No.%d : Token <RELOP> Lexeme %s found\n",newline,yytext) ;
                    string name(yytext) ;
                    string type("RELOP") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return RELOP ;
                }

{COMMENT}       {
                string s(yytext) ;
                fprintf(logout,"Line No.%d : Token <COMMENT> Lexeme",newline) ;
                for(int i=0;i<s.size();i++){
                        if(s[i]=='\n'){
                            newline++ ;
                        }
                        fprintf(logout,"%c",s[i]) ;
                }

                fprintf(logout," found\n") ;
}

{MULTILINECOMMENT}  {
                string s(yytext) ;
                fprintf(logout,"Line No.%d : Token <COMMENT> Lexeme ",newline) ;
                for(int i=0;i<s.size();i++){
                        if(s[i]=='\n'){
                            newline++ ;
                        }
                        fprintf(logout,"%c",s[i]) ;
                }
                fprintf(logout," found\n") ;
}


{UFMLCOMMENT}  {
            string s(yytext) ;
            fprintf(logout,"Error at Line:%d : Unfinished Comment ",newline) ;
            fprintf(logout,"Line No.%d : Token <COMMENT> Lexeme ",newline) ;
            for(int i=0;i<s.size();i++){
                    if(s[i]=='\n'){
                        newline++ ;
                    }
                    fprintf(logout,"%c",s[i]) ;
            }
            fprintf(logout," \n")   ;
            errors++ ;        
}

{ASSIGNOP}         {
                    fprintf(logout,"Line No.%d : Token <ASSIGNOP> Lexeme %s found\n",newline,yytext) ;       
                    return ASSIGNOP ;
                }

{LOGICOP}       {
                    fprintf(logout,"Line No.%d : Token <LOGICOP> Lexeme %s found\n",newline,yytext) ;
                    string name(yytext) ;
                    string type("LOGICOP") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return LOGICOP ;
                }

{BITOP}         {
                    fprintf(logout,"Line No.%d : Token <BITOP> Lexeme %s found\n",newline,yytext) ;
                    string name(yytext) ;
                    string type("BITOP") ;
                    SymbolInfo* s ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return BITOP ;
                }

{NOT}           {
                    fprintf(logout,"Line No.%d : Token <NOT> Lexeme %s found\n",newline,yytext) ;       
                    return NOT ;
                }

{LPAREN}         {
                    fprintf(logout,"Line No.%d : Token <LPAREN> Lexeme %s found\n",newline,yytext) ;        
                    return LPAREN ; 
                }

{RPAREN}         {
                    fprintf(logout,"Line No.%d : Token <RPAREN> Lexeme %s found\n",newline,yytext) ;         
                    return RPAREN ; 
                }

{LCURL}         {
                    fprintf(logout,"Line No.%d : Token <LCURL> Lexeme %s found\n",newline,yytext) ;         
                    return LCURL ; 
                }

{RCURL}         {
                    fprintf(logout,"Line No.%d : Token <RCURL> Lexeme %s found\n",newline,yytext) ;       
                    return RCURL ; 
                }

{LTHIRD}        {
                    fprintf(logout,"Line No.%d : Token <LTHIRD> Lexeme %s found\n",newline,yytext) ;        
                    return LTHIRD ;   
                }

{RTHIRD}         {
                    fprintf(logout,"Line No.%d : Token <RTHIRD> Lexeme %s found\n",newline,yytext) ;         
                    return RTHIRD ; 
                }

{COMMA}         {
                    fprintf(logout,"Line No.%d : Token <COMMA> Lexeme %s found\n",newline,yytext) ;
                    return COMMA ;
                }

{SEMICOLON}         {
                    fprintf(logout,"Line No.%d : Token <SEMICOLON> Lexeme %s found\n",newline,yytext) ;
                    return SEMICOLON ;
                }

{STRING}        {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <STRING> Lexeme ",newline) ;
                    for(int i=0;i<s.size();i++){
                            if(s[i]=='\n'){
                                newline++ ;
                            }
                            fprintf(logout,"%c",s[i]) ;
                    }
                    fprintf(logout," \n")   ;
                    string tem ;
                    for(int i=1;i<s.size()-1;i++){
                        if(s.at(i)=='\\' && s.at(i+1)=='n'){
                            tem += "\n" ;
                            i = i + 2;
                        }
                        
                        if(s.at(i)=='\\' && s.at(i+1)=='t'){
                            tem += "\t" ;
                            i = i + 1;
                        }
                        else if(s.at(i)=='\\' && s.at(i+1)=='"'){
                            tem += "\"" ;
                            i = i + 1 ;
                        }    
                        else if(s.at(i)=='\\' && s.at(i+1)=='\\'){
                            tem += "\\" ;
                            i = i + 1 ;
                        }
                        else if(s.at(i)=='\\' && (s[i]!='n' | s[i]!='t')){
                            i = i+1 ;
                        }
                        else tem += s[i] ; ;
                    }

                    /*string name = s  ;
                    string type("STRING") ;
                    SymbolInfo *symbol ;
                    symbol->setName(name) ;
                    symbol->setType(type) ;
                    yylval = (YYSTYPE) symbol ;         
                    return STRING ;*/
                }

{ID} {
                    fprintf(logout,"Line No.%d : Token <ID> Lexeme %s found\n",newline,yytext) ; 
                    string name(yytext) ;
                    string type("ID") ;
                    SymbolInfo *s = new SymbolInfo() ;
                    s->setName(name) ;
                    s->setType(type) ;
                    yylval = (YYSTYPE) s ;         
                    return ID ;
                }

%%