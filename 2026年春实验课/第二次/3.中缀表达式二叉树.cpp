#include<iostream>
#include<string>
#include<sstream>
#include<stack>
#include <map>      // 引入 map 头文件,主要是要学会map 
#include<queue> 
using namespace std;
struct treenode{
	char data;
	treenode* left;
	treenode* right;
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
string to_str(int num){
	string r;
	stringstream temp_ss; 
	temp_ss << num; 
	r += temp_ss.str();
	return r;
}
treenode* buildtree(string& line){//思路：先把中缀表达式转化为后缀表达式，再利用辅助栈创建树 
	stack<char>oprand;
	string postexp;
	int len=line.length();
	for(int i=0;i<len;i++){
		char temp=line[i];
		if(temp=='('){
			oprand.push(temp);
		}
		else if(temp=='+'||temp=='-'){
			while(!oprand.empty()){
				char e=oprand.top();
				if(e!='('){
					oprand.pop();
					postexp.push_back(e);
				}
				else{
					break;
				}
			}
			oprand.push(temp);
		}
		else if(temp=='*'||temp=='/'){
			while(!oprand.empty()){
				char e=oprand.top();
				if(e=='*'||e=='/'){
					oprand.pop();
					postexp.push_back(e);
				}
				else{
					break;	
				}
			}
			oprand.push(temp);
		}
		else if(temp==')'){
			while(!oprand.empty()){
				char e=oprand.top();
				if(e=='('){
					oprand.pop();
					break;
				}
				else{
					postexp.push_back(e);
					oprand.pop();
				}
			}
		}
		else{
			postexp.push_back(temp);
		}
	}
	while(!oprand.empty()){
		char x=oprand.top();
		oprand.pop();
		postexp+=x;
	}//从for一直到这里都是在进行中缀表达式转换成后缀表达式的过程 
	stack<treenode*> s;
	for(int i=0;i<(int)postexp.length();i++){
		char temp=postexp[i];
		treenode*t=new treenode(temp);
		if(temp=='+'||temp=='*'||temp=='-'||temp=='/'){
			treenode*p1=s.top();s.pop();
			treenode*p2=s.top();s.pop();//先进栈的，左结点
			t->left=p2;
			t->right=p1;
			s.push(t);//把这个运算符也要进栈 
		}
		else{
			s.push(t);//如果是运算数那么就直接进栈 
		}
	}//开始进行结点的创造 
	//循环结束之后根节点还在栈中，出栈返回就创建好树了
	return s.top(); 
}
bool shu(char temp){
	if(temp=='+'||temp=='*'||temp=='-'||temp=='/'){
		return false;
	}
	else{
		return true;
	}
}//判断是不是运算数 
int cal(treenode*r){
	if (!r) return 0; // 防御性判空
	// 物理定律：如果是叶子节点（说明它一定是运算数），直接剥离 ASCII 码返回整型值
	if (!r->left && !r->right) {
        if (r->data >= '0' && r->data <= '9') {
            return r->data - '0'; // 还原为真实的数值
        } 
        // 否则就是英文字母
        else {
            return r->data; // 直接返回它原生的 ASCII 码
        }
    }
    // 既然能走到这里，说明当前节点绝对是运算符。
    // 分别向下属（左右子树）要结果
    int left_val = cal(r->left);
    int right_val = cal(r->right);
    // 汇总下属的结果
    if (r->data == '+') return left_val + right_val;
    if (r->data == '-') return left_val - right_val;
    if (r->data == '*') return left_val * right_val;
    if (r->data == '/') return left_val / right_val;
    return 0; // 兜底
}//利用递归，根据表达式树去计算结果
int print_reverse_cal_reverse(treenode*r){//用来打印层序遍历的倒序 以及输出这个顺序的计算值 
	if(!r) return 0;
	//一边层序遍历一遍入栈，通过栈进行倒序输出
	stack<treenode*> s;//辅助栈 
	queue<treenode*>q; //层序遍历的队列
	q.push(r);//先让根节点进队列 
	while(!q.empty()){
		int curr=(int)q.size();//当前层的节点个数
		for(int i=0;i<curr;i++){
			treenode*p=q.front();q.pop();
			if(p->left) q.push(p->left);
			if(p->right) q.push(p->right);
			s.push(p);
		} 
	}//循环结束之后栈中就是所有节点
	map<treenode*, int> val_map;
	while(!s.empty()){
		treenode*node=s.top();s.pop();
		//输出的时候，顺便利用一下刚刚用完的队列来存放倒序；
		cout<<node->data;
		// 物理分流 1：如果是叶子节点（运算数）
        if (!node->left && !node->right) {
            if (node->data >= '0' && node->data <= '9') {
                // 直接存入 map 字典中
                val_map[node] = node->data - '0'; 
            } else {
                val_map[node] = node->data;       
            }
        }
        // 物理分流 2：如果是运算符
        else {
            // 极其优雅的查表：因为是倒序，孩子绝对已经算完了
            // 直接用孩子的指针当钥匙，去 map 里把值掏出来！
            int left_val = val_map[node->left];
            int right_val = val_map[node->right];

            // 算完当前节点的结果后，也立刻存进 map 字典里，供它的父亲以后查用
            if (node->data == '+') val_map[node] = left_val + right_val;
            else if (node->data == '-') val_map[node] = left_val - right_val;
            else if (node->data == '*') val_map[node] = left_val * right_val;
            else if (node->data == '/') val_map[node] = left_val / right_val;
        }
	}
	cout<<endl;//换行 
	return val_map[r];//根节点的计算值就是结果 
} 
int main(){
	string line;
	cin>>line;
	treenode* root=buildtree(line);
	int result=cal(root);
	cout<<result<<endl;//第一行用来输出表达式的值
	int result1= print_reverse_cal_reverse(root);
	cout<<result1; 
} 
