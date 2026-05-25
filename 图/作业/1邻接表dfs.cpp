#include<iostream>
#include<vector>
#include<cstring>
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
    
    // 严格对齐你最初的“头插法”构建逻辑
	void create(int a[][maxv], string vexs[], int n, int e) {
		this->n = n; this->e = e;
		arcnode* p;
		for (int i = 0; i < n; i++) {
			list[i].info = vexs[i];  
		}
		for(int i = 0; i < n; i++) {
            // 头插法：从 n-1 到 0 逆序扫描，可以保证链表输出的节点顺序正好是升序，极其漂亮
			for(int j = n - 1; j >= 0; j--) {
				if(a[i][j] != inf && a[i][j] != 0) { 
					p = new arcnode();
					p->weight = a[i][j]; p->adjvex = j;
					p->next = list[i].first;
					list[i].first = p;
				}
			}
		}
	} 
    
    // 【排版优化】：将你的 print 函数升级为完全可视化的邻接表打印结构
	void print() {
		arcnode* p;
		for(int i = 0; i < n; i++) {
			cout << "[顶点的下标 " << i << " | info: " << list[i].info << "]";
			p = list[i].first;
			if(p != NULL) cout << " -> ";
			while(p != NULL) {
				cout << "[临接点: " << p->adjvex << "]";
				p = p->next; 
                if(p != NULL) cout << " -> ";
			}
			cout << " -> ∧ (NULL)" << endl;
		} 
	}
};

int inpath[maxv]; // 判断访问过没有 
vector<int> path; 

// 你写的最完美的回溯寻路发动机
void findpath1(adjgraph& g, int u, int v) {
	if(u == v) {
		for(int i = 0; i < (int)path.size(); i++) {
			cout << path[i] << (i == (int)path.size() - 1 ? "" : " -> ");
		}
		cout << endl;
		return;
	}
	arcnode* p = g.list[u].first;
	while(p != NULL) {
		int w = p->adjvex;
		if(inpath[w] == 0) {
			path.push_back(w);
			inpath[w] = 1;
            
			findpath1(g, w, v); // 递归下沉
            
			inpath[w] = 0;      // 对称撤销（回溯核心）
			path.pop_back();
		}
		p = p->next;
	}
}

void findpath(adjgraph& g, int u, int v) {
	memset(inpath, 0, sizeof(inpath));
    path.clear();
	path.push_back(u);
	inpath[u] = 1;
	findpath1(g, u, v);
}

int main() {
    // ----------------------------------------------------
    // 精准还原原图中的有向邻接关系（共 5 个顶点，7 条有向边）
    // ----------------------------------------------------
    int n = 5;
    int e = 7;
    string vexs[maxv] = {"0", "1", "2", "3", "4"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 根据原图的绿色箭头精准填入物理连线：
    a[0][1] = 1; a[0][2] = 1; // 0 指向 1, 2
    a[1][2] = 1;              // 1 指向 2
    a[2][3] = 1; a[2][4] = 1; // 2 指向 3, 4
    a[3][4] = 1;              // 3 指向 4
    a[4][0] = 1;              // 4 指向 0 (形成了回环通路)

    adjgraph g;
    g.create(a, vexs, n, e);

    cout << "=================== 第一部分：画出邻接表存储结构 ===================" << endl;
    g.print();
    cout << "====================================================================" << endl << endl;

    cout << "========= 第二部分：调用 DFS 算法找出从 0 到 4 的所有路径 =========" << endl;
    findpath(g, 0, 4);
    cout << "====================================================================" << endl;

    return 0;
}
