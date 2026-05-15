#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
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
void print_level(treenode*r,int level){
	if(!r) return;
	cout << "节点 " << r->data << " 的层数 : " << level << endl;
	print_level(r->left,level+1);
	print_level(r->right,level+1);
} 

int main() {
    // 构建测试树：
    //         A            (第 1 层)
    //        / \
    //       B   C          (第 2 层)
    //      /   / \
    //     D   E   F        (第 3 层)
    string tree_str = "A(B(D),C(E,F))";
    
    cout << "正在构建测试二叉树..." << endl;
    treenode* root = buildtree(tree_str);
    cout << "--------------------------------" << endl;
    
    cout << "=== 先序遍历输出所有节点层数 ===" << endl;
    // 根节点是第 1 层，所以初始 level 传入 1
    print_level(root, 1);
    
    cout << "--------------------------------" << endl;

    return 0;
}
