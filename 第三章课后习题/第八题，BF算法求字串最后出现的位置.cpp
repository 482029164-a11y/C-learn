//顺序串存储，BF算法在串S中找到子串T最后一次出现的位置 
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;
const int maxsize = 100;
// 自定义顺序串类
class mystring {
public:
    char* data;
    int length;
    int cap;

    mystring() {
        cap = maxsize;
        data = new char[cap];
        length = 0;
    }
    
    // 【客观必需】：析构函数，防止物理内存泄漏
    ~mystring() {
        delete[] data;
    }

    // 动态扩容
    void recap(int c) {
        if (c <= this->cap) return;
        
        char* olddata = data;
        data = new char[c];
        for (int i = 0; i < this->length; i++) {
            data[i] = olddata[i];
        }
        delete[] olddata; 
        cap = c;
    }

    int getlength() const {
        return this->length;
    }

    // 批量赋值
    void str(const char a[], int num) {
        for (int i = 0; i < num; i++) {
            if (this->length == cap) {
                recap(2 * cap); 
            }
            data[this->length] = a[i];
            length++;
        }
    }
    
    // 追加单个字符（已修复吞字漏洞）
    void push(char x) {
        if (length == cap) {
            recap(2 * cap);
        }
        data[length] = x;
        length++;
    }

    // 打印当前串
    void print() const {
        for (int i = 0; i < length; i++) {
            cout << data[i];
        }
        cout << endl;
    }
};
int BF(mystring &s,mystring &t){
	int j=s.length-1;
	int i=t.length-1;
	int match=0;
	if(j<i||i==-1){
		return -1;
	}
	while(j>=0&&i>=0){
		if(s.data[j]==t.data[i]){
			i--;
			j--;
			match++;
		}
		else{
			j=j+match-1;
			i=t.length-1;
			match=0;
		}
	}
	if(i<0){
		return j+1;
	}
	else{
		return -1;
	}
}
int main(){
	char a[1000]={};
	char b[1000]={};
	int i1=0;
	int i2=0;
	char x;
	string line1;
	string line2;
	getline(cin,line1);
	stringstream ss1(line1);
	while(ss1>>x){
		a[i1]=x;
		i1++;
	}
	getline(cin,line2);
	stringstream ss2(line2);
	while(ss2>>x){
		b[i2]=x;
		i2++;
	}
	mystring s1;
	s1.str(a,i1);
	s1.print();
	mystring s2;
	s2.str(b,i2);
	s2.print();
	cout<<BF(s1,s2);
} 
