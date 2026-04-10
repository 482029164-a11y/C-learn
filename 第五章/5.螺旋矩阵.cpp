#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// 教科书视角：严格区分横纵起始坐标
void fill_spiral(vector< vector <int> >& matrix, int n, int startX, int startY, int num) {
    // 物理终点 1：洋葱剥完，没有维度了
    if (n <= 0) {
        return;
    }
    
    // 物理终点 2：只剩最后中心的一个绝对点
    if (n == 1) {
        matrix[startX][startY] = num;
        return;
    }

    // 游标起点，直接锚定书本上的起始坐标
    int x = startX; 
    int y = startY;

    // 阶段 1：画顶边 (向右走 n-1 步)
    for (int i = 0; i < n - 1; i++) {
        matrix[x][y] = num++;
        y++; 
    }

    // 阶段 2：画右边 (向下走 n-1 步)
    for (int i = 0; i < n - 1; i++) {
        matrix[x][y] = num++;
        x++; 
    }

    // 阶段 3：画底边 (向左走 n-1 步)
    for (int i = 0; i < n - 1; i++) {
        matrix[x][y] = num++;
        y--; 
    }

    // 阶段 4：画左边 (向上走 n-1 步)
    for (int i = 0; i < n - 1; i++) {
        matrix[x][y] = num++;
        x--; 
    }

    // 【状态转移】：进入内圈。
    // 物理特征：边长缩小 2，行起点下移 1 格，列起点右移 1 格
    fill_spiral(matrix, n - 2, startX + 1, startY + 1, num);
}

int main() {
    int n;
    if (cin >> n && n > 0) {
        vector< vector<int> > matrix(n, vector<int>(n, 0));

        // 初始调用：起点严格传递横坐标 0 和纵坐标 0
        fill_spiral(matrix, n, 0, 0, 1);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(3) << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
