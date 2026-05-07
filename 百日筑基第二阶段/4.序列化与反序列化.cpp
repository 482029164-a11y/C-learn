#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
#include<stack>
#include <cstdlib> // 为了使用 atoi 函数把字符串变数字
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
string int_to_string(int n) {
    stringstream ss;
    ss << n;         // 把数字像 cout 一样塞进流里
    return ss.str(); // 把流里的东西打包成真正的 string 吐出来
}

string xulie(treenode* r) {
    // 物理防线：见空必回
    if (!r) return "#,"; 
    
    // 完美替换：用我们手搓的函数代替 to_string
    return int_to_string(r->data) + "," + xulie(r->left) + xulie(r->right);
}
// 外部的干净接口（专门给 main 函数调用的）
string serialize(treenode* root) {
    string res = xulie(root);
    
    // 只要字符串不是空的，一刀切掉最后一个字符（必定是逗号）
    if (!res.empty()) {
       res = res.substr(0, res.length() - 1);
    }
    
    return res;
}
void print(treenode*r){
	if(!r) return; 
	print(r->left);
	cout<<r->data<<" ";
	print(r->right); 
}//中序遍历递归 
//中序非递归
void inorder_iterative(treenode* root) {
    stack<treenode*> s;
    treenode* p = root; // 游标 p 从根节点出发

    // 核心大循环：只要游标还没变成虚无，或者栈里还有人没处理，就不能停
    while (p != NULL || !s.empty()) {
        
        if (p != NULL) {
            // 状态 1：还没撞墙。把当前节点压入栈，然后无脑往左走
            s.push(p);
            p = p->left;
        } else {
            // 状态 2：撞墙了（p == NULL）。左边没路了，准备处理当前层，并转向右边
            
            // 从栈顶抽出刚才最后路过的那个节点
            p = s.top();
            s.pop();
            
            // 【执行输出】因为左边走不通了，现在终于轮到自己了
            cout << p->data << " ";
            
            // 转身去右边看看有没有路（如果有，下一轮循环会把它压栈；如果没有，下一轮会继续弹栈）
            p = p->right;
        }
    }
}
treenode* fanxulie_engine(stringstream& ss) {
    string item;
	if(getline(ss,item,',')){
		if(item=="#") return NULL;
		treenode*r=new treenode(atoi(item.c_str()));
		r->left=fanxulie_engine(ss);
		r->right=fanxulie_engine(ss);
		return r;
	}
	return NULL;
}

// 供主函数调用
treenode* fanxulie(string s) {
    // 就在这里，把死板的 string 灌入 stream 里，让它流动起来！
    stringstream ss(s); 
    return fanxulie_engine(ss);
}
int main(){
	string line;
	getline(cin,line);
	stringstream ss(line);
	vector<int>data;
	int x,i=0;
	while(ss >> x){
        data.push_back(x); 
    }
	treenode* root=buildtree(data,i);
	string s;
	s=serialize(root);
	treenode*r=fanxulie(s);
	cout<<s<<endl;
	print(r);
} 
