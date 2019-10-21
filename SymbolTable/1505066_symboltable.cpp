#include <bits/stdc++.h>

using namespace std ;

ofstream out("output.txt") ;
int llpos = -1;

vector<string> split_string(string input,char sep){
    vector<string> v ;
    size_t start = 0, end = 0;
    while ((end = input.find(sep, start)) != std::string::npos) {
        v.push_back(input.substr(start, end - start));
        start = end + 1;
    }
    v.push_back(input.substr(start));
    return v;
}

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
            cout<<"<"<<temp->getName()<<","<<temp->getType()<<"> ";
            out<<"<"<<temp->getName()<<","<<temp->getType()<<"> ";
            temp = temp->getNext() ;
        }
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
            cout<<" " ;
            cout<<i<<" --> " ;
            out<<i<<" --> " ;
            list[i].printList() ;
            cout<<endl ;
            out<<endl ;
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
            cout<<" Inserted in ScopeTable# 1 at position "<<pos<<" , "<<llpos<<endl ;
            out<<" Inserted in ScopeTable# 1 at position "<<pos<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            cout<<" Already Exists in ScopeTable# 1"<<endl ;
            out<<" Already Exists in ScopeTable# 1 at"<<endl ;
            return false ;
        }
    }

    bool searchSymbol(string name){
        ScopeTable *temp = tables ;
        int i = 0;
        int index = tables->searchSymbol(name) ;
        if(index!=-1){
            cout<<" Found in ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
            out<<" Found in ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
            return true ;
        }
        else{
            while(temp!=0){
                index = tables->searchSymbol(name) ;
                if(index!=-1){
                    cout<<" Found in ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
                    out<<" Found in ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
                    return true ;
                }
                temp = temp->getParent();
                i++ ;
            }
        }

        if(index==-1){
            cout<<name<<" Not found"<<endl ;
            out<<name<<" Not found"<<endl ;
            return false ;
        }
    }

    bool deleteSymbol(string name){
        ScopeTable *temp = tables ;
        int i = 0;
        int index = tables->deleteSymbol(name) ;
        if(index!=-1){
            cout<<" Deleted from Current ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
            out<<" Deleted from Current ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
            return true ;
        }

        else{
            while(temp!=0){
                index = tables->deleteSymbol(name) ;
                if(index!=-1){
                    cout<<" Deleted from ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
                    out<<" Deleted from ScopeTable# "<<current<<" at position "<<index<<" , "<<llpos<<endl ;
                    return true ;
                }
                temp = temp->getParent();
                i++ ;
            }
        }

        if(index==-1){
            cout<<name<<" Not found"<<endl ;
            out<<name<<" Not found"<<endl ;
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
            cout<<" Scope : "<<current-i<<endl<<endl ;
            out<<" Scope : "<<current-i<<endl<<endl ;
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

        cout<<"Entered into new scope ScopeTable with id "<<current<<endl ;
        out<<"Entered into new scope ScopeTable with id "<<current<<endl ;
    }

    void exitScope(){
        ScopeTable *temp = tables ;
        tables = tables->getParent() ;
        free(temp) ;

        cout<<"ScopeTable with id "<<current<<" removed"<<endl ;
        out<<"ScopeTable with id "<<current<<" removed"<<endl ;
        current-- ;


    }
};

int main(){
    ifstream in ;
    in.open("input.txt") ;
    string input_line ;
    getline(in,input_line);
    int hashSize = (int)(input_line[0]-'0') ;
    SymbolTable s(hashSize) ;
    while(getline(in,input_line)){
        cout<<input_line<<endl<<endl ;
        out<<input_line<<endl<<endl ;
        vector<string> v = split_string(input_line,' ') ;
        if(v[0]=="I"){
            s.insertSymbol(v[1],v[2]) ;
        }
        if(v[0]=="L"){
            s.searchSymbol(v[1]);
        }
        if(v[0]=="S"){
            s.enterScope() ;
        }

        if(v[0]=="E"){
            s.exitScope() ;

        }
        if(v[0]=="D"){
            s.deleteSymbol(v[1]);
        }
        if(v[0]=="P"){
            if(v[1]=="A"){
                s.printAll() ;
            }
            if(v[1]=="C"){
                s.printCurrent() ;
            }
        }
        cout<<endl ;
        out<<endl ;
    }
    in.close() ;
    out.close() ;
    return 0 ;
}

