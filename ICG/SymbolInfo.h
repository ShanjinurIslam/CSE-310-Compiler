#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std ;

class parameter{
private:
    string param_name ;
    string param_type ;
    string param_asm ;
public:
    parameter(){    
    }

    parameter(string name,string type){
        this->param_name = name ;
        this->param_type = type ;
    }

    parameter(string name,string type,string param_asm){
        this->param_name = name ;
        this->param_type = type ;
        this->param_asm = param_asm ;
    }

    string getParamName(){
        return param_name ;
    }

    string getParamType(){
        return param_type ;
    }

    string getParamASM(){
	return param_asm ;
    }

    void toString(){

    }
};

class func_spec{
private:
    string return_type ;
    int no_of_params ; 
    parameter *param ;
    int current = 0;
public:
    func_spec(){
    }

    func_spec(string return_type,int no_of_params,parameter *param){
        this->return_type = return_type ;
        this->no_of_params = no_of_params ;
        this->param = param ;
    }

    string get_return_type(){ 
        return return_type ;
    }

    int get_no_of_params(){
        return no_of_params ;
    }

    parameter* get_parameters(){
        return param ;
    }

    void printParams(){
        for(int i=0;i<no_of_params;i++){
            param[i].toString();
        }
    }
};
class SymbolInfo{
private:
    string code ;
    string asm_name ;
    string name ;
    string type ;
    string identifier_type ;
    int length ;
    string data_type ;
    func_spec specs ;
    int para ;
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

    SymbolInfo(string name,string type,string data_type){
        this->name = name ;
        this->type = type ;
        this->data_type = data_type ;
        this->identifier_type = "simple_id" ;
        this->length = -1 ;
        prev = next = 0 ;
    }

    SymbolInfo(string name,string type,string data_type,string asm_name){
        this->name = name ;
	this->asm_name = asm_name ;
        this->type = type ;
        this->data_type = data_type ;
        this->identifier_type = "simple_id" ;
        this->length = -1 ;
        prev = next = 0 ;
    }

    SymbolInfo(string name,string type,string data_type,string asm_name,int para){
        this->name = name ;
	this->asm_name = asm_name ;
        this->type = type ;
        this->data_type = data_type ;
        this->identifier_type = "simple_id" ;
	this->para = para ;
        this->length = -1 ;
        prev = next = 0 ;
    }


    SymbolInfo(string name,string type,string data_type,int length){
        this->name = name ;
        this->type = type ;
        this->data_type = data_type ;
        this->identifier_type = "array" ;
        this->length = length ;
        prev = next = 0 ;
    }

    SymbolInfo(string name,string type,string data_type,int length,string asm_name){
	this->asm_name = asm_name ;	
        this->name = name ;
        this->type = type ;
        this->data_type = data_type ;
        this->identifier_type = "array" ;
        this->length = length ;
        prev = next = 0 ;
    }


    SymbolInfo(string name,string type,string identifier_type,func_spec specs){
        this->name = name ;
        this->type = type ;
        this->identifier_type = identifier_type;
        this->specs = specs ;
        this->data_type = specs.get_return_type() ;
        this->length = -2 ;
        prev = next = 0 ;
    }

    int getPara(){
	return para ;
    }
    
    void setasmName(string asm_name){
	this->asm_name =  asm_name ;
    }	
    string getasmName(){
	return asm_name ;
    }
	
    void setCode(string code){
	this->code = code ;
    }

    void setName(string name){
        this->name = name ;
    }

    void set_data_type(string data_type){
        this->data_type = data_type ;
    }

    void setType(string type){
        this->type = type ;
    }

    string getName(){
        return name ;
    }

    string getCode(){
	return code ;
    }

    string get_identifier_type(){
        return identifier_type ;
    }

    string getType(){
        return type ;
    }

    string get_data_type(){
        return data_type ;
    }

    void setLength(int length){
	this->length = length ;
    }

    int getLength(){
        return length ;
    }

    func_spec get_func_spec(){
        return specs ;
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
