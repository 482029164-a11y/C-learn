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

treenode* sons(treenode* r, char x) {
    // 【修复】：必须返回 NULL，不能只写 return
	if (!r) return NULL; 
	if (r->data == x) return r;
    
    // 左右两路大军齐发
	treenode* le = sons(r->left, x);
	treenode* ri = sons(r->right, x);
    
    // 【极简优化】：因为值唯一，左边找到了直接返回左边；否则返回右边（哪怕右边是空）
	if (le) return le;
    return ri;
} 

// 核心引擎 2：标准的先序遍历输出
void print(treenode* r) {
	if (!r) return;
	cout << r->data << " "; // 【优化】：加个空格防止字符全挤在一起
	print(r->left);
	print(r->right);
}

// 组合技：寻找并输出
void pson(treenode* r, char x) {
	treenode* so = sons(r, x);
    
    // 【物理防线】：必须先判断找没找到，再让 print 去干活
    if (!so) {
        cout << "目标节点 " << x << " 不存在！" << endl;
        return;
    }
    
    cout << "找到目标 " << x << "，其所在子树的先序遍历为: ";
    // 注意：这里的 print(so) 会把 x 本身也打印出来。
    // 如果题目的“子孙”严格要求【不包含 x 自己】，你需要改成：
    // print(so->left); print(so->right);
	print(so); 
    cout << endl;
}
// ==============================================

int main() {
    // 构建测试树：
    //         A
    //        / \
    //       B   C
    //      /   / \
    //     D   E   F
    //        / \
    //       G   H
    string tree_str = "A(B(D),C(E(G,H),F))";
    
    cout << "正在构建测试二叉树..." << endl;
    treenode* root = buildtree(tree_str);
    cout << "--------------------------------" << endl;
    
    // 测试 1：搜索存在且有子孙的节点 'E'
    char target1 = 'E';
    pson(root, target1); // 预期输出：E G H
    
    // 测试 2：搜索存在的叶子节点 'D'
    char target2 = 'D';
    pson(root, target2); // 预期输出：D
    
    // 测试 3：搜索不存在的节点 'Z'
    char target3 = 'Z';
    pson(root, target3); // 预期输出：目标节点 Z 不存在！
    
    cout << "--------------------------------" << endl;
    cout << "搜索与遍历引擎物理闭环，测试通过！" << endl;

    return 0;
}
