#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
struct treenode{
	char data;
	treenode* left;
	treenode* right;
	treenode*parent; 
	treenode(){
		left=NULL;
		right=NULL;
	}
	treenode(char d){
		data=d;
		left=NULL;
		right=NULL;
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

bool wanquan(treenode*r){
	if(!r) return true;//空树也是完全二叉树 
	queue<treenode*> q;
	q.push(r);
	treenode*p=NULL;
	bool end=false;
	while(!q.empty()){
		p=q.front();q.pop();
		if(p==NULL){
			end=true;
		}
		else{
			if(end) return false;
			q.push(p->left);
			q.push(p->right);
		}
	}
	return true;
} 
// ==============================================

int main() {
    // 测试树 1：完美的完全二叉树
    //        A
    //      /   \
    //     B     C
    //    / \   /
    //   D   E F
    string tree1_str = "A(B(D,E),C(F))";
    treenode* tree1 = buildtree(tree1_str);
    
    // 测试树 2：极其隐蔽的非完全二叉树 (就是尸检里推演的那棵)
    //        A
    //      /   \
    //     B     C
    //    /     /
    //   D     E
    string tree2_str = "A(B(D),C(E))";
    treenode* tree2 = buildtree(tree2_str);
    
    cout << "--------------------------------" << endl;
    cout << "[测试 1] 树1 是否为完全二叉树: " << (wanquan(tree1) ? "是" : "否") << " (预期: 是)" << endl;
    cout << "[测试 2] 树2 是否为完全二叉树: " << (wanquan(tree2) ? "是" : "否") << " (预期: 否)" << endl;
    cout << "--------------------------------" << endl;

    return 0;
}
