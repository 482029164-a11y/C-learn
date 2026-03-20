#include<iostream>
using namespace std;
#include<string>
template<class T>
class sqlist{
	public:
		int maxsize;
		T* data;//首地址 
		int top;
		int mintop;
	sqlist(){
		maxsize=100;
		top=-1;
		data=new T[maxsize];
		mintop=-1;
	} //构造函数 
	~sqlist(){
		delete[]data;
	}//析构函数
	bool empty(){
		if(top==-1){
			return true;
		}
		return false; 
	}//判断顺序栈为空
	bool push(T e){
		if(top+1==maxsize){
			return false;
		}//元素个数达到上限 
		data[top+1]=e;
		top++; 
		return true; 
	}//在栈顶插入元素 
	bool pop(T&e){
		if(empty()){
			return false;
		}//栈是空的返回false
		e=data[top];
		top--; 
		return true; 
	}//删除栈顶元素
	bool gettop(T&e) {
		if(empty()){
			return false;
		}//栈是空的返回false
		e=data[top];
		return true; 
	}//取栈顶元素
}; 
//下面是顺序栈的算法设计
//1.用户输入括号是否达标
bool inputkuo(char c[],int num){
	sqlist<char>l;
	for(int i=0;i<num;i++)
	{
		if(c[i]=='(' || c[i]=='[' || c[i]=='{')
		{
			l.push(c[i]);
		}
		else if(c[i]=='}'){
			if(l.empty()){
				return false;
			}//如果为空直接结束 
			char top;
			l.pop(top);
			if(top!='{'){
			return false;
			}	
		}
		else if(c[i]==']'){
			if(l.empty()){
				return false;
			}
			char top;
			l.pop(top);
			if(top!='['){
			return false;
			}
		}
		else if(c[i]==')'){
			if(l.empty()){
				return false;
			}
			char top;
			l.pop(top);
			if(top!='('){
			return false;
			}
		}
		else{
			return false;
		}//别的字符输出假； 
	}
	return l.empty();//如果是正常情况，结束时就是空的 
}
//2.设计一个回文判断程序 
bool isPalindrome(string str){
	sqlist<char>l;
	int num=str.length();//获取字符串的长度
	int n=num/2;//只需要进行一半就行了，出栈出一半，和正常的一半比较就可以
	for(int i=0;i<n;i++){
		l.push(str[i]);
	} 
	int start=(num % 2 == 0) ? n : n + 1;//是偶数就从下一个开始，不是偶数就跳一个再开始 
	for(int i=start;i<num;i++){
		char temp;
		l.pop(temp);
		if(str[i]!=temp){
			return false;
		} 
	}
	return true; 
}
//3.设计最小栈，这个我放在类里面去定义了 
class minstack{
	public:
		int* data;
		int* mindata;
		int maxsize;
		int top;
		int mintop;
		minstack(){
			maxsize=100;
			data=new int[maxsize];
			mindata=new int[maxsize];
			top=-1;
			mintop=-1;
		}
		~minstack(){
			delete[]data;
			delete[]mindata;
		}
		void push(int e){
			if(empty()||e<=mindata[mintop]){
				mindata[++mintop]=e;
			}//这里是小于等于 
			data[++top]=e;
		}
		int pop(){
			int e=data[top];
			if(e==mindata[mintop]){
				mintop--;
			}
			top--;
			return e;
		}
		bool empty(){
			return top==-1;
		}
		bool minempty(){
			return mintop==-1;
		}
		int getmin(){
			return mindata[mintop];
		}
};
int main(){
	char arr[6]={'(','[','{','}',']',')'};
	cout<<inputkuo(arr,6)<<endl;
	string s="abcdcba";
	cout<<isPalindrome(s)<<endl;
	int arr1[]={7,10,3,4,5};
	sqlist<int>l;
	for(int i=0;i<5;i++){
		l.push(arr1[i]);
	}
	minstack l2;
		for(int i=0;i<5;i++){
		l2.push(arr1[i]);
	}
	cout<<l2.getmin()<<endl;
} 
