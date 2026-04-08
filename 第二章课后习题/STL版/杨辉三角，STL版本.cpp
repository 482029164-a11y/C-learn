//杨辉三角，STL版本
#include<iostream>
#include<queue> 
using namespace std;
void yanghui(queue<int>&q,int n){
	//利用滑动窗口解决问题
	int left;
	int right;
	//初始化第一行元素 
	q.push(1);
	q.push(0); 
	for(int i=1;i<=n;i++){
		for(int j=0;j<n-i;j++){
			cout<<" ";
		}
		left=0;
		right=q.front();
		while(right!=0){
			cout<<right<<" ";//谨记我们需要打印的是右边的元素
			q.pop();
			q.push(left+right);
			left=right;
			right=q.front();
		}
		cout<<endl;
		q.pop();
		q.push(left+right);
		q.push(0);
	} 
} 
int main(){
	queue<int>q;
	int n;
	cin>>n;
	yanghui(q,n);
	return 0;
}
