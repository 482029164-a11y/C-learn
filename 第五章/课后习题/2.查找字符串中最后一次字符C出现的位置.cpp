#include <iostream>
#include <string>
using namespace std;
// 物理递归引擎：直接操作原内存，通过 index 游标进行逆向回退寻址
int chazhao_helper(const string& s, char c, int index) {
    // 1. 绝对终止防线：如果游标越界到了 -1，说明整个物理空间都没找到该字符
    if (index < 0) {
        return -1; // 工业标准：用 -1 代表物理坐标不存在
    }
    
    // 2. 碰撞检测：因为是从后往前扫描，第一个撞上的绝对就是最后一次出现的位置
    if (s[index] == c) {
        return index; 
    }
    
    // 3. 递归推进：游标向头部物理收缩
    return chazhao_helper(s, c, index - 1);
}

int main() {
    string s;
    char c;
    
    if (cin >> s >> c) {
        // 启动递归引擎：游标初始位置锁定在物理绝对末尾 (size - 1)
        int last_pos = chazhao_helper(s, c, s.size() - 1);
        cout << last_pos << "\n";
    }
    
    return 0;
}
