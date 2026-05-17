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
void dfs(adjgraph&g,int v){//v为遍历的起始结点 
	cout<<v<<" ";
	visited[v]=1;//访问过就标为1
	arcnode*p=g.list[v].first;
	while(p!=NULL){
		int w=p->adjvex;
		if(visited[w]!=1) dfs(g,w);
		p=p->next;
	} 
}
int main() {
    // 1. 准备图的原材料 (5个顶点，6条边的有向图)
    int n = 5;
    int e = 6;
    string vexs[maxv] = {"北京", "上海", "广州", "深圳", "杭州"};
    
    // 2. 初始化无穷大邻接矩阵 (0x3f的极速涂抹魔法)
    int a[maxv][maxv];
    memset(a, 0x3f, sizeof(a));
    
    // 把对角线（自己到自己）设为 0
    for(int i = 0; i < n; i++) a[i][i] = 0;
    
    // 3. 开始连线 (填入权重)
    // 0(北京) -> 1(上海) w:100,  0(北京) -> 2(广州) w:200
    a[0][1] = 100; a[0][2] = 200;
    // 1(上海) -> 3(深圳) w:50,   1(上海) -> 4(杭州) w:30
    a[1][3] = 50;  a[1][4] = 30;
    // 2(广州) -> 3(深圳) w:10
    a[2][3] = 10;
    // 3(深圳) -> 4(杭州) w:80
    a[3][4] = 80;

    // 4. 召唤并组装图的邻接表实体
    adjgraph g;
    g.create(a, vexs, n, e);
    
    // 5. 打印底层物理拓扑结构验证
    cout << "=== 图的邻接表底层物理结构 ===" << endl;
    g.print();
    cout << "------------------------------" << endl;
    
    // 6. 启动 DFS 深搜巡逻兵
    cout << "=== 从【北京(0)】开始进行 DFS 深度优先搜索 ===" << endl;
    
    // 【极其关键的保命动作】：每次 DFS 前必须清扫历史记录！
    memset(visited, 0, sizeof(visited)); 
    
    dfs(g, 0); 
    cout << endl;

    return 0;
}
