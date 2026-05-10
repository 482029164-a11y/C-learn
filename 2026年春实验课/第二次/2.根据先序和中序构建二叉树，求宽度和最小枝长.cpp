#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include<queue>
#include<cctype>
#include<algorithm>
using namespace std; 
struct treenode{
	char data;
	treenode*left;
	treenode*right;
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
treenode* buildtree(string&pre,int i,string&mid,int j,int n){
	if (n <= 0) return NULL;
	char val = pre[i];
	treenode* r=new treenode(val);
	int p=j;
	while(pre[i]!=mid[p]){
		p++;
	}
	int k=p-j;
	r->left=buildtree(pre,i+1,mid,j,k);
	r->right=buildtree(pre,i+k+1,mid,p+1,n-k-1);
	return r;
}
int max_wideth(treenode*r){
	if(!r) return 0;//空节点返回0
	int max=1;//根结点的宽度为1
	queue<treenode*> q;//层次遍历
	q.push(r);
	while(!q.empty()){
		int size_now=(int)q.size();//记录当前层的大小
		if(max<=size_now){
			max=size_now;
		}
		for(int i=0;i<size_now;i++){
			treenode*p=q.front();q.pop();
			if (p->left) q.push(p->left);//加判断条件是为了防止把NULL也放进去 
			if (p->right) q.push(p->right);	
		}
	}
	return max;
}
int min_zhi(treenode*r){
	if(!r) return 0;
	// 【条件 1】：我是真正的叶子，左右都没路了，我自身算 1 步长度
    if (!r->left && !r->right) return 0;
    
    // 【条件 2】：我左边没路了，我不能把左边的“断崖(0)”拿去参加 min 运算
    // 只能硬着头皮往右边走
    if (!r->left) return min_zhi(r->right)+1;
    
    // 【条件 3】：我右边没路了，只能硬着头皮往左边走
    if (!r->right) return min_zhi(r->left)+1;
    
    // 【条件 4】：两边都有路，那才去比较哪边更短
    return min(min_zhi(r->left), min_zhi(r->right))+1;
}//假如只有最后一个return 那么就会出现左边没路，但是右边右路，结果算出来最后的结果是1，很明显是错的 
int main(){
	string line1,line2;
	getline(cin,line1);
	getline(cin,line2);
	stringstream ss1(line1);
	stringstream ss2(line2);
	int n=line1.length();
	treenode* root=buildtree(line1,0,line2,0,n);
	int max_w=max_wideth(root);
	int min_z=min_zhi(root);
	cout<<max_w<<" "<<min_z;
}
