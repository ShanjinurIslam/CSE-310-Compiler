#include <bits/stdc++.h>

using namespace std ;

ofstream out("symboltable_log.txt") ;
int llpos = -1;
string print ;

class parameter{
private:
    string param_name ;
    string param_type ;
public:
    parameter(){    
    }

    parameter(string name,string type){
        this->param_name = name ;
        this->param_type = type ;
    }

    string getParamName(){
        return param_name ;
    }

    string getParamType(){
        return param_type ;
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
    string name ;
    string type ;
    string identifier_type ;
    int length ;
    string data_type ;
    func_spec specs ;
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

    SymbolInfo(string name,string type,string data_type,int length){
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

    string get_identifier_type(){
        return identifier_type ;
    }

    string getType(){
        return type ;
    }

    string get_data_type(){
        return data_type ;
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


class LinkedList{
private:
    SymbolInfo *head,*tail ;
    int current ;
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

        llpos = 0 ;
        return current ;
    }

    int insertSymbol(string name,string type,string data_type){
        SymbolInfo *temp = new SymbolInfo(name,type,data_type) ;
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

        llpos = 0 ;
        return current ;
    }

    int insertSymbol(string name,string type,string data_type,int length){
        SymbolInfo *temp = new SymbolInfo(name,type,data_type,length) ;
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

        llpos = 0 ;
        return current ;
    }

    int insertSymbol(string name,string type,string data_type,func_spec specs){
        SymbolInfo *temp = new SymbolInfo(name,type,data_type,specs) ;
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

    SymbolInfo* getSymbol(string name){
        int pos = 0 ;
        SymbolInfo *temp = head ;
        while (temp!=0){
            if(temp->getName()==name){
                return temp ;
            }
            temp = temp->getNext();
            pos++ ;
        }
        return 0 ;
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
            out<<"<"<<temp->getName()<<","<<temp->getType()<<","<<temp->get_data_type()<<"> ";
	    print  += "<" + temp->getName()+","+temp->getType()+"> " ;	
            temp = temp->getNext() ;
        }
    }
};

class ScopeTable{
private:
    LinkedList *list ;
    int scopeNum ;
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

    SymbolInfo* getSymbol(string name){
        int index = hash_function(name) ;
        SymbolInfo *temp = list[index].getSymbol(name);
        return temp ;
    }

    int insertSymbol(string name,string type){
        int index = hash_function(name) ;
        if(list[index].searchSymbol(name)==-1){
            list[index].insertSymbol(name,type) ;
            return index ;
        }
        return -1;
    }

    int insertSymbol(string name,string type,string data_type){
        int index = hash_function(name) ;
        if(list[index].searchSymbol(name)==-1){
            list[index].insertSymbol(name,type,data_type) ;
            return index ;
        }
        return -1;
    }

    int insertSymbol(string name,string type,string data_type,int length){
        int index = hash_function(name) ;
        if(list[index].searchSymbol(name)==-1){
            list[index].insertSymbol(name,type,data_type,length) ;
            return index ;
        }
        return -1;
    }

    int insertSymbol(string name,string type,string data_type,func_spec specs){
        int index = hash_function(name) ;
        if(list[index].searchSymbol(name)==-1){
            list[index].insertSymbol(name,type,data_type,specs) ;
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
            out<<i<<" --> " ;
	    print += to_string(i) + " --> " ;
            list[i].printList() ;	
            out<<endl ;
	    print += "\n" ;	
        }
    }

    ~ScopeTable(){
        delete list ;
        delete parentScope ;
    }

    ScopeTable(int hashSize,int scopeNum){
        this->hashSize = hashSize ;
	this->scopeNum = scopeNum ;
        list = new LinkedList[hashSize] ;
        parentScope = 0 ;
    }

    int getScopeNum(){
	return scopeNum ; 
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
    int scope_num ;
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
        tables = new ScopeTable(hashSize,1) ;
        current++ ;
	    scope_num = current ;
    }

    bool insertSymbol(string name,string type){
        int pos = tables->insertSymbol(name,type) ;
        if(pos!=-1){
            out<<" Inserted in ScopeTable#"<<tables->getScopeNum()<<" at position "<<pos<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            out<<" Already Exists in ScopeTable#"<<tables->getScopeNum()<<endl ;
            return false ;
        }
    }

    bool insertSymbol(string name,string type,string data_type){
        int pos = tables->insertSymbol(name,type,data_type) ;
        if(pos!=-1){
            out<<" Inserted in ScopeTable#"<<tables->getScopeNum()<<" at position "<<pos<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            out<<" Already Exists in ScopeTable#"<<tables->getScopeNum()<<endl ;
            return false ;
        }
    }

    bool insertSymbol(string name,string type,string data_type,int length){
        int pos = tables->insertSymbol(name,type,data_type,length) ;
        if(pos!=-1){
            out<<" Inserted in ScopeTable#"<<tables->getScopeNum()<<" at position "<<pos<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            out<<" Already Exists in ScopeTable#"<<tables->getScopeNum()<<endl ;
            return false ;
        }
    }

    bool insertSymbol(string name,string type,string data_type,func_spec specs){
        int pos = tables->insertSymbol(name,type,data_type,specs) ;
        if(pos!=-1){
            out<<" Inserted in ScopeTable#"<<tables->getScopeNum()<<" at position "<<pos<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            out<<" Already Exists in ScopeTable#"<<tables->getScopeNum()<<endl ;
            return false ;
        }
    }

    bool searchSymbol(string name){
        ScopeTable *temp = tables ;
        int i = 0;
        int index = tables->searchSymbol(name) ;
        if(index!=-1){
            out<<" Found in ScopeTable# "<<temp->getScopeNum()<<" at position "<<index<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            /*while(temp!=0){
                index = temp->searchSymbol(name) ;
                if(index!=-1){
                    out<<" Found in ScopeTable# "<<temp->getScopeNum()<<" at position "<<index<<" , "<<llpos<<endl ;
                    return true ;
                }
                temp = temp->getParent();
                i++ ;
            }*/
        }

        if(index==-1){
            out<<name<<" Not found"<<endl ;
            return false ;
        }
    }

    SymbolInfo* getSymbol(string name){
        ScopeTable *temp = tables ;
        int i = 0;
        SymbolInfo *symbol = tables->getSymbol(name) ;
        if(symbol!=0){
            return symbol ;
        }
        else{
            while(temp!=0){
                symbol = temp->getSymbol(name) ;
                if(symbol!=0){
                    return symbol ;
                }
                temp = temp->getParent();
                i++ ;
            }
            return 0 ;
        }
    }

    bool deleteSymbol(string name){
        ScopeTable *temp = tables ;
        int i = 0;
        int index = temp->deleteSymbol(name) ;
        if(index!=-1){
            out<<" Deleted from Current ScopeTable# "<<temp->getScopeNum()<<" at position "<<index<<" , "<<llpos<<endl ;
            return true ;
        }

        else{
            while(temp!=0){
                index = temp->deleteSymbol(name) ;
                if(index!=-1){
                    out<<" Deleted from ScopeTable# "<<temp->getScopeNum()<<" at position "<<index<<" , "<<llpos<<endl ;
                    return true ;
                }
                temp = temp->getParent();
                i++ ;
            }
        }

        if(index==-1){
            out<<name<<" Not found"<<endl ;
            return false ;
        }
    }

    string printCurrent(){
        tables->printTable() ;
    }

    string printAll(){
        ScopeTable *temp = tables ;
        int i = 0;
        while(temp!=0){
            out<<" Scope : "<<temp->getScopeNum()<<endl<<endl ;
	    print += " Scope : " + to_string(temp->getScopeNum()) + "\n" ;
            temp-> printTable() ;
            temp = temp->getParent();
            i++ ;
        }
	string t = print ;
	print = "" ;
	return t ;
    }
    string enterScope(){
	current++ ;
	scope_num = current ;
        ScopeTable *temp = new ScopeTable(hashSize,scope_num) ;
        temp->setParent(tables) ;
        tables = temp ;
        out<<"Entered into new scope ScopeTable with id "<<scope_num<<endl ;
	return "Entered into new scope ScopeTable with id " + to_string(scope_num) + "\n" ;
    }

    string exitScope(){
        ScopeTable *temp = tables ;
	scope_num = temp->getScopeNum();
        tables = tables->getParent() ;
        free(temp) ;
        out<<"ScopeTable with id "<<scope_num<<" removed"<<endl ;
	return "ScopeTable with id " + to_string(scope_num) + " removed" + "\n" ;
    }
};

