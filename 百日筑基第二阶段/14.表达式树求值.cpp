#include<iostream>
#include<string>
#include<vector>
#include<sstream> 
using namespace std;

struct treenode {
	int index;
	int data;
	char opr;
	int typ;
	int l_id; //在节点身上先记下孩子编号，不急着连线
	int r_id;
	treenode* left;
	treenode* right;
	treenode() {
		left = NULL;
		right = NULL;
		l_id = -1;
		r_id = -1;
	}
};

// 刚性扩大容量
vector<treenode*> tree(10005, NULL); 
bool has_parent[10005] = {false}; // 用于铁血寻找根节点

int cal_tree(treenode* r) {
	if (!r) return 0;
	if (!r->left && !r->right) return r->data;
	
	int result_l = cal_tree(r->left);
	int result_r = cal_tree(r->right);
	int result_curr = 0;
	
	if (r->opr == '+') result_curr = result_l + result_r;
	else if (r->opr == '-') result_curr = result_l - result_r;
	else if (r->opr == '*') result_curr = result_l * result_r;
	else if (r->opr == '/') {
		if (result_r != 0) result_curr = result_l / result_r;
	}
	return result_curr; 
} 

int main() {
	int n;
	if (!(cin >> n)) return 0;
	
	string line, trash;
	getline(cin, trash); 
	
	vector<int> input_ids; // 记录所有出生了的节点编号
	
	// 【第一步】：只读数据，让节点在确定的 tree[in] 位置诞生
	for (int i = 0; i < n; i++) {
		getline(cin, line);
		if (line.empty()) { i--; continue; }
		
		stringstream ss(line);
		int in, t, l, r;
		ss >> in >> t;
		
		treenode* p = new treenode();
		p->index = in;
		p->typ = t;
		
		if (t == 0) { 
			int v;
			ss >> v >> l >> r; // 严格用 ss 读取
			p->data = v;
			p->l_id = l;
			p->r_id = r;
		} 
		else if (t == 1) { 
			char v;
			ss >> v >> l >> r; // 严格用 ss 读取
			p->opr = v;
			p->l_id = l;
			p->r_id = r;
		}
		
		tree[in] = p; // 修正：严格让 编号 等于 数组下标
		input_ids.push_back(in);//看哪些编号已经存储了 
	} 
	
	// 【第二步】：所有节点在内存里已经全部坐好，此时安全地统一织网（连指针）
	for (int id : input_ids) {
		treenode* p = tree[id];
		if (p->l_id != -1) {
			p->left = tree[p->l_id];
			has_parent[p->l_id] = true; // 记录谁当了孩子
		}
		if (p->r_id != -1) {
			p->right = tree[p->r_id];
			has_parent[p->r_id] = true; // 记录谁当了孩子
		}
	}
	
	//寻找根结点 
	treenode* root = NULL;
	for (int id : input_ids) {
		if (!has_parent[id]) {
			root = tree[id];
			break;
		}
	}
	//若根节点不为空就输出 
	if (root) {
		int result = cal_tree(root);
		cout << result;
	}
	return 0;
}
