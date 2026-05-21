#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

const int maxv = 100;       // 最大结点个数
const int inf = 0x3f3f3f3f; // 定义无穷大

class matgraph {
public:
	int edges[maxv][maxv];
	int n, e;             // 矩阵顶点和边数
	string vexs[maxv];    // 存放顶点信息
    
	void create(int a[][maxv], string v[], int n, int e) {
		this->n = n;
		this->e = e;
		for (int i = 0; i < n; i++) {
			this->vexs[i] = v[i];
			for (int j = 0; j < n; j++) {
				edges[i][j] = a[i][j];
			}
		} 
	}
    
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (edges[i][j] == inf) cout << "∞\t";
				else cout << edges[i][j] << "\t";
			}
			cout << endl; // 已修复：跑完一行再换行
		}
	} 
}; 

// 满分修复版 Prim 算法
void prim(matgraph& g, int v) {
	int close[maxv] = {0}; // 修复 3：使用静态常量 maxv 声明
	int low[maxv] = {0};
	
	// 1. 初始化 U-V 集合防线
	for (int i = 0; i < g.n; i++) {
		close[i] = v;
		low[i] = g.edges[v][i];
	} 
    
    low[v] = 0; // 初始节点直接拉入 MST 集合
	
	for (int i = 1; i < g.n; i++) { // 需要选出 n-1 条边
		int k = -1;                 // 【修复 1】：k 必须提升到循环外定义
		int min_weight = inf;
        
		// 2. 核心贪心：挑出当前离 MST 最近的外部节点
		for (int j = 0; j < g.n; j++) {
			if (low[j] != 0 && low[j] < min_weight) { 
				min_weight = low[j];
				k = j;
			}
		}
        
        if (k == -1) break; // 如果图不连通，及时切断防止崩溃
        
        // 打印生成的边，结合城市名字输出更直观
		cout << "修路铺设边: (" << g.vexs[close[k]] << " — " << g.vexs[k] << ")  \t成本(权值): " << min_weight << endl; 
        
        // 【修复 2】：以下的所有动作，必须在每轮选完点后立刻在循环内部执行！
        low[k] = 0; // 标记节点 k 正式加入 MST 集合
        
        // 3. 动态刷新：拿着新来的节点 k，去更新剩余外部节点的最新最优防线
        for (int j = 0; j < g.n; j++) {
            if (low[j] != 0 && g.edges[k][j] < low[j]) {
                low[j] = g.edges[k][j]; // 刷新最短修路成本
                close[j] = k;           // 标记它的最近中间人是 k
            }
        }
	} 
}

int main() {
    // ----------------------------------------------------
    // 构造一幅标准的无向联通图 (注意：生成树一定要用无向图才有物理意义！)
    // 假设 4 个城市要联通，我们要在多条路中选出成本最低的 MST 树
    // ----------------------------------------------------
    int n = 4;
    int e = 5;
    string vexs[maxv] = {"北京", "上海", "广州", "武汉"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 铺设无向边（必须对称填入）：
    a[0][1] = a[1][0] = 10; // 北京 <—> 上海 成本: 10
    a[0][2] = a[2][0] = 30; // 北京 <—> 广州 成本: 30
    a[0][3] = a[3][0] = 20; // 北京 <—> 武汉 成本: 20
    a[1][3] = a[3][1] = 5;  // 上海 <—> 武汉 成本: 5
    a[2][3] = a[3][2] = 15; // 广州 <—> 武汉 成本: 15

    matgraph g;
    g.create(a, vexs, n, e);

    cout << "=== 原始地图修路成本矩阵 ===" << endl;
    g.print();
    cout << "-----------------------------------------------" << endl;

    // 启动 Prim 算法，假设以 北京(0) 为总指挥中心开始向外连通
    cout << "=== 启动 Prim 算法生成最小生产树 ===" << endl;
    prim(g, 0);
    cout << "-----------------------------------------------" << endl;
    cout << "所有城市以最低总成本实现完美物理连通！" << endl;

    return 0;
}
