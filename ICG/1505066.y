%{
    #include  <iostream>
	#include <algorithm>
    #include <cstdlib>
	#include <vector>
    #include "Symboltable.h"
	#define YYSTYPE SymbolInfo*
	using namespace std;
	int yyparse(void);
	int yylex(void);
	extern FILE *yyin;
	FILE *fp,*fp2,*fp3 ;
	SymbolTable symbolTable(7) ;
	extern FILE* logout ;
	extern int newline ;
	string var(""),type_term(""),se(""),re(""),le(""),type(""),arr_var("");
	int tem=0,arr = 0,ft=0;
	
	vector<parameter> params ;
	vector<string> argms ;
	vector<string> args ;
	vector<string> procedures ;
	
	vector<SymbolInfo*> vars ;
	vector<SymbolInfo*> arrays ;
	
	int total_error = 0 ;
	extern int errors ; 

	int labelCount=0;
	int tempCount=0;


	char *newLabel()
	{
		char *lb= new char[4];
		strcpy(lb,"L");
		char b[3];
		sprintf(b,"%d", labelCount);
		labelCount++;
		strcat(lb,b);
		return lb;
	}

	char *newTemp()
	{
		char *t= new char[4];
		strcpy(t,"t");
		char b[3];
		sprintf(b,"%d", tempCount);
		tempCount++;
		strcat(t,b);
		return t;
	}

	void yyerror(char *s)
	{
		total_error++ ;
		fprintf(fp3,"Error at line %d : %s\n\n",newline,s) ;
	}

	string optimize(string code){
		string optimized_code ;
		vector<string> lines = split_string(code,'\n') ;
		for(int i=0;i<lines.size();i++){
			if(lines[i].substr(0,4)=="\tMOV" && lines[i+1].substr(0,4)=="\tMOV"){
				vector<string> r1 = split_string(lines[i].substr(5,lines[i].size()-5),',') ;
				vector<string> r2 = split_string(lines[i+1].substr(5,lines[i+1].size()-5),',') ;
				if(r1[0]==r2[1] && r2[0]==r1[1]){
					optimized_code += lines[i] + "\n" ;
					i = i+1 ;
				}
				else{
					optimized_code += lines[i] + "\n" ;
				}
			}
			else{
				optimized_code += lines[i] + "\n" ;
			}
		}
		return optimized_code ;
	}
%}

%token IF ELSE WHILE RETURN INT FLOAT CHAR DOUBLE FOR CONST_FLOAT CONST_INT CONST_CHAR ID COMMA SEMICOLON ADDOP ASSIGNOP RELOP LPAREN RPAREN LCURL RCURL LOGICOP DECOP INCOP MULOP BITOP VOID LTHIRD RTHIRD NOT PRINTLN 

%nonassoc LTE
%nonassoc ELSE

%%

start : program {
	if(errors==0 && total_error==0){
		FILE *assembly ;
		assembly = fopen("code.asm","w") ;
		fprintf(assembly,".MODEL SMALL\n.STACK 100h\n\n.DATA\n") ;
		fprintf(assembly,"return DW ?\n") ;
		for(int i=0;i<vars.size();i++){
			fprintf(assembly,"%s DW ?\n",vars[i]->getasmName().c_str()) ;
		}

		for(int i=0;i<arrays.size();i++){
			fprintf(assembly,"%s DW %d DUP(?)\n",arrays[i]->getasmName().c_str(),arrays[i]->getLength()*2) ;
		}

		fprintf(assembly,".CODE\n") ;
		string code = optimize($1->getCode()) ;
		fprintf(assembly,"%s",code.c_str()) ;
		fprintf(assembly,"\n\nDECIMAL_OUT PROC NEAR\n\n\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n\tor ax,ax\n \tjge enddif\n\tpush ax\n\tmov dl,'-'\n\tmov ah,2\n\tint 21h\n\tpop ax\n\tneg ax\nenddif:\n\txor cx,cx\n\tmov bx,10d\nrepeat:\n\txor dx,dx\n\tdiv bx\n\t push dx\n\tinc cx\n\tor ax,ax\n\tjne repeat\n\tmov ah,2\nprint_loop:\n\tpop dx\n\tor dl,30h\n\tint 21h\n\tloop print_loop\n\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax\n\tmov ah,2\n\tmov dl,0Dh\n\tint 21h\n\tmov dl,0Ah\n\tint 21h\n\tret\n\nDECIMAL_OUT ENDP\n") ;
		fclose(assembly) ;
	}
};

program : program unit {
		$$ = $1;
		$$->setCode($$->getCode()+$2->getCode()) ;
		fprintf(fp2,"At line no: %d program : program unit \n\n",newline);
		}
	| unit {
		$$ = $1;
		fprintf(fp2,"At line no: %d program : unit \n\n",newline);
	}
	;
	
unit : var_declaration {
		$$ = $1;
		fprintf(fp2,"At line no: %d unit : var_declaration \n\n",newline);
	}
     | func_declaration {
		$$ = $1;
	 	fprintf(fp2,"At line no: %d unit : func_declaration \n\n",newline);
	 }
     | func_definition {
	    $$ = $1;
	 	fprintf(fp2,"At line no: %d unit : func_definition \n\n",newline);
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
		parameter *p = new parameter[params.size()]; 
		for(int i=0;i<params.size();i++){
			p[i]=params[i];
		}
		func_spec specs(type,params.size(),p) ; 
		SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ; 
		if(symbol==0){
			symbolTable.insertSymbol($2->getName(),$2->getType(),"function_dec",specs);
		}
		else{
			total_error++ ; 
			fprintf(fp3,"Error at line %d: Multiple declaration \n",newline);
		} 
		params.clear();
		fprintf(fp2,"At line no: %d unit : func_definition \n\n",newline);
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON	{
			func_spec specs(type,0,0) ; 
			SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ; 
			if(symbol==0){
				symbolTable.insertSymbol($2->getName(),$2->getType(),"function_dec",specs);
			} 
			else{
				total_error++ ; 
				fprintf(fp3,"Error at line %d: Multiple declaration\n\n",newline);
			}
			params.clear();
			fprintf(fp2,"At line no: %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON \n",newline);
			}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN { 
				parameter *p = new parameter[params.size()]; 
				for(int i=0;i<params.size();i++) 
					p[i]=params[i] ; 
				func_spec specs($1->getName(),params.size(),p) ; 
				SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ; 
				if(symbol==0){
					symbolTable.insertSymbol($2->getName(),$2->getType(),"function",specs);
					}
				else{ 
					if(symbol->get_identifier_type()!="function")
					{
						if(symbol->get_identifier_type()=="function_dec")
						{
							int a = 1 ; 
							if(specs.get_no_of_params()!=symbol->get_func_spec().get_no_of_params()){
								a=0;
							}
							else{ 
								parameter *tem = symbol->get_func_spec().get_parameters() ; 
								for(int i=0;i<specs.get_no_of_params();i++)
								{
									if(tem[i].getParamName()!=p[i].getParamName()){
										a=0;
									}
									if(tem[i].getParamType()!=p[i].getParamType()){
										a=0;
									}
								}
							}
						if(specs.get_return_type()!=symbol->get_func_spec().get_return_type()){
							a=0;
						}
					if(a==0){
						total_error++ ; 
						fprintf(fp3,"Error at line %d: Declation and definition does not match\n",newline);
						} 
					} 
					else{
						total_error++ ; 
						fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);
						}
					}
					else{ 
						total_error++ ; 
						fprintf(fp3,"Error at line %d : Function already defined\n",newline);}
						}
					} compound_statement {
						string code ;
						
						if($2->getName()=="main"){
							code = $2->getName() + " PROC\n"+$7->getCode() ;
							$$->setCode(code + "\tMOV AH,4CH\n\tINT 21H\n");
							$$->setCode($$->getCode() + $2->getName() + " ENDP\n\n");

							for(int i = 0 ;i<procedures.size();i++){
								$$->setCode($$->getCode()+procedures[i]) ;
							}

							procedures.clear() ;
							
						}
						else{
							code = $2->getName() + " PROC\n" ;
							code += "\tPUSH BP\n\tMOV BP,SP\n" ;
							code += $7->getCode() ;
							code += "\tPOP BP\n\tRET 2\n" ;
							code += $2->getName() + " ENDP\n\n" ;
							procedures.push_back(code) ;
						}
						fprintf(fp2,"At line no: %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",newline);
					}
		| type_specifier ID LPAREN RPAREN {
				func_spec specs(type,0,0) ;
				SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ;
				if(symbol==0){
					symbolTable.insertSymbol($2->getName(),$2->getType(),"function",specs);
					}
				else{ 
					if(symbol->get_identifier_type()!="function")
					{
						if(symbol->get_identifier_type()=="function_dec")
						{
							int a=1;
						if(specs.get_no_of_params()!=symbol->get_func_spec().get_no_of_params()){
							a=0;
						}
						if(specs.get_return_type()!=symbol->get_func_spec().get_return_type()){
							a=0;
						}
						if(a==0){
							total_error++ ;
							fprintf(fp3,"Error at line %d: Declation and definition does not match\n",newline);
						}
					} 
					else{total_error++ ;
					fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);
					}
					}
					else{fprintf(fp3,"Error at line %d : Function already defined\n",newline);} 
					} 
					params.clear();
					} compound_statement {
						string code = $2->getName() + " PROC\n"+$6->getCode() ;
						
						if($2->getName()=="main"){
							$$->setCode(code + "\tMOV AH,4CH\n\tINT 21H\n");
							$$->setCode($$->getCode() + $2->getName() + " ENDP\n\n");

							for(int i = 0 ;i<procedures.size();i++){
								$$->setCode($$->getCode()+procedures[i]) ;
							}

							procedures.clear() ;
							
						}
						else{
							code += "\tRET\n" ;
							code += $2->getName() + " ENDP\n\n" ;
							procedures.push_back(code) ;
						}
						
						fprintf(fp2,"At line no: %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",newline);
					}
		;				

parameter_list  : parameter_list COMMA type_specifier ID { 
		parameter p($4->getName(),type,$4->getName()+to_string(symbolTable.getScopeNumber()+1));
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : parameter_list COMMA type_specifier ID\n",newline); 
		}
		| parameter_list COMMA type_specifier {
		parameter p("",type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : parameter_list COMMA type_specifier \n",newline); 
		}
 		| type_specifier ID {
		 parameter p($2->getName(),type,$2->getName()+to_string(symbolTable.getScopeNumber()+1));
		 params.push_back(p);
		 fprintf(fp2,"At line no: %d parameter_list  : type_specifier ID\n",newline);
		 }
		| type_specifier {
		parameter p("",type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : type_specifier \n",newline); 
		}
 		;
 		
compound_statement : LCURL { fprintf(fp2,"%s",symbolTable.enterScope().c_str()); 
			for(int i=0;i<params.size();i++){
			if(params[i].getParamName()!=""){
				vars.push_back(new SymbolInfo(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber()))) ;
				symbolTable.insertSymbol(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber()),(i+1)*2);
			}
			}
			params.clear();
			} statements RCURL { 
			$$=$3;
			fprintf(fp2,"At line no: %d compound_statement : LCURL statements RCURL\n",newline);
			fprintf(fp2,"%s",symbolTable.printAll().c_str());
			fprintf(fp2,"%s",symbolTable.exitScope().c_str());
			}
 		    | LCURL { fprintf(fp2,"%s",symbolTable.enterScope().c_str()); 
			 for(int i=0;i<params.size();i++){
				 if(params[i].getParamName()!=""){
					 	vars.push_back(new SymbolInfo(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber())));
					 	symbolTable.insertSymbol(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber()),(i+1)*2);
					}
				}
				params.clear(); 
				} RCURL {
				fprintf(fp2,"At line no: %d compound_statement : LCURL RCURL\n",newline);
				fprintf(fp2,"%s",symbolTable.printAll().c_str());
				fprintf(fp2,"%s",symbolTable.exitScope().c_str());
				}
 		    ;

 		    
var_declaration : type_specifier declaration_list SEMICOLON {
		fprintf(fp2,"At line no: %d var_declaration : type_specifier declaration_list SEMICOLON \n",newline);}
 		;
 		 
type_specifier	: INT {SymbolInfo *symbol = new SymbolInfo("int","keyword");  
		type="int"; 
		$$ = symbol ;
		fprintf(fp2,"At line no: %d type_specifier : INT \n",newline);}
 		| FLOAT {SymbolInfo *symbol = new SymbolInfo("float","keyword"); 
		 type="float"; 
		 $$ = symbol ; 
		 fprintf(fp2,"At line no: %d type_specifier : FLOAT \n",newline);}
 		| VOID 	{SymbolInfo *symbol = new SymbolInfo("void","keyword"); 
		 type="void";
		 $$ = symbol ; 
		 fprintf(fp2,"At line no: %d type_specifier : VOID \n",newline);}
 		;
 		
declaration_list : declaration_list COMMA ID {
			if(!symbolTable.searchSymbol($3->getName()))
			{
				if(type!="void"){
					vars.push_back(new SymbolInfo($3->getName(),$3->getType(),type,$3->getName()+to_string(symbolTable.getScopeNumber())));
					symbolTable.insertSymbol($3->getName(),$3->getType(),type,$3->getName()+to_string(symbolTable.getScopeNumber())) ;
				}
			else{
				total_error++ ;
				fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
				}
			}
			else{
				total_error++ ;
				fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$3->getName().c_str());
			} 
			fprintf(fp2,"At line no: %d declaration_list : declaration_list COMMA ID\n",newline);
			} 
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD 	{ 
		   if(!symbolTable.searchSymbol($3->getName())){
			   if(type!="void"){
				   arrays.push_back(new SymbolInfo($3->getName(),$3->getType(),type,stoi($5->getName().c_str()),$3->getName()+to_string(symbolTable.getScopeNumber())));
				   symbolTable.insertSymbol($3->getName(),$3->getType(),type,stoi($5->getName().c_str()),$3->getName()+to_string(symbolTable.getScopeNumber()));
				}
			   else{
				   total_error++ ;
				   fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
				}
			   }else{
				   total_error++ ;
				   fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$3->getName().c_str());
				} 
			   fprintf(fp2,"At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",newline);}
 		  | ID	{
				if(!symbolTable.searchSymbol($$->getName()))
				{
					if(type!="void"){
						vars.push_back(new SymbolInfo($$->getName(),$$->getType(),type,$$->getName()+to_string(symbolTable.getScopeNumber())));
						symbolTable.insertSymbol($$->getName(),$$->getType(),type,$$->getName()+to_string(symbolTable.getScopeNumber())) ;
					}
					else{
						total_error++ ;
						fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
						}
					}
				else{
					total_error++ ;
					fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$$->getName().c_str());
					} 
					fprintf(fp2,"At line no: %d declaration_list : ID\n",newline);
				}
 		  | ID LTHIRD CONST_INT RTHIRD 	{ 
		   		if(!symbolTable.searchSymbol($$->getName())){

			   		if(type!="void"){
						arrays.push_back(new SymbolInfo($$->getName(),$$->getType(),type,stoi($3->getName().c_str()),$$->getName()+to_string(symbolTable.getScopeNumber()))) ;
						symbolTable.insertSymbol($$->getName(),$$->getType(),type,stoi($3->getName().c_str()),$$->getName()+to_string(symbolTable.getScopeNumber()));
					}
					else{
						total_error++ ;
						fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
					}
				}
				else{
					total_error++ ;
					fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$$->getName().c_str());
				} 
				fprintf(fp2,"At line no: %d declaration_list : LTHIRD CONST_INT RTHIRD\n",newline);}
 		  ;
 		  
statements : statement {
			fprintf(fp2,"At line no: %d statements : statement\n",newline);
			$$ = $1 ;
		}
	   | statements statement {
		    $$ = $1 ;
			$$->setCode($$->getCode()+$2->getCode()) ;
	   		fprintf(fp2,"At line no: %d statements : statements statement\n",newline);
	   }
	   ;

statement : var_declaration	{
			$$ = $1 ;
			fprintf(fp2,"At line no: %d statement : var_declaration\n",newline);
		}
	  | expression_statement {
		  	$$ = $1 ;
	  		fprintf(fp2,"At line no: %d statement : expression_statement\n",newline);
	  }
	  | compound_statement {
		    $$ = $1 ;
	  		fprintf(fp2,"At line no: %d statement : compound_statement\n",newline);
	  } 
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		  	$$ = $3 ;
			char *label1 = newLabel();
			char *label2 = newLabel();
			$$->setCode($$->getCode() + string(label1) + ":\n");
			$$->setCode($$->getCode() + $4->getCode() + "\n");
			$$->setCode($$->getCode() + "\tMOV AX,"+$4->getName()+"\n");
			$$->setCode($$->getCode() + "\tCMP AX , 0\n");
			$$->setCode($$->getCode() + "\tJE "+string(label2)+"\n");
			$$->setCode($$->getCode() + $7->getCode());
			$$->setCode($$->getCode() + $5->getCode());
			$$->setCode($$->getCode() + "\tJMP "+string(label1)+"\n");
			$$->setCode($$->getCode() + string(label2)+":\n");		
			fprintf(fp2,"At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",newline);
		}
	  | IF LPAREN expression RPAREN statement %prec LTE {
	  		$$ = $3 ;
			char *label=newLabel();
			$$->setCode($$->getCode() + "\tMOV AX,"+$3->getName()+"\n\tCMP AX, 0\n\tJE "+string(label)+"\n"+$5->getCode()+string(label)+":\n");
			fprintf(fp2,"At line no: %d statement : IF LPAREN expression RPAREN statement \n",newline);
	  }
	  | IF LPAREN expression RPAREN statement ELSE statement { 
		    $$ = $3 ;
		  	char *label1=newLabel();
			char *label2=newLabel();
			$$->setCode($$->getCode() + "\tMOV AX,"+$3->getName()+"\n\tCMP AX,0\n\tJE "+string(label1)+"\n"+$5->getCode() +"\tJMP "+string(label2)+"\n" + string(label1)+":\n"+$7->getCode()+string(label2)+":\n");
	  		fprintf(fp2,"At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",newline);
	  }
	  | WHILE LPAREN expression RPAREN statement {
		    $$ = $3 ;
			char * label1 = newLabel();
			char * label2 = newLabel();
			$$->setCode($$->getCode() + string(label1) + ":\n" +$3->getCode() + "\tMOV AX,"+$3->getName()+"\n" + "\tCMP ax , 0\n" + "\tJE "+string(label2)+"\n" + $5->getCode() + "\tJMP "+string(label1)+"\n" + string(label2)+":\n");
	  		fprintf(fp2,"At line no: %d statement : WHILE LPAREN expression RPAREN statement statement\n",newline);
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON {
		  	SymbolInfo *temp = symbolTable.getSymbol($3->getName()) ;
			if(temp!=0){
				$$ = new SymbolInfo("println","PRINTFUNC") ;
		   		$$->setCode("\tMOV AX," + symbolTable.getSymbol($3->getName())->getasmName() + "\n\tcall DECIMAL_OUT\n") ;
		  		fprintf(fp2,"At line no: %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n",newline);
			}
			else{
				total_error++ ;
		  		fprintf(fp3,"Error at line no %d : variable is not declared in the scope\n",newline);
			}    
		}
	  | RETURN expression SEMICOLON {
		    $$ = $2 ;
		  	$$->setCode($$->getCode()+ "\tMOV AX," + $2->getName() + "\n\tMOV return,AX\n") ;
	  		fprintf(fp2,"At line no: %d statement : RETURN expression SEMICOLON\n",newline);
		}
	  ;

expression_statement 	: SEMICOLON {
			SymbolInfo* symbol = new SymbolInfo(";","SEMICOLON") ;
			$$ = symbol ;
			$$->setCode("") ;
			fprintf(fp2,"At line no: %d expression_statement : SEMICOLON\n",newline);
			}			
			| expression SEMICOLON {
			$$ = $1 ;
			fprintf(fp2,"At line no: %d expression_statement : expression SEMICOLON\n",newline);
			}
			;
	  
variable : ID {
	 var=$1->getName(); 
	 SymbolInfo *symbol ; 
	 symbol = symbolTable.getSymbol(var);
	 if(symbol!=0){
		 type = symbol->get_data_type(); 
	 	 if(symbol->get_identifier_type()=="array"){
			total_error++ ;
			fprintf(fp3,"Error at line %d : array-type variable declared but index not found\n",newline);
			type="";
		}
		$$->setLength(-1) ;
		if(symbol->getPara()>0){
			$$->setName("[BP + "+ to_string(2+symbol->getPara())+"]") ; 
		}
		else{
			$$->setName(symbol->getasmName()) ; 
		}
		$$->set_data_type(type);

		} 
		else{
			total_error++ ;
			fprintf(fp3,"Error at line %d : %s is not declared in the Scope\n",newline,$1->getName().c_str());
		} 
		fprintf(fp2,"At line no: %d variable : ID\n",newline,var.c_str());
		}
	 | ID LTHIRD expression RTHIRD {
	 	arr_var = $1->getName() ; 
		if($3->get_data_type()!="int"){
			total_error++ ;
			fprintf(fp3,"Error at line %d : Array index is non-integer type\n",newline);
		} 
		SymbolInfo *symbol ; 
		symbol = symbolTable.getSymbol(arr_var); 
		if(symbol!=0){
			$$->setName(symbol->getasmName()) ;
			$$->setLength(symbol->getLength()) ;
			$1->setLength(symbol->getLength()) ;
			
			type = symbol->get_data_type(); 
			$$->set_data_type(type);
			$$->setCode($3->getCode()) ;
			$$->setCode($$->getCode() + "\tMOV BX," +$3->getName() +"\n" + "\tSHL BX, 1\n") ;
			
			delete $3;
			if(symbol->get_identifier_type()!="array"){
			 	total_error++ ;
			 	fprintf(fp3,"Error at line %d : index used but used variable is not an array\n",newline);}
			} 
			else{
				total_error++ ;
				fprintf(fp3,"Error at line %d : %s is not declared in the Scope\n",newline);
			}
			fprintf(fp2,"At line no: %d variable : ID LTHIRD expression RTHIRD\n",newline,var.c_str()); 
		}
	 ;
	 
expression : logic_expression {
		$$ = $1 ;
		fprintf(fp2,"At line no: %d expression : logic_expression\n",newline);
		}
	   | variable ASSIGNOP logic_expression { 
	   		type = $1->get_data_type() ; 
			if(type!=$3->get_data_type() && (type!="" && $3->get_data_type()!="") ){
				total_error++ ;
				fprintf(fp3,"Error at line %d : Type Mismatch\n",newline);
			}  
			fprintf(fp2,"At line no: %d expression : variable ASSIGNOP logic_expression\n",newline);
			$$ = $1 ;
			$$->setCode($3->getCode()+$1->getCode() + "\tMOV AX,"+$3->getName()+"\n") ;
			if($1->getLength()>=0){
				$$->setCode($$->getCode() + "\tMOV " + $1->getName() + "[BX],AX\n" ) ;
			}
			else{
				$$->setCode($$->getCode() + "\tMOV " + $1->getName() + ",AX\n" ) ;
			}

			delete $3 ;
	   }	
	   ;
			
logic_expression : rel_expression {
		$$ = $1 ;
		fprintf(fp2,"At line no: %d logic_expression : rel_expression\n",newline);}	
		 | rel_expression LOGICOP rel_expression {
		 $$ = $1 ;
		 char *temp = newTemp() ;
		 char *label1=newLabel();
		 char *label2=newLabel();
		 
		 if($2->getName()=="&&"){
			$$->setCode($$->getCode() + "\tMOV AX," + $1->getName() +"\n\tCMP AX , 0\n\tJE " + string(label1) +"\n\tMOV AX," + $3->getName() +"\n\tCMP AX , 0\n\tJE " + string(label1) +"\n\tMOV " + string(temp) + " , 1\n");
			$$->setCode($$->getCode() + "\tJMP " + string(label2) + "\n" + string(label1) + ":\n" + "\tMOV " + string(temp) + ", 0\n" + string(label2) + ":\n") ;
			$$->setName(temp);
			$$->setasmName(string(temp));
			vars.push_back($$) ;
		 }

		 if($2->getName()=="||"){
			$$->setCode($$->getCode() + "\tMOV AX," + $1->getName() +"\n\tCMP AX , 1\n\tJE " + string(label1) +"\n\tMOV AX," + $3->getName() +"\n\tCMP AX , 1\n\tJE " + string(label1) +"\n\tMOV " + string(temp) + " , 0\n");
			$$->setCode($$->getCode() + "\tJMP " + string(label2) + "\n" + string(label1) + ":\n" + "\tMOV " + string(temp) + ", 1\n" + string(label2) + ":\n") ;
			$$->setName(temp);
			$$->setasmName(string(temp)) ;
			vars.push_back($$) ;
		 }

		 $$->set_data_type("int");
		 fprintf(fp2,"At line no: %d logic_expression : rel_expression LOGICOP rel_expression\n",newline);
		 delete $3 ;
		 }	
		 ; 
			
rel_expression	: simple_expression {
			$$ = $1 ;
			fprintf(fp2,"At line no: %d rel_expression : simple_expression\n",newline);
		}
		| simple_expression RELOP simple_expression	{
			$$ = $1 ;
			char *temp=newTemp();
			char *label1=newLabel();
			char *label2=newLabel();
			
			$$->setCode($$->getCode() + $3->getCode()) ;
			$$->setCode($$->getCode() + "\tMOV AX," + $1->getName()+"\n" + "\tCMP AX, " + $3->getName()+"\n") ;
			if($2->getName()=="<"){
					$$->setCode($$->getCode() +"\tJL " + string(label1)+"\n");
			}
			else if($2->getName()=="<="){
				$$->setCode($$->getCode() +"\tJLE " + string(label1)+"\n");
			}
			else if($2->getName()==">"){
				$$->setCode($$->getCode() +"\tJG " + string(label1)+"\n");
			}
			else if($2->getName()==">="){
				$$->setCode($$->getCode() +"\tJGE " + string(label1)+"\n");
			}
			else if($2->getName()=="=="){
				$$->setCode($$->getCode() +"\tJE " + string(label1)+"\n");
			}
			else{
				$$->setCode($$->getCode() +"\tJNE " + string(label1)+"\n");
			}
				
			$$->setCode($$->getCode() + "\tMOV "+string(temp) +", 0\n" +"\tJMP "+string(label2) +"\n" + string(label1)+":\n\tMOV "+string(temp)+", 1\n" + string(label2)+":\n");
			$$->set_data_type("int") ;
			$$->setName(string(temp)) ;

			SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
			symbol->setasmName(symbol->getName()) ;
		  	vars.push_back(symbol) ;
			
			fprintf(fp2,"At line no: %d simple_expression RELOP simple_expression\n",newline);
			delete $3 ;
		} 
	;
				
simple_expression : term {
		  $$ = $1 ;
		  $$->set_data_type(type_term);
		  fprintf(fp2,"At line no: %d simple_expression : term \n",newline,se.c_str());
		  }
		  | simple_expression ADDOP term {
		  $$ = $1 ;	  
		  if(($$->get_data_type()=="float" && type_term=="int")|($$->get_data_type()=="int" && type_term=="float")|($$->get_data_type()=="float" && type_term=="float"))
		  {
			  $$->set_data_type("float");
		  }
		  else if($$->get_data_type()=="int" && type_term=="int"){
			  $$->set_data_type("int");
		  }
		  else $$->set_data_type("") ;
		  fprintf(fp2,"At line no: %d simple_expression : simple_expression ADDOP term\n",newline);

		  $$->setCode($$->getCode()+$3->getCode() + "\tMOV AX,"+ $1->getName()+"\n" + "\tMOV BX,"+ $3->getName() +"\n") ;
		  char *temp = newTemp() ;//does it needs to be added to the vars array????
		  
		  if($2->getName()=="+"){
			  $$->setCode($$->getCode() + "\tADD AX,BX\n" + +"\tMOV "+ string(temp) + ",AX\n") ;  
		  }

		  if($2->getName()=="-"){
			  $$->setCode($$->getCode() + "\tSUB AX,BX\n" + +"\tMOV "+ string(temp) + ", AX\n") ;  
		  }	

		  $$->setName(string(temp)) ; 
		  
		  SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
		  symbol->setasmName(symbol->getName()) ;
		  vars.push_back(symbol) ;

		  delete $3 ;
		  }
		  ;
					
term :	unary_expression {
			$$ = $1 ;
			type_term = type ;
			$$->set_data_type(type_term) ;
			fprintf(fp2,"At line no: %d term : unary_expression\n",newline);
		}
     |  term MULOP unary_expression {
		$$ = $1 ; 
		type_term = $1->get_data_type() ; 
	 	if((type_term=="float" && type=="int")|(type_term=="int" && type=="float") | (type_term=="float" && type=="float"))
	 	{
			 type_term = "float"; 
	 	if($2->getName()=="%")
	 	{
			 type_term = "int" ; 
			 total_error++ ;
			 fprintf(fp3,"Error at line %d : Operands of % Operators are not Integers\n",newline);}
	 	} 
	 	else if((type_term=="int" && type=="int")) {
			 type_term = "int"; 
	 	}
		else {
			type_term= "" ; 
	 		if($2->getName()=="%"){
				 type_term="int"; 
				 total_error++ ;
				 fprintf(fp3,"Error at line %d : Operands of % Operators are not Integers\n",newline);
				 }
		}
		$$->set_data_type(type_term) ;
		$$->setCode($$->getCode()+$3->getCode() + "\tMOV AX,"+ $1->getName()+"\n" + "\tMOV BX,"+ $3->getName() +"\n") ;
		char *temp = newTemp() ;
		if($2->getName()=="*"){
			//without using temp
			$$->setCode($$->getCode()+"\tMUL BX\n"+"\tMOV "+ string(temp) + ",AX\n") ;
		}
		else if($2->getName()=="/"){
			$$->setCode($$->getCode()+"\tMOV DX , 0\n\tDIV BX\n"+"\tMOV "+ string(temp) + ",AX\n") ;
		}

		else{
			$$->setCode($$->getCode()+"\tMOV DX , 0\n\tDIV BX\n"+"\tMOV "+ string(temp) + ",DX\n") ;
		}
		$$->setName(string(temp)) ; 
		
		SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
		symbol->setasmName(symbol->getName()) ;
		vars.push_back(symbol) ;
		/// printf("%s",$$->getCode().c_str()) ; //check ICG generation
		delete $3;
	 	fprintf(fp2,"At line no: %d term : term MULOP unary_expression\n",newline);}
     ;

unary_expression : ADDOP unary_expression {
			 if($1->getName()=="+"){
				$$ = $2 ;
			 }
			 else if($1->getName()=="-"){
				 $$ = $2;
				 char *temp=newTemp();
				 $$->setCode($$->getCode() + "\tMOV AX," + $2->getName() + "\n" + "\tNEG AX\n" + "\tMOV " + string(temp) + ",AX\n");
			 	 SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
				 symbol->setasmName(symbol->getName()) ;
		         vars.push_back(symbol) ;
			 }
			 fprintf(fp2,"At line no: %d unary_expression : ADDOP factor\n",newline);
		 }
		 | NOT unary_expression {
			 $$ = $2 ;
			 char *temp=newTemp();
			 $$->setCode($$->getCode()+"\tMOV AX," + $2->getName() + "\n" + "\tNOT AX\n" + "\tMOV "+$2->getName()+",AX") ;
			 fprintf(fp2,"At line no: %d unary_expression :NOT factor\n",newline); 
			 }
		 | factor {
			 $$ = $1 ;
			 fprintf(fp2,"At line no: %d unary_expression : factor\n",newline);
		}
		 ;
	
factor	: variable {
			fprintf(fp2,"At line no: %d factor : variable\n",newline);
			if($1->getLength()>=0){
				char *temp = newTemp() ;
				$$->setCode($1->getCode() + "\tMOV AX," + $1->getName() + "[BX]\n" + "\tMOV " + string(temp) + ",AX\n") ;
				$$->setName(string(temp)) ; 

				SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
				symbol->setasmName(symbol->getName()) ;
		  		vars.push_back(symbol) ;
			}
			else{
				$$ = $1 ;
			}
			
		}
	| ID LPAREN argument_list RPAREN {
		$$ = $3 ;
		SymbolInfo *symbol = symbolTable.getSymbol($1->getName()) ;
		string code ; 
		if(symbol!=0){
			type=symbol->get_data_type() ; 
			if(symbol->get_identifier_type()=="function" || symbol->get_identifier_type()=="function_dec")
			{ 
				func_spec specs = symbol->get_func_spec() ; 
					if(argms.size()==specs.get_no_of_params()){ 
						parameter *p = specs.get_parameters() ; 
						int ap = 0 ; 
						for(int i=0;i<argms.size();i++){
							if(argms[i]!=p[i].getParamType())
							{
								ap=1;
								break;
							}
							if(p[i].getParamName()!=""){
								code += "\tMOV AX," + args[i] + "\n";
								code += "\tPUSH AX\n" ; 
							}
							else{
								// cause it does nothing :-) 
							}
						}


					if(ap==1){
						total_error++ ;
						fprintf(fp3,"Error at line %d : Function arguments type  does not match\n", newline);
					}
				}


				else{
					total_error++ ;
					fprintf(fp3,"Error at line %d : Function argument numbers does not match\n", newline);
				}  
			} 
			else {
				total_error++ ;
				fprintf(fp3,"Error at line %d : %s is not a function\n",newline, $$->getName().c_str());
			}
		} 
		else{
			type="" ;
			total_error++ ;
			fprintf(fp3,"Error at line %d : %s not declared in the scope\n",newline);
		}  
		fprintf(fp2,"At line no: %d factor : variable\n",newline);
		char *temp = newTemp() ;
		code += "\tCALL " + $1->getName() + "\n" ;
		code += "\tMOV AX, return\n\tMOV " + string(temp) + ",AX\n" ; 
		$$->setName(string(temp)) ;
		SymbolInfo* t = new SymbolInfo(string(temp),"ID") ;
		t->setasmName(string(temp)) ;
		vars.push_back(t) ;
		$$->setCode($3->getCode() + code) ;
		argms.clear();
		args.clear() ;
		}
	| LPAREN expression RPAREN {
		$$ = $2;
		type = $2->get_data_type() ;
		fprintf(fp2,"At line no: %d factor : LPAREN expression RPAREN\n",newline);
		}
	| CONST_INT {
		$$ = $1;
		type = "int" ;
		fprintf(fp2,"At line no: %d factor : CONST_INT\n",newline);
		}
	| CONST_FLOAT {
		$$ = $1;
		type = "float" ;
		fprintf(fp2,"At line no: %d factor : CONST_FLOAT\n",newline);
		}
	| CONST_CHAR {
		$$ = $1;
		type = "char" ;
		fprintf(fp2,"At line no: %d factor : CONST_CHAR\n",newline);
		}
	| variable INCOP {
		fprintf(fp2,"At line no: %d factor : variable INCOP\n",newline);
		$$ = $1;
		$$->setCode($$->getCode()+"\tMOV AX ," + $$->getName()+ "\n" + "\tADD AX , 1\n" + "\tMOV " + $$->getName() + " ,AX\n") ;
		} 
	| variable DECOP {
		fprintf(fp2,"At line no: %d factor : variable DECOP\n",newline);
		$$ = $1;
		$$->setCode($$->getCode()+"\tMOV AX ," + $$->getName()+ "\n" + "\tSUB AX , 1\n" + "\tMOV " + $$->getName() + " ,AX\n") ;
	}
	;
	
argument_list : arguments {
					$$ = $1 ;
					fprintf(fp2,"At line no: %d argument_list : arguments\n",newline);
				}
			  |{$$ = new SymbolInfo();}
			  ;
	
arguments : arguments COMMA logic_expression {
				$$ = $1 ;
				$$->setCode($$->getCode() + $3->getCode()) ;
			  	args.push_back($3->getName()) ;
				le= $3->get_data_type()  ; 
				argms.push_back(le) ; 
				fprintf(fp2,"At line no: %d arguments : arguments COMMA logic_expression\n",newline);

				delete $3 ;
			}
	      | logic_expression {
			  $$ = $1 ;
			  args.push_back($$->getName()) ;
			  le=$$->get_data_type() ;
		   	  argms.push_back(le) ; 
		   	  fprintf(fp2,"At line no: %d arguments : logic_expression\n",newline);
		   }
	      ;

%%
int main(int argc,char *argv[])
{
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp2= fopen(argv[2],"a");

	fp3= fopen(argv[3],"w");
	fclose(fp3);
	fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	symbolTable.printAll();
	fclose(fp) ;
	fprintf(fp2,"%s",symbolTable.printAll().c_str());
	fclose(fp2);
	fprintf(fp3,"Total Error : %d",total_error);
	fclose(fp3);
	fclose(logout) ;
	return 0;
}
