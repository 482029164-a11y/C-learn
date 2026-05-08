#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include<stack>
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
int jiedian(treenode*r){
	if(!r)return 0;
	return jiedian(r->left)+jiedian(r->right)+1;
}
int main() {
    string line1, line2;
    while (getline(cin, line1)){
        vector<int> data1;
        stringstream ss1(line1);
        int x;
        while (ss1 >> x) data1.push_back(x);
        // 物理防线 3：独立的建树游标
        int index1 = 0;
        treenode* root = buildtree(data1, index1);
        int num=jiedian(root);
		cout<<num; 
    }
    return 0;
}
