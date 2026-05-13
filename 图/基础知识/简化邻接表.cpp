#include <iostream>
#include <cstring> // 必须引入，为了使用 memset 的内存黑魔法
using namespace std;
//重点看 addedge(int u, int v, int weight)函数 
const int maxv = 100;     // 最大顶点数
const int maxe = 10000;   // 【修复1】：最大边数！边仓库的地皮要比顶点多得多
const int inf = 0x3f3f3f3f;

int head[maxv]; // 专属电话簿：每一个元素永远指向该顶点最新一条边的数组下标

struct ednode {
	int j;      // 邻接点 (终点)
	int next;   // 指向上一条同起点边的下标 (寻宝线索)
	int weight; // 权重 
} edge[maxe];   // 【修复1】：使用 maxe 分配边仓库大小

int n;   // 顶点数
int cnt; // 边仓库管理员的计步器 (edge数组中当前可用的空格子下标)

void init() {
	cnt = 0;
	// 【修复2】：是数字 0xff，不是英文字母 o
	memset(head, 0xff, sizeof(head)); 
}

// 核心引擎：添加一条从 u 到 v，权重为 weight 的有向边
void addedge(int u, int v, int weight) {
	edge[cnt].weight = weight;
	edge[cnt].j = v;
	edge[cnt].next = head[u]; // 新边记住旧边的位置
	head[u] = cnt;            // 电话簿更新为新边的位置
	cnt++;
}

// 【新增】：遍历图的标准写法，用来验证拓扑结构
void print_graph(int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        cout << "顶点 " << i << " 发出的边: ";
        
        // 极其经典的静态链表遍历手法！
        // 1. 起点：e = head[i]
        // 2. 终点：e != -1 (遇到 -1 说明找完了)
        // 3. 步进：e = edge[e].next (顺着线索往下跳)
        for (int e = head[i]; e != -1; e = edge[e].next) {
            cout << "-> (去往:" << edge[e].j << ", 权:" << edge[e].weight << ") ";
        }
        cout << endl;
    }
}

int main() {
    // 1. 世界之初：初始化仓库和电话簿
    init();

    // 假设我们有 4 个顶点 (编号 0, 1, 2, 3)
    int vertices = 4; 

    // 2. 开始疯狂建边 (跟我们上一轮沙盘推演的结构一样)
    addedge(0, 1, 100);
    addedge(0, 2, 200);
    addedge(2, 1, 50);
    addedge(2, 3, 80);
    addedge(1, 3, 30);

    // 3. 打印图的拓扑结构，见证奇迹
    cout << "=== 链式前向星 (静态链表) 内部拓扑 ===" << endl;
    print_graph(vertices);

    return 0;
}
