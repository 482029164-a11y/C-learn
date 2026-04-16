#include<iostream>
#include<string>
using namespace std;
int strStr(string s, string t){
	int len1=s.length();
	int len2=t.length();
	if(len1<len2){
		return -1;
	}
	int j=0;
	int i=0;
	while(j<len2&&i<len1){
		if(s[i]==t[j]){
			i++;
			j++;
		}
		else{
			i=i-j+1;
			j=0;
		}
	}
	if(j==len2){
		return i-j;
	}
	return -1;
}
int main(){
	freopen("in.txt","r",stdin);
	string s,t;
	getline(cin,s);
	getline(cin,t);
	cout<<strStr(s,t);
} 
