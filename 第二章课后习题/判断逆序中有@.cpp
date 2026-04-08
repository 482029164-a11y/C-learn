#include<iostream>
#include<string>
#include<sstream>
//这个题目需要注意，栈的长度每次pop之后都会改变，所以要在函数一开始的时候就要记录当前栈的长度 
using namespace std;
const int maxsize=100;
class my_stack{
	public:
		char*data;
		int length;
		int cap;
	my_stack(){
		cap=maxsize;
		length=0;
		data=new char[cap];
	}
	~my_stack(){
		delete[]data;
	}
	void recap(int c){
		char*olddata=data;
		data=new char[c]; 
		for(int i=0;i<length;i++){
			data[i]=olddata[i];
		}
		cap=c;
		delete[]olddata;
	}
	void push(char x){
		if(length==cap){
			recap(2*cap);
		}
		data[length]=x;
		++length;
	}
	void gettop(char&e){
		if(length==0){
			return;
		}
		else{
			e=data[length-1];
		}
	}
	void pop(char&e){
		if(length==0){
			return; 
		} 
		else{
			e=data[length-1];
			--length;
		}
	}
};
bool panduan(my_stack& s){
	int original_len = s.length; // 【核心修正】：用常量锁死初始长度，防止边界坍缩
	if(original_len % 2 == 0){
		return false;
	}
	
	my_stack s1;
	char c, x;
	int i = 0;
	int half = original_len / 2; // 计算出一半的数量
	
	// 阶段 1：前半段逆序入辅助栈 s1
	while(i < half){
		s.pop(c);
		s1.push(c);
		i++;
	}
	
	// 阶段 2：校验中心轴
	s.pop(c);
	if(c != '@'){
		return false;
	}
	
	// 阶段 3：用 s 里面剩余元素的数量来控制循环，绝对安全
	while(s.length > 0){ 
		s.pop(c);
		s1.pop(x);
		if(x != c){
			return false;
		}
	}
	
	return true;
}
int main(){
	string line;
	getline(cin,line);
	stringstream ss(line);
	char x;
	my_stack s;
	while(ss>>x){
		s.push(x);
	}
	if(panduan(s)){
		cout<<"是正确结构"<<endl; 
	}
	else{
		cout<<"不是正确结构"<<endl;
	}
	return 0;
} 
