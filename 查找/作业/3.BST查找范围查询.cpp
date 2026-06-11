#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
//流式传值法，把流传给建树函数 
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
treenode* buildtree(stringstream& ss) {
    int val;
    if (!(ss >> val) || val == -1) return NULL;
    treenode* root = new treenode(val);
    root->left = buildtree(ss);
    root->right = buildtree(ss);
    return root;
}
void print(treenode*r,int low,int high){
	if(!r) return;
	print(r->left,low,high);
	if(r->data>=low&&r->data<=high){
		cout<<r->data<<" ";
	}
	print(r->right,low,high);
}
int main(){
	string line1,line2;//第一行和第二行的输入
	getline(cin,line1);
	getline(cin,line2);
	int m,n;//m为下界，n为上界
	stringstream ss1(line1);
	ss1>>m>>n;
	stringstream ss2(line2);//先序遍历BST 
	treenode*root=buildtree(ss2);
	print(root,m,n);
} 
