#include<iostream>
#include<vector>
#include<cstring> 
#include<stack>
#include<string>
using namespace std;

const int maxv = 100;
const int inf = 0x3f3f3f3f;

struct arcnode { // 边结点 
	int adjvex;  // 在数组中的下标
	int weight;  // 该边权重
	arcnode* next; 
};

struct hnode {
	string info;    // 顶点信息
	arcnode* first; // 指向第一条边的边界点 
};

class adjgraph { // 图的邻接表类 
public:
	hnode list[maxv]; // 创建头节点数组
	int n, e;         // 顶点数和边数
	adjgraph() {
		for(int i = 0; i < maxv; i++) {
			list[i].first = NULL; // 第一条边的指针默认指向空 
		}
	} 
	~adjgraph() {
		arcnode* pre, * p;
		for(int i = 0; i < n; i++) {
			pre = list[i].first;
			if(pre != NULL) { 
				p = pre->next;
				while(p != NULL) {
					delete pre;
					pre = p; p = p->next;
				}
				delete pre;
			}
		}
	} 
	void create(int a[][maxv], string vexs[], int n, int e) {
		this->n = n; this->e = e;
		arcnode* p;
		for (int i = 0; i < n; i++) {
			list[i].info = vexs[i];  // 把传入的名字赋给头结点
		}
		for(int i = 0; i < n; i++) {
			for(int j = n - 1; j >= 0; j--) {
				if(a[i][j] != inf && a[i][j] != 0) { // 头插法 
					p = new arcnode();
					p->weight = a[i][j]; p->adjvex = j;
					p->next = list[i].first;
					list[i].first = p;
				}
			}
		}
	} 
	void print() {
		arcnode* p;
		for(int i = 0; i < n; i++) {
			cout << "[" << i << " " << list[i].info << "]";
			p = list[i].first;
			if(p != NULL) cout << " -> ";
			while(p != NULL) {
				printf("(%d, 权:%d) ", p->adjvex, p->weight);
				p = p->next; 
			}
			cout << endl;
		} 
	}
};

// 拓扑排序核心算法（未修改你的核心逻辑，仅优化了输出排版）
void topsort(adjgraph& g) {
	stack<int> st;      // 栈用来存放入度为0的结点序号 
	int ind[maxv];      // 记录每个结点的入度
	memset(ind, 0, sizeof(ind)); // 初始化为0 
    
	for(int i = 0; i < g.n; i++) { // 计算每个顶点的入度 
		arcnode* p = g.list[i].first;
		while(p != NULL) {
			int w = p->adjvex;
			ind[w]++;
			p = p->next;
		}	
	} 
    
	for(int i = 0; i < g.n; i++) {
		if(ind[i] == 0) st.push(i); // 如果入度为0就入栈 
	}
    
    cout << "计算出的拓扑学习序列为：";
    int count = 0; // 用来统计输出了多少个节点，用于判定是否有环
    
	while(!st.empty()) { // 拓扑排序开始 
		int p = st.top(); 
        st.pop();
        count++;
        
        // 【排版优化】：结合类里的中文名字输出，并且巧妙去掉最后一个箭头的尾巴
		cout << g.list[p].info << (count == g.n ? "" : " -> ");
        
		arcnode* t = g.list[p].first;
		while(t != NULL) {
			int w = t->adjvex;
			ind[w]--;
			if(ind[w] == 0) {
				st.push(w);
			}
			t = t->next;
		} 
	}
    cout << endl;
    
    // 【高级竞赛控线】：如果输出的节点数少于总节点数，铁证如图中必定藏有环（死锁）
    if(count < g.n) {
        cout << "?? 警告：该图存在有向环路，无法完成完全拓扑排序（选课发生死锁）！" << endl;
    }
} 

int main() {
    // ----------------------------------------------------
    // 构造一个大学计算机专业的选课依赖图（5门课，5条依赖线）
    // 0:高等数学, 1:程序设计, 2:数据结构, 3:离散数学, 4:算法分析
    // ----------------------------------------------------
    int n = 5;
    int e = 5;
    string vexs[maxv] = {"高等数学", "程序设计", "数据结构", "离散数学", "算法分析"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 建立单向依赖关系（有向边）：
    a[0][3] = 1; // 高等数学 ——> 离散数学 (学离散前必须先学高数)
    a[1][2] = 1; // 程序设计 ——> 数据结构 (学数据结构前必须先学会敲代码)
    a[3][4] = 1; // 离散数学 ——> 算法分析 (算法分析需要离散数学功底)
    a[2][4] = 1; // 数据结构 ——> 算法分析 (算法分析需要数据结构基础)
    // 此时【高等数学】和【程序设计】入度为0，属于可以直接开始学的基础课

    adjgraph g;
    g.create(a, vexs, n, e);

    cout << "=== 专业课程依赖邻接表底层结构 ===" << endl;
    g.print();
    cout << "--------------------------------------------------------" << endl;

    // 启动拓扑排序引擎
    topsort(g);

    cout << "--------------------------------------------------------" << endl;
    cout << "课程排期计算完毕，拓扑流完美安全闭环！" << endl;

    return 0;
}
