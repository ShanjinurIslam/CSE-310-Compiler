%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <cmath>

    using namespace std ;

    int newline = 1 ;
    int errors = 0 ;

    FILE *logout;
    FILE *tokenout;

    int llpos = -1 ;

    class SymbolInfo{
        private:
            string name ;
            string type ;
            SymbolInfo *prev ;
            SymbolInfo *next ;
        public:
            SymbolInfo(){
                prev = next = 0 ;
            }
            SymbolInfo(string name,string type){
                this->name = name ;
                this->type = type ;
                prev = next = 0 ;
            }

            SymbolInfo operator = (SymbolInfo &a){
                this->name = a.name ;
                this->type = a.type ;
                this->prev = a.prev ;
                this->next = a.next ;

                return *this ;
            }

            ~SymbolInfo(){
                free(prev) ;
                free(next) ;
            }

            void setName(string name){
                this->name = name ;
            }


            void setType(string type){
                this->name = type ;
            }

            string getName(){
                return name ;
            }

            string getType(){
                return type ;
            }

            void setNext(SymbolInfo *next){
                this->next = next ;
            }

            SymbolInfo* getNext(){
                return this->next ;
            }


            void setPrev(SymbolInfo *prev){
                this->prev = prev ;
            }

            SymbolInfo* getPrev(){
                return this->prev ;
            }
        } ;


    class LinkedList{
        private:
            SymbolInfo *head,*tail ;
            int current ;
            int len ;
        public:
            LinkedList(){
                head = 0 ;
                tail = 0 ;
                current = 0 ;
            }

            int insertSymbol(string name,string type){
                SymbolInfo *temp = new SymbolInfo(name,type) ;
                if(head==0){
                    temp->setNext(0) ;
                    temp->setPrev(0) ;
                    head = temp ;
                    tail = temp ;
                } else{
                    current++ ;
                    temp->setNext(head) ;
                    head->setPrev(temp) ;
                    temp->setPrev(0) ;
                    head = temp ;
                }
                len++ ;
                llpos = 0 ;
                return current ;
            }

            int searchSymbol(string name){
                int pos = 0 ;
                SymbolInfo *temp = head ;
                while (temp!=0){
                    if(temp->getName()==name){
                        llpos = pos ;
                        return pos ;
                    }
                    temp = temp->getNext();
                    pos++ ;
                }

                return -1 ;
            }

            int deleteSymbol(string name){
                int b = 0 ;
                SymbolInfo *temp = head ;
                if(temp==NULL) return -1;
                else if(temp->getNext()== NULL){
                    if(temp->getName()==name){
                        head = tail = 0 ;
                        free(temp) ;
                        llpos = b ;
                        return b ;
                    }
                    len-- ;
                }

                while (temp!=0){
                    if(temp->getName()==name){
                        if(temp->getPrev()==NULL){
                            temp = temp->getNext() ;
                        }
                        else if(temp->getNext()==NULL){
                            temp->getPrev()->setNext(0) ;
                        }
                        else{
                            temp->getPrev()->setNext(temp->getNext());
                            temp->getNext()->setPrev(temp->getPrev());
                        }
                        len-- ;
                        break ;
                    }
                    temp = temp->getNext() ;
                    b++ ;
                }

                free(temp) ;

                llpos = b ;

                return b ;
            }

            void printList(){
                SymbolInfo *temp = head ;
                if(temp== NULL){
                    return;
                }
                while(temp!=0){
                    fprintf(logout,"<%s,%s>",temp->getName().c_str(),temp->getType().c_str());
                    temp = temp->getNext() ;
                }
            }

            int getLength(){
                return len ;
            }
        };

        class ScopeTable{
            private:
                LinkedList *list ;
                ScopeTable *parentScope ;
                int hashSize ;


                int hash_function(string key){
                    double factor = (sqrt(7)-1)*0.5 ;
                    int hash = 0;
                    for(int i = 0; i < key.size(); ++i)
                    {
                        hash += key[i];
                    }

                    hash *= factor ;
                    return abs(hash%hashSize);
                }
            public:
                ScopeTable(){
                    list = 0 ;
                    parentScope = 0 ;
                    hashSize = 0 ;
                }

                int searchSymbol(string name){
                    int index = hash_function(name) ;
                    int pos = list[index].searchSymbol(name) ;
                    if(pos!=-1){
                        return index ;
                    }
                    else{
                        return -1 ;
                    }
                }

                int insertSymbol(string name,string type){
                    int index = hash_function(name) ;
                    if(list[index].searchSymbol(name)==-1){
                        list[index].insertSymbol(name,type) ;
                        return index ;
                    }
                    return -1;
                }

                int deleteSymbol(string name){
                    int index = hash_function(name) ;
                    int pos = list[index].deleteSymbol(name) ;
                    if(pos!=-1){
                        return index ;
                    }
                    else{
                        return -1 ;
                    }
                }

                void printTable(){
                    for(int i=0;i<hashSize;i++){
                        if(list[i].getLength()>0){
                            fprintf(logout,"%d --> ",i) ;
                            list[i].printList() ;
                            fprintf(logout,"\n") ;
                        }
                    }
                }

                ~ScopeTable(){
                    delete list ;
                    delete parentScope ;
                }

                ScopeTable(int hashSize){
                    this->hashSize = hashSize ;
                    list = new LinkedList[hashSize] ;
                    parentScope = 0 ;
                }

                void setParent(ScopeTable *a){
                    this->parentScope = a ;
                }

                ScopeTable* getParent(){
                    return parentScope ;
                }
            };

        class SymbolTable{
            private:
                ScopeTable *tables ;
                int current ;
                int hashSize ;
            public:
                SymbolTable(){
                    tables = 0 ;
                    current = 0 ;
                    hashSize = 0 ;
                }

                SymbolTable(int hashSize){
                    this->hashSize = hashSize ;
                    this->current = 0 ;
                    tables = new ScopeTable(hashSize) ;
                    current++ ;
                }

                bool insertSymbol(string name,string type){
                    int pos = tables->insertSymbol(name,type) ;
                    if(pos!=-1){
                        return true ;
                    }
                    else{
                        return false ;
                    }
                }

                bool searchSymbol(string name){
                    ScopeTable *temp = tables ;
                    int i = 0;
                    int index = tables->searchSymbol(name) ;
                    if(index!=-1){
                        return true ;
                    }
                    else{
                        while(temp!=0){
                            index = tables->searchSymbol(name) ;
                            if(index!=-1){
                                return true ;
                            }
                            temp = temp->getParent();
                            i++ ;
                        }
                    }

                    if(index==-1){
                        return false ;
                    }
                }

                bool deleteSymbol(string name){
                    ScopeTable *temp = tables ;
                    int i = 0;
                    int index = tables->deleteSymbol(name) ;
                    if(index!=-1){
                        return true ;
                    }

                    else{
                        while(temp!=0){
                            index = tables->deleteSymbol(name) ;
                            if(index!=-1){
                                return true ;
                            }
                            temp = temp->getParent();
                            i++ ;
                        }
                    }

                    if(index==-1){
                        return false ;
                    }
                }

                void printCurrent(){
                    tables->printTable() ;
                }

                void printAll(){
                    ScopeTable *temp = tables ;
                    int i = 0;
                    while(temp!=0){
                        fprintf(logout,"Scope : %d\n",current-i) ;
                        temp-> printTable() ;
                        temp = temp->getParent();
                        i++ ;
                    }
                }
                void enterScope(){
                    ScopeTable *temp = new ScopeTable(hashSize) ;
                    temp->setParent(tables) ;
                    tables = temp ;
                    current++ ;
                }

                void exitScope(){
                    if(current>0){
                        ScopeTable *temp = tables ;
                        tables = tables->getParent() ;
                        free(temp) ;
                        current-- ;
                    }

                    else{
                    }
                }
            };

    SymbolTable symbolTable(7) ;

%}

KEYWORDS (if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue)

DIGITS [0-9]

CHARACTERS .

ADDOP (\+|\-)

MULOP (\*|\/|\%)

INCOP (\+\+|\-\-)

RELOP (\<|\<\=|\>|\>\=|\=\=|\!\=)

ASSIGNOP \=

LOGICOP (\&\&|\|\|)

BITOP (\&|\||\^|\<<|\>>) 

NOT \!

LPAREN \(

RPAREN \)

LCURL \{

RCURL \}

LTHIRD \[

RTHIRD \]

COMMA \,

SEMICOLON \;

WNL [^\\\n][^'\n]

WONL \\[^'\n][^'\n]

STRING \"(([^\n\"]|(\\\"))*(\\\n)*)*\"

UFSTRING \"(([^\n\"]|(\\\"))*(\\\n)*)*

COMMENT \/\/.*(\\\n.*)*?\n

MULTILINECOMMENT \/\*([^*]|\*+[^/*])*\*+\/

UFMLCOMMENT \/\*([^*]|\*+[^/*])*

UNBACKSLASH \'\\'

UNRECOGCHAR [\:$#@]

ALPHANUMERIC [a-zA-Z0-9_]

STRTIDCHAR [a-zA-z_] 

%%

{DIGITS}*\.({DIGITS}+\.)+{DIGITS}* {
                    fprintf(logout,"Error at Line:%d : Too many decimal points %s\n",newline,yytext) ;
                    errors++ ;
                }

{DIGITS}*(\.{DIGITS})*(E[+-]?({DIGITS}*\.{DIGITS}*)+)+    {
                        fprintf(logout,"Error at Line:%d : Ill formed number %s\n",newline,yytext) ;
                        errors++ ;
                } 

{DIGITS}+{STRTIDCHAR}+   {
                            fprintf(logout,"Error at Line:%d : Invalid Suffix on numaric constant or invalid prefix on idetifier %s\n",newline,yytext) ;
                            errors++ ;
                }

{DIGITS}*\.{DIGITS}+(E[+-]?{DIGITS}+)?{STRTIDCHAR}+    {
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

\'{CHARACTERS}                 {
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

{KEYWORDS}      {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <",newline) ;
                    fprintf(tokenout,"<") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",(s[i]-32)) ;
                        fprintf(logout,"%c",(s[i]-32)) ;
                    }
                    fprintf(tokenout,">") ;
                    fprintf(logout,"> Lexeme %s found\n",s.c_str() ) ;
                }

{DIGITS}+       {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <CONST_INT> Lexeme %s found\n",newline,s.c_str()) ;
                    symbolTable.insertSymbol(s,"CONST_INT") ; 
                    symbolTable.printAll() ;
                    fprintf(tokenout,"<CONST_INT,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;   
                }

{DIGITS}*(\.)?{DIGITS}+(E[+-]?{DIGITS}+)?     {
                                                string s(yytext) ;
                                                fprintf(logout,"Line No.%d : Token <CONST_FLOAT> Lexeme %s found\n",newline,s.c_str()) ;
                                                symbolTable.insertSymbol(s,"CONST_FLOAT") ;
                                                fprintf(tokenout,"<CONST_FLOAT,") ;
                                                for(int i=0;i<s.size();i++){
                                                    fprintf(tokenout,"%c",s[i]) ;
                                                }
                                                fprintf(tokenout,">") ;   
                                            }

\n                         {
                            newline = newline + 1 ;
} 

\'(\\)?{CHARACTERS}\'     {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <CONST_CHAR> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<CONST_CHAR,") ;
                    if(s[1]=='\\'){
                        if(s[2]=='n'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\n") ;
                        }
                        if(s[2]=='t'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ;
                            fprintf(tokenout,"\t") ;
                        }
                        if(s[2]=='a'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\a") ;
                        }
                        if(s[2]=='f'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\f") ;
                        }
                        if(s[2]=='r'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\r") ;
                        }
                        if(s[2]=='b'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\b") ;
                        }
                        if(s[2]=='v'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\v") ;
                        }
                        if(s[2]=='0'){
                            symbolTable.insertSymbol(s,"CONST_CHAR") ; 
                            fprintf(tokenout,"\v") ;
                        }
                    }
                    else{
                        for(int i=1;i<s.size()-1;i++){
                            fprintf(tokenout,"%c",s[i]) ;
                        }
                        symbolTable.insertSymbol(s,"CONST_CHAR") ;
                    }
                    symbolTable.printAll() ;
                    fprintf(tokenout,">") ;  
    }



{ADDOP}         {
                    string s(yytext) ; 
                    fprintf(logout,"Line No.%d : Token <ADDOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<ADDOP,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }


{MULOP}         {
                    string s(yytext) ; 
                    fprintf(logout,"Line No.%d : Token <ADDOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<MULOP,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }


{INCOP}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <INCOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<INCOP,") ;
                    for(int i=0;i<s.size();i++){
                        if(s[i]=='\n'){
                            printf("ues") ;
                        }
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{RELOP}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <RELOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<RELOP,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{COMMENT}       {
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
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <ASSIGNOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<ASSIGNOP,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{LOGICOP}       {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <LOGICOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<LOGICOP,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{BITOP}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <BITOP> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<BITOP,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{NOT}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <NOT> Lexeme %s found\n",newline,s.c_str()) ; 
                    fprintf(tokenout,"<NOT,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{LPAREN}         {
                    string s(yytext) ; 
                    fprintf(logout,"Line No.%d : Token <LPAREN> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<LPAREN,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{RPAREN}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <RPAREN> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<RPAREN,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{LCURL}         {
                    string s(yytext) ; 
                    fprintf(logout,"Line No.%d : Token <LCURL> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<LCURL,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{RCURL}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <RCURL> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<RCURL,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{LTHIRD}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <LTHIRD> Lexeme %s found\n",newline,s.c_str()) ; 
                    fprintf(tokenout,"<LTHIRD,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{RTHIRD}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <RTHIRD> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<RTHIRD,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{COMMA}         {
                    string s(yytext) ;
                    fprintf(tokenout,"<COMMA,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{SEMICOLON}         {
                    string s(yytext) ;
                    fprintf(logout,"Line No.%d : Token <SEMICOLON> Lexeme %s found\n",newline,s.c_str()) ;
                    fprintf(tokenout,"<SEMICOLON,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{STRING}        {
                    string s(yytext) ;
                    fprintf(tokenout,"<STRING,") ;
                    fprintf(logout,"Line No.%d : Token <STRING> Lexeme ",newline) ;
                    for(int i=0;i<s.size();i++){
                            if(s[i]=='\n'){
                                newline++ ;
                            }
                            fprintf(logout,"%c",s[i]) ;
                    }
                    fprintf(logout," \n")   ;
                    for(int i=1;i<s.size()-1;i++){
                        if(s.at(i)=='\\' && s.at(i+1)=='n'){
                            fprintf(tokenout,"\n") ;
                            i = i + 2;
                        }
                        
                        if(s.at(i)=='\\' && s.at(i+1)=='t'){
                            fprintf(tokenout,"\t") ;
                            i = i + 1;
                        }
                        else if(s.at(i)=='\\' && s.at(i+1)=='"'){
                            fprintf(tokenout,"\"") ;
                            i = i + 1 ;
                        }    
                        else if(s.at(i)=='\\' && s.at(i+1)=='\\'){
                            fprintf(tokenout,"\\") ;
                            i = i + 1 ;
                        }
                        else if(s.at(i)=='\\' && (s[i]!='n' | s[i]!='t')){
                            i = i+1 ;
                        }
                        else fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

{STRTIDCHAR}{ALPHANUMERIC}* {
                    string s(yytext) ;
                    symbolTable.insertSymbol(s,"ID") ;
                    fprintf(logout,"Line No.%d : Token <ID> Lexeme %s found\n",newline,s.c_str()) ;
                    symbolTable.printAll() ; 
                    fprintf(tokenout,"<ID,") ;
                    for(int i=0;i<s.size();i++){
                        fprintf(tokenout,"%c",s[i]) ;
                    }
                    fprintf(tokenout,">") ;  
                }

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	logout =  fopen("log.txt","w");
	tokenout = fopen("token.txt","w");
	yyin= fin;
	yylex();
    fprintf(logout,"Total Lines : %d\n",newline-1) ;  
    fprintf(logout,"Total Errors : %d\n",errors) ;
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}