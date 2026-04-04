//求顺序串中的最大等值字串（长度大于1），如果没有等值字串那么返回空串 
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
void maxstring(mystring& a,mystring& b){
	char c=a.data[0];
	int k_max=0;//记录最大等值的长度 
	int j=0;//记录等值字串的开始下标 
	int k=0;//记录当前等值字串的长度 
	for(int i=0;i<a.length;i++){
		if(a.data[i]==c){
			k++;
			if(k>k_max){
				k_max=k;
				if(b.length!=0&&b.data[0]==c){
					b.push(c);
				}
				else{
					b.length=0;
					for(int m=j;m<i+1;m++){
						b.push(a.data[m]);
					}
				}
			}
		}
		else{
			j=i;
			k=1;
			c=a.data[i];
		}
	}
	if(k_max<=1){
		b.length=0;
	}
}
int main(){
	char a[1000]={};
	int i=0;
	char x;
	string line;
	getline(cin,line);
	stringstream ss(line);
	while(ss>>x){
		a[i]=x;
		i++;
	}
	mystring s1;
	s1.str(a,i);
	s1.print();
	mystring s2;
	maxstring(s1,s2);
	s2.print();
} 
