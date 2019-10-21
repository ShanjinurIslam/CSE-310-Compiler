int factorial(int n){
	if(n==1) return 1 ;
	else return n*factorial(n-1) ;
}

int main(){
    int i ,j , k,count ;
    count = factorial(5);
    println(count) ; 
}
