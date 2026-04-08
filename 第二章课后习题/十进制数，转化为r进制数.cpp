//十进制数，转化为r进制数
//要求r进制数用字符串表示
//这题需要知道三个点，1.进制转化怎么做2.余数怎么转化成字符，需要建立一个表3.循环条件是最后数本身不是0 
#include<iostream>
#include<string>
#include<sstream>
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
void jz(int x, int r, my_stack &s1) {
    // 物理拦截 1：处理 x = 0 的绝对虚无状态
    if (x == 0) {
        s1.push('0');
        return;
    }
    
    // 物理拦截 2：处理负数（如果题目可能给负数）
    bool is_negative = false;
    if (x < 0) {
        is_negative = true;
        x = -x;
    }

    // 建立绝对映射字典（查表法）：完美兼容 2 到 36 进制
    const char map[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // 修正 1：剥离直到 x 本身物理清零
    while (x != 0) {
        int mod = x % r;
        // 修正 2：通过查表法，将余数转化为绝对正确的字符
        s1.push(map[mod]); 
        x = x / r;
    }
    
    if (is_negative) {
        s1.push('-'); // 负号最后入栈，打印时会在最前面
    }
}
int main(){
	int x,r;
	cin>>x>>r;
	my_stack s;
	jz(x,r,s);
	string s1;
	char e;
	while(s.length>0){
		s.pop(e);
		s1.push_back(e);
	}
	cout<<s1;
} 
