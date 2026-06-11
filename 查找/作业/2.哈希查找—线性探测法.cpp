//哈希查找
#include<iostream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<cmath>
#include<vector> 
using namespace std;
int main(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int dest;//查找目标
	cin>>dest;
	string line,trash;//无序正整数序列，用来构建哈希表
	getline(cin,trash);
	getline(cin,line);
	stringstream ss(line);
	vector<int> v;//哈希表
	v.resize(200,0);//题目要求200长度,并初始化为0 
	int x;
	while(ss>>x){
		int h=x%199;
		while(v[h]!=0){
			h=(h+1)%200;
		} 
		v[h]=x;//线性探针法 
	}  
	int begin_index=dest%199;
	int count=0;
	vector<int> path;
	while(v[begin_index]!=dest&&v[begin_index]!=0&&count<=200){
		path.push_back(v[begin_index]);
		begin_index=(begin_index+1)%200;
		count++;
	}
	if(v[begin_index]!=0){
		path.push_back(v[begin_index]);
	}
	if(count>200||v[begin_index]==0){
		cout<<"False"<<endl;
	}
	else{
		cout<<"True"<<endl;
	}
	for(int i=0;i<(int)path.size();i++){
		cout<<path[i]<<" ";
	}
} 
