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
treenode* bulidtree(vector<int>&v,int&index){
	if(index>=(int)v.size()) return NULL;
	int curr=v[index++];//提取的时候顺便让index往后走
	if(curr==-1) return NULL;
	treenode*r=new treenode(curr);
	r->left=bulidtree(v,index);
	r->right=bulidtree(v,index);
	return r;
}//采用先序遍历创建二叉树 
bool is_mirrio(treenode*p,treenode*q){
	if(!p&&!q) return true;
	if(!p||!q) return false;
	if(p->data!=q->data) return false;
	return is_mirrio(p->left,q->right)&&is_mirrio(p->right,q->left);
}
bool panduan(treenode*r){
	if(!r) return true;
	return is_mirrio(r->left,r->right);
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
	treenode* root=bulidtree(data,i);
	if(panduan(root)){
		cout<<"YES";
	}
	else{
		cout<<"NO";
	}
} 
