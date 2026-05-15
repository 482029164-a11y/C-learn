#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f; // 引入无穷大：代表“此路不通/没找到”
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
int cenci(treenode*r,char x,int level){
	//level用来记录当前层次
	if(!r) return INF;
	if(r->data==x) return level;
	int left_min = cenci(r->left, x, level + 1);
    int right_min = cenci(r->right, x, level + 1);
    // 4. 汇总比较：如果两边都没找到，就是 min(INF, INF) = INF
    // 如果一边找到(3)，一边没找到(INF)，就是 min(3, INF) = 3，完美保留正确答案！
    return min(left_min, right_min);
} 

int main() {
    // 构建一棵极具针对性的测试树：
    //         A            (第 1 层)
    //        / \
    //       B   C          (第 2 层)
    //      /   / \
    //     D   X   E        (第 3 层)  <-- 这里有一个 X
    //    /     
    //   X                  (第 4 层)  <-- 这里还有一个 X
    
    // 对应的广义表字符串：
    string tree_str = "A(B(D(X)),C(X,E))";
    
    cout << "正在构建测试二叉树..." << endl;
    treenode* root = buildtree(tree_str);
    cout << "--------------------------------" << endl;
    
    // ================= 测试 1：找存在的节点 =================
    char target1 = 'X';
    cout << "[测试 1] 正在寻找节点 '" << target1 << "' ..." << endl;
    // 根节点是第 1 层，所以初始 level 传入 1
    int ans1 = cenci(root, target1, 1); 
    
    if (ans1 == INF) {
        cout << " -> 树中根本不存在该节点！" << endl;
    } else {
        cout << " -> 找到了！该节点出现的最小层次是: " << ans1 << endl;
        // 预期输出：3 （虽然第 4 层也有 X，但 3 更小）
    }
    cout << endl;
    
    // ================= 测试 2：找不存在的节点 =================
    char target2 = 'Z';
    cout << "[测试 2] 正在寻找节点 '" << target2 << "' ..." << endl;
    int ans2 = cenci(root, target2, 1);
    
    if (ans2 == INF) {
        cout << " -> 树中根本不存在该节点！" << endl;
        // 预期输出：这行话被打印出来
    } else {
        cout << " -> 找到了！该节点出现的最小层次是: " << ans2 << endl;
    }
    
    cout << "--------------------------------" << endl;
    cout << "测试完毕！深搜引擎逻辑完美闭环！" << endl;

    return 0;
}
