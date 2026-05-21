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
int parent[maxv];
int rank[maxv];
void init(int n){
	for(int i=0;i<n;i++){
		parent[i]=i;
		rank[i]=0; 
	}
}
int find(int x){
	if(x!=parent[x]) parent[x]=find(parent[x]);
	return parent[x];
} 
void unio(int u,int v){
	int u1=find(u);
	int v1=find(v);
	if(u1==v1) return;
	if(rank[u1]<rank[v1]) parent[u1]=v1;
	else{
		if(rank[u1]==rank[v1]) rank[u1]++;
		parent[v1]=u1;
	}
}
void krus(matgraph& g) {
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
	init(g.n);
	int k=0;//用来记录已经加入的边数
	int j=0;//用来访问边vector的下标
	while(k<g.n-1){
		int u1=l[j].u;
		int v1=l[j].v;
		int sn1=find(u1);
		int sn2=find(v1);
		if(sn1!=sn2){
			cout << "修路铺设边: (" << g.vexs[u1] << " — " << g.vexs[v1] << ")  \t成本(权值): " << l[j].w << endl;
			unio(sn1,sn2);//其实用u1，v1也可以，主要是反正都要再找parent这样方便一些 
			k++;
		}
		j++;
	} 
}

int main() {
    // ----------------------------------------------------
    // 构造一幅标准的 5 城市、7 边无向连通网进行高级 DSU 验证
    // ----------------------------------------------------
    int n = 5;
    int e = 7;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "杭州"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 无向图对称边成本赋值：
    a[0][1] = a[1][0] = 10; // 北京 <—> 上海 : 10
    a[0][2] = a[2][0] = 20; // 北京 <—> 广州 : 20
    a[1][3] = a[3][1] = 30; // 上海 <—> 深圳 : 30
    a[1][2] = a[2][1] = 40; // 上海 <—> 广州 : 40
    a[2][3] = a[3][2] = 15; // 广州 <—> 深圳 : 15
    a[2][4] = a[4][2] = 25; // 广州 <—> 杭州 : 25
    a[3][4] = a[4][3] = 5;  // 深圳 <—> 杭州 : 5

    matgraph g;
    g.create(a, vexs, n, e);

    cout << "=== 原始地图修路成本矩阵 ===" << endl;
    g.print();
    cout << "------------------------------------------------" << endl;

    cout << "=== 启动终极并查集优化版 Kruskal 算法 ===" << endl;
    krus(g);
    cout << "------------------------------------------------" << endl;
    cout << "全图兼并大一统，最小生产树以极优性能构建完毕！" << endl;

    return 0;
}
