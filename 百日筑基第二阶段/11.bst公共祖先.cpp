#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
struct treenode{
	int data;
	treenode*left;
	treenode*right;
	treenode(){
		left=NULL;
		right=NULL;
	}
	treenode(int d){
		data=d;
		left=NULL;
		right=NULL;
	}
};
treenode* buildtree(vector<int>&v,int& index){
	if(index>=(int)v.size()) return NULL;
	int curr=v[index++];
	if(curr==-1) return NULL;
	treenode*r=new treenode(curr);
	r->left=buildtree(v,index);
	r->right=buildtree(v,index);
	return r;
}
bool search_bst(treenode* r, int target) {
    if (!r) return false;
    if (r->data == target) return true;
    if (r->data > target) return search_bst(r->left, target); // 太大了，往左找
    return search_bst(r->right, target);                      // 太小了，往右找
}
treenode* find_split_point(treenode* r, int p, int q) {
    if (!r) return NULL;
    
    if (r->data > p && r->data > q) {
        return find_split_point(r->left, p, q); 
    }
    if (r->data < p && r->data < q) {
        return find_split_point(r->right, p, q);
    }
    return r;//假如p,q在r两边，假如p,q能被找到，那么这个绝对就是lca了 
} //bst 找lca
int lca(treenode* r, int p, int q) {
    // 找到理论上的分叉点
    treenode* split_node = find_split_point(r, p, q);
    // 如果连分叉点都没找到（比如树是空的）
    if (!split_node) return -1; 
   //去看看p,q在不在树里面 
    if (search_bst(split_node, p) && search_bst(split_node, q)) {
        return split_node->data; 
    }
    
    //没有那个结点的话就输出-1 
    return -1; 
} 
int main() {
    int p, q;
    cin >> p >> q;
    string line1, trash;
    getline(cin, trash); // 吃掉第一行的残留回车
    
    while (getline(cin, line1)) {
        vector<int> data1;
        stringstream ss1(line1);
        int x;
        while (ss1 >> x) data1.push_back(x);
        if (data1.empty()) {
            continue; 
        }
        int index1 = 0;
        treenode* root = buildtree(data1, index1);
        int lca1 = lca(root, p, q);
        cout << lca1 << endl;
    }
    return 0;
}
