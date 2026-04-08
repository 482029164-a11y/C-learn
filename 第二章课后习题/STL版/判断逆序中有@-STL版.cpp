#include <iostream>
#include <string>
#include <sstream>
#include <stack> // 【STL库】引入标准栈

using namespace std;

// 注意这里传入的是 std::stack
bool panduan_stl(stack<char>& s) {
    int original_len = s.size(); // STL 获取长度用 size()
    if (original_len % 2 == 0) {
        return false;
    }

    stack<char> s1; // STL 声明辅助栈
    int i = 0;
    int half = original_len / 2;

    // 阶段 1：前半段逆序入辅助栈 s1
    while (i < half) {
        char c = s.top(); // STL: 先取栈顶元素
        s.pop();          // STL: 再将栈顶出栈（此函数无返回值）
        s1.push(c);
        i++;
    }

    // 阶段 2：校验中心轴
    char center = s.top();
    s.pop();
    if (center != '@') {
        return false;
    }

    // 阶段 3：比对剩余部分
    while (!s.empty()) { // STL: 用 empty() 判断是否为空
        char c = s.top(); s.pop();
        char x = s1.top(); s1.pop();
        
        if (x != c) {
            return false;
        }
    }

    return true;
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    char x;
    stack<char> s; // 【STL库】直接使用 std::stack
    
    while (ss >> x) {
        s.push(x);
    }
    
    if (panduan_stl(s)) {
        cout << "是正确结构" << endl; 
    } else {
        cout << "不是正确结构" << endl;
    }
    return 0;
}
