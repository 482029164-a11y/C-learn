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
struct node{//此处的node表示边向量 
	int u;
	int v;
	int w;
	node(int u1,int v1,int w1){
		u=u1;
		v=v1;
		w=w1;
	}
	node(){
	}
	bool operator<(const node& n1) const{
		return this->w<n1.w;
	}
};
// 满分修复版 Prim 算法
void krus(matgraph& g) {
	int vex[maxv];//存放每个图点的连通分量编号
	for(int i=0;i<g.n;i++){
		vex[i]=i;//初始时，每个图点属于各自的连通分量 
	} 
	vector<node>l;//存放边向量
	for(int i=0;i<g.n;i++){
		for(int j=i+1;j<g.n;j++){//由于无向图是对称的，因此只需要对上三角进行操作 
			if(g.edges[i][j]!=0&&g.edges[i][j]!=inf){
							node temp(i,j,g.edges[i][j]);
			l.push_back(temp);//边有效才加进去 
			}
		}
	}
	sort(l.begin(),l.end());//从小到大排序
	int k=0;//用来记录已经加入的边数
	int j=0;//用来访问边vector的下标
	while(k<g.n-1){
		int u1=l[j].u;
		int v1=l[j].v;
		int sn1=vex[u1];
		int sn2=vex[v1];
		if(sn1!=sn2){
			cout << "修路铺设边: (" << g.vexs[u1] << " — " << g.vexs[v1] << ")  \t成本(权值): " << l[j].w << endl;
			for(int i=0;i<g.n;i++){
				if(vex[i]==sn2){
					vex[i]=sn1;
				}
			}
			k++;
		}
		j++;
	} 
}

int main() {
    // ----------------------------------------------------
    // 复用上一轮无向连通图材料，方便你直观对比 Prim 与 Kruskal 的异同
    // ----------------------------------------------------
    int n = 4;
    int e = 5;
    string vexs[maxv] = {"北京", "上海", "广州", "武汉"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 铺设无向边：
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

    // 启动 Kruskal 算法
    cout << "=== 启动 Kruskal 算法生成最小生产树 ===" << endl;
    krus(g);
    cout << "-----------------------------------------------" << endl;
    cout << "全图兼并完成，完美构建最小生产树！" << endl;

    return 0;
}
