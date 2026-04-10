#include <iostream>
using namespace std;

int w, h;
int grid[25][25];
int start_x, start_y;
int min_steps; // 记录最小步数
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 绝对的 DFS 引擎
// x, y: 当前冰壶坐标
// step: 当前已经抛出的次数
void dfs(int x, int y, int step) {
    // 【法则 4】：10步视界上限。如果已经抛了 10 次还没到，这条时间线彻底作废
    if (step >= 10) {
        return;
    }

    // 尝试 4 个物理方向盘
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 【法则 1】：贴脸禁射，或者第一步就直接飞出边界
        if (nx < 0 || nx >= h || ny < 0 || ny >= w || grid[nx][ny] == 1) {
            continue; 
        }

        // 【法则 2】：绝对惯性滑动！只要是冰面(0)或者起点(2也是冰面)，就疯狂滑行
        // 注意：题目中起点 2 离开后，那个位置物理上就变成了 0
        while (nx >= 0 && nx < h && ny >= 0 && ny < w && (grid[nx][ny] == 0 || grid[nx][ny] == 2)) {
            nx += dx[i];
            ny += dy[i];
        }

        // 惯性停止后，判断此刻的物理坐标状态
        if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
            // 状态 A：撞到了终点！
            if (grid[nx][ny] == 3) {
                if (step + 1 < min_steps) {
                    min_steps = step + 1; // 刷新宇宙最小步数记录
                }
            } 
            // 状态 B：撞到了障碍物
            else if (grid[nx][ny] == 1) {
                // 【法则 3：物理破壁】障碍物粉碎
                grid[nx][ny] = 0; 
                
                // 冰壶停在障碍物的前一格：nx - dx[i], ny - dy[i]
                // 抛出次数 +1，进入深渊
                dfs(nx - dx[i], ny - dy[i], step + 1);
                
                // 【法则 3：时空重置 (绝对回溯)】退出深渊时，将障碍物原地复原！
                grid[nx][ny] = 1; 
            }
        }
        // 如果滑出边界 (越界了)，则冰壶坠入深渊，什么都不做，直接走下一次 for 循环
    }
}

int main() {
    // POJ 标准的连续多测输入模板
    while (cin >> w >> h && (w != 0 || h != 0)) {
        min_steps = 11; // 初始值为 11 (代表无穷大，因为最多只能 10 步)
        
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> grid[i][j];
                // 扫描到起点，物理锚定坐标
                if (grid[i][j] == 2) {
                    start_x = i;
                    start_y = j;
                }
            }
        }

        // 从起点启动状态机，初始抛出次数为 0
        dfs(start_x, start_y, 0);

        // 结算最终命运
        if (min_steps <= 10) {
            cout << min_steps << endl;
        } else {
            cout << -1 << endl; // 超出10步或死路一条
        }
    }
    return 0;
}
