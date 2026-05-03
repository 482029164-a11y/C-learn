#include<iostream>
#include<vector>
using namespace std;
int main(){
	freopen("in.txt","r",stdin);
	int n,u,v;
	while(cin>>n){
		vector<int>parent(n+1,0);
		vector<bool>zuxian(n+1,false);
		for(int i=0;i<n-1;i++){
			cin>>u>>v;//剩下n-1行，每一行输出一对数字，前一个是父节点
			parent[v]=u; 
		}
		int target1,target2,curren;
		cin>>target1>>target2;//最后输入目标值
		curren=target1;
		while(curren!=0){
			zuxian[curren]=true;//只要祖先中提到了curren走过的路径，那么就把值置为true 
			curren=parent[curren];//继续往前走 
		} 
		curren=target2;
		int lca=-1;
		while(curren!=0){
			if(zuxian[curren]==true){
				lca=curren;
				break;//此时的lca就是最近的公共祖先 
			}
			else{
				curren=parent[curren];//继续往前走
			} 
		} 
		cout<<lca<<endl;
	}
} 
