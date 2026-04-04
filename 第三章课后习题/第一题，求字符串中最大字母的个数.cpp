#include <iostream>
#include <string>
#include <cctype> // 引入字符处理库
//客观的 ASCII 码物理布局：

//大写字母 A 到 Z 的十进制值是 65 到 90。

//小写字母 a 到 z 的十进制值是 97 到 122。
using namespace std;

int getmax(string s) {
    int k = 0; // 最大字母出现的个数
    char c = 0; // 记录当前的最大字母，初始化为一个极小值 (ASCII 的 0)

    for (int i = 0; i < s.length(); i++) {
        // 使用 isalpha 直接判断是否为字母，彻底避开手写 ASCII 边界的风险
        if (isalpha(s[i])) { 
            if (k == 0) {
                c = s[i];
                k = 1;
            } else {
                if (s[i] > c) {
                    c = s[i];
                    k = 1; // 发现了更大的字母，计数器物理重置
                } else if (s[i] == c) {
                    k++;   // 再次遇到当前最大字母，计数器累加
                }
            }
        }
    } 
    return k;
}

int main() {
    string s;
    if (cin >> s) { // 增加对输入的客观防御
        cout << "最大字母的个数为：" << getmax(s) << endl; 
    }
    return 0;
}
