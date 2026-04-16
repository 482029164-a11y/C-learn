//两串的最长相同前后缀
#include<iostream>
#include<string>
#include<vector>
using namespace std;
void getnext(vector<int>&next,string&s){
	int len=s.length();
	int k=-1;
	int j=0; 
	next[0]=-1;
	while(j<len){
		if(k==-1||s[j]==s[k]){
			k++;
			j++;
			next[j]=k;
		}
		else{
			k=next[k];
		}
	}
}
void the_same(string& s,string& t,string& m){
	//s是前缀串
	//t是后缀串
	 string t1=s+t;
	vector<int>next(t1.length()+1);
	getnext(next,t1);
	int n=next[t1.length()];
	for(int i=0;i<n;i++){
		m+=s[i];
	}
}
int main(){
	freopen("in.txt","r",stdin);
	string s;
	string t;
	getline(cin,s);
	getline(cin,t);
	string m="";
	the_same(s,t,m);
	if(m.length()==0){
		cout<<0;
	}
	else{
		cout<<m<<" "<<m.length();	
	}
}
