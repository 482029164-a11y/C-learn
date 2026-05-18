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
bool cycle1(adjgraph&g,int u,vector<int> path,vector<int> inpath){
	//判断从起点u能不能找到一条回路，path就是之前的路径，inpath就是存当前结点是否已经出现在路径中
	//应当注意到两个vector都没有引用，一是为了方便自动回退，二是保持他们两个的状态对应
	inpath[u]=1;
	arcnode*p=g.list[u].first;
	while(p!=NULL){
		int w=p->adjvex;
		if(inpath[w]==0){
			if(cycle1(g,w,path,inpath)) return true;
		}
		else{
			return true;//假如现在w已经出现在路径当中了就说明形成环形了，因为相当于二次访问w了 
		}
		p=p->next;
	} 
	return false; 
} 
bool cycle(adjgraph&g){
	for(int i=0;i<g.n;i++){
		vector<int> path,inpath(maxv,0);
		if(cycle1(g,i,path,inpath)) return true;
	}
	return false;
}
int main() {
    int n = 4;
    string vexs[maxv] = {"A", "B", "C", "D"};
    int a[maxv][maxv];

    // ------------------------------------------
    // 测试用例 1：构造一个【无环】的 DAG (有向无环图)
    // A -> B, A -> C, B -> C, C -> D
    // 虽然有多条路径到 C，但全都是向前的，没有回头路。
    // ------------------------------------------
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;
    a[0][1] = 10; a[0][2] = 10;
    a[1][2] = 10;
    a[2][3] = 10;
    
    adjgraph g_no_cycle;
    g_no_cycle.create(a, vexs, n, 4);
    
    cout << "=== 测试图 1 (DAG 有向无环图) ===" << endl;
    g_no_cycle.print();
    cout << "检测结果：图 1 " << (cycle(g_no_cycle) ? "? 包含环！" : "? 没有环！") << endl;
    cout << endl;

    // ------------------------------------------
    // 测试用例 2：构造一个【有环】的图
    // A -> B, B -> C, C -> D, D -> B (形成 B-C-D-B 环)
    // ------------------------------------------
    memset(a, 0x3f, sizeof(a));
    for(int i = 0; i < n; i++) a[i][i] = 0;
    a[0][1] = 10;
    a[1][2] = 10;
    a[2][3] = 10;
    a[3][1] = 10; // 这是一条回头路，指向了路径中正在访问的 B
    
    adjgraph g_has_cycle;
    g_has_cycle.create(a, vexs, n, 4);
    
    cout << "=== 测试图 2 (包含环路) ===" << endl;
    g_has_cycle.print();
    cout << "检测结果：图 2 " << (cycle(g_has_cycle) ? "? 包含环！" : "? 没有环！") << endl;

    return 0;
}
