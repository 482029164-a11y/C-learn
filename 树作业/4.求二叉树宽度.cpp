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
TreeNode* buildtree(string data){
	int start=data.find("[");
	int end=data.find("]");
	string line,item;
	if(start==-1||end==-1) return NULL;
	line=data.substr(start+1,end-start-1);
	vector<string>node;
	stringstream ss(line);
	while(getline(ss,item,',')){
		node.push_back(item);
	}
	queue<TreeNode*>q;
	if(node.empty()||node[0]=="null") return NULL;
	TreeNode*root=new TreeNode(atoi(node[0].c_str()));
	TreeNode*p;
	q.push(root);
	int i=1;
	while(!q.empty()&&i<(int)node.size()){
		p=q.front();
		q.pop();
		if(i<(int)node.size()&&node[i]!="null"){
			p->left=new TreeNode(atoi(node[i].c_str()));
			q.push(p->left);
		}
		i++;
		if(i<(int)node.size()&&node[i]!="null"){
			p->right=new TreeNode(atoi(node[i].c_str()));
			q.push(p->right);
		}
		i++;
	}
	return root;
} 
void count_level(TreeNode*r,int level,vector<int>& counts){
	if(!r) return;
	if(level==(int)counts.size()){
		counts.push_back(1);//第一次到这一层直接加1 
	}
	else{
		counts[level]++;
	}
	count_level(r->left,level+1,counts);
	count_level(r->right,level+1,counts);
}
int main(){
	string line;
	getline(cin,line);
	TreeNode*r=buildtree(line);
	int max=0;
	vector<int>counts;
	count_level(r,0,counts);
	for(int i=0;i<(int)counts.size();i++){
		if(max<=counts[i]){
			max=counts[i];
		}
	}
	cout<<max;
}
