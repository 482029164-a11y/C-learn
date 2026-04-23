//二维数组原地转置，这里默认方阵 ,不是方阵则输出false 
#include <iostream>
#include <vector>
#include<string>
#include<sstream>
using namespace std;
void swap(int&a,int&b){
	int temp=a;
	a=b;
	b=temp;
}
bool zhuan(vector<vector<int> >&v,int m,int n){
	if(m!=n){
		return false;
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<i;j++){
			swap(v[i][j],v[j][i]);
		}
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
	zhuan(v,m,n);
		for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
} 
