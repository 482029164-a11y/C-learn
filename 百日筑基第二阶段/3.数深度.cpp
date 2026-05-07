#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include <algorithm> // 引入 max 函数
using namespace std;
struct treenode{
	int data;
	treenode*left;
	treenode*right;
	treenode(){
		left=NULL;
		right=NULL;
	}
	treenode(int d){
		data=d;
		left=NULL;
		right=NULL;
	}
};
treenode* buildtree(vector<int>&v,int& index){
	if(index>=(int)v.size()) return NULL;
	int curr=v[index++];
	if(curr==-1) return NULL;
	treenode*r=new treenode(curr);
	r->left=buildtree(v,index);
	r->right=buildtree(v,index);
	return r;
} 
int maxh(treenode*r){
	if(!r)return 0;
	int left_depth = maxh(r->left);
    int right_depth = maxh(r->right);
	return max(left_depth,right_depth)+1;//加1是根节点 
}
int main(){
	string line;
	getline(cin,line);
	stringstream ss(line);
	vector<int>data;
	int x,i=0;
	while(ss >> x){
        data.push_back(x); 
    }
	treenode* root=buildtree(data,i);
	int max=0;
	max=maxh(root);
	cout<<max;
} 
