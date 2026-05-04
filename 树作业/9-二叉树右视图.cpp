#include<iostream>
#include<cctype>
#include<stack>
#include<queue>
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
void print(treenode*r){
	if(!r) {
		cout<<"[]\n" ;
		return;
	}
	vector<int>out_data;
	queue<treenode*> q;
	q.push(r);
	treenode*p=NULL;
	while(!q.empty()){
		int level_counts=(int)q.size();
		for(int i=0;i<level_counts;i++){
			p=q.front();
			q.pop();
			if(p->left) q.push(p->left);
			if(p->right) q.push(p->right);
		}//循环结束的时候p指向该层最后一个结点，也就是最右边的结点 
		out_data.push_back(p->data);
	}
	cout<<"[";
	for(int i=0;i<(int)out_data.size();i++){
		cout<<out_data[i];
		if((int)out_data.size()-i!=1) cout<<",";
	}
	cout<<"]\n";
} 
int main(){
	freopen("in.txt","r",stdin);
	string line;
	while(getline(cin,line)){
		treenode*root=buildtree(line);
		print(root);
	}//每一次循环体都是一行测试数据  
} 
