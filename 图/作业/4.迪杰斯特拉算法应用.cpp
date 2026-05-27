#include <iostream>
#include <vector>
#include <algorithm>
#include<string>
#include<sstream>
using namespace std;
const int inf = 0x3f3f3f3f;
struct arcnode{
	int weight;
	int adjvex;
	arcnode*next;
	arcnode(){
		next=NULL;
	}
	arcnode(int a,int w){
		weight=w;
		adjvex=a;
		next=NULL;
	}
};
struct hnode{
	int info;
	arcnode*first;
	hnode(){
		first=NULL;
	}
};
class Solution {
public:
    int networkDelayTime(vector<vector<int> >& times, int n, int k) {
        vector<hnode> list;
        list.resize(n+1);//0号位用来存垃圾 
        for(int i=0;i<(int)times.size();i++){
        	int u=times[i][0];
			int v=times[i][1];
			int w=times[i][2];
			arcnode*p=new arcnode(v,w); 
			p->next=list[u].first;
			list[u].first=p;
		}//建立头节点表
		vector<int>s;s.resize(n+1,0);
		vector<int>dist;dist.resize(n+1,inf);
		arcnode*p=list[k].first;
		dist[k]=0;//自己到自己就是0 
		s[k]=1;
		while(p!=NULL){//初始化点距离 
			int j=p->adjvex;
			int w=p->weight;
			dist[j]=w;
			p=p->next;
		}
		for(int i=0;i<n-1;i++){
			int min_dist=inf;int u=-1;
			for(int j=1;j<=n;j++){
				if(s[j]==0&&min_dist>dist[j]){
					min_dist=dist[j];
					u=j;
				}
			}
			if(u==-1) return -1;
			s[u]=1;
			arcnode* edge = list[u].first;
			while(edge!=NULL){
				int j=edge->adjvex;
				int w=edge->weight;
				if(s[j]==0&&dist[j]>dist[u]+w){
					dist[j]=dist[u]+w;
				}
				edge=edge->next;
			}
		} //求最短距离
		int max_dist=0;
		for(int i=1;i<=n;i++){
			if(max_dist<dist[i]){
				max_dist=dist[i];
			}
		} 
		if(max_dist==inf) return -1;
		else{
			return max_dist;
		}
	}
};
int main() {
	freopen("in.txt","r",stdin); 
	int num,k;
	cin>>num>>k;
	string line;
	getline(cin,line);
	vector<vector<int> >v;
	while(getline(cin,line)){
		vector<int>temp;
		stringstream ss(line);
		int x;
		while(ss>>x){
			temp.push_back(x);
		}
		v.push_back(temp);
	}
	int time=0;
	Solution s;
	time=s.networkDelayTime(v,num,k);
	cout<<time;
}
