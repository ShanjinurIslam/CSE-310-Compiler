%{
    #include  <iostream>
    #include <cstdlib>
	#include <vector>
    #include "Symboltable.h"
	#include "LinkedList.h"
	#define YYSTYPE SymbolInfo*
	using namespace std;
	int yyparse(void);
	int yylex(void);
	extern FILE *yyin;
	FILE *fp,*fp2,*fp3 ;
	SymbolTable symbolTable(7) ;
	extern FILE* logout ;
	extern int newline ;
	string func_type(""),f_tem(""),id_dec(""),param(""),prog(""),unit(""),scope(""),stmt(""),per(""),var_dec(""),expre(""),var(""),term(""),type_term(""),se(""),re(""),le(""),a(""),temp(""),argm(""),type(""),arr_var("");
	int tem=0,arr = 0,ft=0;
	vector<parameter> params ;
	vector<string> argms ;
	llstring llist ;
	int total_error = 0 ; 
	void yyerror(char *s)
	{
		total_error++ ;
		fprintf(fp3,"Error at line %d : %s\n",newline,s) ;
	}
%}

%token IF ELSE WHILE INT FLOAT CHAR DOUBLE FOR CONST_FLOAT CONST_INT CONST_CHAR ID COMMA SEMICOLON ADDOP ASSIGNOP RELOP LPAREN RPAREN LCURL RCURL LOGICOP DECOP INCOP MULOP BITOP VOID LTHIRD RTHIRD NOT PRINTLN RETURN 

%nonassoc LTE
%nonassoc ELSE

%%

start : program;

program : program unit {prog+=unit;
		fprintf(fp2,"At line no: %d program : program unit \n\n%s\n\n",newline,prog.c_str());
		unit="";
		}
	| unit {fprintf(fp2,"At line no: %d program : unit \n\n%s\n\n",newline,unit.c_str());
	prog=unit;unit="";
	}
	;
	
unit : var_declaration {unit += var_dec + "\n" ;
	var_dec="" ;
	fprintf(fp2,"At line no: %d unit : var_declaration \n\n%s\n\n",newline,unit.c_str());
	}
     | func_declaration {unit += "\n" ;
	 fprintf(fp2,"At line no: %d unit : func_declaration \n\n%s\n\n",newline,unit.c_str());
	 }
     | func_definition {unit +=  "\n" ;
	 fprintf(fp2,"At line no: %d unit : func_definition \n\n%s\n\n",newline,unit.c_str());
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {parameter *p = new parameter[params.size()]; 
		for(int i=0;i<params.size();i++){
			p[i]=params[i];
		}
		func_spec specs(type,params.size(),p) ; 
		SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ; 
		if(symbol==0){symbolTable.insertSymbol($2->getName(),$2->getType(),"function_dec",specs);}
		else{total_error++ ; fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);} 
		params.clear(); unit += $$->getName() + $2->getName() + "(" + param + ");"; 
		fprintf(fp2,"At line no: %d unit : func_definition \n\n%s\n\n",newline,unit.c_str());}
		| type_specifier ID LPAREN RPAREN SEMICOLON	{func_spec specs(type,0,0) ; SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ; if(symbol==0){symbolTable.insertSymbol($2->getName(),$2->getType(),"function_dec",specs);} else{total_error++ ; fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);}params.clear();unit += $$->getName() + $2->getName() + "() ;" ;fprintf(fp2,"At line no: %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON \n\n%s\n\n",newline,unit.c_str()); }
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN { parameter *p = new parameter[params.size()]; 
				for(int i=0;i<params.size();i++) p[i]=params[i] ; func_spec specs(func_type,params.size(),p) ; 
				SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ; 
				if(symbol==0){symbolTable.insertSymbol($2->getName(),$2->getType(),"function",specs);}
				else{ if(symbol->get_identifier_type()!="function")
				{if(symbol->get_identifier_type()=="function_dec")
				{int a = 1 ; 
				if(specs.get_no_of_params()!=symbol->get_func_spec().get_no_of_params()){a=0;}
				else{ parameter *tem = symbol->get_func_spec().get_parameters() ; for(int i=0;i<specs.get_no_of_params();i++){if(tem[i].getParamName()!=p[i].getParamName()){a=0;} if(tem[i].getParamType()!=p[i].getParamType()){a=0;}} }
				if(specs.get_return_type()!=symbol->get_func_spec().get_return_type()){a=0;}
				if(a==0){total_error++ ; fprintf(fp3,"Error at line %d: Declation and definition does not match\n",newline);} } else{total_error++ ; fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);}}else{ total_error++ ; fprintf(fp3,"Error at line %d : Function already defined\n",newline);}}} compound_statement {unit += $$->getName() +$2->getName() + "(" + param + ")" + scope ; param = scope = "" ; fprintf(fp2,"At line no: %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n%s\n\n",newline,unit.c_str());}
		| type_specifier ID LPAREN RPAREN {func_spec specs(type,0,0) ;
				SymbolInfo *symbol = symbolTable.getSymbol($2->getName()) ;
				if(symbol==0){symbolTable.insertSymbol($2->getName(),$2->getType(),"function",specs);}
				else{ if(symbol->get_identifier_type()!="function")
				{if(symbol->get_identifier_type()=="function_dec")
				{int a=1;
				if(specs.get_no_of_params()!=symbol->get_func_spec().get_no_of_params()){a=0;}
				if(specs.get_return_type()!=symbol->get_func_spec().get_return_type()){a=0;}
				if(a==0){total_error++ ;fprintf(fp3,"Error at line %d: Declation and definition does not match\n",newline);}} else{total_error++ ;fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);}}else{fprintf(fp3,"Error at line %d : Function already defined\n",newline);} } params.clear();unit += type + " " + $2->getName() + "()" ;} compound_statement {unit += scope ; scope = "" ;fprintf(fp2,"At line no: %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n%s\n\n",newline,unit.c_str());}
		;				

parameter_list  : parameter_list COMMA type_specifier ID { param = param + "," + $3->getName() + $4->getName() ;
		parameter p($4->getName(),type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : parameter_list COMMA type_specifier ID\n\n%s\n\n",newline,param.c_str()); 
		}
		| parameter_list COMMA type_specifier {param = param + "," + $3->getName() ;
		parameter p("",type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : parameter_list COMMA type_specifier \n\n%s\n\n",newline,param.c_str()); 
		}
 		| type_specifier ID {func_type = f_tem ;
		 param = $$->getName() + $2->getName() ;
		 parameter p($2->getName(),type);
		 params.push_back(p);
		 fprintf(fp2,"At line no: %d parameter_list  : type_specifier ID\n\n%s\n\n",newline,param.c_str());
		 }
		| type_specifier {func_type = f_tem ; 
		param = $$->getName() ;
		parameter p("",type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : type_specifier \n\n%s\n\n",newline,param.c_str()); 
		}
 		;
 		
compound_statement : LCURL { fprintf(fp2,"%s",symbolTable.enterScope().c_str()); 
			for(int i=0;i<params.size();i++){
			if(params[i].getParamName()!=""){
			symbolTable.insertSymbol(params[i].getParamName(),"ID",params[i].getParamType());
			}
			}
			params.clear(); 
			llist.insert_first(stmt); stmt="";
			} statements RCURL { scope ="{\n" + stmt + "}\n" ;
			stmt="";
			fprintf(fp2,"At line no: %d compound_statement : LCURL statements RCURL\n\n%s\n\n",newline,scope.c_str());
			fprintf(fp2,"%s",symbolTable.printAll().c_str());
			fprintf(fp2,"%s",symbolTable.exitScope().c_str());
			}
 		    | LCURL { fprintf(fp2,"%s",symbolTable.enterScope().c_str()); 
			 for(int i=0;i<params.size();i++){
				 if(params[i].getParamName()!=""){
					 symbolTable.insertSymbol(params[i].getParamName(),"ID",params[i].getParamType());
					 }
				}
				params.clear(); 
				llist.insert_first(stmt); stmt="";
				} RCURL {scope="{\n}" ;
				stmt="";
				fprintf(fp2,"At line no: %d compound_statement : LCURL RCURL\n\n%s\n\n",newline,scope.c_str());
				fprintf(fp2,"%s",symbolTable.printAll().c_str());
				fprintf(fp2,"%s",symbolTable.exitScope().c_str());
				}
 		    ;

 		    
var_declaration : type_specifier declaration_list SEMICOLON {var_dec = $$->getName() + id_dec + " ;" ;id_dec = "" ;
		fprintf(fp2,"At line no: %d var_declaration : type_specifier declaration_list SEMICOLON \n\n%s\n\n",newline,var_dec.c_str());;}
 		 ;
 		 
type_specifier	: INT {SymbolInfo *symbol = new SymbolInfo("int ","keyword"); 
		f_tem = type ; 
		type="int"; 
		$$ = symbol ;
		fprintf(fp2,"At line no: %d type_specifier : INT \n\nint\n\n",newline);}
 		| FLOAT {SymbolInfo *symbol = new SymbolInfo("float ","keyword"); 
		 f_tem = type ; 
		 type="float"; 
		 $$ = symbol ; 
		 fprintf(fp2,"At line no: %d type_specifier : FLOAT \n\nfloat\n\n",newline);}
 		| VOID 	{SymbolInfo *symbol = new SymbolInfo("void ","keyword"); 
		 f_tem = type ; 
		 type="void";
		 $$ = symbol ; 
		 fprintf(fp2,"At line no: %d type_specifier : VOID \nvoid\n\n",newline);}
 		;
 		
declaration_list : declaration_list COMMA ID {id_dec += ","+$3->getName() ; 
			if(!symbolTable.searchSymbol($3->getName()))
			{if(type!="void"){symbolTable.insertSymbol($3->getName(),$3->getType(),type) ;}
			else{total_error++ ;fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);}}
			else{total_error++ ;fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$3->getName().c_str());} 
			fprintf(fp2,"At line no: %d declaration_list : declaration_list COMMA ID\n\n%s\n\n",newline,id_dec.c_str());} 
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD 	{id_dec += "," + $3->getName()+"["+$5->getName()+"]";  
		   if(!symbolTable.searchSymbol($3->getName())){
			   if(type!="void"){symbolTable.insertSymbol($3->getName(),$3->getType(),type,stoi($5->getName().c_str()));}
			   else{total_error++ ;fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);}
			   }else{total_error++ ;fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$3->getName().c_str());} 
			   fprintf(fp2,"At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n%s\n\n",newline,id_dec.c_str());}
 		  | ID	{id_dec = $$->getName(); 
		   if(!symbolTable.searchSymbol($$->getName())){
			   if(type!="void"){symbolTable.insertSymbol($$->getName(),$$->getType(),type) ;
			   }else{total_error++ ;
				   fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
				   }
				   }else{total_error++ ;fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$$->getName().c_str());} 
				   fprintf(fp2,"At line no: %d declaration_list : ID\n\n%s\n\n",newline,id_dec.c_str());}
 		  | ID LTHIRD CONST_INT RTHIRD 	{ id_dec = $$->getName()+"["+$3->getName()+"]"; 
		   if(!symbolTable.searchSymbol($$->getName())){
			   if(type!="void"){
				   symbolTable.insertSymbol($$->getName(),$$->getType(),type,stoi($3->getName().c_str()));
				   }else{total_error++ ;fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
				   }
				   }else{total_error++ ;fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,$$->getName().c_str());} 
				   fprintf(fp2,"At line no: %d declaration_list : LTHIRD CONST_INT RTHIRD\n\n%s\n\n",newline,id_dec.c_str());}
 		  ;
 		  
statements : statement {if(tem==0){stmt+= per + "\n";per="";}
		else{stmt = llist.delete_first()+per;tem=0;}
		fprintf(fp2,"At line no: %d statements : statement\n\n%s\n\n",newline,stmt.c_str());}
	   | statements statement {if(tem==0){stmt+= per + "\n";per="";}
	   else{stmt = llist.delete_first() +per;tem=0;}
	   fprintf(fp2,"At line no: %d statements : statements statement\n\n%s\n\n",newline,stmt.c_str());}
	   ;

statement : var_declaration	{per = var_dec;
		fprintf(fp2,"At line no: %d statement : var_declaration\n\n%s\n\n",newline,var_dec.c_str());
		var_dec="";}
	  | expression_statement {per = expre;
	  $$->setName(per);
	  fprintf(fp2,"At line no: %d statement : expression_statement\n\n%s\n\n",newline,expre.c_str());
	  expre="";}
	  | compound_statement {per=scope;
	  tem=1;
	  $$->setName(per);
	  fprintf(fp2,"At line no: %d statement : compound_statement\n\n%s\n\n",newline,per.c_str());
	  } 
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		  per = "for("+ $3->getName() + $4->getName() + $5->getName() + ")" + per; 
		  $$->setName(per);
		  fprintf(fp2,"At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n%s\n\n",newline,per.c_str());
		  }
	  | IF LPAREN expression RPAREN statement %prec LTE {per= "if("+$3->getName() +")"+per; 
	  $$->setName(per); 
	  fprintf(fp2,"At line no: %d statement : IF LPAREN expression RPAREN statement \n\n%s\n\n",newline,per.c_str());
	  }
	  | IF LPAREN expression RPAREN statement ELSE statement{per= "if("+$3->getName() +")"+ $5->getName() + "else" + $7->getName(); 
	  fprintf(fp2,"At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n%s\n\n",newline,per.c_str());}
	  | WHILE LPAREN expression RPAREN statement {per = "while("+$3->getName()+")"+per ;
	  fprintf(fp2,"At line no: %d statement : WHILE LPAREN expression RPAREN statement statement\n\n%s\n\n",newline,per.c_str());}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON { fprintf(fp2,"PRINTLN LPAREN ID RPAREN SEMICOLON\n println(%s);\n",$3->getName().c_str());}
	  | RETURN expression SEMICOLON {per = "return "+$2->getName()+" ;" ; 
	  fprintf(fp2,"At line no: %d statement : RETURN expression SEMICOLON\n\n%s\n\n",newline,per.c_str());}
	  ;

expression_statement 	: SEMICOLON {expre += ";";
			$$->setName(expre);
			fprintf(fp2,"At line no: %d expression_statement : SEMICOLON\n\n%s\n\n",newline,expre.c_str());
			}			
			| expression SEMICOLON {expre += ";"; 
			$$->setName(expre);
			fprintf(fp2,"At line no: %d expression_statement : expression SEMICOLON\n\n%s\n\n",newline,expre.c_str());
			}
			;
	  
variable : ID {var=$$->getName(); 
	 $$->setName(var); 
	 SymbolInfo *symbol ; 
	 symbol = symbolTable.getSymbol(var); 
	 if(symbol!=0){type = symbol->get_data_type(); 
	 if(symbol->get_identifier_type()=="array"){
		 total_error++ ;
		 fprintf(fp3,"Error at line %d : array-type variable declared but index not found\n",newline);
		 type="";
		 } $$->set_data_type(type);
		} else{
			total_error++ ;
			fprintf(fp3,"Error at line %d : %s is not declared in the Scope\n",newline,var.c_str());} 
			fprintf(fp2,"At line no: %d variable : ID\n\n%s\n\n",newline,var.c_str());}
	 | ID LTHIRD expression RTHIRD {var = $$->getName() + "[" + $3->getName() + "]" ; 
	 arr_var = $$->getName() ; 
	 $$->setName(var); 
	 if($3->get_data_type()!="int"){
		 total_error++ ;
		 fprintf(fp3,"Error at line %d : Array index is non-integer type\n",newline);} 
		 SymbolInfo *symbol ; symbol = symbolTable.getSymbol(arr_var); 
		 if(symbol!=0){type = symbol->get_data_type(); $$->set_data_type(type); 
		 if(symbol->get_identifier_type()!="array"){
			 total_error++ ;
			 fprintf(fp3,"Error at line %d : index used but used variable is not an array\n",newline);}
			} else{total_error++ ;fprintf(fp3,"Error at line %d : %s is not declared in the Scope\n",newline,arr_var.c_str());
			}fprintf(fp2,"At line no: %d variable : ID LTHIRD expression RTHIRD\n\n%s\n\n",newline,var.c_str()); 
			}
	 ;
	 
expression : logic_expression {expre = $$->getName() ; le= $$->get_data_type() ;  
		$$->setName(expre); $$->set_data_type(le) ; le = "" ;
		fprintf(fp2,"At line no: %d expression : logic_expression\n\n%s\n\n",newline,expre.c_str());}
	   | variable ASSIGNOP logic_expression {expre = $$->getName() + "=" + $3->getName() ; le="" ; 
	   type = $$->get_data_type() ; 
	   if(type!=$3->get_data_type() && (type!="" && $3->get_data_type()!="") ){
		   total_error++ ;
		   fprintf(fp3,"Error at line %d : Type Mismatch\n",newline);}  $$->setName(expre);fprintf(fp2,"At line no: %d expression : variable ASSIGNOP logic_expression\n\n%s\n\n",newline,expre.c_str());
	   }	
	   ;
			
logic_expression : rel_expression {le = $$->getName() ; re = $$->get_data_type() ; 
		$$->setName(le); $$->set_data_type(re) ; re = "" ; 
		fprintf(fp2,"At line no: %d logic_expression : rel_expression\n\n%s\n\n",newline,le.c_str());}	
		 | rel_expression LOGICOP rel_expression {le = $$->getName()+$2->getName() + $3->getName() ; 
		 re = "" ;
		 $$->setName(le);
		 $$->set_data_type("int");
		 fprintf(fp2,"At line no: %d logic_expression : rel_expression LOGICOP rel_expression\n\n%s\n\n",newline,le.c_str());}	
		 ; 
			
rel_expression	: simple_expression {re = $$->getName() ; 
		se = $$->get_data_type() ;$$->setName(re);
		$$->set_data_type(se); se=""; 
		fprintf(fp2,"At line no: %d rel_expression : simple_expression\n\n%s\n\n",newline,re.c_str());}
		| simple_expression RELOP simple_expression	{re +=$$->getName()+$2->getName()+$3->getName() ;
		$$->setName(re); $$->setType("int") ; 
		fprintf(fp2,"At line no: %d simple_expression RELOP simple_expression\n\n%s\n\n",newline,re.c_str());} 
		;
				
simple_expression : term {se = term ; term=""; 
		  $$->setName(se);$$->set_data_type(type_term);
		  fprintf(fp2,"At line no: %d simple_expression : term \n\n%s\n\n",newline,se.c_str());}
		  | simple_expression ADDOP term {se = $$->getName() + $2->getName() + term ;
		  term = "" ;
		  $$->setName(se);
		  if(($$->get_data_type()=="float" && type_term=="int")|($$->get_data_type()=="int" && type_term=="float")|($$->get_data_type()=="float" && type_term=="float"))
		  {$$->set_data_type("float");}
		  else if($$->get_data_type()=="int" && type_term=="int"){$$->set_data_type("int");}
		  else $$->set_data_type("") ;
		  fprintf(fp2,"At line no: %d simple_expression : simple_expression ADDOP term\n\n%s\n\n",newline,se.c_str());}
		  ;
					
term :	unary_expression {term += var ; var = "" ; type_term = type ;type = "" ;fprintf(fp2,"At line no: %d term : unary_expression\n\n%s\n\n",newline,term.c_str());}
     |  term MULOP unary_expression {term += $2->getName() + var ;var="";
	 if((type_term=="float" && type=="int")|(type_term=="int" && type=="float") | (type_term=="float" && type=="float"))
	 {type_term = "float"; 
	 if($2->getName()=="%")
	 {total_error++ ;fprintf(fp3,"Error at line %d : Operands of % Operators are not Integers\n",newline);}
	 } 
	 else if((type_term=="int" && type=="int")) {type_term = "int";
	 if($2->getName()=="%"){type_term="int";} }
	 else {type_term= "" ; 
	 if($2->getName()=="%"){type_term=""; total_error++ ;fprintf(fp3,"Error at line %d : Operands of % Operators are not Integers\n",newline);}} 
	 fprintf(fp2,"At line no: %d term : term MULOP unary_expression\n\n%s\n\n",newline,term.c_str());}
     ;

unary_expression : ADDOP unary_expression {var = $$->getName() + var ;fprintf(fp2,"At line no: %d unary_expression : ADDOP factor\n\n%s\n\n",newline,var.c_str());}
		 | NOT unary_expression {var = "!" + var ;fprintf(fp2,"At line no: %d unary_expression :NOT factor\n\n%s\n\n",newline,var.c_str()); }
		 | factor {fprintf(fp2,"At line no: %d unary_expression : factor\n\n%s\n\n",newline,var.c_str());}
		 ;
	
factor	: variable {fprintf(fp2,"At line no: %d factor : variable\n\n%s\n\n",newline,var.c_str());}
	| ID LPAREN argument_list RPAREN {var = $$->getName()+"("+argm+")" ; 
	SymbolInfo *symbol = symbolTable.getSymbol($$->getName()) ; 
	if(symbol!=0){type=symbol->get_data_type() ; 
	if(symbol->get_identifier_type()=="function" || symbol->get_identifier_type()=="function_dec")
	{ func_spec specs = symbol->get_func_spec() ; 
	if(argms.size()==specs.get_no_of_params()){ 
		parameter *p = specs.get_parameters() ; int ap = 0 ; 
		for(int i=0;i<argms.size();i++){if(argms[i]!=p[i].getParamType()){ap=1;break;} 
		} if(ap==1){total_error++ ;
			fprintf(fp3,"Error at line %d : Function arguments type  does not match\n", newline);
			} 
			}else{total_error++ ;
				fprintf(fp3,"Error at line %d : Function argument numbers does not match\n", newline);
				}  
			} else {total_error++ ;
				fprintf(fp3,"Error at line %d : %s is not a function\n",newline, $$->getName().c_str());
				}
			} else{type="" ;total_error++ ;fprintf(fp3,"Error at line %d : %s not declared in the scope\n",newline, $$->getName().c_str());}  
			fprintf(fp2,"At line no: %d factor : variable\n\n%s\n\n",newline,var.c_str());argms.clear(); }
	| LPAREN expression RPAREN {var = "("+expre+")" ; expre=""; 
	type = $2->get_data_type() ;
	fprintf(fp2,"At line no: %d factor : LPAREN expression RPAREN\n\n%s\n\n",newline,var.c_str());}
	| CONST_INT {var = $$->getName() ; type = "int" ;
	fprintf(fp2,"At line no: %d factor : CONST_INT\n\n%s\n\n",newline,var.c_str());}
	| CONST_FLOAT {var = $$->getName() ; type = "float" ;
	fprintf(fp2,"At line no: %d factor : CONST_FLOAT\n\n%s\n\n",newline,var.c_str());}
	| CONST_CHAR {var = $$->getName() ; type = "char" ;
	fprintf(fp2,"At line no: %d factor : CONST_CHAR\n\n%s\n\n",newline,var.c_str());}
	| variable INCOP {var = $$->getName() + $2->getName() ;
	fprintf(fp2,"At line no: %d factor : variable INCOP\n\n%s\n\n",newline,var.c_str());} 
	| variable DECOP {var = $$->getName() + $2->getName() ;
	fprintf(fp2,"At line no: %d factor : variable DECOP\n\n%s\n\n",newline,var.c_str());}
	;
	
argument_list : arguments {fprintf(fp2,"At line no: %d argument_list : arguments\n\n%s\n\n",newline,argm.c_str());}
			  |
			  ;
	
arguments : arguments COMMA logic_expression {argm += "," + $3->getName() ; le= $3->get_data_type()  ; 
			argms.push_back(le) ; fprintf(fp2,"At line no: %d arguments : arguments COMMA logic_expression\n\n%s\n\n",newline,argm.c_str());}
	      | logic_expression {argm = $$->getName() ; le=$$->get_data_type() ;
		   argms.push_back(le) ; fprintf(fp2,"At line no: %d arguments : logic_expression\n\n%s\n\n",newline,argm.c_str());}
	      ;

%%
int main(int argc,char *argv[])
{
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
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
