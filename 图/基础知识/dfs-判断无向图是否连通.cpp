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
void dfs(adjgraph&g,int v){
	visited[v]=1;
	arcnode*p=g.list[v].first;
	while(p!=NULL){
		if(visited[p->adjvex]==0){
			dfs(g,p->adjvex);
		}
		p=p->next;
	}
}
bool panduan(adjgraph&g){
	memset(visited,0,sizeof(visited));
	dfs(g,0);
	for(int i=0;i<g.n;i++){
		if(visited[i]==0) return false;
	}
	return true;
}
int main(){
    // 1. 定义顶点数和边数
    int n = 5; 
    int e = 5; // 这里以无向图的5条边为例

    // 2. 初始化顶点名称
    string vexs[maxv] = {"A", "B", "C", "D", "E"};

    // 3. 初始化邻接矩阵
    int a[maxv][maxv];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                a[i][j] = 0;   // 自己到自己的距离为0
            } else {
                a[i][j] = inf; // 初始时均无连接，设为无穷大
            }
        }
    }

    // 4. 插入边信息（权重）
    // 假设构建以下无向图结构：
    // A(0) --2-- B(1)
    // |          |
    // 5          1
    // |          |
    // C(2) --3-- D(3) --4-- E(4)
    
    a[0][1] = 2; a[1][0] = 2; // 顶点0与1之间的边，权重为2
    a[0][2] = 5; a[2][0] = 5; // 顶点0与2之间的边，权重为5
    a[1][3] = 1; a[3][1] = 1; // 顶点1与3之间的边，权重为1
    a[2][3] = 3; a[3][2] = 3; // 顶点2与3之间的边，权重为3
    a[3][4] = 4; a[4][3] = 4; // 顶点3与4之间的边，权重为4

    // 5. 实例化图并构建邻接表
    adjgraph g;
    g.create(a, vexs, n, e);

    // 6. 打印生成的邻接表结构
    cout << "--- 图的邻接表结构 ---" << endl;
    g.print();
    cout << endl;

    // 7. 测试连通性判断函数
    cout << "--- 连通性测试 ---" << endl;
    if (panduan(g)) {
        cout << "该图是连通的（从顶点 0 开始可以访问到所有其他顶点）。" << endl;
    } else {
        cout << "该图不是连通图。" << endl;
    }

    // 8. 断开一个节点以测试不连通的情况 (可选测试)
    cout << "\n--- 修改图结构 (断开顶点E) 后再次测试 ---" << endl;
    adjgraph g2;
    a[3][4] = inf; // 断开 D 和 E 之间的边
    a[4][3] = inf;
    g2.create(a, vexs, n, e - 1);
    
    if (panduan(g2)) {
        cout << "该图是连通的。" << endl;
    } else {
        cout << "该图不是连通图（存在无法到达的顶点）。" << endl;
    }

    return 0;
}
