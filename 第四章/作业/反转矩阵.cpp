#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // 引入底层交换指令 swap
using namespace std;
void xz(vector<vector<int> >& v) {
    int n = v.size();
    
    // 第一步：沿主对角线进行物理转置
    for (int i = 0; i < n; i++) {
        // 注意：j 从 i 开始，只遍历右上半区，防止重复交换导致数据还原
        for (int j = i; j < n; j++) {
            swap(v[i][j], v[j][i]);
        }
    }
    // 第二步：沿垂直中轴线进行物理翻转（每一行逆序）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            swap(v[i][j], v[i][n - 1 - j]);
        }
    }
}
void print(vector<vector<int> >& v) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v.size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n"; 
    }
}

int main() {
    int n, x;
     freopen("in.txt", "r", stdin);
    string line, trash;
    
    if (cin >> n) {
        getline(cin, trash); // 吸收掉输入 n 之后的换行符
        
        // 预分配外层物理维度
        vector<vector<int> > v(n);
        
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            stringstream ss(line);
            while (ss >> x) {
                v[i].push_back(x);
            }
        }
        // 启动原地旋转引擎
        xz(v);
        print(v);
    }
    
    return 0;
}
