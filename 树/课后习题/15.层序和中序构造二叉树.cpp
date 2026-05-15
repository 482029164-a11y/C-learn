#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
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
treenode* buildtree(string &level, string &in) {
	if(level.empty()||in.empty()) return NULL;
	char root_value=level[0];
	treenode* r=new treenode(root_value);
	int r_po=in.find(root_value);
	string left_in=in.substr(0,r_po);
	string right_in=in.substr(r_po+1);//从下标开始，一直到结束 
	string left_level="";
	string right_level="";
	for(int i=1;i<level.length();i++){
		if(left_in.find(level[i])!=string::npos){
			left_level+=level[i];
		}
		else{
			right_level+=level[i];
		}
	}
	r->left=buildtree(left_level,left_in);
	r->right=buildtree(right_level,right_in);
    return r;
}//层序和中序构造二叉树 
int main() {

}
