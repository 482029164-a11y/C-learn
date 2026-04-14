#include<iostream>
#include<string>
#include<sstream>
using namespace std;
string to_str(int num){
	string r;
	stringstream temp_ss; 
	temp_ss << num; 
	r += temp_ss.str();
	return r;
}
string yasuo(string&s){
	char e=s[0];//记录当前的重复字母,初始化为第0个字符 
	int num=0;//记录当前重复的次数，初始化为0 
	int len=s.length();
	string r;//存储压缩后的字符串 
	char x;//记录字符串当前字母 
	for(int i=0;i<len;i++){
		x=s[i];
		if(x==e){
			num++;
		}
		else{
			if(num>1){
				r.push_back(e);
				r+=to_str(num);
				e=x;
			}
			else{
				r.push_back(e);
				e=x;
			} 
			num=1;
		} 
	} 
	if(num>1){
		r.push_back(e);
		r+=to_str(num);
	}
	else{
		r.push_back(x);
	} 
	return r;
}
int main(){
	freopen("in.txt","r",stdin);
	string line;
	getline(cin,line);
	stringstream ss(line);
	string s;
	char x;
	while(ss>>x){
		s.push_back(x);
	}
	string s1=yasuo(s);
	cout<<s1;
}
