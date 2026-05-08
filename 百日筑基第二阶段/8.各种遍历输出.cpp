#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include<stack>
#include<queue>
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
void mid_print(treenode*r){//中序输出,非递归法 
	if(!r) return;
	treenode*p=r;
	stack<treenode*> s;
	while(p!=NULL||!s.empty()){
		if(p!=NULL){
			s.push(p);
			p=p->left;
		}
		else{
			p=s.top();
			s.pop();
			cout<<p->data<<" ";
			p=p->right;
		}
	}
	cout<<endl;
}
void post_print(treenode*r){//后序输出，非递归法 
	if(!r) return;
	treenode*p=r;
	stack<treenode*> s;
	treenode* lastVisited = NULL; // 【核心法器】：跟屁虫指针，永远指向刚刚被输出的那个节点
	while(p!=NULL||!s.empty()){
		if(p!=NULL){
			s.push(p);
			p=p->left;
		}
		else{
			p=s.top();
			if(p->right==NULL||p->right==lastVisited){//如果没有右节点，或者刚刚已经访问过右边的节点了 
				cout<<p->data<<" ";
				s.pop();
				lastVisited=p;
				p=NULL;//当前树已经完成，因此需要去逼迫下一次去弹栈，而不是继续往下走 
			}
			else{
				p=p->right;
			}
		}
	}
	cout<<endl;
}
void cenxu_print_by_level(treenode* r) {
    if (!r) return;
    queue<treenode*> q;
    q.push(r);
    
    while (!q.empty()) {
        // 【核心法器】：在这一层开始处理前，立刻拍下一张快照，记录当前队列里有多少人
        // 这些人，绝对完完全全只属于当前这一层！
        int currentLevelSize = q.size(); 
        
        // 开启一个专门处理当前层的微循环
        for (int i = 0; i < currentLevelSize; ++i) {
            treenode* p = q.front();
            q.pop();
            
            cout << p->data << " "; // 打印当前层的人
            
            // 下一层的人虽然被推进了队伍，但不会影响 currentLevelSize 这个固定的快照指标
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        
//        // 当前层全部处理完，强制换行！
//        cout << endl; 
    }
}
int main() {
    string line1, line2;
    while (getline(cin, line1)){
        vector<int> data1;
        stringstream ss1(line1);
        int x;
        while (ss1 >> x) data1.push_back(x);
        // 物理防线 3：独立的建树游标
        int index1 = 0;
        treenode* root = buildtree(data1, index1);
		mid_print(root);
		post_print(root);
		cenxu_print_by_level(root);
    }
    return 0;
}
