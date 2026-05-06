#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
struct htnode{
	char data;
	double weight;
	int parent;
	int left;
	int right;
	bool flag;//标识是双亲的左节点还是右节点，true则是左孩子
	htnode(){
		parent=-1;
		left=-1;
		right=-1;
	} 
	htnode(char d,double w){
		data=d;
		weight=w;
		parent=left=right=-1;
		flag=true;//默认是左节点 
	}
};
void createhcode(vector<string>&hcd,htnode*h,int n){
	for(int i=0;i<n;i++){
		string code="";
		int j=i;
		while(h[j].parent!=-1){
			if(h[j].flag){
				code+="0";//左边则编码1 
			}
			else{
				code+="1";
			} 
			j=h[j].parent;
		}
		reverse(code.begin(),code.end());
		hcd[i]=code;
	}
}
struct heapnode{
	int i;//数组下标
	double w;//权值
	heapnode(double w1,int i1):i(i1),w(w1){};
	bool operator<(const heapnode& s)const{
		return w>s.w; 
	} //这里重载是重点，这样才能让小的权值先进队列 
}; //构造优先队列元素类型 
void creatht(htnode*h,char*d,double*w,int n){
	priority_queue<heapnode> qu;//建立优先队列
	for(int i=0;i<n;i++){
		h[i]=htnode(d[i],w[i]);
		qu.push(heapnode(w[i],i));
	}
	for(int i=n;i<2*n-1;i++){
		heapnode p1=qu.top();qu.pop();
		heapnode p2=qu.top();qu.pop();
		h[i]=htnode();
		h[i].weight=h[p1.i].weight+h[p2.i].weight;
		h[p1.i].parent=i;
		h[p2.i].parent=i;
		h[p1.i].flag=true;
		h[p2.i].flag=false;
		h[i].left=p1.i;
		h[i].right=p2.i;
		qu.push(heapnode(h[i].weight,i));//将新建立的结点进队列 
	}
}
int main(){
	char d[]={'a','b','c','d'};
	int n=4;
	double w[]={1,3,5,7};
	htnode h[2*n-1]={};
	creatht(h,d,w,n);
	// 简单验证：输出根节点（最后建立的那个节点）的权值
    // 正确结果应该是 1+3+5+7 = 16
    cout << "Root weight: " << h[2 * n - 2].weight << endl;
    vector<string>hcd(n,"");
    createhcode(hcd,h,n);
    for(int i=0;i<n;i++){
    	cout<<h[i].data<<":"<<hcd[i]<<endl;
	}
} 
