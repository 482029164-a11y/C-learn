#include<iostream>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
const int maxv=100;//最大结点个数
const int inf=0x3f3f3f3f;//定义无穷
class matgraph{
	public:
		int edges[maxv][maxv];
		int n,e;//矩阵顶点和边数（正常元素个数） 
		string vexs[maxv];//存放顶点信息
		// 创建图
	void create(int a[][maxv], string v[], int n, int e) {
		this->n = n;
		this->e = e;
		for (int i = 0; i < n; i++) {
            this->vexs[i] = v[i]; // 把顶点名字存进去
			for (int j = 0; j < n; j++) {
				edges[i][j] = a[i][j];
			}
		} 
	}//创建图
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (edges[i][j] == inf) cout << "∞\t";
				else cout << edges[i][j] << "\t";
			}
            cout << endl; // 【修复】：换行必须在一整行（j循环）跑完之后！
		}
	}
		 
}; 
int visited[maxv];
void dfs(matgraph&g,int v){
	cout<<v<<" ";
	visited[v]=1;
	for(int j=0;j<g.n;j++){
		int w=g.edges[v][j];
		if(w!=0&&w!=inf){
			if(visited[j]==0) dfs(g,j);
		}	
	}
}
int main() {
    // 1. 准备材料 (5个顶点，6条边的有向图)
    int n = 5;
    int e = 6;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "杭州"};
    
    // 2. 初始化原始矩阵，全部涂抹为无穷大
    int a[maxv][maxv];
    memset(a, 0x3f, sizeof(a));
    
    // 对角线（自己到自己）设为 0
    for(int i = 0; i < n; i++) a[i][i] = 0;
    
    // 3. 填入边的权重（物理连线）
    a[0][1] = 100; a[0][2] = 200; // 北京 -> 上海, 广州
    a[1][3] = 50;  a[1][4] = 30;  // 上海 -> 深圳, 杭州
    a[2][3] = 10;                 // 广州 -> 深圳
    a[3][4] = 80;                 // 深圳 -> 杭州

    // 4. 召唤并初始化邻接矩阵图实体
    matgraph g;
    g.create(a, vexs, n, e);
    
    // 5. 打印底层二维数组的物理排布
    cout << "=== 图的邻接矩阵底层物理结构 ===" << endl;
    g.print();
    cout << "--------------------------------" << endl;
    
    // 6. 启动 DFS 深搜引擎
    cout << "=== 从【北京(0)】开始进行 DFS 深度优先搜索 ===" << endl;
    
    // 保命动作：清扫访问记录
    memset(visited, 0, sizeof(visited)); 
    
    dfs(g, 0); 
    cout << endl;

    return 0;
}
