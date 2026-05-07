#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
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
treenode*mirro(treenode*r){
	if(!r)return NULL;
	treenode*t=r->left;
	r->left=r->right;
	r->right=t;
	mirro(r->left);
	mirro(r->right);
	return r;
}
void print(treenode*r){
	if(!r) return;
	cout<<r->data<<" ";
	if(r->left) print(r->left);
	if(r->right) print(r->right);
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
	treenode*r1=mirro(root);
	print(r1);
} 
