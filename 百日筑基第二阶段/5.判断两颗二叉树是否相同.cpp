#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include<stack>
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
bool panduan(treenode*r1,treenode*r2){
	if(!r1&&!r2) return true;
	if(!r1||!r2) return false;
	if(r1->data!=r2->data) return false;
	return panduan(r1->left,r2->left)&&panduan(r1->right,r2->right);
} 
int main() {
    string line1, line2;
    
    // 物理防线 1：强行成对读取！只要能同时读到两行，才进入处理流程。
    // 这能完美过滤掉末尾孤立的空行干扰。
    while (getline(cin, line1) && getline(cin, line2)) {
        
        // 物理防线 2：绝对隔离的数据流
        // 每次循环都在内部创建全新的 vector，绝不给上一轮残留数据任何污染的机会
        vector<int> data1;
        vector<int> data2;
        
        stringstream ss1(line1);
        stringstream ss2(line2);
        
        int x;
        while (ss1 >> x) data1.push_back(x);
        while (ss2 >> x) data2.push_back(x);
        
        // 物理防线 3：独立的建树游标
        int index1 = 0;
        int index2 = 0;
        
        // 互不干扰地建立两棵树
        treenode* root1 = buildtree(data1, index1);
        treenode* root2 = buildtree(data2, index2);
        
        // 启动你完美的判断引擎
        if (panduan(root1, root2)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
