#include<iostream>
using namespace std;
//本身求幂操作很简单，但是这里没有用f(n-1)去递归，而是用n/2去递归，非常巧妙，减少了时间复杂度 
int pow(int x,int n){
	if(n==1){
		return x;
	}
	else{
		int p; 
		if(n%2==0){
			p=pow(x,n/2);
			return p*p;
		}
		else{
			p=pow(x,n/2);
			return x*p*p;
		}
	}
}
int main(){
	cout<<pow(2,4);
}
