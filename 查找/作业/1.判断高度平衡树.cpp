#include<iostream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<cmath>
#include<vector> 
using namespace std;
//1.利用下标建立树之前不知道2.一边算高度一遍判断是否不平衡（后序遍历） 
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
treenode* buildtree(vector<string >&v,int i){//当前结点的下标为i,则左孩子为2i+1,右孩子为2i+2 
	if(i>=(int)v.size()||v[i]=="null") return NULL;//如果当前下标超出范围或者当前结点是Null都返回空节点
	treenode*r=new treenode(atoi(v[i].c_str()));
	r->left=buildtree(v,2*i+1);
	r->right=buildtree(v,2*i+2);
	return r; 
}
int check_avl(treenode*r){//实际是在算树高 
	if(!r) return 0;//如果是空树那么树高就是0
	int left_height=check_avl(r->left);
	if (left_height == -1) return -1;//左树已经不平衡直接-1 
	int right_height=check_avl(r->right);
	if (right_height == -1) return -1;//右树已经不平衡也直接-1； 
	if(abs(left_height-right_height)>1) return-1;
	else{
		return max(left_height, right_height) + 1;//现在的结点已经平衡那么就输出当前的高度 
	}
}//求高度和判断是否平衡放在一起做了 
int main(){
	//测试数据的文件名为in.txt，输出文件名为out.txt
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	string line; 
	while(getline(cin,line)){
		string item;
		vector<string>nodes;
		stringstream ss(line);
		while(ss>>item){
			nodes.push_back(item);
		}
		treenode*root=buildtree(nodes,0);//从第0个元素开始建树
		int is_val=check_avl(root);
		if(is_val==-1){
			cout<<"False"<<endl;
		} 
		else{
			cout<<"True"<<endl;
		}
	}//每一行就是一行测试数据 
} 
