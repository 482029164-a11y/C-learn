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
	int weight;
	arcnode(){
		next=NULL;
	}
	arcnode(int a,int w){
		weight=w;
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
		vector<hnode> list;
		int n,e;//n为结点个数。e为边数
		void createlist(vector<vector<int> >&arr,int num){
			int temp_e=0;
			list.resize(num);
			for(int i=0;i<num;i++){
				for(int j=0;j<num;j++){
					if(arr[i][j]!=0){
						int w=arr[i][j];
						arcnode*p=new arcnode(j,w); 
						p->next=list[i].first;
						list[i].first=p;
						list[i].info=i; 
						temp_e++;
					}
				}
			}
			n=num;
			e=temp_e;
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
vector<int> dist;//用来存储起点到某个点的最短距离 
vector<int> s;//用来判断在哪个集合里面 
void diji(adjgraph&g,int v){
	dist.resize(g.n,inf);//初始都是各自，所以距离为inf
	s.resize(g.n,0);//初始都在一个集合
	dist[v]=0; 
	arcnode*p=g.list[v].first;
		while(p!=NULL){
			int j=p->adjvex;
			dist[j]=p->weight;
			p=p->next;
		}
	//初始化距离 
	s[v]=1;
	for(int i=1;i<g.n;i++){
		int min_dist=inf;int u=-1;
		for(int j=0;j<g.n;j++){
			if(s[j]==0&&dist[j]<min_dist){
				min_dist=dist[j];
				u=j;
			}
		}
		if(u==-1) return; 
		s[u]=1;//把这个点放进去
		arcnode*p=g.list[u].first;
		while(p!=NULL){
			int j=p->adjvex;
			if(s[j]==0&&dist[j]>dist[u]+p->weight){
				dist[j]=dist[u]+p->weight;//这里的权重只有1，所以省略求w了 
			} 
			p=p->next;
		}
	}
}
int main(){
	int num;
	string line;
	cin>>num;
	getline(cin,line); 
	vector<vector<int> >arr;
	for(int i=0;i<num;i++){
		vector<int> temp;
		getline(cin,line);
		stringstream ss(line);
		int x;
		while(ss>>x){
			temp.push_back(x);
		}
		arr.push_back(temp);
	}
	int v;
	cin>>v;
	adjgraph g;
	g.createlist(arr,num);
	diji(g,v);
	int max_dist=0;vector<int> u;
	for(int i=0;i<g.n;i++){
		if(max_dist<dist[i]&&dist[i]!=inf){
			max_dist=dist[i];
		}
	}
	if(max_dist==0) {
		cout<<-1;
		return 0;
	} 
	for(int i=0;i<g.n;i++){
		if(dist[i]==max_dist){
			u.push_back(i);
		}
	}
	for(int i=0;i<(int)u.size();i++){
		cout<<u[i]<<" ";
	}
} 
