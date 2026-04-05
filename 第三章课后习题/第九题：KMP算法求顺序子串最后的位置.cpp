//KMP求最后一次顺序子串出现的位置
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
void getnextval(mystring& s,int*nextval){
	int k=s.length;
	int i=s.length-1;
	nextval[i]=s.length;
	while(i>0){
		if(k==s.length||s.data[i]==s.data[k]){
			k--;
			i--;
			if(s.data[i]==s.data[k]){
				nextval[i]=nextval[k];
			}
			else{
				nextval[i]=k;
			}
		}
		else{
			k=nextval[k];
		}
	}
}
int KMP(mystring& s, mystring& t) {
    // 1. 【核心修正】：最先进行物理拦截，绝对防御非法输入
    if (s.length < t.length || t.length == 0) {
        return -1; 
    }

    // 2. 【核心修正】：符合 C++ 规范的堆区动态内存申请
    int* nextval = new int[t.length];
    
    getnextval(t, nextval); // 你的逻辑完全正确，直接调用
    
    int i = s.length - 1;
    int j = t.length - 1;
    
    while (i >= 0 && j >= 0) {
        // 3. 【核心修正】：增加 j == t.length 短路拦截
        // 这等效于标准 KMP 中的 j == -1
        if (j == t.length || s.data[i] == t.data[j]) {
            i--;
            j--;
        } else {
            j = nextval[j];
        }
    }
    
    int result = -1;
    if (j < 0) {
        result = i + 1; // 找准真实坐标
    }
    
    // 4. 【核心修正】：用完必须销毁，维持物理内存的绝对干净
    delete[] nextval; 
    
    return result;
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
	cout<<KMP(s1,s2);
} 
