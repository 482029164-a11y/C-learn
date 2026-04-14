/*（1）输入规则：第一行输入正整数n（表示需判断的算术表达式对数/测试用例数，1≤n≤20）；

后续输入n对算术表达式，每对表达式各占一行（无空行），单个表达式长度不超过20个字符。

（2）表达式构成：包含运算符（ + 、-、*、/）、运算数（一位数字或单个大小写区别的字母）、正确匹配且可嵌套的圆括号；输入表达式均为合法格式（无语法错误）。

（3）计算规则：除号"/"按整数除法规则计算（结果取整，例如5/3结果为 1）；必须通过逆波兰式（后缀表达式）完成表达式的计算逻辑。*/
#include<iostream>
#include<string>
#include<stack>
using namespace std;
double calculate(string s){
	string postexp;
	stack<char> oprand;
	stack<int>num;
	int len=s.length();
	char x;
	char e;
	for(int i=0;i<len;i++){
		x=s[i];
		if(x=='('||oprand.empty()){
			oprand.push(x);
		}
		else if(x=='+'||x=='-'){
			while(!oprand.empty()){
				e=oprand.top();
				if(e!='('){
					postexp.push_back(e);
					oprand.pop();
				}
				else{
					break;
				}
			}
			oprand.push(x);
		}
		else if(x=='*'||x=='/'){
			while(!oprand.empty()){
				e=oprand.top();
				if(e=='*'||e=='/'){
					postexp.push_back(e);
					oprand.pop();
				}
				else{
					break;
				}
			}
			oprand.push(x);
		}
		else if(x==')'){
			while(!oprand.empty()){
				e=oprand.top();
				if(e=='('){
					oprand.pop();
					break;
				}
				else{
					postexp.push_back(e);
					oprand.pop();
				}
			}
		}
		else{
			postexp.push_back(x);
		}
	}
	while(!oprand.empty()){
		x=oprand.top();
		oprand.pop();
		postexp+=x;
	}
	int len1=postexp.length();
	for(int i=0;i<len1;i++){
		int t1,t2;
		x=postexp[i];
		if(x=='+'){
			t1=num.top();
			num.pop();
			t2=num.top();
			num.pop();
			num.push(t2+t1);
		}
		else if(x=='-'){
			t1=num.top();
			num.pop();
			t2=num.top();
			num.pop();
			num.push(t2-t1);
		}
		else if(x=='*'){
			t1=num.top();
			num.pop();
			t2=num.top();
			num.pop();
			num.push(t2*t1);
		}
		else if(x=='/'){
			t1=num.top();
			num.pop();
			t2=num.top();
			num.pop();
			num.push(t2/t1);
		}
		else{
			num.push(x-'0');
		}
	}
	double result=num.top();
	return result;
}
bool is_match(string&s1,string&s2){
	int d1=calculate(s1);
	int d2=calculate(s2);
	if(d1==d2){
		return true;
	}
	return false;
} 
int main(){
	int n;
	cin>>n;
	string s1;
	string s2;
	for(int i=0;i<n;i++){
		cin>>s1>>s2;
		if(is_match(s1,s2)){
			cout<<"TRUE"<<endl;
		}
		else{
			cout<<"FALSE"<<endl;
		}
	} 
} 
