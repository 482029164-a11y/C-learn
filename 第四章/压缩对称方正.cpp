#include <iostream>
using namespace std;

// 定义矩阵的最大维度，解决二维数组传参必须指定列数的物理限制
const int MAX = 100; 

// 1. 打印二维矩阵
void print(int a[][MAX], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

// 2. 将二维对称矩阵压缩到一维数组 b 中（按下三角存储）
void yasuo(int a[][MAX], int n, int b[]) {
    int k = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) { // 遍历下三角区域 (j <= i)
            b[k] = a[i][j];
            k++;
        }
    }
}

// 3. 核心映射函数：根据二维坐标 (i, j) 获取一维数组的下标 k
int getk(int i, int j) {
    int k;
    // 【修正】：i >= j 才是下三角
    if(i >= j) {
        k = (i * (i + 1)) / 2 + j;
    } else {
        // 如果是上三角 (i < j)，在物理上去查对称的下三角位置 (j, i)
        k = (j * (j + 1)) / 2 + i;
    }
    return k;
}

// 4. 在压缩状态下直接进行矩阵乘法：C = A * B
// 将结果存入二维数组 c 中
void mult(int a[], int b[], int c[][MAX], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int s = 0;
            for(int k = 0; k < n; k++) {
                // 【修正】：补充 int 声明
                int k1 = getk(i, k); // 提取 A 矩阵在压缩数组中的位置
                int k2 = getk(k, j); // 提取 B 矩阵在压缩数组中的位置
                s += a[k1] * b[k2];
            }
            c[i][j] = s;
        }
    }
}

int main() {
    int n = 3;
    
    // 初始化两个对称矩阵 A 和 B
    int A[MAX][MAX] = {
        {1, 2, 3},
        {2, 4, 5},
        {3, 5, 6}
    };
    
    int B[MAX][MAX] = {
        {1, 0, 1},
        {0, 2, 0},
        {1, 0, 1}
    };
    
    // 计算压缩数组所需的大小：n*(n+1)/2
    int size = n * (n + 1) / 2;
    int compressed_A[100];
    int compressed_B[100];
    
    // 压缩它们
    yasuo(A, n, compressed_A);
    yasuo(B, n, compressed_B);
    
    int C[MAX][MAX] = {0}; // 存放结果的矩阵
    
    // 调用你写的乘法逻辑
    mult(compressed_A, compressed_B, C, n);
    
    // 打印结果矩阵验证
    cout << "A * B 结果矩阵：" << endl;
    print(C, n);
    
    return 0;
}
