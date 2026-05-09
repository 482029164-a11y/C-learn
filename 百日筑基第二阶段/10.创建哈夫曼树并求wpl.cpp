#include<iostream>
#include<queue>
#include<sstream>
#include<string>
using namespace std;
struct htnode{
	int weight;
	int parent;
	int left;
	int right;
	bool flag;//为双亲结点的左节点还是右节点（真为左节点）
	htnode(){
		parent=-1;
		left=right=-1;
	} 
	htnode(int w){
		weight=w;
		flag=true;//默认先左节点 
		parent=-1;
		left=right=-1;
	}
};
struct heapnode{
	int w;//结点权值 
	int i;//对应哈夫曼编码的结点编号 
	heapnode(int w1,int i1){
		w=w1;
		i=i1;
	} 
	bool operator<(const heapnode&s) const{
		return w>s.w;
	}
};
void creat(int W[],int n,htnode h[]){
	priority_queue<heapnode> qu;
	for(int i=0;i<n;i++){
		h[i]=htnode(W[i]);
		qu.push(heapnode(W[i],i));
	}
	for(int i=n;i<2*n-1;i++){
		heapnode p1=qu.top();qu.pop();
		heapnode p2=qu.top();qu.pop();
		h[i]=htnode();
		h[i].weight=h[p1.i].weight+h[p2.i].weight;
		h[p1.i].parent=i;
		h[p1.i].flag=true;
		h[i].left=p1.i;
		h[p2.i].parent=i;
		h[i].right=p2.i;
		h[p2.i].flag=false;
		qu.push(heapnode(h[i].weight,i));
	}
}
int wpl(htnode h[],int n){//这里的n是代表哈夫曼树有几个叶结点，因为如果把新增结点也算进去就会多数 
	int wpl=0;
	for(int i=0;i<n;i++){
		int path=0;
		htnode p=h[i];
		htnode t=h[i];
		while(p.parent!=-1){
			path++;
			p=h[p.parent];
		} 
		wpl+=path*t.weight;
	}
	return wpl;
}
int main(){
	int n;//用来输入叶节点的个数
	string line,trash;
	cin>>n;
	getline(cin,trash);
	getline(cin,line);
	int x;
htnode* h = new htnode[2 * n - 1];
int* W = new int[n];
	stringstream ss(line);
	int i=0;
	while(ss>>x&& i < n){
		W[i]=x;
		i++;
	}
	creat(W,n,h);
	int wpl1=wpl(h,n);
}
