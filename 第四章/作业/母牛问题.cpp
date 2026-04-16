#include<iostream>
#include<string>
using namespace std;
int num(int n){
	if(n==1){
		return 1;
	}
	if(n==2){
		return 2;
	}
	if(n==3){
		return 3;
	}
	else{
		return num(n-1)+num(n-3);
	}
}
int main(){
	int n;
	freopen("in.txt","r",stdin);
	cin>>n;
	cout<<num(n);
} 
