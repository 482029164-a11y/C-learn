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

int wid(treenode*r){
	if(!r) return 0;
	treenode*p;
	queue<treenode*> q;
	q.push(r);
	int maxsize=0; 
	while(!q.empty()){
		int curr=(int)q.size();
		maxsize=max(maxsize,curr);
		for(int i=0;i<curr;i++){
			p=q.front();q.pop();
			if(p->left) q.push(p->left);
			if(p->right) q.push(p->right);
		}
	}
	return maxsize;
} 
int main() {
    // 构建测试树 (与前序遍历求宽度时的结构完全一致)：
    //         A            (第 1 层：1个)
    //        / \
    //       B   C          (第 2 层：2个)
    //      /   / \
    //     D   E   F        (第 3 层：3个) <-- 这里是最宽的！
    //    /         \
    //   G           H      (第 4 层：2个)
    string tree_str = "A(B(D(G)),C(E,F(,H)))";
    
    cout << "正在构建测试二叉树..." << endl;
    treenode* root = buildtree(tree_str);
    cout << "--------------------------------" << endl;
    
    // 启动层序遍历引擎
    int max_width = wid(root);
    
    cout << "=== 层序遍历 (BFS) 统计完毕 ===" << endl;
    cout << "整棵树的最大宽度是 : " << max_width << endl;
    // 预期输出必须是 3
    
    cout << "--------------------------------" << endl;

    return 0;
}
