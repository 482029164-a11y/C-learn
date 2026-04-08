//这题目需要学会的是自己根据sstream去制造to_string函数 
#include<iostream>
#include<string>
#include<stack>
//因为这个题目，没有要求什么类型的栈，所以我就直接用STL库了 
//进栈我就叫做操作0，出栈我就叫做操作1 
using namespace std;
#include <sstream>
// 这是一个绝对兼容远古编译器的自制 "to_string"
string to_string(int i) {
    stringstream ss;  // 建立物理管道
    ss << i;          // 将整数以流的形式灌入管道
    return ss.str();  // 从管道另一端抽出标准字符串
}
void zhuan(int n,string&s1,string&s2){
	int i=1;
	stack<string> sm;
	string train; 
	while(i<=n){
		if(i%2==0){
			train=to_string(i);
			sm.push(train);
			s1.push_back('0');
		}
		else{
			train=to_string(i);
			s2+=train;
			s1.push_back('0');
			s1.push_back('1');
		}
		++i;
	}
	while(!sm.empty()){
		train=sm.top();
		sm.pop();
		s2+=train;
	}
} 
int main(){
	int n;
	cin>>n;
	string op;//操作字符串 
	string ans;//最终结果字符串
	zhuan(n,op,ans);
	cout<<ans<<endl;
	cout<<op;
} 
