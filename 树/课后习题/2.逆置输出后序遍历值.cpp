#include<iostream>
#include<stack>
#include<string>
using namespace std;
struct treenode{
	char data;
	treenode* left;
	treenode* right;
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
// 复用你写得非常优秀的建树引擎
treenode* buildtree(string & d) {
	stack<treenode*> s;
	if ((int)d.size() <= 0) return NULL;
	int len = d.length();
	treenode* p = NULL;
	treenode* root = NULL; 
	int k = 0; 
	char e;    
	for (int i = 0; i < len; i++) {
		e = d[i];
		if (e == '(') { s.push(p); k = 1; }
		else if (e == ',') { k = 2; }
		else if (e == ')') { s.pop(); }
		else {
			p = new treenode(e);
			if (root == NULL) root = p;
			else {
				if (k == 1) s.top()->left = p;
				else if (k == 2) s.top()->right = p;
			}
		} 
	} 
	return root;
} 

// 1. 标准的后序遍历 (左-右-根 L-R-N)
void PostOrder(treenode* root) {
    if (!root) return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->data << " ";
}

// 2. 满分解法：基于物理拓扑的“后序遍历逆置” (根-右-左 N-R-L)
void ReversePostOrder(treenode* root) {
    if (!root) return;
    cout << root->data << " ";          // 先打印根
    ReversePostOrder(root->right);      // 往右走
    ReversePostOrder(root->left);       // 往左走
}

int main() {
    // 构建一棵测试二叉树：
    //         A
    //        / \
    //       B   C
    //      / \   \
    //     D   E   F
    string tree_str = "A(B(D,E),C(,F))";
    
    cout << "正在构建测试树: " << tree_str << endl;
    treenode* root = buildtree(tree_str);
    
    cout << "--------------------------------" << endl;
    
    // 预期结果：D E B F C A
    cout << "[标准后序遍历]: ";
    PostOrder(root);
    cout << endl;
    
    // 预期结果：A C F B E D
    cout << "[拓扑逆序输出]: ";
    ReversePostOrder(root);
    cout << endl;
    
    cout << "--------------------------------" << endl;
    cout << "结论：不需要开辟任何数组逆置，只需改变遍历路径即可完美反向！" << endl;

    return 0;
}
