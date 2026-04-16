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
int KMP(string&s,string&t){
	vector<int>next(t.length()+1);
	getnext(next,t);
	int len1=s.length();
	int len2=t.length();
	int i,j;
	i=0;
	j=0;
	int count=0;
	while(i<len1){
		if(j==-1||s[i]==t[j]){
			i++;
			j++;
			if(j==len2){
				count++;
				j=next[j];
			}
		}
		else{
			j=next[j];
		}
	}
	return count;
}
int main(){
	string t;
	string s;
	getline(cin,t);
	getline(cin,s);
	cout<<KMP(s,t);
}
