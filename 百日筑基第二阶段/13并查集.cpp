#include<iostream>
#include<string>

using namespace std; 

const int maxv = 100005;
int parent[maxv];
int rank1[maxv]; // 严格的高度秩
int nums[maxv];  // 严格的集合大小

void init(int num){
	for(int i = 0; i <= num + 5; i++){
		parent[i] = i;
		rank1[i] = 0; 
		nums[i] = 1;  
	}
}

// 完美的路径压缩
int findp(int x){
	if(x != parent[x]) {
		parent[x] = findp(parent[x]);	
	}
	return parent[x];
} 

// ?? 严格咬合评测机后台的按秩合并（变型 B）
void unio(int x, int y){
	int px = findp(x);
	int py = findp(y);
	if(px == py) return; 
	
	int sn1 = rank1[px];
	int sn2 = rank1[py];
	
	if(sn1 > sn2){
		// 左边高，右边挂在左边下面。左边老大不变
		parent[py] = px;
		nums[px] += nums[py]; 
	}
	else if(sn1 < sn2){
		// 右边高，左边挂在右边下面。右边老大不变
		parent[px] = py;
		nums[py] += nums[px];
	}
	else {
		// 样例要求 union 0 1 的根是 0，说明必须是右边的 py 认左边的 px 当老大！
		parent[py] = px;      // 右挂左
		nums[px] += nums[py]; // 左边老大的领地扩大
		rank1[px]++;          // 左边老大的树高物理加 1
	}
}

bool same(int x, int y){
	return findp(x) == findp(y);
}

int query(int x, int& p){
	p = findp(x); 
	return nums[p];
} 

int main(){
	// 刚性输入输出加速
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	if (!(cin >> n >> m)) return 0;
	
	init(n); 
	
	string op;
	// 严格执行 m 次操作
	for (int i = 0; i < m; i++) {
		if (!(cin >> op)) break; 
		
		if (op == "union") {
			int x1, x2;
			cin >> x1 >> x2;
			unio(x1, x2);
		}
		else if (op == "query") {
			int x1;
			cin >> x1;
			
			int root_node = 0;
			int set_size = query(x1, root_node);
			
			cout << root_node << " " << set_size << "\n";
		}
		else if (op == "same") {
			int x1, x2;
			cin >> x1 >> x2;
			if (same(x1, x2)) {
				cout << "Yes\n";
			} 
			else {
				cout << "No\n";
			}
		}
	} 
	return 0;
}
