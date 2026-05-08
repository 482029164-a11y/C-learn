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
int LCA(treenode*r,int a,int b){
	if(!r) return 1;
	treenode*p=r,*q=r; 
	vector<treenode*> s1;//去寻找a的路径
	vector<treenode*> s2;//去寻找b的路径
	treenode* lastVisited = NULL; // 核心法器：专治失忆症
	while(p!=NULL||!s1.empty()){
		if(p!=NULL){
			s1.push_back(p);
			if(p->data==a){
				break;
			}
			p=p->left;
		}
		else{
			p=s1[s1.size()-1];
			if(p->right==NULL||p->right==lastVisited){
				s1.pop_back();
				lastVisited=p;
				p=NULL;
			}
			else{
				p=p->right;
			}
		}
	}
	if(!p) return 1;
	lastVisited = NULL;
	while(q!=NULL||!s2.empty()){
		if(q!=NULL){
			s2.push_back(q);
			if(q->data==b){
				break;
			}
			q=q->left;
		}
		else{
			q=s2[s2.size()-1];
			if(q->right==NULL||q->right==lastVisited){
				s2.pop_back();
				lastVisited=q;
				q=NULL;
			}
			else{
				q=q->right;
			}
		}
	}
	if(!q) return 1;
	int lca_val=0;
	for (int i = 0; i < (int)s1.size() && i < (int)s2.size(); ++i) {
	        if (s1[i]->data == s2[i]->data) {
	            lca_val = s1[i]->data; // 只要还一样，就更新 LCA
	        } else {
	           return lca_val;
	        }
	    }
} 
int main() {
	int p,q;
	cin>>p>>q;
    string line1,trash;
    getline(cin,trash);
    while (getline(cin, line1)){
        vector<int> data1;
        stringstream ss1(line1);
        int x;
        while (ss1 >> x) data1.push_back(x);
        // 物理防线 3：独立的建树游标
        int index1 = 0;
        treenode* root = buildtree(data1, index1);
		int lca=LCA(root,p,q);
		cout<<lca;
    }
    return 0;
}
