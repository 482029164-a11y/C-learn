#include<iostream>
#include<sstream>
#include<string>
#include<queue>
using namespace std;
void change(queue<int>&q){
	queue<int>q1;
	int l=q.size();
	int e;
	for(int i=1;i<=l;i++){
		if(i%2==0){
			e=q.front();
			q.pop();
			q.push(e);
		}
		else{
			e=q.front();
			q.pop();
			q1.push(e);
		}
	}
	l=q1.size();
	for(int j=0;j<l;j++){
		e=q1.front();
		q1.pop();
		q.push(e);
	}
}
int main(){
	string line;
	 getline(cin,line);
	 stringstream ss(line);
	 int x;
	 queue<int>q1;
	 while(ss>>x){
	 	q1.push(x);
	 }
	 change(q1);
	 while(!q1.empty()){
	 	cout<<q1.front()<<" ";
	 	q1.pop();
	 }
}
