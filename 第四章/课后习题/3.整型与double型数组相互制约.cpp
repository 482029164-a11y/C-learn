#include <iostream>
#include <vector>
#include<string>
#include<sstream>
using namespace std;
// 修正：采用非破坏性的映射逻辑
void change(vector<double> &v1, const vector<int> &v2) {
    int n = v1.size();
    vector<double> temp_v = v1; // 物理备份：保留原始数据的快照
    for (int i = 0; i < n; i++) {
        // 严格遵循置换定义：新位置 i 存放原始数据中 v2[i] 位置的值
        v1[i] = temp_v[v2[i]]; 
    }
}
int main(){
	int n;
	cin>>n;//n为double型的个数
	vector<double>v1;
	vector<int>v2;//v2中的内容不可能导致v1越界访存 
	string line,trash;
	getline(cin,trash);//消除无效字符 
	getline(cin,line);
	stringstream ss(line);
	double x1;int x2;
	while(ss>>x1){
		v1.push_back(x1);
	} 
	getline(cin,line);
	stringstream ss1(line);
	while(ss1>>x2){
		v2.push_back(x2);
	}
	change(v1,v2);
	for(int i=0;i<n;i++){
		cout<<v1[i]<<" ";
	} 
}
