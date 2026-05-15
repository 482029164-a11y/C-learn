#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
#include <cstring> // 引入 memset 必须的头文件
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
const int MAX_LEVEL = 1000; // 假设树最高 1000 层
int cnt[MAX_LEVEL];         // 物理记分牌：记录每层的节点数
int max_width = 0;          // 历史最高记录
void wid(treenode*r,int level){
	if(!r) return ;
	cnt[level]++;
	max_width=max(max_width,cnt[level]);//数组中只有这个元素变了，因此只需要和变过的比较就可以 
	wid(r->left,level+1);
	wid(r->right,level+1);
} 
int main() {
    // 构建一棵物理形态如下的测试树：
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
    
    // 【工程保命动作】：每次使用前，务必清空全局记分牌和最高记录！
    memset(cnt, 0, sizeof(cnt));
    max_width = 0;
    
    // 启动前序遍历引擎，根节点从第 1 层开始往下走
    wid(root, 1);
    
    // 验证输出
    cout << "=== 前序遍历统计完毕 ===" << endl;
    cout << "整棵树的最大宽度是 : " << max_width << endl;
    
    // 额外福利：打印出记分牌上的详细战况，证明前序遍历没有骗人
    cout << "\n[详细记分牌数据]:" << endl;
    for (int i = 1; i < MAX_LEVEL; i++) {
        if (cnt[i] > 0) {
            cout << "第 " << i << " 层共有 " << cnt[i] << " 个节点" << endl;
        } else {
            // 遇到 0 说明下面的层数已经没有节点了，停止打印
            break; 
        }
    }
    
    cout << "--------------------------------" << endl;

    return 0;
}
