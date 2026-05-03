#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<queue>
#include<cstdlib>
using namespace std;
//vector.size() 记得要类型转化 (int)node.size()
struct TreeNode{
	int data;
	TreeNode*left;
	TreeNode*right;
	TreeNode(){
		left=NULL;
		right=NULL;
	}
	TreeNode(int d){
		data=d;
		left=NULL;
		right=NULL;
	}
};
class Solution {
	public:
		vector<int>res;
		vector<TreeNode*>path;
		TreeNode* findtarget(TreeNode* r,int target_v){
			if(!r) return NULL;
			if(r->data==target_v) return r;
			TreeNode*l=findtarget(r->left,target_v);
			if(l) return l;//不空才返回 
			return findtarget(r->right,target_v);
		}//通过结点值寻找对应的结点
		bool findpath(TreeNode* r,TreeNode* target){
			if(!r) return false;
			path.push_back(r);
			if(r==target) return true;
			if(findpath(r->left,target)) return true;
			if(findpath(r->right,target)) return true;
			path.pop_back();
			return false;
		}//查询从根节点到目标结点的路径,这样方便之后找父节点之类的 
		void get_descendants(TreeNode* r,int k){
			if(!r||k<0) return;
			if(k==0){
				res.push_back(r->data);
				return;
			}
			get_descendants(r->left,k-1);
			get_descendants(r->right,k-1);
			
		} //从左到右边输出距离目标节点为指定距离的结点值 
        vector<int> distanceK(TreeNode* root, TreeNode* target, int k){
        	res.clear();
        	path.clear();
        	if(!root||!target||k<0) return res;
			findpath(root,target);//1.找到路径 
			get_descendants(target,k);//2.先找到目标结点的子孙结点
			for(int i=path.size()-2;i>=0;i--){
				TreeNode* curr=path[i];//当前的父节点 
				TreeNode* curr_child=path[i+1];//当前父节点对应的孩子结点
				int curr_distance=path.size()-1-i;//当前父节点距离目标结点的距离
				if(curr_distance==k){
					res.push_back(curr->data);
				}//如果当前父节点已经达到距离就直接入vector 
				else if(curr->left==curr_child){
					get_descendants(curr->right,k-curr_distance-1);
				}
				else if(curr->right==curr_child){
					get_descendants(curr->left,k-curr_distance-1);
				}//否则，两种情况判断
			}
			return res; 
		}
};
TreeNode* buildtree(string data){
	string d1=data.substr(1,data.size()-2);//除去[]
	stringstream ss(d1);//这里面的d1是包含","的，因此还需要getline进行切分
	string item;//用来保存切分后的一个个元素
	vector<string>node;
	while(getline(ss,item,',')){
		node.push_back(item);
	}
	if(node.empty()||node[0]=="#") return NULL;
	queue<TreeNode*> q;//用来层次遍历构造二叉树；
	int i=1;
	TreeNode*root=new TreeNode(atoi(node[0].c_str()));
	TreeNode*p;
	q.push(root); 
	while(!q.empty()&&i<(int)node.size()){//此处的循环条件要注意 
		p=q.front();
		q.pop();
		if(i<(int)node.size()&&node[i]!="#"){
			p->left=new TreeNode(atoi(node[i].c_str()));
			q.push(p->left);
		}
		i++;
		if(i<(int)node.size()&&node[i]!="#"){
			p->right=new TreeNode(atoi(node[i].c_str()));
			q.push(p->right);
		}
		i++;
	}
	 return root;
}
void print(vector<int> res){
	cout<<"[";
	for(int i=0;i<(int)res.size();i++){
		cout<<res[i];
		if(i<(int)res.size()-1){
			cout<<",";
		}
	}
	cout<<"]";
}
int main(){
	freopen("in.txt","r",stdin);
	    string treeStr;
    while (cin >> treeStr) {
        int targetVal, k;
        cin >> targetVal >> k;
        Solution sol;
        TreeNode* root = buildtree(treeStr);
        TreeNode* target = sol.findtarget(root, targetVal);
        vector<int> ans = sol.distanceK(root, target, k);
        print(ans);
    }
    return 0;
} 
