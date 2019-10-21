#include <bits/stdc++.h>

using namespace std ;

class node{
private:
	string s ;
	node *prev ;
	node *next ;
public:
	node(string s){
		this->s = s ;
	}

	string getS(){
		return s ;
	}

	void setNext(node *next){
        this->next = next ;
   	 }
	
   	node* getNext(){
   	     return this->next ;
    	}


    	void setPrev(node *prev){
        	this->prev = prev ;
    	}

    	node* getPrev(){
        	return this->prev ;
    	}	
};

class llstring{
private:
    node *head,*tail ;
    int current ;
public:
    llstring(){
        head = 0 ;
        tail = 0 ;
        current = 0 ;
    }

    int insert_first(string name){
        node *temp = new node(name);
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

    string delete_first(){
        int b = 0 ;
        node *temp = head ;
	if(temp==0) return 0 ;
	else{
		head = temp->getNext();
		head->setPrev(0);
		string s = temp->getS();
		free(temp);
		return s ;
	}
    }

};

