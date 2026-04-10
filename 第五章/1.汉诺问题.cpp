#include<iostream>
using namespace std;
void hanoi(int n, char x, char y, char z) {
    // 【物理终点】：当真正只剩最小的 1 号盘子时，直接移动
    if(n == 1) {
        cout << "将第" << n << "个盘子,从" << x << "移动到" << z << endl; 
    }
    else {
        // 阶段 1：整体让路 (把 n-1 个盘子从 x 移到 y)
        hanoi(n - 1, x, z, y); 
        
        // 阶段 2：底层跃迁 (绝对动作)
        // 【核心修正】：不要调用 hanoi(1...)，直接在这里打印真实的 n 号盘子移动轨迹
        cout << "将第" << n << "个盘子,从" << x << "移动到" << z << endl; 
        
        // 阶段 3：整体归位 (把 n-1 个盘子从 y 移到 z)
        hanoi(n - 1, y, x, z); 
    }
}

int main() {
    int n;
    cin >> n;
    char a = 'a'; // 把物理字符 'a' 装进名叫 a 的箱子里
    char b = 'b';
    char c = 'c';
    hanoi(n, a, b, c);
    return 0;
}

