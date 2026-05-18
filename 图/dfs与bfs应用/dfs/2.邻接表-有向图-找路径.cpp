#include<iostream>
#include<vector>
#include<cstring>
#include<string>
//重点看看为什么有的path引用有的path没有引用 ,findpath1和findpath2是不一样的 
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
// ================== 方法 1：边找边打印 ==================
// path 不加 &：利用克隆机制自动隔离每一层的路线
void findpath1_dfs(adjgraph& g, int u, int v, vector<int> path) {
	path.push_back(u); // 【修复】：拼写错误
	visited[u] = 1;
    
    // 走到终点了，直接打印
	if(u == v) {
		cout << "找到路径：";
		for(int i = 0; i < (int)path.size(); i++) cout << g.list[path[i]].info << " ";
		cout << endl;
		return;
	}
    
	arcnode* p = g.list[u].first;
	while(p != NULL) {
		int w = p->adjvex;
		if(visited[w] == 0) {
			findpath1_dfs(g, w, v, path); // 【修复】：函数名
		}
		p = p->next; // 【致命修复】：必须放在 if 外面，否则死循环！
	}
} 

void findpath1(adjgraph& g, int u, int v) {
	vector<int> path;
	memset(visited, 0, sizeof(visited));
    cout << "--- 策略1：边找边输出简单路径 ---" << endl;
	findpath1_dfs(g, u, v, path);
}

// ================== 方法 2：把答案带回 ==================
// path 不加 & (隔离路线)， res 加 & (锚定物理内存带回答案)
void findpath2_dfs(adjgraph& g, int u, int v, vector<int> path, vector<int>& res) {
	path.push_back(u);
	visited[u] = 1;
    
	if(u == v) {
		res = path; // 找到了！把克隆的 path 塞进绝对的物理锚点 res 中
		return;
	}
    
	arcnode* p = g.list[u].first;
	while(p != NULL) {
		int w = p->adjvex;
		if(visited[w] == 0) {
			findpath2_dfs(g, w, v, path, res);
		}
		p = p->next;
	}
}

void findpath2(adjgraph& g, int u, int v) {
	vector<int> path, res;
	memset(visited, 0, sizeof(visited));
	findpath2_dfs(g, u, v, path, res);
    
    cout << "--- 策略2：带回最后找到的路径并输出 ---" << endl;
    if(res.empty()) {
        cout << "无路可走！" << endl;
    } else {
        cout << "带回的路径为：";
        for(int i = 0; i < (int)res.size(); i++) cout << g.list[res[i]].info << " ";
        cout << endl;
    }
}
int main() {
    // 1. 准备材料 (4个城市)
    int n = 4;
    int e = 5;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳"};
    
    // 2. 初始化图 (连线造出【多条路径】来测试我们的回溯)
    int a[maxv][maxv];
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0; 
    
    // 北京 -> 上海， 北京 -> 广州
    a[0][1] = 100; a[0][2] = 200; 
    // 上海 -> 深圳， 上海 -> 广州
    a[1][3] = 50;  a[1][2] = 30;  
    // 广州 -> 深圳
    a[2][3] = 10;                 

    // 3. 构建邻接表
    adjgraph g;
    g.create(a, vexs, n, e);
    
    // 4. 测试
    // 从 北京(0) 到 深圳(3)，存在两条路：
    // 路A：北京 -> 上海 -> 深圳
    // 路B：北京 -> 上海 -> 广州 -> 深圳
    // 路C：北京 -> 广州 -> 深圳
    
    findpath1(g, 0, 3);
    cout << endl;
    findpath2(g, 0, 3); // res 会保存最后一次找到的路径

    return 0;
}
