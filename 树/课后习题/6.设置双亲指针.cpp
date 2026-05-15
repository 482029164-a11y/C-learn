#include<iostream>
#include<stack>
#include<string>
using namespace std;
struct treenode{
	char data;
	treenode* left;
	treenode* right;
	treenode*parent; 
	treenode(){
		left=NULL;
		right=NULL;
		parent=NULL;
	}
	treenode(char d){
		data=d;
		left=NULL;
		right=NULL;
		parent=NULL;
	}
};
treenode* buildtree(string & d){
	stack<treenode*> s;
	if((int)d.size()<=0) return NULL;
	int len=d.length();
	treenode* p=NULL;
	treenode* root=NULL; 
	int k=0;//父节点拨片，1的时候去连接左节点，2的时候去连接右节点 
	char e;//用来存储当前字符
	for(int i=0;i<len;i++){
		e=d[i];
		if(e=='('){
			s.push(p);
			k=1;
		}
		else if(e==','){
			k=2;
		}
		else if(e==')'){
			s.pop(); 
		}
		else{
			p=new treenode(e);
			if(root==NULL) root=p;
			else{
				if(k==1){
					s.top()->left=p;
				}
				else if(k==2){
					s.top()->right=p;
				}
			}
		} 
	} 
	return root;
} //这里的结点里面的值都是字符，因此无需转换
void paren(treenode*r){
	if(!r) return;
	if(r->left) r->left->parent=r;
	if(r->right) r->right->parent=r;
	paren(r->left);
	paren(r->right);
}
int main(){
	
} 
