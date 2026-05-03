#include<iostream>
#include<vector>
#include<string>
#include<sstream>
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
treenode* buildtree(vector<int> pre,int i,vector<int> mid,int j,int n){
	//pre代表先序，mid代表中序，i代表先序开始，j代表中序开始，n代表当前子树的个数
	if(n<=0) return NULL;//basecase
	treenode* b=new treenode(pre[i]); 
	int p=j; 
	while(mid[p]!=b->data){
		p++;
	}
	int k=p-j;//k代表左子树的个数
	b->left=buildtree(pre,i+1,mid,j,k);
	b->right=buildtree(pre,i + k + 1,mid,p+1,n-1-k);
	return b;
}
void print(treenode*r,bool&isroot){
	if(!r) return;
	print(r->left,isroot);
	print(r->right,isroot);
	if(!isroot) cout<<" ";//除了第一个不需要空格，其余的都需要空格； 
	cout<<r->data;
	isroot=false;
}//后序输出 
int main(){
	freopen("in.txt","r",stdin);
    int n;
    // cin 自动处理所有换行和空格，直接读 n
    while(cin >> n){
        vector<int> pre(n);
        vector<int> mid(n);
        
        // 连续读入 n 个先序数据
        for(int i = 0; i < n; i++){
            cin >> pre[i];
        }
        
        // 连续读入 n 个中序数据
        for(int i = 0; i < n; i++){
            cin >> mid[i];
        }
        
        treenode* r = buildtree(pre, 0, mid, 0, n);
        
        bool isfirst = true;
        print(r, isfirst);
        cout << "\n"; 
    }
} 
