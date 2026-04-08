#include<iostream>
#include<string>
#include<stack>
using namespace std;
//记得函数引用要加&，不然值传递，实参没变 
void jz(int x,int r,stack<char>&s){
	if(x==0){
		s.push('0');
		return;
	}
	bool fu=false;
	if(x<0){
		fu=true;
		x=-x;
	}
	int mod;
	const char map[]="0123456789ABCDEF";
	while(x!=0){
		mod=x%r;
		s.push(map[mod]);
		x=x/r;
	}
	if(fu){
		s.push('-');
	}
}
int main(){
	stack<char>s1;
	int x,r;
	cin>>x>>r;
	jz(x,r,s1);
	string s;
	char e;
	while(!s1.empty()){
		e=s1.top();
		s1.pop();
		s.push_back(e);
	}
	cout<<s;
} 
