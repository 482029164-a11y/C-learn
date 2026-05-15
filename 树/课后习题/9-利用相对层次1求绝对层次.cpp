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
void find_absolute_level(treenode* r, int abs_level) {
    // 防御防线：走到底了，直接回头
    if (!r) return;
    
    // 动作：输出当前节点的信息（在这里已经求得了绝对层次）
    cout << "节点 [" << r->data << "] 的绝对层次是 : " << abs_level << endl;
    
    // 递归推进：利用“相对层次为1”的物理定理
    // 父亲把自己的绝对层次 +1，传递给左右孩子
    find_absolute_level(r->left, abs_level + 1);
    find_absolute_level(r->right, abs_level + 1);
}
// ==============================================

int main() {
    // 构建一棵物理形态如下的测试树：
    //         A            (第 1 层)
    //        / \
    //       B   C          (第 2 层)
    //      /   / \
    //     D   E   F        (第 3 层)
    //          \
    //           G          (第 4 层)
    string tree_str = "A(B(D),C(E(,G),F))";
    
    cout << "正在构建测试二叉树..." << endl;
    treenode* root = buildtree(tree_str);
    cout << "--------------------------------" << endl;
    
    // 启动算法引擎：
    // 根节点 A 就是这棵树的绝对起点，所以它的绝对层次初始值传入 1
    find_absolute_level(root, 1);
    
    cout << "--------------------------------" << endl;
    cout << "计算完成！没有任何队列，完全依靠参数传递实现物理降维！" << endl;

    return 0;
}
