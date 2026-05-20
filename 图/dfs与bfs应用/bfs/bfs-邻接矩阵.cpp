#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#include<string>
const int maxv=100;//最大结点个数
const int inf=0x3f3f3f3f;//定义无穷
class matgraph{
	public:
		int edges[maxv][maxv];
		int n,e;//矩阵顶点和边数（正常元素个数） 
		string vexs[maxv];//存放顶点信息
		void create(int a[][maxv], string v[], int n, int e) {
		this->n = n;
		this->e = e;
		for (int i = 0; i < n; i++) {
			this->vexs[i] = v[i]; // 把传入的名字赋给头结点
			for (int j = 0; j < n; j++) {
				edges[i][j] = a[i][j];
			}
		} 
	}//创建图
		void print(){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					if(edges[i][j]==inf) cout<<"无穷";
					else cout<<edges[i][j];
				}
				cout<<endl;
			}
		} //打印 
		 
}; 
void bfs(matgraph&g,int v){
	int visited[maxv]={0};
	queue<int> q;
	q.push(v);
	cout<<g.vexs[v]<<" ";
	visited[v]=1;
	while(!q.empty()){
		int t=q.front();q.pop();
		for(int i=0;i<g.n;i++){
			int w=g.edges[t][i];
			if(w!=0&&w!=inf){
				if(visited[i]==0){
					cout<<g.vexs[i]<<" ";
					visited[1]=1;
					q.push(i);
				}
			}
		}
	}
} 
int main() {
    // 1. 准备图的原材料 (5个城市，6条有向边)
    int n = 5;
    int e = 6;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "杭州"};
    
    // 2. 初始化原始二维数组，全部填满无穷大
    int a[maxv][maxv];
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0; // 自己到自己距离为 0
    
    // 3. 建立物理交通连线
    a[0][1] = 100; a[0][2] = 200; // 北京 -> 上海, 广州
    a[1][3] = 50;  a[1][4] = 30;  // 上海 -> 深圳, 杭州
    a[2][3] = 10;                 // 广州 -> 深圳
    a[3][4] = 80;                 // 深圳 -> 杭州

    // 4. 召唤矩阵图实体并初始化
    matgraph g;
    g.create(a, vexs, n, e);
    
    // 5. 打印矩阵拓扑结构验证
    cout << "=== 图的邻接矩阵底层物理结构 ===" << endl;
    g.print();
    cout << "--------------------------------" << endl;
    
    // 6. 启动 BFS 广搜波纹引擎
    cout << "=== 从【北京(0)】开始进行 BFS 广度优先搜索 ===" << endl;
    bfs(g, 0); 
    cout << endl;

    return 0;
} 
