#include <iostream>
#include <string>

using namespace std;

const int maxsize = 100;

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
    
    // 【补充】：客观上必须拥有的析构函数，防止内存泄漏
    ~mystring() {
        delete[] data;
    }

    void recap(int c) {
        if (c <= this->cap) return;
        
        char* olddata = data;
        data = new char[c];
        for (int i = 0; i < this->length; i++) {
            data[i] = olddata[i];
        }
        delete[] olddata; // 释放旧内存
        cap = c;
    }

    int getlength() const {
        return this->length;
    }

    // 修复赋值错位问题
    void str(const char a[], int num) {
        for (int i = 0; i < num; i++) {
            if (this->length == cap) {
                recap(2 * cap); // 扩容一般是扩当前容量的2倍，不是长度
            }
            // 永远插入到当前物理长度的末尾
            data[this->length] = a[i];
            length++;
        }
    }
};

// 【核心修复】：传引用，绝对避免野指针和性能浪费
bool huiwen(const mystring& s) {
    if (s.length == 0) return true; // 空串客观上也是回文
    
    int i = 0;
    int j = s.length - 1;
    
    // 【核心修复】：极简的双指针相向运动模型
    while (i < j) {
        if (s.data[i] != s.data[j]) {
            return false;
        }
        i++; 
        j--;
    }
    return true;
}

int main() {
    // 既然用了 C++，直接用 getline 获取带空格的原始输入
    string line;
    if (getline(cin, line)) {
        mystring s1;
        // line.c_str() 可以直接把 string 转成底层的 char 数组
        s1.str(line.c_str(), line.length());
        
        if (huiwen(s1)) {
            cout << "是回文" << endl; 
        } else {
            cout << "不是回文" << endl;
        }
    }
    return 0;
}
