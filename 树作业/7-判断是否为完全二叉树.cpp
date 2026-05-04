#include<iostream>
#include<cctype>
#include<stack>
#include<queue>
using namespace std;
//水平特性”、“按层排序”、“靠左对齐”这类字眼
//立刻抛弃递归（DFS），毫不犹豫地去掏你的队列（Queue）写 BFS。
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
treenode* buildtree(string data){
	stack<treenode*>s;
	treenode* root=NULL;
	treenode *p=NULL;
	int k=0;
	for(int i=0;i<(int)data.size();i++){
		char ch=data[i];
		if(ch=='('){
			s.push(p);
			k=1;
		}
		else if(ch==','){
			k=2;
		}
		else if(ch==')'){
			s.pop();
		}
		else if(isdigit(ch)){
			int num=0;
			while(i<(int)data.size()&&isdigit(data[i])){
				ch=data[i];
				num=num*10+(ch-'0');
				i++;
			}
			i--;
			p=new treenode(num);
			if(root==NULL){
				root=p;
			}
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
}
bool is_com_binary_tree(treenode*r){
	if(!r) return true;//空树也是完全二叉树 
	queue<treenode*>q;
	q.push(r);
	bool engin=true;//判断是否已经出现了NULL，假如出现了后面就应该停止的 
	while(!q.empty()){
		treenode*p=q.front();
		q.pop();
		if(p==NULL){
			engin=false; 
		}
		else{
			if(!engin){
				return false;//假如现在已经不准走了，但是后面却出现了非空结点，就不是完全二叉树 
			}
			q.push(p->left);
			q.push(p->right);	
		}
	} 
	return true;
} 
int main(){
	freopen("in.txt","r",stdin);
	string line;
	while(getline(cin,line)){
		treenode*root=buildtree(line);
		if(is_com_binary_tree(root)){
			cout<<1<<endl;
		}
		else{
			cout<<0<<endl;
		}
	}//每一次循环体都是一行测试数据  
} 
