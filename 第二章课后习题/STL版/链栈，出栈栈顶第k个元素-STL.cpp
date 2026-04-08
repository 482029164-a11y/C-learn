//用STL库需要一个辅助栈 
#include <iostream>
#include <stack>
using namespace std;
// 使用 STL 实现出栈顶第 k 个元素
bool chu_k_stl(stack<int>& s, int& x, int k) {
    // 物理防御：k 不合法，或栈里根本没有 k 个元素
    if (k <= 0 || s.size() < k) {
        return false;
    }

    stack<int> temp; // 【核心武器】：辅助栈（相当于汉诺塔的 B 柱）

    // 阶段 1：把上面的 k-1 个障碍物搬到辅助栈里暂存
    for (int i = 1; i < k; ++i) {
        temp.push(s.top());
        s.pop();
    }

    // 阶段 2：现在栈顶就是第 k 个元素了，精准拿取并摧毁
    x = s.top();
    s.pop();

    // 阶段 3：把辅助栈里的 k-1 个元素原样搬回来，恢复栈的生态
    while (!temp.empty()) {
        s.push(temp.top());
        temp.pop();
    }

    return true;
}

int main() {
    stack<int> s;
    s.push(10); // 栈底
    s.push(20);
    s.push(30); // 栈顶 (k=1)
    
    int val = 0;
    if (chu_k_stl(s, val, 2)) {
        cout << "成功提取第 2 个元素: " << val << endl; // 应该输出 20
    }
    
    return 0;
}
