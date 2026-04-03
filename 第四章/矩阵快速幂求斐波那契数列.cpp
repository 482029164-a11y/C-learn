#include <iostream>
using namespace std;
//提前取模不会影响最终的结果 
//二进制快速幂 
//线性代数中的矩阵和算法结合，其核心意义往往不在于“能不能算”，
//而在于“能不能加速”。把 % 10000 嵌入到每一次计算中，并用快速幂思维替代线性遍历，这是从普通解法向竞赛级解法跨越的关键门槛。
const int MOD = 10000;

// 将 2x2 矩阵封装起来，代码更加整洁
struct Matrix {
    int mat[2][2];
    
    // 构造函数：默认初始化为全 0
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

// 独立的矩阵乘法函数，自带防溢出取模
Matrix multiply(Matrix A, Matrix B) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                // 每一步乘法和加法都必须立刻取模
                res.mat[i][j] = (res.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return res;
}

// 矩阵快速幂核心算法：求 base 矩阵的 n 次方
Matrix power(Matrix base, int n) {
    Matrix res;
    // res 初始化为单位矩阵（相当于普通数字里的 1）
    res.mat[0][0] = 1; res.mat[0][1] = 0;
    res.mat[1][0] = 0; res.mat[1][1] = 1;
    
    while (n > 0) {
        // 如果 n 的当前二进制最低位是 1，就把当前的 base 乘到结果里
        if (n % 2 == 1) {
            res = multiply(res, base);
        }
        // base 矩阵自己做平方升级（M -> M^2 -> M^4 -> M^8...）
        base = multiply(base, base);
        
        // n 向右移位（相当于除以 2），看下一个二进制位
        n /= 2; 
    }
    return res;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    // 初始化基础矩阵 M
    Matrix base;
    base.mat[0][0] = 1; base.mat[0][1] = 1;
    base.mat[1][0] = 1; base.mat[1][1] = 0;
    
    // 根据矩阵递推公式，求 M 的 n-1 次方
    // (因为 [F_n, F_{n-1}] = [F_1, F_0] * M^{n-1})
    Matrix result = power(base, n - 1);
    
    // 输出结果（此时的值已经是取模过的绝对安全值）
    cout << result.mat[0][0] << endl;
    
    return 0;
}
