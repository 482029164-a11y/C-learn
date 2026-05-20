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
int inpath[maxv];//判断访问过没有 
vector<int> path; 
void findpath1(adjgraph&g,int u,int v){//u,v代表两个结点
	if(u==v){
		for(int i=0;i<(int)path.size();i++){
			cout<<path[i]<<" ";
		}
		cout<<endl;
		return;
	}
	arcnode*p=g.list[u].first;
	while(p!=NULL){
		int w=p->adjvex;
		if(inpath[w]==0){
			path.push_back(w);
			inpath[w]=1;
			findpath1(g,w,v);
			inpath[w]=0;
			path.pop_back();
		}
		p=p->next;
	}
}
void findpath(adjgraph&g,int u,int v){
	memset(inpath,0,sizeof(inpath));
	path.push_back(u);
	inpath[u]=1;
	findpath1(g,u,v);
}
int main() {
    // ------------------------------------------
    // 构建一棵拥有 5 个城市、7 条有向边的复杂交通网络
    // 允许从 0(北京) 到 4(杭州) 衍生出 4 条完全不同的走法
    // ------------------------------------------
    int n = 5;
    int e = 7;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "杭州"};
    int a[maxv][maxv];
    
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;

    // 物理连线建立：
    a[0][1] = 10; a[0][2] = 10; // 北京 -> 上海, 广州
    a[1][3] = 10; a[1][2] = 10; // 上海 -> 深圳, 广州
    a[2][3] = 10; a[2][4] = 10; // 广州 -> 深圳, 杭州
    a[3][4] = 10;               // 深圳 -> 杭州

    adjgraph g;
    g.create(a, vexs, n, e);

    cout << "=== 图的邻接表拓扑网络 ===" << endl;
    g.print();
    cout << "---------------------------------------" << endl;

    // 启动回溯寻路引擎
    int start_node = 0; // 北京
    int end_node = 4;   // 杭州
    
    cout << "从【" << vexs[start_node] << "】到【" << vexs[end_node] << "】的所有简单路径如下：" << endl;
    
    findpath(g, start_node, end_node);
    
    cout << "---------------------------------------" << endl;
    cout << "所有平行宇宙穷举完毕，回溯动作完美闭环！" << endl;

    return 0;
}
