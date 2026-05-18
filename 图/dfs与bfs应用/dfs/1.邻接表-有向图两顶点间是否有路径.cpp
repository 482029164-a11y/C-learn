#include<iostream>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
const int maxv=100;
const int inf=0x3f3f3f3f;
struct arcnode{//边结点 
	int adjvex;//在数组中的下标
	int weight;//该边权重
	arcnode*next; 
};
struct hnode{
	string info;//顶点信息
	arcnode*first;//指向第一条边的边界点 
};
class adjgraph{//图的邻接表类 
	public:
		hnode list[maxv];//创建头节点数组
		int n,e;//顶点数和边数
		adjgraph(){
			for(int i=0;i<maxv;i++){
				list[i].first=NULL;//第一条边的指针默认指向空 
			}
		} 
		~adjgraph(){
			arcnode* pre,*p;
			for(int i=0;i<n;i++){
				pre=list[i].first;
				if(pre!=NULL){//先判断有没有边 
					p=pre->next;
					while(p!=NULL){
						delete pre;
						pre=p;p=p->next;
					}
					delete pre;
				}
			}
		} 
		void create(int a[][maxv],string vexs[],int n,int e){
			this->n=n;this->e=e;
			arcnode*p;
			for (int i = 0; i < n; i++) {
		        list[i].info = vexs[i];  // 把传入的名字赋给头结点
		    }
			for(int i=0;i<n;i++){
				for(int j=n-1;j>=0;j--){
					if(a[i][j]!=inf&&a[i][j]!=0){//头插法 
						p=new arcnode();
						p->weight=a[i][j];p->adjvex=j;
						p->next=list[i].first;
						list[i].first=p;
					}
				}
			}
		} 
		void print(){
			arcnode*p;
			for(int i=0;i<n;i++){
				cout<<i;
				p=list[i].first;
				if(p!=NULL) cout<<"->";
				while(p!=NULL){
					printf("(%d,%d)",p->adjvex,p->weight);
					p=p->next; 
				}
				cout<<endl;
			} 
		}
};
int visited[maxv];
bool haspath1(adjgraph&g,int u,int v){//u,v代表两个结点
	visited[u]=1;
	arcnode*p=g.list[u].first;
	while(p!=NULL){
		int w=p->adjvex;
		if(w==v) return true;
		if(visited[w]==0){
			if(haspath1(g,w,v)) return true;
		}
		p=p->next;
	}
	return false;
}
bool haspath(adjgraph&g,int u,int v){
	memset(visited,0,sizeof(visited));
	return haspath1(g,u,v);
}
int main() {
    // 1. 准备图的原材料 (5个城市，6条有向边)
    int n = 5;
    int e = 6;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "杭州"};
    
    // 2. 初始化原始二维数组
    int a[maxv][maxv];
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0; 
    
    // 3. 建立物理交通连线 (注意是有向图！)
    a[0][1] = 100; a[0][2] = 200; // 北京 -> 上海, 广州
    a[1][3] = 50;  a[1][4] = 30;  // 上海 -> 深圳, 杭州
    a[2][3] = 10;                 // 广州 -> 深圳
    a[3][4] = 80;                 // 深圳 -> 杭州

    // 4. 召唤邻接表图实体并初始化
    adjgraph g;
    g.create(a, vexs, n, e);
    
    cout << "=== 图的底层物理结构 ===" << endl;
    g.print();
    cout << "------------------------" << endl;
    
    // 5. 启动寻路引擎测试
    cout << "=== 启动 DFS 寻路引擎 ===" << endl;
    
    // 测试 1：存在一条很长的通路 (北京 -> 上海 -> 杭州)
    int u1 = 0, v1 = 4;
    cout << "测试 1：从【" << vexs[u1] << "】到【" << vexs[v1] << "】是否有路? ";
    cout << (haspath(g, u1, v1) ? "? 有路！" : "? 没路。") << endl;

    // 测试 2：由于是有向图，逆向必定没路 (杭州 -> 北京)
    int u2 = 4, v2 = 0;
    cout << "测试 2：从【" << vexs[u2] << "】到【" << vexs[v2] << "】是否有路? ";
    cout << (haspath(g, u2, v2) ? "? 有路！" : "? 没路。") << endl;

    // 测试 3：平级的非连通分支 (广州 -> 上海)
    int u3 = 2, v3 = 1;
    cout << "测试 3：从【" << vexs[u3] << "】到【" << vexs[v3] << "】是否有路? ";
    cout << (haspath(g, u3, v3) ? "? 有路！" : "? 没路。") << endl;

    return 0;
}
