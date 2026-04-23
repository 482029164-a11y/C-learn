//主对角线和次对角线元素之和 
#include <iostream>
#include <vector>
#include<string>
#include<sstream>
using namespace std;
bool my_sum(vector<vector<int> >v,int m,int n,int&e){
	e=0;
	if(m!=n){
		return false;
	}
	for(int i=0;i<m;i++){
		e+=v[i][i];
		e+=v[i][m-i-1];
	}
	// 核心修复2：数学去重。如果是奇数维度方阵，最中心的元素会被加两次，必须物理剥离一次
    if (m % 2 != 0) {
        e -= v[m / 2][m / 2];
    }
	return true;
} 
int main(){
	int m,n,x;
	cin>>m>>n;
// 核心修复：预分配物理内存空间
    vector<vector<int> > v(m, vector<int>(n));
	string line,trash;
	getline(cin,trash);//消除无效字符 
	for(int i=0;i<m;i++){
		getline(cin,line);
		stringstream ss(line);
		for(int j=0;j<n;j++){
			ss>>v[i][j];
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
	my_sum(v,m,n,x);
	cout<<x;
} 
