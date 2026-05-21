#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
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
int path[maxv];//其实相当于pre数组 
int dist[maxv];//当前所谓的路径起始结点到各个结点的最短路径，这里要比较就要让inf排上用场了！ 
int s[maxv];//用来判断结点用过没有，防止成环 
void dijkstra(matgraph&g,int v){
	for(int i=0;i<g.n;i++){//第一次循环用来初始化 
		s[i]=0;//初始都在U集
		dist[i]=g.edges[v][i];
		if(g.edges[v][i]!=inf&&g.edges[v][i]!=0){
			path[i]=v;
		}
		else{
			path[i]=-1;
		}
	}
	s[v]=1;
	for(int i=1;i<g.n;i++){
		int min_dist=inf;int u=-1;
		for(int j=0;j<g.n;j++){
			if(s[j] == 0 && dist[j] < min_dist){
				min_dist=dist[j];
				u=j;
			}
		}
		s[u]=1;
		for(int j=0;j<g.n;j++){
			if(s[j]==0&&dist[u] < inf&&g.edges[u][j] < inf && dist[j] > g.edges[u][j] + dist[u]){
				dist[j]=g.edges[u][j]+dist[u];
				path[j]=u;
			}
		}
	}
} 
void display(int s[], int path[], int dist[], int v, int n, matgraph& g) {
	for(int i = 0; i < n; i++) {
		// 铁证分流 1：如果 dist 依然是无穷大，这才是真正的没有路径
		if(dist[i] == inf) {
			cout << "从 " << g.vexs[v] << " 到 " << g.vexs[i] << " : ? 没有路径" << endl;
		} 
		// 铁证分流 2：只要 dist 不是无穷大，就说明物理可达
		else {
			vector<int> apath;
			int u = i;
			while(u != -1) { 
				apath.push_back(u);
				u = path[u];
			}
			
			cout << "从 " << g.vexs[v] << " 到 " << g.vexs[i] << " 的最优路径为：";
			
			// 修改：把原先打印数字编号改为打印具体城市中文名字，极其直观漂亮！
			for(int k = (int)apath.size() - 1; k >= 0; k--) {
				cout << g.vexs[apath[k]];
				if(k != 0) cout << " -> "; 
			} 
			cout << "\t[总权重: " << dist[i] << "]" << endl;
		} 
	}
}

int main() {
    int n = 5;
    int e = 5;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "乌鲁木齐"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 单向有向图连线：
    a[0][1] = 100; a[0][2] = 500; // 北京 -> 上海(100), 广州(500)
    a[1][3] = 50;                 // 上海 -> 深圳(50)
    a[2][3] = 10;                 // 广州 -> 深圳(10)
    a[3][2] = 20;                 // 深圳 -> 广州(20)

    matgraph g;
    g.create(a, vexs, n, e);

    cout << "=== 原始全国单向直达交通成本矩阵 ===" << endl;
    g.print();
    cout << "--------------------------------------------------------" << endl;

    // 启动 Dijkstra 引擎，以 北京(0) 为全国始发站
    dijkstra(g, 0);
    
    // 【修复 4】：调用时把图实体 g 一并传进去
    display(s, path, dist, 0, g.n, g);
    
    cout << "--------------------------------------------------------" << endl;
    cout << "单源最短路径物理推推演完毕，图论大天王算法完美闭环！" << endl;

    return 0;
}
