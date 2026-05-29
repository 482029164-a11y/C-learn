#include<iostream>
#include<string>
#include<vector>
#include<sstream> 
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
		left=NULL;
		right=NULL;
		data=d;
	}
};
//一定要注意n的错误条件是n<=0,这个等于一定不要忘记啊 
treenode* buildtree(vector<int>&pre,vector<int>&mid,int i,int j,int n){//i为pre开始，j为中序开始，n为子树的个数，初始就是整棵树的个数啦
	if(pre.empty()||mid.empty()) return NULL;
	if(i<0||j<0||n<=0||i>=(int)pre.size()||j>=(int)mid.size()) return NULL;
	treenode*r=new treenode(pre[i]);
	int p=j;
	while(pre[i]!=mid[p]){
		p++;
	} 	
	int k=p-j;//左子树的个数
	r->left=buildtree(pre,mid,i+1,j,k);
	r->right=buildtree(pre,mid,k+i+1,p+1,n-1-k);
	return r; 
}

void post_print(treenode*r,vector<int>&post){
	if(!r) return;
	if(r->left)post_print(r->left,post); 
	if(r->right)post_print(r->right,post); 
	post.push_back(r->data);
}
void print(treenode*r){
	vector<int> post;
	post_print(r,post);
	for(int i=0;i<(int)post.size();i++){
		cout<<post[i]<<" ";
	}
	cout<<"\n";
}
int main(){
	int num;//结点的个数
	cin>>num;
	string line1,line2,trash;
	getline(cin,trash);//先吃掉垃圾字符
	vector<int> pre;vector<int> mid;
	getline(cin,line1);
	stringstream ss(line1);
	int x;
	while(ss>>x){
		pre.push_back(x);
	}
	getline(cin,line2);
	stringstream ss1(line2);
	while(ss1>>x){
		mid.push_back(x);
	}
	treenode*root=buildtree(pre,mid,0,0,num);
	print(root);
} 
