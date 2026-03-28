#include<iostream>
#include<string>
#include<sstream> 
using namespace std;
//这个题目需要学到的是：	string trash; getline(cin, trash);//以后默认都要写这一行 
class mystack{
	public:
		int*data;
		int top;
		int maxsize;
		mystack(int n){
			maxsize=n;
			data=new int[maxsize];
			top=-1;
		}
		~mystack(){
			delete []data;
		}
		bool push(int x){
			if(top==maxsize-1){
				return false;
			}
			else{
				top=top+1;
				data[top]=x;
				return true;
			}
		}
		bool empty(){
			return top==-1;
		}
		bool pop(int &x){
			if(empty()){
				return false;
			}
			else{
				x=data[top];
				--top;
				return true;
			}
		}
		bool gettop(int &x){
			if(empty()){
				return false;
			}
			else{
				x=data[top];
				return true;
			}
		}
		
};//创建顺序栈
class cirqueue{
	public:
		int*data;
		int front;
		int rear;
		int count;
		int maxsize;
		cirqueue(int n){
			maxsize=n;
			data=new int[maxsize];
			front=0;
			rear=0;
			count=0;
		}
		~cirqueue(){
			delete[]data;
		}
		bool is_full(){
			return count==maxsize;
		}
		bool empty(){
			return count==0;
		} 
		bool push(int x){
			if(is_full()){
				return false;
			}
			else{
				data[rear]=x;
				rear=(rear+1)%maxsize;
				++count;
				return true;
			}
		}
		bool pop(int &x){
			if(empty()){
				return false;
			}
			else{
				x=data[front];
				front=(front+1)%maxsize;
				--count;
				return true;
			}
		}
		bool getfront(int &x){
			if(empty()){
				return false;
			}
			else{
				x=data[front];
				return true;
			}
		}
		void print(){
			int i=0;
			int head=front;
			while(i!=count){
				cout<<data[head]<<" ";
				head=(head+1)%maxsize;
				i++;
			}
			cout<<endl;
		}	
}; 
int main(){
	int num;//循环队列的长度
	cin>>num;
	string trash;
    getline(cin, trash);
	string line;
	getline(cin,line);
	stringstream ss(line);
	int x;
	cirqueue q1(num);
	mystack s(num);
	while(ss>>x){
		s.push(x);
	}
	while(!s.empty()){
		s.pop(x);
		q1.push(x);
	}
	q1.print();
} 
