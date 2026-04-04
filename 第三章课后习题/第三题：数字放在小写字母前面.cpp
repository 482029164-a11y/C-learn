//顺序串中含有数字和小写字母，把数字都放在顺序串的前面
//三种方法，不同的要求
//无论哪种方法都要搞懂 #include <cctype>咋用的 
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

    // ==========================================
    // 方法一：双指针首尾交换法 (时间 O(N), 空间 O(1), 破坏顺序)
    // ==========================================
    void paixu_unstable_twopointer() {
        int i = 0;
        int j = length - 1;
        while (i < j) {
            // 左找字母，右找数字
            while (i < j && isdigit(data[i])) i++;
            while (i < j && isalpha(data[j])) j--;
            
            // 发生物理互换
            if (i < j) {
                char temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                i++;
                j--;
            }
        }
    }

    // ==========================================
    // 方法三：相邻交换冒泡法 (时间 O(N^2), 空间 O(1), 绝对稳定)
    // ==========================================
    void paixu_stable_bubble() {
        for (int i = 0; i < length; i++) {
            if (isdigit(data[i])) {
                int j = i;
                // 数字像气泡一样向左挤掉字母
                while (j > 0 && isalpha(data[j - 1])) {
                    char temp = data[j];
                    data[j] = data[j - 1];
                    data[j - 1] = temp;
                    j--;
                }
            }
        }
    }
};

// ==========================================
// 方法二：开辟新数组异地分拣 (时间 O(N), 空间 O(N), 绝对稳定)
// 【注意】：为了防止浅拷贝导致的内存崩溃，参数必须加 const &
// ==========================================
void paixu_stable_newarray(const mystring& a, mystring& b) {
    for (int i = 0; i < a.length; i++) {
        if (isdigit(a.data[i])) {
            b.push(a.data[i]);
        }
    }
    for (int i = 0; i < a.length; i++) {
        if (isalpha(a.data[i])) {
            b.push(a.data[i]);
        }
    }
}

int main() {
    // 模拟一段包含数字和字母，且能明显看出顺序的测试数据
    // 预期字母顺序：a, b, c；预期数字顺序：1, 2, 3
    string input = "a1b2c3"; 
    
    // 初始化测试数据
    mystring s_original;
    s_original.str(input.c_str(), input.length());
    
    cout << "原始数据: ";
    s_original.print();
    cout << "------------------------" << endl;

    // 测试方法一：双指针
    mystring s1;
    s1.str(input.c_str(), input.length());
    s1.paixu_unstable_twopointer();
    cout << "方法一 (双指针，破坏顺序): ";
    s1.print(); // 输出极大概率是 312bca 之类的乱序

    // 测试方法二：新数组异地分拣
    mystring s2_source;
    s2_source.str(input.c_str(), input.length());
    mystring s2_result;
    paixu_stable_newarray(s2_source, s2_result);
    cout << "方法二 (新数组，绝对稳定): ";
    s2_result.print(); // 绝对输出 123abc

    // 测试方法三：冒泡相邻交换
    mystring s3;
    s3.str(input.c_str(), input.length());
    s3.paixu_stable_bubble();
    cout << "方法三 (相邻交换，绝对稳定): ";
    s3.print(); // 绝对输出 123abc

    return 0;
}
