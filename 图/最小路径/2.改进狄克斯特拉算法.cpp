#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue> 
using namespace std;
const int maxv = 100;       // 最大结点个数
const int inf = 0x3f3f3f3f; // 定义无穷大
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
struct qnode{
	int v;
	int dist;
	qnode(int v1,int d){
		v=v1;
		dist=d;
	}
	bool operator<(const qnode& q) const{
		return this->dist>q.dist;//便于优先队列的使用 
	}
}; 
int path[maxv]; // 全局前驱数组，追踪最优路径的亲爹是谁
int dist[maxv];//当前所谓的路径起始结点到各个结点的最短路径，这里要比较就要让inf排上用场了！ 
int s[maxv];//用来判断结点用过没有，防止成环 
void dijkstra(adjgraph& g, int v) {
	priority_queue<qnode> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(s, 0, sizeof(s));
	memset(path, -1, sizeof(path)); // 初始时所有人都没有前驱父亲
    
	dist[v] = 0; 
	q.push(qnode(v, dist[v]));
    
    // 【已修复】：改为经典的 while (!q.empty()) 弹队控制
	while(!q.empty()) {
		qnode e = q.top(); // 【已修复】：优先队列没有 front()，必须使用 top()！
        q.pop();
        
		int u = e.v;
        
        // 【已修复】：堆优化标配防线。如果是出过队的过时冗余垃圾数据，直接无视并修剪
        if (s[u] == 1) continue; 
        
		s[u] = 1; // 【物理铁律】：只有在这一刻，u 的最短距离才正式确立！
        
		arcnode* p = g.list[u].first;
		while(p != NULL) {
			int w = p->adjvex;
            // 【已修复】：去掉了这里错误的 s[w] = 1 动作，松弛逻辑重归完美
			if(s[w] == 0 && dist[w] > dist[u] + p->weight) {
				dist[w] = dist[u] + p->weight;
                path[w] = u; // 刷新前驱：想去 w，从 u 走最近
				q.push(qnode(w, dist[w]));
			}
			p = p->next;
		}
	} 
} 

// 满分中文化路径输出函数
void display(adjgraph& g, int path[], int dist[], int v, int n) {
    cout << "====== 堆优化 Dijkstra 全国最优寻路雷达 ======" << endl;
    for(int i = 0; i < n; i++) {
        // 铁证分流 1：如果 dist 依然是无穷大，说明在邻居网络里是绝对死局
        if(dist[i] == inf) {
            cout << "从 " << g.list[v].info << " 到 " << g.list[i].info << " : ? 物理隔绝，没有路径！" << endl;
        } 
        // 铁证分流 2：只要能连通（包括源点自己），利用 vector 缓冲做无越界逆序输出
        else {
            vector<int> apath;
            int u = i;
            while(u != -1) { // 顺藤摸瓜找爸爸，直到退到 -1（源点）为止
                apath.push_back(u);
                u = path[u];
            }
            
            cout << "从 " << g.list[v].info << " 到 " << g.list[i].info << " 的最优路径：";
            // 完美的防越界倒序输出
            for(int k = (int)apath.size() - 1; k >= 0; k--) {
                cout << g.list[apath[k]].info;
                if(k != 0) cout << " -> ";
            }
            cout << "\t\t[最低总耗时: " << dist[i] << "]" << endl;
        }
    }
}

int main() {
    // ----------------------------------------------------
    // 构造 5 个城市。加入高危孤岛“乌鲁木齐”来验证兜底逻辑
    // ----------------------------------------------------
    int n = 5;
    int e = 5;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "乌鲁木齐"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 单向连通赋值：
    a[0][1] = 100; a[0][2] = 500; // 北京 -> 上海(100), 广州(500)
    a[1][3] = 50;                 // 上海 -> 深圳(50)
    a[2][3] = 10;                 // 广州 -> 深圳(10)
    a[3][2] = 20;                 // 深圳 -> 广州(20)

    adjgraph g;
    g.create(a, vexs, n, e);

    // 启动大厂面试、算法机试标准级别的堆优化 Dijkstra 引擎
    int start_node = 0; // 以北京为总调度始发站
    dijkstra(g, start_node);
    
    // 召唤追踪打印引擎
    display(g, path, dist, start_node, g.n);
    
    cout << "------------------------------------------------------------" << endl;
    cout << "大范围堆优化寻路追踪完美闭环！全部图论核心算法恭喜正式大圆满！" << endl;

    return 0;
}
