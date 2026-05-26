#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cstring>
#include<stack> 
using namespace std;
int const maxv=1000;
int const inf=0x0f0f0f0f;
struct arcnode{
	int adjvex;
	arcnode*next;
	arcnode(){
		next=NULL;
	}
	arcnode(int a){
		adjvex=a;
		next=NULL;
	}
}; //这里weight成员就省略掉了，因为权重都是1 
struct hnode{
	arcnode*first;
	int info;
	hnode(){
		first=NULL;
	}
	hnode(int f){
		info=f;
		first=NULL;
	}
}; 
class adjgraph{
	public:
		vector<hnode> list;//同样此题需要把第0个元素当垃圾桶用 
		int n,e;//n为结点个数。e为边数
		void createlist(vector<vector<int> >&arr,int num,int edge){
			list.resize(num+1);//因为0元素是垃圾桶 
			for(int i=0;i<(int)arr.size();i++){
				int u=arr[i][0];
				int v=arr[i][1];
				arcnode*p=new arcnode(v); 
				p->next=list[u].first;
				list[u].first=p;
				list[u].info=u; 
			}
			n=num;
			e=edge;
		} 
		~adjgraph() {
            for(int i = 0; i < (int)list.size(); i++) {
                arcnode* p = list[i].first;
                while(p != NULL) {
                    arcnode* tmp = p->next;
                    delete p;
                    p = tmp;
                }
            }
        }
};
//如果存在环结构，那么拓扑排序在遇到环的有向图，拓扑排序将无法输出完整的图结构，也就是说假设到达某一阶段，明明还有点，但是都不满足入度为0了，就是有环！
vector<int> ind;
vector<int> visited;
bool huan(adjgraph& g){
	//先初始化ind
	ind.resize(g.n+1,0);
	visited.resize(g.n+1,0);
	for(int i=1;i<=g.n;i++){//从1开始，因为0是垃圾桶 ,计算入度，没碰到就是0喽 
		arcnode*p=g.list[i].first;
		while(p!=NULL){
			int j=p->adjvex;
			ind[j]++;
			p=p->next;
		} 
	} 
	stack<int>s;
	for(int i=1;i<=g.n;i++){
		if(ind[i]==0){
			s.push(i);
		}
	}
	while(!s.empty()){
		int t=s.top();s.pop();
		visited[t]=1;
		arcnode*p=g.list[t].first;
		while(p!=NULL){
			int j=p->adjvex;
			ind[j]--;
			if(ind[j]==0){
				s.push(j);
			}
			p=p->next;
		}	
	}
	for(int i=1;i<=g.n;i++){//只要访问顶点范围就可以 
		if(visited[i]==0) return true;
	}
	return false;//如果都放问过了自然就是无环呗 
} 
int main(){
	int num,edge;
	cin>>num>>edge;
	string line,trash;
	getline(cin,trash);
	vector<vector<int> >v;
	for(int i=0;i<edge;i++){
		vector<int> temp;
		getline(cin,line);
		stringstream ss(line);
		int x;
		while(ss>>x){
			temp.push_back(x);
		}
		v.push_back(temp);
	}
	adjgraph g;
	g.createlist(v,num,edge);
	if(huan(g)) cout<<"Yes";
	else{
		cout<<"No";
	}
} 
