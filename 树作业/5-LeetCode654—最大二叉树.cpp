#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<queue>
#include<cstdlib>
using namespace std;
struct TreeNode{
	int data;
	TreeNode*left;
	TreeNode*right;
	TreeNode(){
		left=NULL;
		right=NULL;
	}
	TreeNode(int d){
		data=d;
		left=NULL;
		right=NULL;
	}
};
TreeNode*bulidtree(vector<int>node,int start,int end){
	if(start>=end) return NULL;
	TreeNode*p;
	int j=start;
	int max_index=start;
	int max=node[start];
	while(j<end){
		if(max<=node[j]){
			max_index=j;
			max=node[j];
		}
		j++;
	}
	p=new TreeNode(node[max_index]);
	p->left=bulidtree(node,start,max_index);
	p->right=bulidtree(node,max_index+1,end);
	return p;
} 
void print(TreeNode* r){
	if(!r) return;
	cout<<r->data;
	if(!r->left&&!r->right) return;
	cout<<"(";
	if(r->left){
		print(r->left);	
	}
	if(r->right){
		cout<<",";
		print(r->right);	
	}
	cout<<")";
}
int main(){
	freopen("in.txt","r",stdin);
	string line;
	int x;
	while(getline(cin,line)){
		vector<int> node;
		stringstream ss(line);
		while(ss>>x){
			node.push_back(x);
		}
		TreeNode*root=bulidtree(node,0,(int)node.size());
		print(root);
	}//每一次循环体内部都是一行 
}
