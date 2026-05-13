#include<iostream>
#include<vector>
using namespace std;
#include<string>
const int maxv=100;//最大结点个数
const int inf=0x3f3f3f3f;//定义无穷
class matgraph{
	public:
		int edges[maxv][maxv];
		int n,e;//矩阵顶点和边数（正常元素个数） 
		string vexs[maxv];//存放顶点信息
		void create(int a[][maxv],int n,int e){
			this->n=n;
			this->e=e;
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					edges[i][j]=a[i][j];
				}
			} 
		}//创建图
		void print(){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					if(edges[i][j]==inf) cout<<"无穷";
					else cout<<edges[i][j];
					cout<<endl; 
				}
			}
		} //打印 
		 
}; 
int getdgree(matgraph&g,int v){
	int d=0;
	for(int j=0;j<g.n;j++){
		if(g.edges[v][j]!=0&&g.edges[v][j]!=inf) d++;
	}
	return d;
} //求无向图的度
vector<int> getdgree1(matgraph&g,int v){
	int d1=0;
	int d2=0;
	for(int i=v;i<g.n;i++){
		if(g.edges[v][i]!=0&&g.edges[v][i]!=inf) d1++;//求行就是出度 
	}
	for(int i=v;i<g.n;i++){
		if(g.edges[i][v]!=0&&g.edges[i][v]!=inf) d2++;//求列就是入度 
	} 
	vector<int>r(2,0);
	r[0]=d1;r[1]=d2;
	return r;
}
int main(){
	matgraph g;
    
    // 1. 在物理内存中准备一个二维数组（大小必须严格匹配 maxv）
    int test_matrix[maxv][maxv];
    int n = 4; // 测试图有 4 个顶点
    int e = 5; // 测试图有 5 条边
    
    // 2. 初始化矩阵（对角线为0，其余默认无穷大）
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j) test_matrix[i][j] = 0;
            else test_matrix[i][j] = inf;
        }
    }
    
    // 3. 手动连上几条有向边 (模拟权值)
    // 节点0 -> 节点1 (权值5)
    // 节点0 -> 节点2 (权值2)
    // 节点2 -> 节点1 (权值8)
    // 节点2 -> 节点3 (权值4)
    // 节点1 -> 节点3 (权值1)
    test_matrix[0][1] = 5;
    test_matrix[0][2] = 2;
    test_matrix[2][1] = 8;
    test_matrix[2][3] = 4;
    test_matrix[1][3] = 1;

    // 4. 调用类的方法生成图
    g.create(test_matrix, n, e);
    
    cout << "=== 图的邻接矩阵 ===" << endl;
    g.print();
    cout << "====================" << endl << endl;

    // 5. 验证度数计算功能
    int target_node = 2; // 我们来测试节点2
    
    cout << "正在测试节点 " << target_node << " 的度数..." << endl;
    
    // 假设它是无向图算总度数
    cout << "[假设为无向图] 总度数: " << getdgree(g, target_node) << endl;
    
    // 有向图算入度和出度
    vector<int> res = getdgree1(g, target_node);
    cout << "[有向图] 出度 (指向别人): " << res[0] << endl;
    cout << "[有向图] 入度 (别人指向它): " << res[1] << endl;

    return 0;
} 
