#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<stack>
#include<cstdlib>
#include<cctype>
using namespace std;
struct TreeNode{   
	int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
class Solution {
	public:
		int max_diameter;
        int diameterOfBinaryTree(TreeNode *root) {
        max_diameter = 0;     // 每次计算前初始化计分板
        get_max_level(root);  // 引擎启动：让递归去跑，我们只管看计分板最后的结果
        return max_diameter;
    }

    // 这个函数不仅要返回深度，还要在暗中更新最大直径
    int get_max_level(TreeNode *root) {
        if (!root) return 0;
        
        // 探底：获取左右子树的真实深度
        int left_depth = get_max_level(root->left);
        int right_depth = get_max_level(root->right);
        
        // 【核心动作】：算一下如果以当前节点为拱桥，跨度（直径）是多少
        int current_diameter = left_depth + right_depth;
        
        // 如果这个跨度打破了历史记录，就更新计分板
        if (current_diameter > max_diameter) {
            max_diameter = current_diameter;
        }
        
        if (left_depth >= right_depth) {
            return left_depth + 1;
        } else {
            return right_depth + 1;
        }
    }
};
TreeNode* buildtree(string data){
	TreeNode*root=NULL;//树的根结点 
	TreeNode*p=NULL;//临时结点 
	int k=0;//父节点的拨片
	stack<TreeNode*> s;
	for(int i=0;i<(int)data.size();i++){
		char ch=data[i];
		if(ch=='('){
			s.push(p);
			k=1;
		}
		if(ch==','){
			k=2;
		}
		if(ch==')'){
			s.pop();
		}
		if(isdigit(ch)){
			int num=0;
			while(i<(int)data.size()&&isdigit(data[i])){
				num=10*num+(ch-'0');
				i++;
			}
			i--;
			p=new TreeNode(num);
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
int main(){
	freopen("in.txt","r",stdin);
	string line;
	while(getline(cin,line)){
		TreeNode*root=buildtree(line);
		Solution s;
		int max=s.diameterOfBinaryTree(root);
		cout<<max<<endl;
	}//每一次循环体代表一个测试样例 
}
