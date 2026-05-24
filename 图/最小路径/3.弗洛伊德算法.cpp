#include<iostream>
#include<vector>
#include<cstring> 
using namespace std;
#include<string>
const int maxv=100;//最大结点个数
const int inf=0x3f3f3f3f;//定义无穷
class matgraph {
public:
	int edges[maxv][maxv];
	int n, e;             // 矩阵顶点和边数
	string vexs[maxv];    // 存放顶点信息
    
    // 【微调】：为了配合主函数，允许把名字数组 v 传进去初始化
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
			cout << endl;
		}
	} 
};
int A[maxv][maxv];
int path[maxv][maxv];
void floyd(matgraph&g){
	for(int i=0;i<g.n;i++){//初始化A和path 
		for(int j=0;j<g.n;j++){
			A[i][j]=g.edges[i][j];
			if(i!=j&&g.edges[i][j]<inf){
				path[i][j]=i;
			}
			else{
				path[i][j]=-1;
			}
		}
	}
	for(int k=0;k<g.n;k++){
		for(int i=0;i<g.n;i++){
			for(int j=0;j<g.n;j++){
				if(A[i][j]>A[i][k]+A[k][j]){
					A[i][j]=A[i][k]+A[k][j];
					path[i][j]=path[k][j];
				}
			}
		}
	} 
} 
void display(matgraph& g) {
    cout << "========== Floyd 全局全城多源最短路径寻路雷达 ==========" << endl;
    for(int i = 0; i < g.n; i++) {
        for(int j = 0; j < g.n; j++) {
            if(i == j) continue; // 自己到自己无需打印
            
            cout << "【" << g.vexs[i] << "】 -> 【" << g.vexs[j] << "】: ";
            
            if(A[i][j] == inf) {
                cout << "? 物理隔绝，没有路径！" << endl;
            } else {
                vector<int> apath;
                int u = j;
                apath.push_back(u); // 先把终点塞进去
                
                // 顺藤摸瓜：根据 path[i][u] 一路往前找前驱父亲，直到退回起点 i 为止
                while(path[i][u] != -1 && u != i) {
                    u = path[i][u];
                    apath.push_back(u);
                }
                
                // 完美的防越界倒序输出
                for(int k = (int)apath.size() - 1; k >= 0; k--) {
                    cout << g.vexs[apath[k]];
                    if(k != 0) cout << " -> ";
                }
                cout << "\t\t[总权重/开销: " << A[i][j] << "]" << endl;
            }
        }
        cout << "--------------------------------------------------------" << endl;
    }
}
int main() {
    // ----------------------------------------------------
    // 构造 4 个城市交错的有向稠密网，包含单向线和必经中转站
    // ----------------------------------------------------
    int n = 4;
    int e = 4;
    string vexs[maxv] = {"北京", "上海", "广州", "成都"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 单向连通有向边成本赋值：
    a[0][1] = 5;   // 北京 -> 上海 : 5
    a[0][3] = 7;   // 北京 -> 成都 : 7
    a[1][2] = 4;   // 上海 -> 广州 : 4
    a[2][3] = 1;   // 广州 -> 成都 : 1
    a[3][0] = 3;   // 成都 -> 北京 : 3 (允许回路产生)

    matgraph g;
    g.create(a, vexs, n, e);

    cout << "=== 原始直达交通成本矩阵 ===" << endl;
    g.print();
    cout << "--------------------------------------------------------" << endl;

    // 启动 Floyd 矩阵全局爆破引擎
    floyd(g);
    
    // 召唤全局路径全量打印
    display(g);

    return 0;
}
