#include<iostream>
#include<vector>
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
int de(adjgraph&g,int v){
	int d=0;
	arcnode*p=g.list[v].first;
	while(p!=NULL){
		d++;
		p=p->next;
	} 
	return d;
}//求无向图某一结点的度 
vector<int> de2(adjgraph&g,int v){//求出度和入度
	int d1=0,d2=0;//d1为出度，d2为入度 
	vector<int> du(2,0);
	arcnode*p=g.list[v].first;
	while(p!=NULL){
		d1++;
		p=p->next;
	} 
	for(int i=0;i<g.n;i++){
		p=g.list[i].first;
		while(p!=NULL){
			if(p->adjvex==v) d2++;
			p=p->next;
		}
	} 
	du[0]=d1;du[1]=d2;
	return du;
}
int main(){
	// 1. 准备物理测试数据
    int n = 4; // 4个顶点
    int e = 5; // 5条边
    string vexs[] = {"北京", "上海", "广州", "深圳"};
    int matrix[maxv][maxv];

    // 初始化矩阵：对角线为0，其余为无穷大
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = inf;
        }
    }

    // 写入有向边数据（模拟）
    // 0(北京) -> 1(上海), 权值 100
    // 0(北京) -> 2(广州), 权值 200
    // 2(广州) -> 1(上海), 权值 50
    // 2(广州) -> 3(深圳), 权值 80
    // 1(上海) -> 3(深圳), 权值 30
    matrix[0][1] = 100;
    matrix[0][2] = 200;
    matrix[2][1] = 50;
    matrix[2][3] = 80;
    matrix[1][3] = 30;

    // 2. 实例化对象并建图
    adjgraph g;
    g.create(matrix, vexs, n, e);

    // 3. 打印邻接表验证拓扑结构
    cout << "=== 图的邻接表结构 ===" << endl;
    g.print();
    cout << "======================" << endl << endl;

    // 4. 验证度数计算函数
    int target = 2; // 测试节点：2号(广州)
    cout << "正在测试节点 " << target << " (" << vexs[target] << ") 的度数..." << endl;
    
    // 如果把图看作无向图算总度数（由于建图是有向的，这里 de 算出的其实只是出度）
    cout << "[如果作为无向图] 当前相连边数: " << de(g, target) << endl;

    // 有向图入度与出度测试
    vector<int> res = de2(g, target);
    cout << "[有向图] 出度 (指出去的边): " << res[0] << endl;
    cout << "[有向图] 入度 (指进来的边): " << res[1] << endl;

    return 0;
}
