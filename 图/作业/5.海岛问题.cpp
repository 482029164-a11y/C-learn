#include<iostream>
#include<vector> 
#include<string>
#include<sstream>
using namespace std;
vector<vector<int> >g;
int r=0;//矩阵的行数 
int c=0;//矩阵的列数 
int dfs(int x,int y){
	if(x>=r||x<0||y>=c||y<0||g[x][y]==0){
		return 0;
	}
	g[x][y]=0;
	int area=1;
	area+=dfs(x-1,y);
	area+=dfs(x,y-1);
	area+=dfs(x+1,y);
	area+=dfs(x,y+1); 
	return area;
} 
void solve() {
    if (g.empty()) return;
    r = g.size();
    c = g[0].size();
    int max_area = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(g[i][j] == 1) max_area = max(max_area, dfs(i, j));
        }
    }
    cout << max_area << "\n";
}
int main(){
	string line;
	freopen("in.txt", "r", stdin); // 提交时注释掉
	while(getline(cin, line)){
		if(line.empty()){
            solve();   // 【结算当前图】：撞见空行，立刻结算上一张图并打印
			g.clear(); // 清洗，迎接下一张图
			continue;
		}
		vector<int> temp; 
		stringstream ss(line);
		int t;
		while(ss >> t) temp.push_back(t);
		g.push_back(temp);
	}
    solve(); 
    return 0;
}
