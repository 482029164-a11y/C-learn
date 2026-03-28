#include<bits/stdc++.h>
using namespace std;
const int maxsize = 1000;
//这个例子需要记住几个几个string的常用函数：1.empty()2.length(),返回元素个数3.substr(size_t pos, size_t len)，从哪个下标开始截字符，截断多少个字符
//这里的输入又更新了文件读取
//1.freopen("in.txt", "r", stdin); 这个是把输入流动变成文件中的内容2.getline(cin,line)//默认整行切分3.getline(string,token,",")//按照逗号切分
//这里的char转化成数字的方法要记住 ，my_stoi(const string& str)的那个函数操作很重要 
// 1. 改个名字避免和 std::stack 冲突
template<class T> 
class MyStack {
public:
    T data[maxsize];
    int topIndex; 
    
    // 2. 构造函数名字要和类名一致
    MyStack() {
        topIndex = -1; 
    }

    bool push(T x) {
        if (topIndex >= maxsize - 1) {
            return false; 
        }
        data[++topIndex] = x; 
        return true;
    }

    bool empty() {
        return topIndex == -1;
    }

    bool pop(T &e) {
        if (empty()) {
            return false;
        }
        e = data[topIndex--]; 
        return true;
    }

    // 3. 补充上缺失的 gettop 函数
    bool gettop(T &e) {
        if (empty()) {
            return false;
        }
        e = data[topIndex]; 
        return true;
    }

    int size() {
        return topIndex + 1;
    }
};
// 专门用来剔除字符串首尾的空格和换行符
string trim(const string& s) {
    if (s.empty()) return s;
    int start = 0, end = s.length() - 1;
    // 找到第一个不是空白字符的位置
    while (start <= end && (s[start] == ' ' || s[start] == '\r' || s[start] == '\n')) {
        start++;
    }
    // 找到最后一个不是空白字符的位置
    while (end >= start && (s[end] == ' ' || s[end] == '\r' || s[end] == '\n')) {
        end--;
    }
    return s.substr(start, end - start + 1);
}
int my_stoi(const string& str) {
    int res = 0;//记录绝对值 
    int sign = 1;
    int start = 0;//初始下标 
    if (str[0] == '-') { sign = -1; start = 1; }//如果是负数，直接跳一格再记录 
    for (int i = start; i < (int)str.length(); ++i) {
        res = res * 10 + (str[i] - '0');
    }
    return res * sign;
}
void qiuzhi(MyStack<string>& a, int &r) {
    string c;
    MyStack<int> b;
    int t1=0, t2=0; 

    while (!a.empty()) {
        a.pop(c);
        
        if (c == ",") {
            continue;
        } 
        // 1. 将 switch 改为 if-else if 结构来匹配字符串
        else if (c == "+") {
            b.pop(t1);
            b.pop(t2);
            b.push(t2 + t1);
        } 
        else if (c == "-") {
            b.pop(t1);
            b.pop(t2);
            b.push(t2 - t1); 
        } 
        else if (c == "*") {
            b.pop(t1);
            b.pop(t2);
            b.push(t2 * t1);
        } 
        else if (c == "/") {
            b.pop(t1);
            b.pop(t2);
            b.push(t2 / t1); 
        } 
        // 2. 如果不是运算符，那就是数字字符串
        else {
            // 使用 stoi (String TO Integer) 将字符串安全转换为 int
            // 如果你的环境因为某种原因禁用了 stoi，可以替换成我在上面给你手写的 my_stoi 函数
            int num = my_stoi(c); 
            b.push(num);
        }
    }
    b.gettop(r);
}
int main() {
    freopen("in.txt", "r", stdin);
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue; 
        MyStack<string> l1; 
        MyStack<string> bolan;
        stringstream ss(line);
        string token;
        // 按逗号切分
        while (getline(ss, token, ',')) {
            // 【关键操作】：把切下来的 token 放进净水器洗一下
            token = trim(token); 
            // 如果洗完之后是空的，就跳过
            if (token.empty()) continue;
            l1.push(token); 
        }
        // 中转逻辑（把正序变倒序）
        string temp;
        while (!l1.empty()) {
            l1.pop(temp);
            bolan.push(temp);
        }
        int result;
        // 执行求值
        qiuzhi(bolan, result); 
        cout << result << endl;
    }
    
    return 0;
}
