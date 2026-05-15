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
int danfenzhi(treenode* r){
	if(!r) return 0;
	if(r->left==NULL&&r->right!=NULL) return danfenzhi(r->right)+1;
	if(r->left!=NULL&&r->right==NULL) return danfenzhi(r->left)+1;
	else{
		return danfenzhi(r->right)+danfenzhi(r->left);
	}
} 
int main(){
	// 构建一棵物理形态如下的测试树：
    //         A
    //        / \
    //      [B] [C]
    //      /   /
    //     D  [E]
    //          \
    //           F
    // (注意：打括号的 B、C、E 都是单分支节点，一共 3 个)
	string tree_str = "A(B(D),C(E(,F)))";
    
    cout << "正在解析广义表构建二叉树: " << tree_str << endl;
    treenode* root = buildtree(tree_str);
    
    int result = danfenzhi(root);
    
    cout << "计算完成！" << endl;
    cout << "该二叉树中的单分支节点个数为: " << result << endl;
    // 预期输出结果应该是 3
    
    return 0;
} 
