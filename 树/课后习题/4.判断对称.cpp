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
// 核心物理引擎：专门负责让两个节点“照镜子”
bool mirrorCheck(treenode* leftNode, treenode* rightNode) {
    // 1. 世界尽头：同时为空，完美对称
    if (leftNode == NULL && rightNode == NULL) return true;
    
    // 2. 骨架断裂：一个为空一个不为空，绝对不对称
    if (leftNode == NULL || rightNode == NULL) return false;
    
    // 3. 血肉不合：虽然都有节点，但里面的值不一样，不对称
    if (leftNode->data != rightNode->data) return false;
    
    // 4. 交叉推进：左的左 对比 右的右，左的右 对比 右的左！
    return mirrorCheck(leftNode->left, rightNode->right) && 
           mirrorCheck(leftNode->right, rightNode->left);
}

// 主函数入口：只需把根节点劈开，派发给双指针引擎即可
bool panduan(treenode* r) {
    if (!r) return true; // 空树绝对对称
    
    // 从根节点的左右孩子开始，启动交叉对比
    return mirrorCheck(r->left, r->right); 
}
int main(){
	
} 
